/**
 * @file        bgt60-logger.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Logger
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-logger.hpp"

#if(BGT60_LOGGER_ENABLED == 1)

using namespace bgt60;

#define LOGGER_NEW_LINE_CHAR          0x0D, 0x0A
#define LOGGER_MAX_WRITE_BUFF         400

Logger::Logger()
{
    logpal  = NULL;
}

Logger::~Logger()
{

}

Logger::Logger(LoggerPAL *logpal)
:logpal(logpal)
{

}

void Logger::init()
{
    logpal->init();
}

void Logger::deinit()
{
    logpal->deinit();
}

void Logger::print(const char * format, ...)
{
    va_list args;
    char    str_buffer[LOGGER_MAX_WRITE_BUFF];

    if(NULL == format)
    {
        return;
    }

    va_start(args, format);

    vsprintf(str_buffer, format, args);

    va_end(args);

    logpal->write((const uint8_t *)str_buffer, strlen(str_buffer));
}

void Logger::printfModule(const char * format,
                          const char * module,
                          const char * color,
                          ...)
{
    va_list args;
    uint8_t new_line_characters[2] = {LOGGER_NEW_LINE_CHAR};
    char    color_buffer[LOGGER_MAX_WRITE_BUFF + 200] = {0};
    char    temp_buffer[LOGGER_MAX_WRITE_BUFF] = {0};


    if ((NULL == format) || (NULL == module) || (NULL == color))
    {
        return;
    }
    va_start(args, color);

    vsprintf(temp_buffer, format, args);

    sprintf(color_buffer,
            "%s%s%s%s",
            color,
            module,
            temp_buffer,
            BGT60_LOGGER_COLOR_DEFAULT);
    logpal->write((const uint8_t *)color_buffer, strlen(color_buffer));
    logpal->write(new_line_characters, 2);

    va_end(args);
}

void Logger::printModuleHex(const uint8_t  * vector,
                                  uint32_t   length,
                            const char     * module,
                            const char     * color)
{
    char     temp_buffer[LOGGER_MAX_WRITE_BUFF-200] = {0};
    uint32_t i;

    if(NULL == vector || length < 1)
    {
        return;
    }

    for(i = 0; i < length; i++)
    {
        sprintf(&temp_buffer[3*i],"%02x ", vector[i]);
    }

    temp_buffer[3*i] = '\0';

    printfModule(temp_buffer, module, color);
}

#endif /* BGT60_LOGGER_ENABLED */