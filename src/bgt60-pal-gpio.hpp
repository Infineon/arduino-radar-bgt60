/**
 * @file        bgt60-pal-gpio.hpp
 * @author		Infineon Technologies AG
 * @brief       Radar BGT60 GPIO Platform Abstraction Layer
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_GPIO_HPP_
#define BGT60_PAL_GPIO_HPP_

#include "bgt60-types.hpp"

namespace bgt60
{

/**
 * @addtogroup pal
 * @{
 */

class GPIO
{
	public:

		/**
		 * @name   Interrupt event
		 * @{
		 */
		enum IntEvent_t
		{
			INT_FALLING_EDGE   = 0,     	/**< Interrupt on falling edge */
			INT_RISING_EDGE    = 1,     	/**< Interrupt on rising edge */
			INT_HIGH = 2,					/**< Interrupt when pin is HIGH */
			INT_LOW = 3,					/**< Interrupt when pin is LOW */
			INT_CHANGE = 4					/**< Interrupt when pin changes its level */
		};
		/** @} */

		/**
		 * @name    Voltage level
		 * @{
		 */
		enum VLevel_t
		{
			GPIO_LOW   = 0,        /**< Level low */
			GPIO_HIGH  = 1         /**< Level high */
		};
		/** @} */

		/**
		 * @name    Voltage logic
		 * @{
		 */
		enum VLogic_t
		{
			NEGATIVE = 1,       /**< Negative logic. 0 on voltage level high, 1 on voltage low */
			POSITIVE = 2,       /**< Positive logic. 1 on voltage level high, 0 on voltage low */
		};
		/** @} */

		/**
		 * @brief       Initializes the GPIO
		 * @return      BGT60 error code
		 * @retval      OK if success
		 */
		virtual Error_t        init        () = 0;

		/**
		* @brief       Deinitializes the GPIO
		* @return      BGT60 error code
		* @retval      OK if success
		 */
		virtual Error_t       deinit      () = 0;

		/**
		 * @brief       Reads the GPIO voltage level
		 * @return      GPIO voltage level
		 * @retval      GPIO_LOW if voltage low
		 * @retval      GPIO_HIGH if voltage high
		 */
		virtual VLevel_t       read        () = 0;

		/**
		 * @brief       Writes the GPIO output voltage level
		 * @param[in]   level  Voltage level
		 * @return      BGT60 error code
		 * @retval      OK if success
		 * @retval      WRITE_ERROR if write error
		 */
		virtual Error_t        write       (VLevel_t level) = 0;

		/**
		 * @brief       Enables the GPIO output according to the GPIO logic
		 *              - Low if negative
		 *              - High if positive
		 * @return      GPIO interrupt event
		 * @retval      OK if success
		 * @retval      WRITE_ERROR if write error
		 */
		virtual Error_t        enable      () = 0;

		/**
		 * @brief       Disables the GPIO output according to the GPIO logic
		 *              - Low if positive
		 *              - High if negative
		 * @return      BGT60 error code
		 * @retval      OK if success
		 * @retval      WRITE_ERROR if write error
		 */
		virtual Error_t        disable     () = 0;

		/**
         * @brief       Enables the GPIO hardware interrupt
         * @param[in]   *cback Function pointer of the interrupt callback
         * @return      BGT60 error code
         * @retval      OK if success
         * @retval      INTF_ERROR if error
         */
        virtual Error_t     enableInt   (void (*cback) (void), IntEvent_t mode) = 0;

		 /**
         * @brief       Disables the GPIO hardware interrupt
         * @return      BGT60 error code
         * @retval      OK if success
         * @retval      INTF_ERROR if disable error
         */
        virtual Error_t     disableInt  () = 0;

		/**
         * @brief       Gets the latest interrupt event
         * @return      GPIO interrupt event
         * @retval      INT_FALLING_EDGE if falling edge event
         * @retval      INT_RISING_EDGE if rising edge event
         */
        virtual IntEvent_t  intEvent    () = 0;
};

}
/** @} */
#endif /** BGT60_PAL_GPIO_HPP_ **/