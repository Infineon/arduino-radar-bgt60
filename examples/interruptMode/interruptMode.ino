/*!
 * \name        interruptMode
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example shows how to use the interrupt functionality
 * \details     This example demonstrates how to detect motion and the direction
 *              of a moving object with the help of interrupts while the BGT60LTR11AIP
 *              shield is connected to Arduino compatible boards.
 *
 *              Connection details:
 *              --------------------------------------------------
 *              Pin on shield   Connected to pin on Arduino
 *              --------------------------------------------------
 *              TD                  depends on Arduino board
 *              PD                  depends on Arduino board
 *              GND                 GND
 *              Vin                 VCC (3.3V or 5V - depends on Arduino board)
 *              --------------------------------------------------
 *
 *              Decoding on-board LED output of BGT60LTR11AIP shield:
 * 
 *              - Red LED indicates the output of direction of motion once target is detected (PD)
 *              ---------------------------------------------
 *              LED    State    Output explanation
 *              ---------------------------------------------
 *              Red     ON       Departing target
 *                      OFF      Approaching target
 *              ---------------------------------------------
 *
 *              - Green LED indicates the output of target in motion detection (TD)
 *              ---------------------------------------------
 *              LED    State    Output explanation
 *              ---------------------------------------------
 *              Green    ON       Moving target detected
 *                       OFF      No target detected
 *              ---------------------------------------------
 *
 * SPDX-License-Identifier: MIT
 */

#include <Arduino.h>
/* Include library main header */
#include <bgt60-ino.hpp>
/* Include Arduino platform header */
#include <bgt60-platf-ino.hpp>

/*
* In case no supported platform is defined, the
* PD and TD pin will be set to the values below.
*/
#ifndef TD
#define TD  15
#endif

#ifndef PD
#define PD  16
#endif

/* Create radar object with following arguments:
 *  TD : Target Detect Pin
 *  PD : Phase Detect Pin */
Bgt60Ino radarShield(TD, PD);

/* Definition and initialization of the interrupt active flag */
volatile static bool intActive = false;

/* User defined callback function */
void cBackFunct(void)
{
    if ( ! intActive ) {

        /* Set the interrupt active flag to avoid parallel execution of this function multiple times. */
        intActive = true;

        /* Create variables to store the state of the motion as well as the direction */
        Bgt60::Motion_t motion = Bgt60::NO_MOTION;
        Bgt60::Direction_t direction = Bgt60::NO_DIR;

        /* Now check what happend, first check if a motion was detected or is
        not detected anymore */
        Error_t err = radarShield.getMotion(motion);

        /* Check if API execution is successful */
        if(OK == err)
        {
            /* In case motion is detected */
            if(Bgt60::MOTION == motion){
                Serial.println("Target in motion was detected!");

                /* Check the direction of the detected motion */
                err = radarShield.getDirection(direction);
                if(OK == err)
                {
                    /* In case the target is approaching */
                    if(Bgt60::APPROACHING == direction){
                        Serial.println("The target is approaching!");
                    }
                    /* In case the target is departing */
                    else{
                        Serial.println("The target is departing!");
                    }
                }
                /* API execution returned error */
                else{
                    Serial.println("Error has occurred during the determination of the direction!");
                }
            }
            /* No motion is detected */
            else{
                Serial.println("No target in motion detected!");
            }
        }
        /* API execution returned errord */
        else {
            Serial.println("Error has occurred during the determination of the direction!");
        }

        Serial.println("\n--------------------------------------\n");

        /* Release the interrupt active flag to allow a new call of this callback function. */
        intActive = false;
    }
}

/* Begin setup function - take care of initializations and executes only once post reset */
void setup()
{
    /* Set the baud rate for sending messages to the serial monitor */
    Serial.begin(9600);

    // Configures the GPIO pins to input mode
    Error_t init_status = radarShield.init();

    /* Check if the initialization was successful */
    if (OK != init_status) {
        Serial.println("Init failed.");
    }
    else {
        Serial.println("Init successful.");
    }

    /* Enable the interrupts */
    init_status = radarShield.enableInterrupt(cBackFunct);
    
    /* Check if the interrupt init was successful */
    if (OK != init_status)
        Serial.println("Interrupt init failed.");
    else
        Serial.println("Interrupt init successful.");
}

/* Beginn loop function - this part of code is executed continuously until external termination */
void loop()
{
    // Here you can do something else in parallel while waiting for an interrupt.
    delay(1000);
}