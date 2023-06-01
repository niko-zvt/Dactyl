#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.ShellProperty.h"

namespace Dactyl::Model
{
    ShellProperty::ShellProperty(int pid, int mid)
    {
        _propertyID = pid;
        _materialID = mid;
    }

    int ShellProperty::getPropertyID()
    {
        return _propertyID;
    }

    int ShellProperty::getMaterialID()
    {
        return _materialID;
    }
}