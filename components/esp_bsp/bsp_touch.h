#ifndef __BSP_TOUCH_H__
#define __BSP_TOUCH_H__

#include "driver/i2c_master.h"
#include "esp_lcd_touch_cst816s.h"

/* The CST816D on this board has no dedicated reset/interrupt lines broken
 * out to the MCU — the touch driver runs purely in I2C polling mode. */

#ifdef __cplusplus
extern "C" {
#endif

void bsp_touch_init(i2c_master_bus_handle_t bus_handle);
esp_lcd_touch_handle_t bsp_touch_get_handle(void);

#ifdef __cplusplus
}
#endif

#endif
