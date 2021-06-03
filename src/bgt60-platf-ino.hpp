/**
 * @file        bgt60-platf-ino.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 platform definitions
 * @details     This file is defining the standard pins for the corresponding
 *              platform. Please make sure to connect your chosen board to pins
 *              mentioned here. Otherwise the functionality of the library can not
 *              be guaranteed. There is also the possibility to changes these pins
 *              either in this file or directly in the sketch. But make sure you're
 *              using the correct pins and in case you want to use the interrupt
 *              function, you also have to make sure the pins you chose are interrupt
 *              capable.
 *
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PLATF_INO_HPP_
#define BGT60_PLATF_INO_HPP_

#include <Arduino.h>

/**
 * \addtogroup platfIno
 * @{
 */

#ifdef ARDUINO_SAMD_MKR1000                 /**< Arduino MKR1000 */

#define TD  16
#define PD  17

#elif defined(ARDUINO_SAMD_MKRWIFI1010)     /**< Arduino MRK WIFI 1010 */

#define TD  16
#define PD  17

#elif defined(ARDUINO_AVR_UNO)              /**< Arduino Uno */

#define TD  2
#define PD  3

#elif defined(XMC1100_Boot_Kit)             /**< XMC1100 Boot Kit */

#define TD  2
#define PD  3

#elif defined(XMC4700_Relax_Kit)            /**< XMC4700 Relax Kit */

#define TD  2
#define PD  3

#else
#warning "You did not define a supported platform! \
Please make sure you're using a platform that is officially \
supported by the library. Have a look in the Wiki for more information."

#endif

#endif /** BGT60_PLATF_INO_HPP_ */