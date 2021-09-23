#include <stdint.h>
#include <Arduino.h>

uint32_t curTime;

/**
 * @brief   Initialiazes the Arduino timer
 */
inline void timerInit()
{
    curTime = 0;
}

/**
 * @brief   Starts the Arduino timer
 */
inline void timerStart()
{
    curTime = micros();
}

/**
 * @brief       Calculates elapsed time since the timer was started
 * @param[out]  elapsed Time in milliseconds
 */
inline void timeElapsed(uint32_t & elapsed)
{
    elapsed = (uint32_t)((micros() - curTime)/1000);
}
