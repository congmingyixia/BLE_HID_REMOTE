1、功能说明
  本程序实现蓝牙遥控器控制手机刷抖音和拍照的功能。

2、使用环境
软件开发环境：Keil MDK-ARM v5.36
硬件环境：N32WB031_STB

3、使用说明
  系统配置：
   1.时钟源：HSI=64M, AHB=64M, APB1=32M, APB2=64M
   2.引脚配置：
    LEFT_KEY_NUMBER：    PA1-PA0
    RIGHT_KEY_NUMBER：   PA2-PA0
    UP_KEY_NUMBER：      PA2-PA1
    DOWN_KEY_NUMBER：    PA3-PA0
    PICK_KEY_NUMBER：    PA3-PA1
    ZOOM_OUT_KEY_NUMBER：PA3-PA2
    ZOOM_IN_KEY_NUMBER： PA6-PA0
    PHOTO_KEY_NUMBER：   PA6-PA1
    VCR_PLUS_KEY_NUMBER：PA6-PA2
    LED：PB0

   3.log输出：
    LPUART1_TX: PB12
    LPUART1_RX: PB11

   使用方法：
    1.在KEIL下编译后烧录到芯片里
    2.打开手机蓝牙，搜索设备名称hid_remote，连接设备
    3.手机打开抖音，遥控器上、下、左、右按键可以控制手机上滑、下滑、左滑、右；pick键可以控制手机播放/暂停，双击可以点赞；
    VCR+键可以控制手机打开相机和转换拍照和录像模式；ZOOM_IN和ZOOM_OUT键可以控制手机加焦和减焦；PHOTO键可以控制手机拍照；
    长按上键可以增加音量，长按下键可以减少音量。

4、注意事项
 由于程序会进入休眠模式，SWD接口将无法访问。请在按下RESET按钮后一秒内执行程序烧录步骤。