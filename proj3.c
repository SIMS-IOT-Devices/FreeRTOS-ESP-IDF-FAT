#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"

static const char *TAG = "FAT";
// Handle of the wear levelling library instance
static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;
// Mount path for the partition
const char *base_path = "/spiflash";

void app_main(void)
{
    // Setup FAT file system
    ESP_LOGI(TAG, "Mounting FAT filesystem");
    const esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE};
    esp_err_t err = esp_vfs_fat_spiflash_mount_rw_wl(base_path, "storage", &mount_config, &s_wl_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
        return;
    }

    // Write file
    ESP_LOGI(TAG, "Opening file");
    FILE *f = fopen("/spiflash/hello.txt", "w");
    fprintf(f, "Written using ESP-IDF\n");
    fclose(f);
    ESP_LOGI(TAG, "File written");

    // Read file
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/spiflash/hello.txt", "r");
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);

    // Print data
    char *pos = strchr(line, '\n');
    if (pos)
    {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Data from file: '%s'", line);

    // Unmount FATFS
    ESP_LOGI(TAG, "Unmounting FAT filesystem");
    esp_vfs_fat_spiflash_unmount_rw_wl(base_path, s_wl_handle);
    ESP_LOGI(TAG, "Done");
}