
#include "Dactyl.ContextLocator.h"
#include "Dactyl.IContext.h"
#include "Dactyl.NullContext.h"

namespace Dactyl::Application
{
    // Init the static class member
    NullContext ContextLocator::nullContext;
    IContext* ContextLocator::_context = nullptr;

    IContext &ContextLocator::getContext()
    {
        if (ContextLocator::_context == nullptr)
        {
            ContextLocator::init();
        }

        return *ContextLocator::_context;
    }

    void ContextLocator::provideContext(IContext *context)
    {
        if (ContextLocator::_context == nullptr)
        {
            ContextLocator::init();
        }

        if (context == nullptr)
        {
            _context = &ContextLocator::nullContext;
            return;
        }

        ContextLocator::_context = context;
    }

    void ContextLocator::init()
    {
        _context = &nullContext;
    }
}
