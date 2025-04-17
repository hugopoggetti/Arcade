#ifndef __IMODULE__
    #define __IMODULE__

#include "Plugin.hpp"

class IModule {
    public:
        IModule() = default;
        virtual ~IModule() = default;
        virtual const Plugin &getPlugin() const = 0;
};

#endif