#pragma once
#ifndef _Dactyl_ModelAliases_h_
#define _Dactyl_ModelAliases_h_

#include "Dactyl.FEModel.h"
#include "Elements/Dactyl.IElement.h"
#include "Nodes/Dactyl.INode.h"

namespace Dactyl::Model
{
    // Aliases for smart pointers
	class INode;
	typedef std::shared_ptr<INode> INodePtr;

	class IElement;
	typedef std::shared_ptr<IElement> IElementPtr;

	class IMaterial;
	typedef std::shared_ptr<IMaterial> IMaterialPtr;

	class IProperty;
	typedef std::shared_ptr<IProperty> IPropertyPtr;

	class IMaterialCreator;
	typedef std::shared_ptr<IMaterialCreator> IMaterialCreatorPtr;

	class IPropertyCreator;
	typedef std::shared_ptr<IPropertyCreator> IPropertyCreatorPtr;

	class FEModel;
	typedef std::unique_ptr<FEModel> FEModelPtr;
}

#endif /* _Dactyl.ModelAliases.h_ */