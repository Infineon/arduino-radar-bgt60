/**
 * @file        bgt60.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_HPP_
#define BGT60_HPP_

#include "bgt60-conf.hpp"
#include "bgt60-pal-gpio.hpp"
#include <stdint.h>

using namespace bgt60;

/**
 * \addtogroup bgt60api
 * @{
 */

class Bgt60
{
    public:

        /**
         * @brief States of motion
         */
        enum Motion_t
        {
            NO_MOTION       = 1,        /**< No presence */
            MOTION          = 2         /**< Presence */
        };

        /**
         * @brief States of direction
         */
        enum Direction_t
        {
            NO_DIR          = 0,        /**< No direction due to no motion */
            APPROACHING     = 1,        /**< Target approaching */
            DEPARTING       = 2         /**< Target departing */
        };

                    Bgt60(GPIO *tDet, GPIO *pDet);
                    ~Bgt60();
        Error_t     init();
        Error_t     deinit();
        Error_t     getMotion(Motion_t &motion);
        Error_t     getDirection(Direction_t &direction);
        Error_t     enableInterrupt(void (*cback) (void));
        Error_t     disableInterrupt(void);

    private:

        GPIO       * tDet;
        GPIO       * pDet;
};

/** @} */

#endif /** BGT60_HPP_ **/