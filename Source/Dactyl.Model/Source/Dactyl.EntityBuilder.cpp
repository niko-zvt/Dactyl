#include <vector>
#include <algorithm>
#include "Dactyl.EntityBuilder.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IMaterialCreator.h"
#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.IPropertyCreator.h"
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.INodeCreator.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.IElementCreator.h"
#include "Dactyl.KData.h"

namespace Dactyl::Model
{

    MaterialSet EntityBuilder::buildMaterials(const std::vector<KMaterial>& kMaterials)
    {
        MaterialSet materials;

        for (const auto& kMaterial : kMaterials)
        {
            auto creator = IMaterialCreator::getMaterialCreator(kMaterial);
            auto material = creator->buildMaterial();
            materials.Add(material);
        }

        return materials;
    }

    PropertySet EntityBuilder::buildProperties(const std::vector<KProperty>& kProperties, const std::vector<KSection>& kSections)
    {
        PropertySet properties;

        for (const auto& kProperty : kProperties)
        {
            auto sid = kProperty.SectionID;
            auto iterator = std::find_if(kSections.begin(), kSections.end(), [&sid](const KSection& s) { return s.ID == sid; });
            auto kSection = *iterator;
            auto creator = IPropertyCreator::getPropertyCreator(kProperty, kSection);
            auto property = creator->buildProperty();
            properties.Add(property);
        }

        return properties;
    }
    
    NodeSet EntityBuilder::buildNodes(const std::vector<KNode>& kNodes)
    {
        NodeSet nodes;

        int globalNodeID = 0;
        for (const auto& kNode : kNodes)
        {
            auto creator = INodeCreator::getNodeCreator(kNode);
            auto node = creator->buildNode();
            node->SetGlobalNodeID(globalNodeID);
            nodes.Add(node);
            globalNodeID++;
        }

        return nodes;
    }
    
    std::vector<IElementPtr> EntityBuilder::buildElements(const std::vector<KElement>& kElements)
    {
        std::vector<IElementPtr> elements;

        for (const auto& kElement : kElements)
        {
            auto creator = IElementCreator::getElementCreator(kElement);
            auto element = creator->buildElement();
            elements.push_back(element);
        }

        return elements;
    }
}
