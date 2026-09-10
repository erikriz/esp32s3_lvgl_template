#include "bsp_touch.h"
#include "bsp_display.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_touch_cst816s.h"
#include "esp_log.h"

static const char *TAG = "bsp_touch";
static esp_lcd_touch_handle_t s_touch_handle = NULL;

void bsp_touch_init(i2c_master_bus_handle_t bus_handle)
{
    ESP_LOGI(TAG, "Initialize touch IO (I2C)");
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG();
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(bus_handle, &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {};
    tp_cfg.x_max = BSP_LCD_NATIVE_H_RES;
    tp_cfg.y_max = BSP_LCD_NATIVE_V_RES;
    tp_cfg.rst_gpio_num = GPIO_NUM_NC;
    tp_cfg.int_gpio_num = GPIO_NUM_NC;

#if BSP_DISPLAY_ROTATION == 90
    tp_cfg.flags.swap_xy = 1;
    tp_cfg.flags.mirror_x = 1;
    tp_cfg.flags.mirror_y = 0;
#elif BSP_DISPLAY_ROTATION == 180
    tp_cfg.flags.swap_xy = 0;
    tp_cfg.flags.mirror_x = 1;
    tp_cfg.flags.mirror_y = 1;
#elif BSP_DISPLAY_ROTATION == 270
    tp_cfg.flags.swap_xy = 1;
    tp_cfg.flags.mirror_x = 0;
    tp_cfg.flags.mirror_y = 1;
#else
    tp_cfg.flags.swap_xy = 0;
    tp_cfg.flags.mirror_x = 0;
    tp_cfg.flags.mirror_y = 0;
#endif

    ESP_LOGI(TAG, "Init touch controller CST816D");
    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_cst816s(tp_io_handle, &tp_cfg, &s_touch_handle));
}

esp_lcd_touch_handle_t bsp_touch_get_handle(void)
{
    return s_touch_handle;
}
