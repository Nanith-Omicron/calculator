// --------------------------------------------------------------------------
// ST7735-library (hw-specific implementations)
//
// If you want to port the library to a different platform, change the
// implementation if necessary. Don't forget to change hw.h too.
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-st7735
// --------------------------------------------------------------------------

#include "hw.h"

void tft_spi_init(cs,dc,rst) {
  gpio_init(cs);
  gpio_set_dir(cs, GPIO_OUT);
  gpio_put(cs, 1);                        // Chip select is active-low

  gpio_init(dc);
  gpio_set_dir(dc, GPIO_OUT);
  gpio_put(dc, 0);                        // Chip select is active-low

  gpio_init(rst);
  gpio_set_dir(rst, GPIO_OUT);
  gpio_put(rst, 0);
}
