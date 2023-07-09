#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "stepper_controller.h"
#include "wifi_driver.h"
#include "rtc_wdt.h"
#include "esp_timer.h"

#define STEP_BLUE GPIO_NUM_21
#define STEP_PINK GPIO_NUM_18
#define STEP_YELLOW GPIO_NUM_19
#define STEP_ORANGE GPIO_NUM_5

// BLUE -> PINK -> YELLOW -> ORANGE
bool full_step_sequence[][4] = {
    {true, false, false, false},
    {false, true, false, false},
    {false, false, true, false},
    {false, false, false, true}};

uint8_t current_step = 0;

static void run_stepper(void *arg)
{
    bool *assign = full_step_sequence[current_step];
    gpio_set_level(STEP_BLUE, assign[0]);
    gpio_set_level(STEP_PINK, assign[1]);
    gpio_set_level(STEP_YELLOW, assign[2]);
    gpio_set_level(STEP_ORANGE, assign[3]);
    gpio_set_level(GPIO_NUM_2, 1);
    current_step++;
    if (current_step > 3)
        current_step = 0;
}

extern "C" void
app_main(void)
{
    gpio_set_direction(STEP_BLUE, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_PINK, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_YELLOW, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP_ORANGE, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t stepper_timer_args = {
        .callback = &run_stepper,
        .arg = (void *)nullptr,
        .name = "stepper"};
    esp_timer_handle_t stepper_timer;

    ESP_ERROR_CHECK(esp_timer_create(&stepper_timer_args, &stepper_timer));

    ESP_ERROR_CHECK(esp_timer_start_periodic(stepper_timer, 2200));

    for (;;)
    {
        vTaskDelay(1);
    }
}
