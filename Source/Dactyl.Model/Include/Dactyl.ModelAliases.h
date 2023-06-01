#pragma once
#ifndef _Dactyl_ModelAliases_h_
#define _Dactyl_ModelAliases_h_

namespace Dactyl::Model
{
    // Aliases for smart pointers
	class FEModel;
	typedef std::unique_ptr<FEModel> FEModelPtr;
}

#endif /* _Dactyl.ModelAliases.h_ */