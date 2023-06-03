#include "Dactyl.GlobalContext.h"

namespace Dactyl::Application
{
    bool GlobalContext::isRunable()
    {
        return _isRunable;
    }

    std::string GlobalContext::getPathToKFile()
    {
        return _pathToKFile;
    }

    void GlobalContext::setPathToKFile(const std::string &path)
    {
        _pathToKFile = path;
    }

    void GlobalContext::makeRunable()
    {
        _isRunable = true;
    }
}
