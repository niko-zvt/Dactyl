#pragma once
#ifndef _Dactyl_ModelLocator_h_
#define _Dactyl_ModelLocator_h_

#include "Dactyl.IModel.h"
#include "Dactyl.NullModel.h"

namespace Dactyl::Model
{
    class ModelLocator
    {
        public:
            static IModel& getModel();
            static void provideModel(IModel* model);
    
        private:
            static void init();
            static NullModel nullModel;
            static IModel* _model;
    };
}

#endif /* _Dactyl.ModelLocator.h_ */