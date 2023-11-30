#include "sd_fat.h"

static const char *TAG = "TF_card";
static const char mount_point[] = MOUNT_POINT;     /* 挂载点：根目录 */
bool sdcard_cd_state;

#define SPI_DMA_CHAN    1

#define PIN_NUM_MISO    19
#define PIN_NUM_MOSI    23
#define PIN_NUM_CLK     18
#define PIN_NUM_CS      5
#define PIN_NUM_CD      17

sdmmc_card_t *card;                         /* SD/MMC卡信息结构 */

esp_err_t sd_card_init(void)
{
    esp_err_t ret;

    /* 文件系统挂载配置 */
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false, /* 如果挂在失败：fasle不会重新分区和格式化 */
        .max_files = 5,                         /* 打开文件最大数量 */
        .allocation_unit_size = 16 * 1024,    
    };

    ESP_LOGI(TAG, "Initializing SD Card");

    /* SD SPI主机默认属性配置 */
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = VSPI_HOST;  /* 默认配置为 HSPI_HOST,需更改为 VSPI_HOST */

    /* spi总线配置 */
    spi_bus_config_t bus_config = {
        .mosi_io_num = PIN_NUM_MOSI,                    /* MOSI信号线端口 */
        .miso_io_num = PIN_NUM_MISO,                    /* MISO信号线端口 */
        .sclk_io_num = PIN_NUM_CLK,                     /* CLK 信号线端口 */
        .quadwp_io_num = -1,                            /* 不使用 */
        .quadhd_io_num = -1,                            /* 不使用 */
        .max_transfer_sz = 4 * 1024 * sizeof(uint8_t)   /* 最大传输数据大小（字节） */
    };

    /* spi总线初始化 */
    ret = spi_bus_initialize(host.slot, &bus_config, host.slot);
    if(ret != ESP_OK)
    {
        ESP_LOGI(TAG, "Failed to initialize bus.");
        return ret;
    }
    ESP_LOGI(TAG, "host slot (SPI%d)", host.slot);

    /* sd spi设备配置 */
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;           /* CS片选信号线端口 */
    slot_config.gpio_cd = PIN_NUM_CD;           /* SD插拔检测信号线端口 */
    slot_config.host_id = host.slot;            /* 主机ID */

    /* 挂载文件系统 */
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config,
                                     &mount_config, &card);
    if(ret != ESP_OK)
    {
        if(ret == ESP_FAIL)
        {
            ESP_LOGI(TAG, "Failed to mount filesystem."
                "If you want to card to be formatted,"
                "set the EXAMOLE_FORMAT_IF_MOUNT_FAILERD menuconfig option.");
        }
        else
        {
            ESP_LOGI(TAG, "Failed to initialize the card (%s)."
                "Make sure SD card lines have pull-up resistors in place.", 
                esp_err_to_name(ret));
        }

        return ESP_FAIL;
    }

    /* SD卡已初始化，打印SD卡属性 */
    sdmmc_card_print_info(stdout, card);

    return ESP_OK;
}

/* 获取sd卡总容量和剩余容量 */
void get_sdcard_total_and_free_capacity(uint32_t *fre_sect, uint32_t *tot_sect)
{
    FATFS *fs;
    DWORD fre_clust, free, total;

    f_getfree(mount_point, &fre_clust, &fs);

    total = (fs->n_fatent - 2) * fs->csize / 2 / 1024;
    free = fre_clust * fs->csize / 2 / 1024;

    *fre_sect = free;
    *tot_sect = total;
}