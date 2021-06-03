/** 
 * @file        gpio-arduino.cpp
 * @brief       Radar BGT60 Arduino PAL Implementation 
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-pal-gpio-ino.hpp"
#include <Arduino.h>

/**
 * @brief 		Constructor of the Arduino GPIO class
 * @details		This function is setting the basics for a GPIO.
 */
GPIOIno::GPIOIno() : pin(0), mode(OUTPUT), logic(POSITIVE)
{

}

/**
 * @brief 		Constructor of the Arduino GPIO class
 * @details		This function is setting the basics for a GPIO. It allows to set the pin number,
 * 				mode of the pin and the logic level.
 * @param[in]   pin     Number of the desired pin
 * @param[in]   mode    Defines the mode of the pin (INPUT, OUTPUT, etc.)
 * @param[in]   logic   Defines the logic level of the pin
 */
GPIOIno::GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic): pin(pin), mode(mode), logic(logic)
{

}
/**
 * @brief 		Initialize the GPIO
 * @details		This function is initializing the chosen pin.
 * @return      BGT60 error code
 * @retval		OK
 */
Error_t GPIOIno::init()
{
	pinMode(this->pin, this->mode);
	return OK;
}

/**
 * @brief 		Deinitialize the GPIO
 * @details		This function is deinitializing the chosen pin.
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::deinit()
{
	return OK;
}

/**
 * @brief 		Read GPIO logic level
 * @details		This function reads the logic level of the chosen pin and
 * 				returns the logic level value.
 * @return      GPIOIno::VLevel_t
 * @retval      0    = GPIO_LOW
 * @retval      1    = GPIO_HIGH
 */
GPIOIno::VLevel_t GPIOIno::read()
{
	return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief 		Set GPIO logic level
 * @details		This functions sets the logic level of the chosen pin.
 * @param[in]   level   Desired logic level of the pin
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::write(VLevel_t level)
{
	digitalWrite(this->pin, level);
	return OK;
}

/**
 * @brief 		Enable the GPIO
 * @details		This functions enable the chosen pin. Depending on the chosen logic of the pin
 * 				it sets the right logic level of the pin.
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::enable()
{
	if(this->logic == POSITIVE){
		digitalWrite(this->pin, GPIO_HIGH);
	}
	else if(this->logic == NEGATIVE){
		digitalWrite(this->pin, GPIO_LOW);;
	}
	return OK;
}

/**
 * @brief 		Disable the GPIO
 * @details		This functions disables the chosen pin. Depending on the chosen logic of the pin
 * 				it sets the right logic level of the pin.
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::disable()
{
	if(this->logic == POSITIVE){
		digitalWrite(this->pin, GPIO_LOW);
	}
	else if(this->logic == NEGATIVE){
		digitalWrite(this->pin, GPIO_HIGH);
	}
	return OK;
}

/**
 * @brief       Enables the Arduino GPIO interrupt
 * @details		This function enables the interrupt on chosen pin. Depending on the mode,
 * 				it triggers the interrupt.
 * @param[in]   *cback  	Function pointer of the interrupt callback
 * @param[in]   mode	  	Event at which the interrupt will occur
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::enableInt(void (*cback) (void), IntEvent_t mode)
{
	switch(mode)
	{
		case INT_FALLING_EDGE:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, FALLING);
			break;

		case INT_RISING_EDGE:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, RISING);
			break;

		case INT_HIGH:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, HIGH);
			break;
		
		case INT_LOW:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, LOW);
			break;

		case INT_CHANGE:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, CHANGE);
			break;

		default:
			attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())cback, LOW);
	}
    
    return OK;
}

/**
 * @brief       Disables the Arduino GPIO interrupt
 * @details		This function disables the interrupt on chosen pin.
 * @return      BGT60 error code
 * @retval      OK
 */
Error_t GPIOIno::disableInt()
{
	detachInterrupt(digitalPinToInterrupt(this->pin));
    return OK;
}

/**
 * @brief   	Gets the latest Arduino interrupt event 
 * @details		This function gets the latest interrupt event on the earlier configured
 *              GPIO pin.
 * @return  	GPIO interrupt event
 * @retval  	INT_FALLING_EDGE if falling edge event
 * @retval  	INT_RISING_EDGE if rising edge event
 */
inline GPIOIno::IntEvent_t GPIOIno::intEvent()
{
    IntEvent_t edge = INT_FALLING_EDGE;
    
    int val = digitalRead(this->pin);
    if(val == LOW)
    {
        edge = INT_FALLING_EDGE;
    }
    else if(val == HIGH) 
    {
        edge = INT_RISING_EDGE;
    }
    return edge;
}

