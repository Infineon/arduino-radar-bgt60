/**
 * @file        gpio-arduino.hpp
 * @brief       Radar BGT 60GHz GPIO Arduino PAL
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_GPIO_INO_HPP_
#define BGT60_PAL_GPIO_INO_HPP_

#include <stdint.h>
#include "bgt60-pal-gpio.hpp"
/**
 * \addtogroup inoPal
 * @{
 */

using namespace bgt60;

class GPIOIno: virtual public GPIO
{
private:
	#define     UNUSED_PIN    0xFF  /**< Unused pin */
	uint8_t     pin;
	uint8_t     mode;
	VLogic_t    logic;

public:
				GPIOIno();
				GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
				~GPIOIno();
	Error_t     init();
	Error_t     deinit();
	VLevel_t    read();
	Error_t     write(VLevel_t level);
	Error_t     enable();
	Error_t     disable();
	Error_t     enableInt(void (*cback) (void), IntEvent_t mode);
	Error_t   	disableInt();
	IntEvent_t  intEvent();
};

/** @} */

#endif /** BGT60_PAL_GPIO_INO_HPP_ **/
