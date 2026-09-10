
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "nvs_flash.h"

#include "esp_check.h"
#include "esp_log.h"

#include "bsp_display.h"
#include "bsp_sdcard.h"

sdmmc_card_t *card = NULL;

static const char *TAG = "bsp_sdcard";

uint64_t bsp_sdcard_get_size(void)
{
    uint64_t sdcard_size = 0;
    if (card != NULL)
    {
        sdcard_size = ((uint64_t)card->csd.capacity) * card->csd.sector_size;
    }
    return sdcard_size;
}

void bsp_sdcard_init(void)
{
    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};
    const char mount_point[] = "/sdcard";
    ESP_LOGI(TAG, "Initializing SD card");

    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.

    ESP_LOGI(TAG, "Using SPI peripheral");

    // The SD card lives on the same SPI bus as the LCD (BSP_SPI_HOST). That
    // bus is already initialized by bsp_display_init() — DO NOT call
    // spi_bus_initialize() again here, esp_vfs_fat_sdspi_mount() just
    // attaches a new device (chip select) to the existing bus.
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = BSP_SPI_HOST;

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = BSP_PIN_SD_CS;
    slot_config.host_id = host.slot;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                          "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                          "Make sure SD card lines have pull-up resistors in place.",
                     esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
}
