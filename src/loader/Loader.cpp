#include "Loader.hpp"
#include "../error/Error.hpp"
#include "../error/ErrorMessages.hpp"

#include <dlfcn.h>
#include <iostream>

Module::Loader::Loader() : _dl(nullptr) {}

Module::Loader::Loader(const std::filesystem::path &modulePath) : _modulePath(modulePath)
{
    _dl = dlopen(modulePath.string().c_str(), RTLD_LAZY);
    if (_dl == nullptr) {
        throw ErrorLoader(messages.find(CANNOT_OPEN)->second);
    }
    dlerror();
}

Module::Loader::~Loader()
{
    // can't be close here !!
    // if (_dl == nullptr) {
    //     return;
    // }
    // dlclose(_dl);
    // _dl = nullptr;
}

const std::filesystem::path &Module::Loader::getModulePath() const
{
    return _modulePath;
}

void Module::Loader::open(const std::filesystem::path &modulePath)
{
    _dl = dlopen(modulePath.string().c_str(), RTLD_LAZY);
    if (_dl == nullptr) {
        std::cout << "open error " << dlerror() << std::endl;
        throw ErrorLoader(messages.find(CANNOT_OPEN)->second);
    }
}

void Module::Loader::close()
{
    if (_dl == nullptr)
        return; 
    dlclose(_dl);
    _dl = nullptr;
}

void *Module::Loader::resolver(const std::string &solver)
{
    if (solver.empty()) {
        throw ErrorLoader(messages.find(SOLVER_NOT_VALID)->second);
    }
    return dlsym(_dl, solver.c_str());
}
