/* --------------------------------------------------------------
   Application: 01 - Rev1
   Release Type:
   Class: Real Time Systems - Fa 2025
   AI Use: AutoFill comments, variable names, and function names
   Student Name: Henry Abshire
   Context: Helathcare heart rate monitor 
---------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

void longprint()
{
    printf("Status: system running\t");

    // Delay ~1000 ms for next print (and LED toggle)
    vTaskDelay(pdMS_TO_TICKS(10000));
}

void read_Heart_Rate(void *pvParameter)
{
    unsigned long previous_time = 0;
    while(1){
        //according to the interwebs, heart rate monitors typically update every 1 second so I updated delays to flick on and off once every second
        printf("LOG: Heart rate read period: %lu ms\n", xTaskGetTickCount()*portTICK_PERIOD_MS - previous_time); //print peroid to console
        previous_time = xTaskGetTickCount()*portTICK_PERIOD_MS; //updates last time
        gpio_set_level(LED_PIN, 1); //this is the equavlent to digitalWirte(LED_PIN, HIGH);
        printf("Heart Rate mesure Time:%lu ms\n", (unsigned long)(xTaskGetTickCount()*portTICK_PERIOD_MS)); //logs timing details of led task
        vTaskDelay(pdMS_TO_TICKS(500)); //pdMS_TO_TICKS converts milliseconds to ticks which keeps everything standard in RTS
        gpio_set_level(LED_PIN, 0);     // this is the equavlent to digitalWirte(LED_PIN, HIGH);
        printf("Heart Rate mesure Time:%lu ms\n", (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS)); // logs timing details of led task
        vTaskDelay(pdMS_TO_TICKS(500)); // pdMS_TO_TICKS converts milliseconds to ticks which keeps everything standard in RTS 

    }
}

void print_system_running(void *pvParameter)
{
    unsigned long previous_time = 0;
    while(1){
        printf("LOG: Print Task time peroid: %lu ms\n", xTaskGetTickCount()*portTICK_PERIOD_MS - previous_time);
        previous_time = xTaskGetTickCount()*portTICK_PERIOD_MS; //updates last time
        printf("System alive, time=%lu ms\n", (unsigned long)(xTaskGetTickCount()*portTICK_PERIOD_MS)); //xTaskGetTickCount gets the number of ticks from the last time the scheduler was called
        //printf("System alive, time=%lu mssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n", (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS)); // xTaskGetTickCount gets the number of ticks from the last time the scheduler was called                                                                                                  // portTick_Period_MS converts ticks to millseconds, so we are getting the number of ticks since last called and converting to ms
        vTaskDelay(pdMS_TO_TICKS(10000));
        //vTaskDelay(pdMS_TO_TICKS(20000)); //increase the delay
    }
}

void app_main()
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    xTaskCreate(read_Heart_Rate, "read_Heart_Rate", 2048, NULL, 1, NULL);
    //xTaskCreate(print_task, "PrintTask", 2048, NULL,1,NULL); 
    xTaskCreate(print_system_running, "print system_running", 2048, NULL, 2, NULL); // Give print task higher priority so it can preempt the blink task if needed

}
