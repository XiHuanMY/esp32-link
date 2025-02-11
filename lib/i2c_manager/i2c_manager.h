#ifndef _I2C_MANAGER_H_
#define _I2C_MANAGER_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "esp_err.h"
#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO           21      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           18      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0           /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000





 esp_err_t i2c_master_init(void);
 esp_err_t i2c_manager_read(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t reg_addr, uint8_t *data, size_t len);
 esp_err_t i2c_manager_write(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t reg_addr, uint8_t data);
 esp_err_t i2c_manager_only_read(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t *data, size_t len);
 esp_err_t i2c_manager_only_write(i2c_port_t i2c_num,uint8_t dev_addr,uint8_t *data, size_t len);
#ifdef __cplusplus
}
#endif

#endif /*_DRIVER_I2C_H_*/
