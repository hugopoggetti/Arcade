#ifndef __ERROR_MESSAGES__
    #define __ERROR_MESSAGES__

#include <string>
#include <map>

#define RESETD "\033[0m"
#define BLACKD "\033[30m"
#define REDD "\033[31m"
#define GREEND "\033[32m"
#define BLEUD "\033[34m"
#define YELLOWD "\033[33m"
#define GREASYD "\033[1m"

namespace Arcade
{
    enum ErrorType {
        BAD_NUMBER_ARGUMENTS,
        NOT_FOUND_LIB,
        NOT_SHARED_LIBRARY
    };

    const std::map<ErrorType, std::string> messages = {
        {BAD_NUMBER_ARGUMENTS, GREASYD REDD ">> -E-" RESETD YELLOWD " Bad number arguments at program." RESETD},
        {NOT_FOUND_LIB, GREASYD REDD ">> -E-" RESETD YELLOWD "Not found library." RESETD},
        {NOT_SHARED_LIBRARY, GREASYD REDD ">> -E-" RESETD YELLOWD " Is not a shared library." RESETD}
    };
}

namespace Module
{
    enum ErrorType {
        CANNOT_OPEN,
        SOLVER_NOT_VALID,
        MODULE_NOT_VALID,
        FIRST_MODULE_NOT_GRAPHIC
    };

    const std::map<ErrorType, std::string> messages = {
        {CANNOT_OPEN, GREASYD REDD ">> -E- " RESETD YELLOWD " Cannot open the module." RESETD},
        {SOLVER_NOT_VALID, GREASYD REDD ">> -E- " RESETD YELLOWD " Solver is not valid." RESETD},
        {MODULE_NOT_VALID, GREASYD REDD ">> -E- " RESETD YELLOWD "Module load is not valid." RESETD},
        {FIRST_MODULE_NOT_GRAPHIC, GREASYD REDD ">> -E- " RESETD YELLOWD "first module not a graphical library." RESETD}
    };
}

namespace Graphic
{
    enum ErrorType {
        CANNOT_INIT,
        CANNOT_OPEN_WINDOW,
        NOT_INIT,
        CANNOT_INIT_RENDERER,
        SPRITE_NOT_LOAD,
        TEXT_NOT_LOAD
    };

    const std::map<ErrorType, std::string> messages = {
        {CANNOT_INIT, GREASYD REDD ">> -E-" RESETD YELLOWD " Cannot init the graphic library." RESETD},
        {CANNOT_OPEN_WINDOW, GREASYD REDD ">> -E-" RESETD YELLOWD " Cannot open the window." RESETD},
        {NOT_INIT, GREASYD REDD ">> -E-" RESETD YELLOWD " Window not open yet." RESETD},
        {CANNOT_INIT_RENDERER, GREASYD REDD ">> -E-" RESETD YELLOWD " Cannot init renderer." RESETD},
        {SPRITE_NOT_LOAD, GREASYD REDD ">> -E-" RESETD YELLOWD " Cannot init sprite." RESETD},
        {TEXT_NOT_LOAD, GREASYD REDD ">> -E-" RESETD YELLOWD " Text not load." RESETD}
    };
}

#endif
