#include <vector>
#include "Dactyl.EntityBuilder.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IMaterialCreator.h"
#include "Properties/Dactyl.IProperty.h"
#include "Nodes/Dactyl.INode.h"
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.KData.h"

namespace Dactyl::Model
{

    std::vector<IMaterialPtr> EntityBuilder::buildMaterials(const std::vector<KMaterial>& kMaterials)
    {
        std::vector<IMaterialPtr> materials;

        for (auto kMaterial : kMaterials)
        {
            auto creator = IMaterialCreator::getMaterialCreator(kMaterial);
            auto material = creator->buildMaterial();
            materials.push_back(material);
        }

        return materials;
    }

    std::vector<IPropertyPtr> EntityBuilder::buildProperties(const std::vector<KProperty>& kProperties, const std::vector<KSection>& kSections)
    {
        std::vector<IPropertyPtr> properties;

        return properties;
    }
    
    std::vector<INodePtr> EntityBuilder::buildNodes(const std::vector<KNode>& kNodes)
    {
        std::vector<INodePtr> nodes;

        return nodes;
    }
    
    std::vector<IElementPtr> EntityBuilder::buildElements(const std::vector<KElement>& kElements)
    {
        std::vector<IElementPtr> elements;

        return elements;
    }
}
