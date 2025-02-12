#include "i2c_manager.h"

 esp_err_t i2c_master_init(void)
{

    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {.clk_speed = I2C_MASTER_FREQ_HZ},
    };

    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


 esp_err_t i2c_manager_read(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(i2c_num, dev_addr, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

 esp_err_t i2c_manager_write(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr, data};
    ret = i2c_master_write_to_device(i2c_num, dev_addr, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
    return ret;
}

 esp_err_t i2c_manager_only_read(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t *data, size_t len)
{
    return i2c_master_read_from_device(i2c_num, dev_addr,data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}
 esp_err_t i2c_manager_only_write(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t *data, size_t len)
{
     return i2c_master_write_to_device(i2c_num, dev_addr, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}