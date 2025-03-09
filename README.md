# 简介



# 开发环境
VScode+platfromIO插件

	[env:esp32-s3-devkitc-1]
	platform = espressif32
	board = esp32-s3-devkitc-1
	framework = arduino
	lib_deps = 
	lvgl/lvgl@^9.2.2
	bodmer/TFT_eSPI@^2.5.43
# 硬件配置
- 1.主控: ESP32S3 (主频:240MHz)
- 2.屏幕: ST7789 IPS 1.69inch SPI接口 240x280分辨率
- 3.输入设备: 触屏CST816 + 拨动按键 
- 4.储存器: W25Q64  8MB
- 5.PMIC: RK618 
- 6.DCDC: MP28167GQ-Z  5V
- 7.电量计:INA226AIDGST
- 8.PD协议：FUSB302BMPX
- 9.拓展IO：PCF8574RGTR(UMW)
- 10.PWM：SI5351A-B07321-GT
- 11.加速度计: LSM6DS3T
- 12.地磁计: HMC5883L
- 13.音频: MAX98357AGTE_V+
- 14.485: SN65HVD3082EDGKR
- 15.CAN: SIT3051TK
- 16.电池: Li-ion 3.7V 683030 700mAh
- 17.外壳: 3D打印
# 功能
ina226电压检测 -ok
pcnt ledc     -ok
# 文档
笔记一 https://www.cnblogs.com/moyuu/p/18722264

笔记二 https://www.cnblogs.com/moyuu/p/18723774

笔记三在写了...
# 致谢
感谢@[obitvn](https://github.com/obitvn/felini-firmware/tree/41be0903c2268b9ea327d9d93401362f00cf73b6 "obitvn")大佬的硬件原理和3D模型


感谢@[FASTSHIFT](https://github.com/FASTSHIFT/X-TRACK "FASTSHIFT")大佬的LVGL页面切换管理和数据订阅管理
