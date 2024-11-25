#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core

#include "driver_passive_buzzer.h"

static TimerHandle_t g_TimerSound;

static void buzzer_Callback(void)
{
    PassiveBuzzer_Control(0);
}

void buzzer_init(void)
{
    
    PassiveBuzzer_Init();
    g_TimerSound = xTimerCreate("BGM", 100, pdFALSE, NULL, buzzer_Callback);
}

void buzzer_buzz(int freq, int time_ms)
{   
    xTimerChangePeriod(g_TimerSound ,time_ms, 0);
    PassiveBuzzer_Set_Freq_Duty(freq, 50);
}



