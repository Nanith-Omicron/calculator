#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"


#define MAX_CLOCK_SPEED_MHZ 133
extern bool m_overclocked;


extern void measure_freqs(void);
extern int changeClockSpeed(int m);