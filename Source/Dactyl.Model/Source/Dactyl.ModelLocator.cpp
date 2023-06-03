#include "Dactyl.ModelLocator.h"

namespace Dactyl::Model
{
    // Init the static class member
    NullModel ModelLocator::nullModel;
    IModel *ModelLocator::_model = nullptr;

    IModel &ModelLocator::getModel()
    {
        if (ModelLocator::_model == nullptr)
        {
            ModelLocator::init();
        }

        return *ModelLocator::_model;
    }

    void ModelLocator::provideModel(IModel *model)
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

    void ModelLocator::init()
    {
        _model = &nullModel;
    }
}
