#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IsotropicMaterial.h"
#include "Dactyl.ModelAliases.h"
#include <Core>
#include <Dense>

namespace Dactyl::Model
{
    IsotropicMaterial::IsotropicMaterial(int id, double elasticModulus, double poissonRatio, double density, std::string name)
    {
        _materialID = id;
        _elasticModulus = elasticModulus;
        _poissonRatio = poissonRatio;
        _density = density;
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
        EMatrix << 1.0, _poissonRatio, 0.0,
            _poissonRatio, 1.0, 0.0,
            0.0, 0.0, 0.5 * (1.0 - _poissonRatio);

        _elasticityMatrix = EMatrix * (_elasticModulus / (1.0 - pow(_poissonRatio, 2)));
    }

    IsotropicMaterialCreator::IsotropicMaterialCreator(const KMaterial &kMaterial) : IMaterialCreator(kMaterial)
    {
        _material = std::make_shared<IsotropicMaterial>(kMaterial.ID,
                                                        kMaterial.ElasticModulus,
                                                        kMaterial.PoissonRatio,
                                                        kMaterial.Density);
    }

    IMaterialPtr IsotropicMaterialCreator::buildMaterial()
    {
        return _material;
    }
}
