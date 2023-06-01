#include <iostream>
#include "Dactyl.Calc.h"
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
#include <Core>
#include <Dense>
#include <vector>

namespace Dactyl::Model
{
    bool FEModel::loadModel()
    {
        // Load FE model 

        // Create materials
        std::shared_ptr<IMaterial> mat = std::make_shared<IsotropicMaterial>(1, 20000, 0.3, "material1");
        _materials.push_back(mat);

        // Create properties
        std::shared_ptr<IProperty> prop = std::make_shared<ShellProperty>(1, mat->getMaterialID())
        
        // Create DOFs

        // Create Loads

        // Create nodes
        Eigen::Vector3d coord;
        coord << 1, 2, 3;
        std::shared_ptr<Node> nod = std::make_shared<Node>(5, coord);
        _nodes.push_back(nod);

        // Create elements
        std::vector<int> ids;
        std::shared_ptr<IElement> elem = std::make_shared<LinearTriangularElement>(1, 1, ids);
        _elements.push_back(elem);
        return true;

        // Check model
    }

    bool FEModel::saveModel()
    {
        return false;
    }

    int FEModel::getNodesCount()
    {
        int count = 0;
        std::vector<std::shared_ptr<IElement>>::iterator it;
        for(it = _elements.begin(); it < _elements.end(); it++)
        {
            count += (*it)->getNodesCount();
        }
        return count;
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