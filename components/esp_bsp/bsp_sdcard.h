#ifndef __BSP_SDCARD_H_
#define __BSP_SDCARD_H_
#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/sdmmc_defs.h"
#include "driver/gpio.h"
#include <stdio.h>

/* SD card over SPI — shares the SPI bus (BSP_SPI_HOST, bsp_display.h) with
 * the LCD. Only the chip-select line is dedicated to the card. */
#define BSP_PIN_SD_CS     GPIO_NUM_41

#ifdef __cplusplus
extern "C" {
#endif

void bsp_sdcard_init(void);
uint64_t bsp_sdcard_get_size(void);

#ifdef __cplusplus
}
#endif


#endif
