#pragma once
#ifndef _Dactyl_ModelAliases_h_
#define _Dactyl_ModelAliases_h_

#include "Dactyl.FEModel.h"
#include "Elements/Dactyl.IElement.h"

namespace Dactyl::Model
{
    // Aliases for smart pointers
	class FEModel;
	typedef std::unique_ptr<FEModel> FEModelPtr;

	class IElement;
	typedef std::shared_ptr<IElement> IElementPtr;
}

#endif /* _Dactyl.ModelAliases.h_ */