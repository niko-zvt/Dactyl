#include "Dactyl.GlobalContext.h"

namespace Dactyl::Application
{
    bool GlobalContext::isRunable()
    {
        return _isRunable;
    }

    const std::string& GlobalContext::getPathToKFile()
    {
        return _pathToKFile;
    }

    const std::string& GlobalContext::getAppName()
    {
        return _appName;
    }

        const std::string& GlobalContext::getAppPath()
    {
        return _appPath;
    }

    void GlobalContext::setPathToKFile(const std::string &path)
    {
        _pathToKFile = path;
    }

    void GlobalContext::setAppName(const std::string &name)
    {
        _appName = name;
    }

    void GlobalContext::setAppPath(const std::string &path)
    {
        _appPath = path;
    }

    void GlobalContext::makeRunable()
    {
        _isRunable = true;
    }
}
