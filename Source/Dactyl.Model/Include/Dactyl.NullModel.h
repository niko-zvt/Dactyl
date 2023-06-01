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
    
            virtual bool loadModel() override
            {
                return false;
            }
    
            virtual bool saveModel() override
            {
                return false;
            }

            virtual void print() override
            {
            }

            virtual int getNodesCount() override
            {
                return -1;
            }
       
            NullModel(NullModel const&) = delete;
            void operator=(NullModel const&) = delete;
    };
}

#endif /* _Dactyl.NullModel.h_ */
