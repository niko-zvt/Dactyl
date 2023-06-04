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

namespace Dactyl::Model
{
    class EntityBuilder
    {
        public:
            static std::vector<IMaterialPtr> buildMaterials(const std::vector<KMaterial>& kMaterials);
            static std::vector<IPropertyPtr> buildProperties(const std::vector<KProperty>& kProperties, const std::vector<KSection>& kSections);
            static std::vector<INodePtr> buildNodes(const std::vector<KNode>& kNodes);
            static std::vector<IElementPtr> buildElements(const std::vector<KElement>& kElements);
    };
}

#endif /* _Dactyl.EntityBuilder.h_ */