#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "stepper_controller.h"
#include "wifi_driver.h"

extern "C" void app_main(void)
{
    printf("Hello world!\n");
}
