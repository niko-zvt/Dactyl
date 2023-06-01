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
            static IModel& getModel()
            {
                if(ModelLocator::_model == nullptr)
                {
                    ModelLocator::init();
                }

                return *ModelLocator::_model;
            }
    
            static void provideModel(IModel* model)
            {
                if (ModelLocator::_model == nullptr) 
                {
                    ModelLocator::init();
                }
 
                if (model == nullptr)
                {
                    _model = &ModelLocator::nullModel;
                    return;
                }

                ModelLocator::_model = model;
            }
    
        private:
            static void init()
            {
                _model = &nullModel;
            }
 
            static NullModel nullModel;
            static IModel* _model;
    };
    
    // Init the static class member
    NullModel ModelLocator::nullModel;
    IModel* ModelLocator::_model = nullptr;

}

#endif /* _Dactyl.ModelLocator.h_ */