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
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include "Dactyl.EntityBuilder.h"
#include "Dactyl.ModelAliases.h"
#include <Sparse>
#include <Core>
#include <Dense>
#include <vector>
#include <optional>

namespace Dactyl::Model
{
    bool FEModel::LoadMesh(const std::optional<KData>& kData)
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

            // Create DOFs
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

    int FEModel::GetNodesCount()
    {
        return _nodes.size();
    }

    bool FEModel::BuildGlobalEnsemble()
    {
        auto result = false;

        // 1. Calculate all local stiffness matrixes
        std::vector<Eigen::Triplet<double>> localStiffnessMatrixes;
        for(auto e: _elements)
        {
            e->CalculateLocalStiffnessMatrix(localStiffnessMatrixes);
        }

        // 2. Build global stiffness matrix
        int doubleNodesSize = 2 * GetNodesCount();
        auto globalStiffnessMatrix = std::make_unique<Eigen::SparseMatrix<double>>(doubleNodesSize, doubleNodesSize);
        globalStiffnessMatrix->setFromTriplets(localStiffnessMatrixes.begin(), localStiffnessMatrixes.end());
        _globalStiffnessMatrix = std::move(globalStiffnessMatrix); // Move global stiffness matrix to model

        // 4. Check global stiffness matrix
        // TODO

        // 5. Build DOFs
        // TODO

        result = false; // TODO -> true

        return result;
    }

    bool FEModel::Calculate()
    {
        auto result = false;

        result = BuildGlobalEnsemble();

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

    void FEModel::Print()
    {
        hello_model();
    }

    void FEModel::hello_model()
    {
        auto suma = Dactyl::Math::test_sum(5.1, 4.2);
        std::cout << "Hello, Model!\n\t5.1 + 4.2 = 9.3 == " << suma << std::endl;

        Eigen::Matrix3d test; //3 by 3 double precision matrix initialization

        // Let's make it a symmetric matrix
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
                test(i,j) = (i+1)*(1+j);
        }

        print_matrix(test);
    }

    void FEModel::print_matrix(Eigen::MatrixX3d m)
    {
        std::cout << m << std::endl;
    }
}