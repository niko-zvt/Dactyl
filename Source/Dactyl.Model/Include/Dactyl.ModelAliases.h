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
	using INodePtr = std::shared_ptr<INode>;

	class IElement;
	using IElementPtr = std::shared_ptr<IElement>;

	class IMaterial;
	typedef std::shared_ptr<IMaterial> IMaterialPtr;

	class IProperty;
	using IPropertyPtr = std::shared_ptr<IProperty>;

	class FEModel;
	typedef std::unique_ptr<FEModel> FEModelPtr;
}

#endif /* _Dactyl.ModelAliases.h_ */