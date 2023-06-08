#pragma once
#ifndef _Dactyl_NullModel_h_
#define _Dactyl_NullModel_h_

#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class NullModel : public IModel
    {
        public:
            NullModel()
            {
            }

            virtual bool Calculate() override
            {
                return false;
            }

            virtual bool LoadMesh(const std::optional<KData>& kData) override
            {
                return false;
            }

            virtual bool LoadModel() override
            {
                return false;
            }

            virtual bool SaveModel() override
            {
                return false;
            }

            virtual void Print() override
            {
            }

            virtual int GetNodesCount() override
            {
                return -1;
            }
       
            NullModel(NullModel const&) = delete;
            void operator=(NullModel const&) = delete;
    };
}

#endif /* _Dactyl.NullModel.h_ */
