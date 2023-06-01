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
	using IElementPtr = std::shared_ptr<IElement>;

	class FEModel;
	typedef std::unique_ptr<FEModel> FEModelPtr;
}

#endif /* _Dactyl.ModelAliases.h_ */