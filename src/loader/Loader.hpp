#ifndef __LOADER__
    #define __LOADER__

#include <filesystem>
#include <string>

namespace Module
{
    enum ModuleType {
        UNDEFINED,
        GRAPHIC,
        GAME
    };

    class Loader {
        public:
            Loader();
            Loader(const std::filesystem::path &modulePath);
            ~Loader();
            const std::filesystem::path &getModulePath() const;
            void open(const std::filesystem::path &modulePath);
            void close();
            void *resolver(const std::string &solver);
        private:
            void *_dl;
            std::filesystem::path _modulePath;
    };
}

#endif
