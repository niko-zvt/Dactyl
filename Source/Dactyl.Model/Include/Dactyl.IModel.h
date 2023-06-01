#pragma once
#ifndef _Dactyl_IModel_h_
#define _Dactyl_IModel_h_

namespace Dactyl::Model
{
    class IModel
    {
        public:
            virtual bool loadModel() = 0;
            virtual bool saveModel() = 0;
            virtual void print() = 0;
            virtual int getNodesCount() = 0;
    };
}

#endif /* _Dactyl.IModel.h_ */