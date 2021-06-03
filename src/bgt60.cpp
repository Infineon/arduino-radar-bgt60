/**
 * @file        bgt60.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60.hpp"
#include "bgt60-logger.hpp"

using namespace bgt60;

/**
 * @brief           Radar Bgt60 constructor
 *
 * @details         This is the constructor of the Radar BGT60 board. The user has to pass the two
 *                  desired pins for reading out the radar data, as well as the mode in which the board
 *                  should acquire the data.
 *
 * @param[in]       *tDet           Instance of a GPIO to read the target-detect-pin
 * @param[in]       *pDet           Instance of a GPIO to read the phase-detect-pin
 */
Bgt60::Bgt60(GPIO *tDet, GPIO *pDet) : tDet(tDet), pDet(pDet)
{

}

/**
 * @brief           Radar Bgt60 destructor
 */
Bgt60::~Bgt60()
{

}

/**
 * @brief           Initialize the Bgt60 class object
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 * @pre             None
 */
Error_t Bgt60::init()
{
    Error_t err = OK;

    BGT60_LOG_INIT();
    BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        err = pDet->init();
        if(err != OK)
            break;

        err = tDet->init();
        if(err != OK)
            break;
    } while (0);
    BGT60_LOG_RETURN(err);

    return err;
}

/**
 * @brief           De-Initialize the Bgt60 class object
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 * @pre             init()
 */
Error_t Bgt60::deinit()
{
    Error_t err = OK;

   BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        err = pDet->deinit();
        if(err != OK)
            break;

        err = tDet->deinit();
        if(err != OK)
            break;
    } while (0);
    BGT60_LOG_RETURN(err);
    BGT60_LOG_DEINIT();

    return err;
}

/**
 * @brief           Read out target-detect-pin
 *
 * @details         This function reads out the target-detect-pin. Depending on the choosen mode
 *                  of the board it is either actively polling the status of the pin or mapping
 *                  an interrupt to the corresponding pin.
 *
 * @note            If you're using the interrupt mode of the board just call this function once
 *                  in the setup(). For each object of the BGT60 this function can be called once.
 *                  Calling it more often can lead to undesired behavior of the radar board.
 *
 * @param[in,out]   motion This variable stores the actual state of the target-detect-pin
 *                  Possible Values:
 *                      - NO_MOTION
 *                      - MOTION
 *
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 * @pre             init()
 */
Error_t Bgt60::getMotion(Motion_t &motion)
{
    Error_t err = OK;

    BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        GPIO::VLevel_t level = tDet->read();

        if(GPIO::VLevel_t::GPIO_LOW == level)
        {
            motion = MOTION;
        }
        else if(GPIO::VLevel_t::GPIO_HIGH == level)
        {
            motion = NO_MOTION;
        }

    } while (0);
    BGT60_LOG_RETURN(err);

    return err;
}

/**
 * @brief           Read out phase-detect-pin
 *
 * @details         This function reads out the phase-detect-pin. Depending on the choosen mode
 *                  of the board it is either actively polling the status of the pin or mapping
 *                  an interrupt to the corresponding pin.
 *
 * @note            If you're using the interrupt mode of the board just call this function once
 *                  in the setup(). For each object of the BGT60 this function can be called once.
 *                  Calling it more often can lead to undesired behavior of the radar board.
 *
 * @param[in,out]   direction This variable stores the actual state of the phase-detect-pin
 *                  Possible Values:
 *                      - NO_DIR
 *                      - APPROACHING
 *                      - DEPARTING
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 * @pre             init()
 */
Error_t Bgt60::getDirection(Direction_t &direction)
{
    Error_t err = OK;
    Motion_t motion = NO_MOTION;

    BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        err = getMotion(motion);
        if(OK != err)
            break;

        if(MOTION == motion)
        {
            GPIO::VLevel_t level = pDet->read();                                  

            if(GPIO::VLevel_t::GPIO_LOW == level)
            {
                direction = DEPARTING;
            }
            else if(GPIO::VLevel_t::GPIO_HIGH == level)
            {
                direction = APPROACHING;
            }
        }
        else 
        {
            direction = NO_DIR;
        }

    } while (0);
    BGT60_LOG_RETURN(err);

    return err;
}

/**
 * @brief       Enables the hardware interrupt
 * 
 * @param[in]   *cback  Pointer to the interrupt callback function 
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if interface error
 * @pre         init()
 */
Error_t Bgt60::enableInterrupt(void (*cback) (void))
{
    Error_t err = OK;

    BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        if(nullptr == cback)
        {
            err = CONF_ERROR;
            break;
        }
        
        err = tDet->enableInt(cback, GPIO::INT_CHANGE);
        if(OK != err)
            break;

        err = pDet->enableInt(cback, GPIO::INT_CHANGE);  
        if(OK != err)
            break;
        
    } while (0);
    BGT60_LOG_RETURN(err);

    return err;
}

/**
 * @brief       Disables the hardware interrupt
 * 
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if interface error
 * @pre         init()
 */
Error_t Bgt60::disableInterrupt(void)
{
   Error_t err = OK;

    BGT60_LOG_MSG(__FUNCTION__);
    do
    {
        err = tDet->disableInt();
        if(OK != err)
            break;

        err = pDet->disableInt();  
        if(OK != err)
            break;

    } while (0);
    BGT60_LOG_RETURN(err);

    return err;
}

