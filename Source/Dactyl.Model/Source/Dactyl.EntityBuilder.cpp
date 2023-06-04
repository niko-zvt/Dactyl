#include <vector>
#include <algorithm>
#include "Dactyl.EntityBuilder.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IMaterialCreator.h"
#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.IPropertyCreator.h"
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

        for (auto kProperty : kProperties)
        {
            auto sid = kProperty.SectionID;
            auto iterator = std::find_if(kSections.begin(), kSections.end(), [&sid](const KSection& s) { return s.ID == sid; });
            auto kSection = *iterator;
            auto creator = IPropertyCreator::getPropertyCreator(kProperty, kSection);
            auto property = creator->buildProperty();
            properties.push_back(property);
        }

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
