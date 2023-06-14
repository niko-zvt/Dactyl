#include <iostream>
#include "Dactyl.Calc.h"
#include "Dactyl.KData.h"
#include "Dactyl.FEModel.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IsotropicMaterial.h"
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.ShellProperty.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include "Dactyl.EntityBuilder.h"
#include "Dactyl.ModelAliases.h"
#include <Sparse>
#include <Core>
#include <Dense>
#include <vector>
#include <optional>
#include <SparseCholesky>

namespace Dactyl::Model
{
    bool FEModel::LoadMesh(const std::optional<KData> &kData)
    {
        // Load FE mesh
        auto loadResult = false;

        // 1. Check KData and build mesh
        if (kData)
        {
            auto data = kData.value();

            // Create materials
            _materials = EntityBuilder::buildMaterials(data.getMaterials());

            // Create properties
            _properties = EntityBuilder::buildProperties(data.getProperties(), data.getSections());

            // Create nodes
            _nodes = EntityBuilder::buildNodes(data.getNodes());

            // Create elements
            _elements = EntityBuilder::buildElements(data.getElements());

            // Create Constraints
            // Do nothing. Manual build

            // Create Loads
            // Do nothing. Manual build
        }

        // 2. Simple check mesh
        if (_materials.size() > 0 && _properties.size() > 0 &&
            _nodes.size() > 0 && _elements.size() > 0)
            loadResult = true;

        return loadResult;
    }

    bool FEModel::LoadModel()
    {
        return false;
    }

    bool FEModel::SaveModel()
    {
        return false;
    }

    bool FEModel::SetConstraintsByCoords(std::any xCoord, std::any yCoord, ConstraintType type, double tolerance)
    {
        auto result = false;

        bool isXAny = !xCoord.has_value();
        bool isYAny = !yCoord.has_value();

        // Simple check - Any coordinate can only be empty or double
        if (isXAny == false && xCoord.type() != typeid(double) ||
            isYAny == false && yCoord.type() != typeid(double) )
                return result;

        // Set const coords
        auto xCoordAsConst = isXAny == false ? std::any_cast<double>(xCoord) : 0.0 ;
        auto yCoordAsConst = isYAny == false ? std::any_cast<double>(yCoord) : 0.0 ;

        // Create constraints
        for (auto& n : _nodes)
        {
            // For each node - check coords
            auto nodeID = n.second->GetNodeID();
            auto nodeCoords = n.second->GetCoords();
            
            if(isXAny == false && tolerance < std::abs(xCoordAsConst - nodeCoords[0]) ||
               isYAny == false && tolerance < std::abs(yCoordAsConst - nodeCoords[1]) )
            {
                continue;
            }

            // Add
            n.second->AddNodeConstraint(type);
            _nodesWithConstraints.Add(n.second);
        }

        result = true;
        return result;
    }

    bool FEModel::SetDistributedForceByCoords(std::any xCoord, std::any yCoord, double Fx, double Fy, double tolerance)
    {
        auto result = false;

        bool isXAny = !xCoord.has_value();
        bool isYAny = !yCoord.has_value();

        // Simple check - Any coordinate can only be empty or double
        if (isXAny == false && xCoord.type() != typeid(double) ||
            isYAny == false && yCoord.type() != typeid(double) )
                return result;

        // Set const coords
        auto xCoordAsConst = isXAny == false ? std::any_cast<double>(xCoord) : 0.0 ;
        auto yCoordAsConst = isYAny == false ? std::any_cast<double>(yCoord) : 0.0 ;

        // Create forces
        std::vector<int> nodesIDs;
        for (const auto& n : _nodes)
        {
            // For each node - check coords
            auto nodeID = n.second->GetNodeID();
            auto nodeCoords = n.second->GetCoords();
            
            if(isXAny == false && tolerance < std::abs(xCoordAsConst - nodeCoords[0]) ||
               isYAny == false && tolerance < std::abs(yCoordAsConst - nodeCoords[1]) )
            {
                continue;
            }

            // List of nodes with force
            nodesIDs.push_back(nodeID);
        }

        if(nodesIDs.size() == 0)
            return result;

        auto nodalFx = Fx / nodesIDs.size();
        auto nodalFy = Fy / nodesIDs.size();

        for(int id : nodesIDs)
        {
            Eigen::Vector3d nodeForce{nodalFx, nodalFy, 0};
            _nodes.GetByID(id)->AddNodeForce(nodeForce);
        }

        result = true;
        return result;
    }

    int FEModel::GetNodesCount()
    {
        return _nodes.size();
    }

    bool FEModel::BuildGlobalEnsemble()
    {
        auto result = false;

        // 1. Calculate all local stiffness matrixes
        std::vector<Eigen::Triplet<double>> localStiffnessMatrixes;
        for (auto e : _elements)
        {
            e.second->CalculateLocalStiffnessMatrix(localStiffnessMatrixes);
        }

        // 2. Build global stiffness matrix
        int doubleNodesSize = 2 * GetNodesCount();
        auto globalStiffnessMatrix = std::make_unique<Eigen::SparseMatrix<double>>(doubleNodesSize, doubleNodesSize);
        globalStiffnessMatrix->setFromTriplets(localStiffnessMatrixes.begin(), localStiffnessMatrixes.end());
        _globalStiffnessMatrix = std::move(globalStiffnessMatrix); // Move (fast and hard) global stiffness matrix to model

        // 3. Build global force vector
        auto externalForcesVector = std::make_unique<Eigen::VectorXd>(BuildExternalForcesVector());
        _globalForceVector = std::move(externalForcesVector); // Move (fast and hard) global forces vector

        // 5. Build Constraints
        auto resultConstraints = ApplyConstraints();

        result = true;

        return result;
    }

    bool FEModel::ApplyConstraints()
    {
        auto result = false;
        std::vector<int> globalIDsToConstraint;
        for(const auto& n : _nodesWithConstraints)
        {
            auto globalID = n.second->GetGlobalNodeID();
            auto movementDOFs = n.second->GetMovementDOFs();
            
            if(movementDOFs[0] > 0)
                globalIDsToConstraint.push_back(2 * globalID);
            
            if(movementDOFs[1] > 0)
                globalIDsToConstraint.push_back(2 * globalID + 1);
        }

        for(int k = 0; k < _globalStiffnessMatrix->outerSize(); ++k)
        {
            for (Eigen::SparseMatrix<double>::InnerIterator it(*_globalStiffnessMatrix, k); it; ++it)
		    {
			    for (std::vector<int>::iterator idit = globalIDsToConstraint.begin(); idit != globalIDsToConstraint.end(); ++idit)
			    {
				    SetConstraintsToGlobalStiffnessMatrix(it, *idit);
			    }
		    }
        }

        result = true;
        return result;
    }

    void FEModel::SetConstraintsToGlobalStiffnessMatrix(Eigen::SparseMatrix<double>::InnerIterator& it, int globalID)
    {
    	if (it.row() == globalID || it.col() == globalID)
    	{
    		it.valueRef() = it.row() == it.col() ? 1.0f : 0.0f;
    	}
    }

    Eigen::VectorXd FEModel::BuildExternalForcesVector()
    {
        auto doubleNodesSize = 2 * _nodes.size();
        Eigen::VectorXd R(doubleNodesSize);
        for (const auto& n : _nodes)
        {
            auto globalNodeID = n.second->GetGlobalNodeID();
            auto nodalForce = n.second->GetForce();
            R.row(2 * globalNodeID) << nodalForce(0);       // Fx
            R.row(2 * globalNodeID + 1) << nodalForce(1);   // Fy
            //R.row(2 * globalNodeID + 2) << nodalForce(2); // Fz
        }
        return R;
    }

    bool FEModel::Calculate()
    {
        auto result = false;

        // 1. Build global ensemble {R} = [K]{u}
        result = BuildGlobalEnsemble();
        if(result == false)
            return result;

        // 2. Solve linear system {u} = [K']{R}
        result = SolveLinearSystem();
        if(result == false)
            return result;
        
        // 3. Calculate strains and stresses matrixes
        result = BuildStrainsAndStressesForAllElements();
        
        return result;
    }

    bool FEModel::BuildStrainsAndStressesForAllElements()
    {
        auto result = false;

        for(const auto& e : _elements)
        {
            e.second->CalculateLocalStrainAndStressMatrix();
        }

        return result;
    }

    bool FEModel::SolveLinearSystem()
    {
        auto result = false;

        Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver(*_globalStiffnessMatrix);
        auto displacements = solver.solve(*_globalForceVector);
        _globalDisplacementVector = std::make_unique<Eigen::VectorXd>(displacements);;
        result = true;
        // TODO: How to properly store displacements data? It may be necessary to copy data to nodes.
        // result = CopyDisplacementsToNodes(displacements);
        
        return result;
    }

    bool FEModel::CopyDisplacementsToNodes(const Eigen::VectorXd& displacements)
    {
        auto result = false;

        if(displacements.size() != 2 * _nodes.size())
            return result;

        for(auto& n : _nodes)
        {
            auto globalID = n.second->GetGlobalNodeID();
            auto u = displacements(2 * globalID);
            auto v = displacements(2 * globalID + 1);
            auto w = 0.0;
            Eigen::Vector3d displacement{u, v, w};
            n.second->SetDisplacements(displacement);
        }
        result = true;
        return result;
    }

    std::shared_ptr<INode> FEModel::GetNodeByID(int id)
    {
        return _nodes.GetByID(id);
    }

    std::shared_ptr<IProperty> FEModel::GetPropertyByID(int id)
    {
        return _properties.GetByID(id);
    }

    std::shared_ptr<IMaterial> FEModel::GetMaterialByID(int id)
    {
        return _materials.GetByID(id);
    }

    Eigen::VectorXd FEModel::GetGlobalDisplacementVector()
    {
        return *_globalDisplacementVector;
    }

    void FEModel::Print()
    {
        //std::cout << "GLOBAL STIFFNESS MATRIX" << std::endl;
        //std::cout << *_globalStiffnessMatrix << std::endl;

        //std::cout << "GLOBAL FORCE VECTOR\n" << std::endl;
        //std::cout << *_globalForceVector << std::endl << std::endl;

        //std::cout << "GLOBAL DISPLACEMENT VECTOR\n" << std::endl;
        //std::cout << *_globalDisplacementVector << std::endl << std::endl;

        std::cout << "NORMAL STRESS XX ALONG Y-AXIS" << std::endl;
        std::cout << "\tEID\tX\tY\tSXX" << std::endl;
        int eid = 0;
        Eigen::Vector3d coords{0, 0, 0};
        double stressXX = 0.0;
        for(auto& e : _elements)
        {
            eid = e.second->GetElementID();
            coords = e.second->GetCoordCenter();
            auto stresses = e.second->GetStressMatrix();
            stressXX = stresses(0, 0);
            double x = coords[0];
            double y = coords[1];
            std::cout << "\t" << eid << "\t" << x << "\t" << y << "\t" << stressXX << std::endl;
        }
        
    }
}