#include "Materials/Dactyl.IMaterialCreator.h"
#include "Materials/Dactyl.IsotropicMaterial.h"

namespace Dactyl::Model
{
    IMaterialCreator* IMaterialCreator::getMaterialCreator(const KMaterial &kMaterial)
    {
        IMaterialCreator *creator;
        auto type = kMaterial.Type;

        if (type == "elastic_isotropic")
        {
            creator = new IsotropicMaterialCreator(kMaterial);
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