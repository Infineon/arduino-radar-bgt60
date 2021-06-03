/**
 * @file        bgt60-pal-timer.hpp
 * @author      Infineon Technologies AG
 * @brief       RADAR BGT60 Timer Platform Abstraction Layer
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_TIMER_HPP_
#define BGT60_PAL_TIMER_HPP_

#include <stdint.h>
#include "bgt60-types.hpp"

namespace bgt60
{

/**
 * @addtogroup pal
 * @{
 */

class Timer
{
    public:

        /**
         * @brief       Initialiazes the timer
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         init           () = 0;

        /**
         * @brief       Deinitialiazes the timer
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         deinit         () = 0;

        /**
         * @brief       Starts the timer
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         start          () = 0;

        /**
         * @brief       Elapsed time since the timer was started in milliseconds
         * @param[out]  elapsed Time in milliseconds
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         elapsed        (uint32_t & elapsed) = 0;

        /**
         * @brief       Elapsed time since the timer was started in microseconds
         * @param[out]  elapsed Time in microseconds
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         elapsedMicro   (uint32_t & elapsed) = 0;

        /**
         * @brief       Stops the timer
         * @return      BGT60 error code
         * @retval      OK if success
         */
         virtual  Error_t         stop          () = 0;

        /**
         * @brief       Introduces a delay during the specified time
         * @param[in]   timeout    Delay time in milliseconds
         * @return      BGT60 error code
         * @retval      OK if success
         */
        virtual  Error_t         delay   (const uint32_t timeout) = 0;
};

/** @} */

}
#endif /** BGT60_PAL_TIMER_HPP_ **/