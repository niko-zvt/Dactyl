#pragma once
#ifndef _Dactyl_EntityBuilder_h_
#define _Dactyl_EntityBuilder_h_

#include <vector>
#include "Materials/Dactyl.IMaterial.h"
#include "Properties/Dactyl.IProperty.h"
#include "Nodes/Dactyl.INode.h"
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.KData.h"
#include "Dactyl.ModelAliases.h"
#include "Sets/Dactyl.NodeSet.h"
#include "Sets/Dactyl.MaterialSet.h"
#include "Sets/Dactyl.PropertySet.h"

namespace Dactyl::Model
{
    class EntityBuilder
    {
        public:
            static MaterialSet buildMaterials(const std::vector<KMaterial>& kMaterials);
            static PropertySet buildProperties(const std::vector<KProperty>& kProperties, const std::vector<KSection>& kSections);
            static NodeSet buildNodes(const std::vector<KNode>& kNodes);
            static ElementSet buildElements(const std::vector<KElement>& kElements);
    };
}

#endif /* _Dactyl.EntityBuilder.h_ */