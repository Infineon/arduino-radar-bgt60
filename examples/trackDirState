/*!
 * \name        trackDirState
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the change in state of direction of a moving object
 * \details     This example demonstrates how to track the change in state of direction of a moving object
 *              alongwith the timestamp while the BGT60LTR11AIP shield is connected to Arduino compatible
 *              boards.
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

#include "timer.h"

using namespace bgt60;
/*
* In case no supported platform is defined, the
* PD and TD pin are set to the values below.
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

/* Initialize the variable to 'NO_DIR' to be able to record new events */
Bgt60::Direction_t lastDirection = Bgt60::NO_DIR;
Bgt60::Direction_t presentDirection = Bgt60::NO_DIR;

/* Begin setup function - takes care of initialization and executes only once post reset */
void setup()
{
    /* Set the baud rate for sending messages to the serial monitor */
    Serial.begin(9600);
    
    // Configures the GPIO pins to input mode
    Error_t init_status = radarShield.init();
    
    // Initialize software timer 
    timerInit();

    // Start the timer
    timerStart();

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
    String readableTime;

    /* The getDirection() API does two things:
        1. Returns the success or failure to detect direction of object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "presentDirection" variable. Events can be: APPROACHING, DEPARTING or NO_DIR */
    Error_t err = radarShield.getDirection(presentDirection);

    /* Check if API execution is successful */
    if(err == OK)
    {
        if(true == getPdHasChanged())
        {
            readableTime = getPdTimeStamp();

            Serial.print("State of Direction changed at : ");
            Serial.println(readableTime);

            Serial.print("Previous Direction   :   ");
            Serial.println(lastDirection);
            Serial.print("Current Direction   :   ");
            Serial.print(presentDirection);

            lastDirection = presentDirection;
        }
        else
            Serial.println("No change in direction");
    }
    /*  API execution returned error */
    else {
        Serial.println("Error occurred!");
    }

    /* Reducing the frequency of the measurements */
    delay(500);
}

/**
 *  @brief  This function checks if the direction has changed since last readout. 
 *          If changed, it sets the flag 'dirChanged' to 'true'
 *  @return 'true' or 'false' based on change in state of direction
 */
bool getPdHasChanged(){
  bool dirChanged = false;

  if(lastDirection != presentDirection)
    dirChanged = true;
  else
    dirChanged = false;

  return dirChanged;
}

/**
 *  @brief  This function allows you to get the time elapsed since the start of timer
 *          and converts it into 'dd:hh:mm:ss' format
 *  @return Readable time in string type
 */
String getPdTimeStamp() {
  String readableTime;
  uint32_t elapsedTime_ms;
  
  unsigned long currentMillis;
  unsigned long seconds;
  unsigned long minutes;
  unsigned long hours;
  unsigned long days;

  // Get time elapsed since start
  timeElapsed(elapsedTime_ms);

  // Convert elapsed time to readable format
  currentMillis = elapsedTime_ms;
  seconds = currentMillis / 1000;
  minutes = seconds / 60;
  hours = minutes / 60;
  days = hours / 24;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  if (days > 0) {
    readableTime = String(days) + " ";
  }

  if (hours > 0) {
    readableTime += String(hours) + ":";
  }

  if (minutes < 10) {
    readableTime += "0";
  }
  readableTime += String(minutes) + ":";

  if (seconds < 10) {
    readableTime += "0";
  }
  readableTime += String(seconds) + " ago";

  return readableTime;
}