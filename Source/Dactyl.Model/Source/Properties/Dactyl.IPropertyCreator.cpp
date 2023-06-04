#include "Properties/Dactyl.IPropertyCreator.h"
#include "Properties/Dactyl.ShellProperty.h""

namespace Dactyl::Model
{
    IPropertyCreatorPtr IPropertyCreator::getPropertyCreator(const KProperty& kProperty, const KSection& kSection)
    {
        IPropertyCreatorPtr creator;
        auto type = kProperty.Type;

        if (type == "shell")
        {
            creator = std::make_shared<ShellPropertyCreator>(kProperty, kSection);
        }
        else if (type == "solid")
        {
            // Do nothing
        }
        else
        {
            throw std::invalid_argument("Unknown type of KProperty.");
        }

        return creator;
    };
}