#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IsotropicMaterial.h"
#include <Core>
#include <Dense>

namespace Dactyl::Model
{

    IsotropicMaterial::IsotropicMaterial(int id, double E, double nu, std::string name)
    {
        _materialID = id;
        _E = E;
        _nu = nu;
        _materialName = name;
        calclulateElasticityMatrix();
    }

    int IsotropicMaterial::getMaterialID()
    {
        return _materialID;
    }

    std::string IsotropicMaterial::getMaterialName()
    {
        return _materialName;
    }

    Eigen::MatrixXd IsotropicMaterial::getElasticityMatrix()
    {
        return _elasticityMatrix;
    }

    void IsotropicMaterial::calclulateElasticityMatrix()
    {
        Eigen::Matrix3d EMatrix;
        EMatrix <<
            1.0,    _nu,     0.0,
            _nu,     1.0,    0.0,
            0.0,    0.0,    0.5 * (1.0 - _nu);
        
        _elasticityMatrix = EMatrix * (_E / (1.0 - pow(_nu, 2)));
    }
}