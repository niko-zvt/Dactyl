#include "Materials/Dactyl.IMaterialCreator.h"
#include "Materials/Dactyl.IsotropicMaterial.h"

namespace Dactyl::Model
{
    IMaterialCreatorPtr IMaterialCreator::getMaterialCreator(const KMaterial &kMaterial)
    {
        IMaterialCreatorPtr creator;
        auto type = kMaterial.Type;

        if (type == "elastic_isotropic")
        {
            creator = std::make_shared<IsotropicMaterialCreator>(kMaterial);
        }
        else if (type == "orthotropic")
        {
            // Do nothing
        }
        else if (type == "anisotropic")
        {
            // Do nothing
        }
        else
        {
            throw std::invalid_argument("Unknown type of KMaterial.");
        }

        return creator;
    };
}