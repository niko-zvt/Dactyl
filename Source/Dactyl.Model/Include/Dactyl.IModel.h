#pragma once
#ifndef _Dactyl_IModel_h_
#define _Dactyl_IModel_h_

#include <optional>
#include "Dactyl.KData.h"

namespace Dactyl::Model
{
    class IModel
    {
        public:
            virtual bool Calculate() = 0;
            virtual bool LoadModel() = 0;
            virtual bool SaveModel() = 0;
            virtual bool LoadMesh(const std::optional<KData>& kData) = 0;
            virtual void Print() = 0;
            virtual int GetNodesCount() = 0;
    };
}

#endif /* _Dactyl.IModel.h_ */