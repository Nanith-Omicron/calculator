/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "inc/sysUtils.h"
#include "inc/display.h"

uint64_t m_renderTime = 0, m_renderElapsedTime = 0;

// Main render function. Called very tick to update teh render buffer.
int render(uint64_t u)
{
    m_renderTime = u;
    uint64_t t_now = to_ms_since_boot(get_absolute_time());
    lcdUpdate(t_now);
    m_renderElapsedTime = t_now - m_renderTime;
}

int systemInit()
{
    // Set clock speed to default 40 mhz
    
    printf("System Init.\n");
    changeClockSpeed(133);
    sleep_ms(50);
    measure_freqs();
}

int main()
{
    stdio_init_all();
    sleep_ms(500);
    systemInit();
    sleep_ms(100);
    lcdInit();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Le Ghanais started.\n");
    sleep_ms(50);

    printf("Main Thread Starting.\n");

    while (true)
    {
        uint64_t update_ms = to_ms_since_boot(get_absolute_time());
        render(update_ms);
       // printf("Used %d to render last frame \n", m_renderElapsedTime);
    }
}