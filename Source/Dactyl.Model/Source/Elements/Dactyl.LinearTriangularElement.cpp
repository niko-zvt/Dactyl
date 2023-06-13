#include "Dactyl.FEModel.h"
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
#include "Dactyl.ModelLocator.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.IElementCreator.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include <Sparse>
#include <Core>
#include <Dense>
#include <vector>
#include <iostream>

namespace Dactyl::Model
{
    class INode;

    LinearTriangularElement::LinearTriangularElement(int eid, int pid, std::vector<int> nodesIDs)
    {
        _elementID = eid;
        _propertyID = pid;
        _nodesIDs = nodesIDs;
    }

    int LinearTriangularElement::GetElementID()
    {
        return _elementID;
    }

    int LinearTriangularElement::GetPropertyID()
    {
        return _propertyID;
    }

    Eigen::Matrix3d LinearTriangularElement::GetStrainMatrix()
    {
        return _strainMatrix;
    }

    Eigen::Matrix3d LinearTriangularElement::GetStressMatrix()
    {
        return _stressMatrix;
    }

    Eigen::Vector3d LinearTriangularElement::GetCoordCenter()
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        auto coords_1 = model.GetNodeByID(_nodesIDs[0])->GetCoords();
        auto coords_2 = model.GetNodeByID(_nodesIDs[1])->GetCoords();
        auto coords_3 = model.GetNodeByID(_nodesIDs[2])->GetCoords();

        auto x = (coords_1[0] + coords_2[0] + coords_3[0]) / 3;
        auto y = (coords_1[1] + coords_2[1] + coords_3[1]) / 3;
        auto z = (coords_1[2] + coords_2[2] + coords_3[2]) / 3;
        Eigen::Vector3d center;
        center << x, y, z;
        return center;
    }

    void LinearTriangularElement::CalculateLocalStrainAndStressMatrix()
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        auto globalDisplacementVector = model.GetGlobalDisplacementVector();
        Eigen::Matrix<double, 6, 1> delta;

        int index = 0;
        for(auto nodeID : _nodesIDs)
        {
            auto globalNodeID = model.GetNodeByID(nodeID)->GetGlobalNodeID();
            auto u = globalDisplacementVector(2 * globalNodeID);
            auto v = globalDisplacementVector(2 * globalNodeID + 1);
            // auto w = 0.0;
            delta(index, 0) = u;
            delta(index + 1, 0) = v; 
            // delta(index + 2, 0) = w;
            index++;
        }

        auto strains = _B * delta;
        auto stresses = _D * strains;

        // Strain matrix
        _strainMatrix(0, 0) = strains[0];
        _strainMatrix(0, 1) = strains[2];
        _strainMatrix(0, 2) = 0.0;

        _strainMatrix(1, 0) = strains[2];
        _strainMatrix(1, 1) = strains[1];
        _strainMatrix(1, 2) = 0.0;
        
        _strainMatrix(2, 0) = 0.0;
        _strainMatrix(2, 1) = 0.0;
        _strainMatrix(2, 2) = 0.0;

        // Stress matrix
        _stressMatrix(0, 0) = stresses[0];
        _stressMatrix(0, 1) = stresses[2];
        _stressMatrix(0, 2) = 0.0;

        _stressMatrix(1, 0) = stresses[2];
        _stressMatrix(1, 1) = stresses[1];
        _stressMatrix(1, 2) = 0.0;
        
        _stressMatrix(2, 0) = 0.0;
        _stressMatrix(2, 1) = 0.0;
        _stressMatrix(2, 2) = 0.0;
    }

    void LinearTriangularElement::CalculateLocalStiffnessMatrix(std::vector<Eigen::Triplet<double>>& subEnsembles)
    {
        _D = BuildElasticityMatrix();
        _A = BuildTwoAreaMatrix();
        _B = BuildGradientMatrix();
        auto t = GetAverageThicknessOfElement();
        Eigen::Matrix<double, 6, 6> K = _B.transpose() * _D * _B * _A.determinant() * 0.5 * t;
        
        // Assembly
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        for (int i = 0; i < 3; i++)
    	{
    		for (int j = 0; j < 3; j++)
    		{
                /*
                A triplets using a vector of node indexes to determine its position in the global stiffness matrix.
                We have two sets of indices [i, j], one local for the array of elements, the other global for the ensemble.
                */
                int g1 = model.GetNodeByID(_nodesIDs[i])->GetGlobalNodeID();
                int g2 = model.GetNodeByID(_nodesIDs[j])->GetGlobalNodeID();
    			Eigen::Triplet<double> var11(2 * g1 + 0, 2 * g2 + 0, K(2 * i + 0, 2 * j + 0));
    			Eigen::Triplet<double> var12(2 * g1 + 0, 2 * g2 + 1, K(2 * i + 0, 2 * j + 1));
    			Eigen::Triplet<double> var21(2 * g1 + 1, 2 * g2 + 0, K(2 * i + 1, 2 * j + 0));
    			Eigen::Triplet<double> var22(2 * g1 + 1, 2 * g2 + 1, K(2 * i + 1, 2 * j + 1));

    			subEnsembles.push_back(var11);
    			subEnsembles.push_back(var12);
    			subEnsembles.push_back(var21);
    			subEnsembles.push_back(var22);
    		}
    	}
    }

    double LinearTriangularElement::GetAverageThicknessOfElement()
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        auto property = model.GetPropertyByID(_propertyID);
        auto thicknesses = property->GetThicknessInNodes();
        double averageThickness = 0.0;
        for(auto t : thicknesses)
        {
            averageThickness += t;
        }
        return averageThickness / thicknesses.size();
    }

    Eigen::Matrix<double, 3, 6> LinearTriangularElement::BuildGradientMatrix()
    {
        auto inverseA = _A.inverse();
        Eigen::Matrix<double, 3, 6> gradMatrix; // <double, 3, 9>
        for (int i = 0; i < 3; i++)
        {
            gradMatrix(0, 2 * i + 0) = inverseA(1, i);
        	gradMatrix(0, 2 * i + 1) = 0.0;
            // gradMatrix(0, 2 * i + 2)
        	gradMatrix(1, 2 * i + 0) = 0.0;
        	gradMatrix(1, 2 * i + 1) = inverseA(2, i);
            // gradMatrix(1, 2 * i + 2)
        	gradMatrix(2, 2 * i + 0) = inverseA(2, i);
        	gradMatrix(2, 2 * i + 1) = inverseA(1, i);
            // gradMatrix(2, 2 * i + 2)
        }
        return gradMatrix;
    }

    Eigen::Matrix3d LinearTriangularElement::BuildElasticityMatrix()
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        auto property = model.GetPropertyByID(_propertyID);
        auto material = model.GetMaterialByID(property->GetMaterialID());
        auto elasticMatrix = material->GetElasticityMatrix();
        return elasticMatrix; 
    }

    Eigen::Matrix3d LinearTriangularElement::BuildTwoAreaMatrix()
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        Eigen::Vector3d xCoordsOfNodes;
        Eigen::Vector3d yCoordsOfNodes;

        for(int i=0; i < 3; i++)
        {
            auto node = model.GetNodeByID(_nodesIDs[i]);
            auto coords = node->GetCoords();
            xCoordsOfNodes[i] = coords[0];
            yCoordsOfNodes[i] = coords[1];
        }

        Eigen::Matrix3d twoAreaMatrix;
        twoAreaMatrix << Eigen::Vector3d(1, 1, 1), xCoordsOfNodes, yCoordsOfNodes;
        return twoAreaMatrix;
    }

    int LinearTriangularElement::GetNodesCount()
    {
        return _nodesIDs.size();
    }

    LinearTriangularCreator::LinearTriangularCreator(const KElement &kElement) : IElementCreator(kElement)
    {
        std::vector<int> nodesIDs { kElement.N1, kElement.N2, kElement.N3 };
        _element = std::make_shared<LinearTriangularElement>(kElement.ID, kElement.PropertyID, nodesIDs);
    }

    IElementPtr LinearTriangularCreator::buildElement()
    {
        return _element;
    }
}
