/**
 * @file        bgt60-logger.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Logger
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_LOGGER_HPP_
#define BGT60_LOGGER_HPP_

#include "bgt60-conf.hpp"

#if (BGT60_LOGGER_ENABLED == 1)

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "bgt60-pal-logger.hpp"

namespace bgt60
{

class Logger
{
    public:
            Logger();
            Logger(LoggerPAL *logpal);
            ~Logger();
            void init();
            void deinit();
            void print(const char * format, ...);
            void printfModule(const char * format, const char *module, const char * color, ...);
            void printModuleHex(const uint8_t * array, uint32_t length, const char * module, const char * color);

    private:
        LoggerPAL *logpal;

};

/**
 * @brief Library Logger
 */

extern Logger bgt60_log;

/**
 * Logger colors options
 */
#define BGT60_LOGGER_COLOR_RED                  "\x1b[31m"
#define BGT60_LOGGER_COLOR_GREEN                "\x1b[32m"
#define BGT60_LOGGER_COLOR_YELLOW               "\x1b[33m"
#define BGT60_LOGGER_COLOR_BLUE                 "\x1b[34m"
#define BGT60_LOGGER_COLOR_MAGENTA              "\x1b[35m"
#define BGT60_LOGGER_COLOR_CYAN                 "\x1b[36m"
#define BGT60_LOGGER_COLOR_LIGHT_GREY           "\x1b[90m"
#define BGT60_LOGGER_COLOR_LIGHT_RED            "\x1b[91m"
#define BGT60_LOGGER_COLOR_LIGHT_GREEN          "\x1b[92m"
#define BGT60_LOGGER_COLOR_LIGHT_YELLOW         "\x1b[93m"
#define BGT60_LOGGER_COLOR_LIGHT_BLUE           "\x1b[94m"
#define BGT60_LOGGER_COLOR_LIGHT_MAGENTA        "\x1b[95m"
#define BGT60_LOGGER_COLOR_LIGHT_CYAN           "\x1b[96m"
#define BGT60_LOGGER_COLOR_DEFAULT              "\x1b[0m"

/**
 * @brief BGT60 logger module
 */

/**
 * Logger color for different error types
 */
#define BGT60_LOGGER_ERROR_COLOR        BGT60_LOGGER_COLOR_RED
#define BGT60_LOGGER_WARNING_COLOR      BGT60_LOGGER_COLOR_YELLOW

#define BGT60_LOG_INIT()\
{\
    bgt60_log.init();\
}

#define BGT60_LOG_DEINIT()\
{\
    bgt60_log.deinit();\
}

/**
 * @brief BGT60 core logger module
 */
#if (BGT60_CORE_LOGGER_ENABLED == 1)

#define BGT60_LOGGER_SERVICE        "[bgt60]        : "
#define BGT60_LOGGER_COLOR          BGT60_LOGGER_COLOR_GREEN

#define BGT60_LOG_MSG(str)\
{\
bgt60_log.printfModule(str, BGT60_LOGGER_SERVICE, BGT60_LOGGER_COLOR);\
}

#define BGT60_LOG_RETURN(ret)\
{\
    if(0 > ret)\
    {\
        bgt60_log.printfModule("fail with return code %i", BGT60_LOGGER_SERVICE, BGT60_LOGGER_ERROR_COLOR, ret);\
    }\
    else\
    {\
        bgt60_log.printfModule("pass", BGT60_LOGGER_SERVICE, BGT60_LOGGER_COLOR);\
    }\
}

#else

#define BGT60_LOG_MSG(str)      {   }
#define BGT60_LOG_RETURN(ret)   {   }

#endif  /** BGT60_CORE_LOGGER_ENABLED */

/**
 * @brief BGT60 application module
 */
#if (BGT60_APP_LOGGER_ENABLED == 1)

/**
 * Logger color for different error types
 */
#define BGT60_APP_LOGGER_ERROR_COLOR            BGT60_LOGGER_COLOR_RED
#define BGT60_APP_LOGGER_WARNING_COLOR          BGT60_LOGGER_COLOR_LIGHT_YELLOW

#define BGT60_APP_LOGGER_SERVICE                "[bgt60 app]    : "
#define BGT60_APP_LOGGER_COLOR                  BGT60_LOGGER_COLOR_MAGENTA

#define BGT60_APP_LOG_MSG(str)\
{\
    bgt60_log.printfModule(str, BGT60_APP_LOGGER_SERVICE, BGT60_APP_LOGGER_COLOR);\
}

#define BGT60_APP_LOG_VAR(str, var)\
{\
    bgt60_log.printfModule(str, BGT60_APP_LOGGER_SERVICE, BGT60_APP_LOGGER_COLOR, var);\
}

#define BGT60_APP_LOG_RETURN(ret)\
{\
    if(0 > ret)\
    {\
        bgt60_log.printfModule("fail with return code %i", BGT60_APP_LOGGER_SERVICE, BGT60_APP_LOGGER_ERROR_COLOR, ret);\
    }\
    else\
    {\
        bgt60_log.printfModule("pass", BGT60_APP_LOGGER_SERVICE, BGT60_APP_LOGGER_COLOR);\
    }\
}

#else

#define BGT60_APP_LOG_MSG(str)          {   }
#define BGT60_APP_LOG_VAR(str, var)     {   }
#define BGT60_APP_LOG_RETURN(ret)       {   }

#endif /* BGT60_APP_LOGGER_ENABLED */

}

#else

/**
 * Logger not enabled. All macros are empty.
 */

#define BGT60_LOG_INIT()                {   }
#define BGT60_LOG_DEINIT()              {   }

#define BGT60_LOG_MSG(str)              {   }
#define BGT60_LOG_RETURN(ret)           {   }

#define BGT60_APP_LOG_MSG(str)          {   }
#define BGT60_APP_LOG_VAR(str, var)     {   }
#define BGT60_APP_LOG_RETURN(ret)       {   }

#endif /* BGT60_LOGGER_ENABLED */

#endif /* BGT60_LOGGER_HPP */