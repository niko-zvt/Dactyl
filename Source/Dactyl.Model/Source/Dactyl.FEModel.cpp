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
#include <Core>
#include <Dense>
#include <vector>
#include <optional>

namespace Dactyl::Model
{
    bool FEModel::loadModel(const std::optional<KData>& kData)
    {
        // Load FE model 
        auto loadResult = false;

        // 1. Check KData and build model
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

            // Create Loads

            // Check model
            loadResult = true;
        }

        return loadResult;
    }

    bool FEModel::saveModel()
    {
        return false;
    }

    int FEModel::getNodesCount()
    {
        return _nodes.size();
    }














    void FEModel::print()
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