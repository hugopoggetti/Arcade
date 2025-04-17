#ifndef __ERROR__
    #define __ERROR__

#include <exception>
#include <string>

class Error : public std::exception {
    public:
        Error() = default;
        Error(const std::string &msgError) noexcept : _msgError(msgError) {}
        const char *what() const noexcept {return _msgError.c_str();}
    protected:
        std::string _msgError;
};

namespace Arcade
{
    class ErrorCore : public Error {
        public:
            ErrorCore() = default;
            ErrorCore(const std::string &msgError) : Error(msgError) {}
    };
}

namespace Module
{
    class ErrorLoader : public Error {
        public:
            ErrorLoader() = default;
            ErrorLoader(const std::string &msgError) : Error(msgError) {}
    };

    class ErrorModule : public Error {
        public:
            ErrorModule() = default;
            ErrorModule(const std::string &msgError) : Error(msgError) {}
    };
}

class GraphicLibraryError : public Error {
    public:
        GraphicLibraryError() = default;
        GraphicLibraryError(const std::string &msgError) : Error(msgError) {}
};

#endif
