/*!
 * \name        motionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object
 * \details     This example demonstrates how to detect a moving object while the
 *              BGT60LTR11AIP shield is connected to Arduino compatible
 *              boards using polling method.
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

/* Begin setup function - takes care of initializations and executes only once post reset */
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
}

/* Begin loop function - this part of code is executed continuously until external termination */
void loop()
{
    /* Initialize the variable to NO_MOTION to be able to record new events */
    Bgt60::Motion_t motion = Bgt60::NO_MOTION;

   /* The getMotion() API does two things:
        1. Returns the success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "motion" variable. Events can be: NO_MOTION or MOTION */
    Error_t err = radarShield.getMotion(motion);

    /* Check if API execution is successful */
    if(err == OK)
    {
        /* Cases based on value set in motion variable */
        switch (motion)
        {
            /* Variable "motion" is set to MOTION when moving target is detected */
            case Bgt60::MOTION:
                Serial.println("Target in motion detected!");
                break;
            /*  Variable "motion" is set to NO_MOTION when moving target is not present */
            case Bgt60::NO_MOTION:
                Serial.println("No target in motion detected.");
                break;
        }
    }
    /*  API execution returned error */
    else {
        Serial.println("Error occurred!");
    }

    /* Reducing the frequency of the measurements */
    delay(500);
}