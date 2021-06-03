/**
 * @file        bgt60-ino.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Arduino API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-ino.hpp"

using namespace bgt60;

/**
 * @brief       Constructor of the Arduino Bgt60 object
 *
 * @param[in]   targetDet Pin number of the target detect pin
 * @param[in]   phaseDet Pin number of the phase detect pin
 * @param[in]   pinMode Desired mode of the board, polling or interrupt driven
 */
Bgt60Ino::Bgt60Ino(uint8_t targetDet, uint8_t phaseDet)
:
Bgt60((tDetPin = new GPIOIno(targetDet, INPUT, GPIO::VLogic_t::NEGATIVE)), (pDetPin = new GPIOIno(phaseDet, INPUT, GPIO::VLogic_t::NEGATIVE)))
{

}

/**
 * @brief       Destructor of the Arduino Bgt60 object
 */
Bgt60Ino::~Bgt60Ino()
{

}

/**
 * @brief       Begin the radar board
 *
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
Error_t Bgt60Ino::begin()
{
    Error_t err = OK;

    err  = init();

    return err;
}

/**
 * @brief       Ends the radar board
 *
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
Error_t Bgt60Ino::end()
{
    Error_t err = OK;

    err = deinit();

    return err;
}