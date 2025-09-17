/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file app_keyscan.h
 * @author Nations Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __APP_KEYSCAN_H__
#define __APP_KEYSCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32wb03x.h"
    
/* Public typedef -----------------------------------------------------------*/

typedef enum {
    KEYSCAN_NULL = 0,
        
   KEYSCAN_KEY1,
   KEYSCAN_KEY2,
   KEYSCAN_KEY3,
   KEYSCAN_KEY4,
   KEYSCAN_KEY5,
   KEYSCAN_KEY6,
   KEYSCAN_KEY7,
   KEYSCAN_KEY8,
   KEYSCAN_KEY9,    
//    KEYSCAN_KEY10,
//    KEYSCAN_KEY11,
//    KEYSCAN_KEY12,
//    KEYSCAN_KEY13,
//    KEYSCAN_KEY14,
//    KEYSCAN_KEY15,
//    KEYSCAN_KEY16,
//    KEYSCAN_KEY17,
//    KEYSCAN_KEY18,
//    KEYSCAN_KEY19,
//    KEYSCAN_KEY20,
//    KEYSCAN_KEY21,
//    KEYSCAN_KEY22,
//    KEYSCAN_KEY23,
//    KEYSCAN_KEY24,
//    KEYSCAN_KEY25,
//    KEYSCAN_KEY26,
//    KEYSCAN_KEY27,
//    KEYSCAN_KEY28,
//    KEYSCAN_KEY29,
//    KEYSCAN_KEY30,
//    KEYSCAN_KEY31,
//    KEYSCAN_KEY32,
//    KEYSCAN_KEY33,
//    KEYSCAN_KEY34,
//    KEYSCAN_KEY35,
//    KEYSCAN_KEY36,
//    KEYSCAN_KEY37,
    // KEYSCAN_KEY38,
    // KEYSCAN_KEY39,
    // KEYSCAN_KEY40,
//    KEYSCAN_KEY41,
//    KEYSCAN_KEY42,
//    KEYSCAN_KEY43,
//    KEYSCAN_KEY44,


    KEYSCAN_KEY_MAX
}keyscan_value_t;  
/* Public define ------------------------------------------------------------*/

#define USER_KEYSCAN_IO_MODE            KEY_44
#define USER_KEYSCAN_DTS                DTS_10MS
#define USER_KEYSCAN_WTS                WTS_0MS

#define  KEY_RELEASE_DETECTION_DELAY    60  //keyscan irq round = 44ms 
#define  KEY_PRESS_TIMEOUT_DELAY        1000

#define DEF_DESKTOP_X_MAX    1000
#define DEF_DESKTOP_Y_MAX    1000

#define  LONG_PRESS_CNT            23  // =1000ms/44


#define  LEFT_KEY_NUMBER                KEYSCAN_KEY1
#define  RIGHT_KEY_NUMBER               KEYSCAN_KEY2
#define  UP_KEY_NUMBER                  KEYSCAN_KEY3
#define  DOWN_KEY_NUMBER                KEYSCAN_KEY4
#define  PICK_KEY_NUMBER                KEYSCAN_KEY5
#define  ZOOM_OUT_KEY_NUMBER            KEYSCAN_KEY6
#define  ZOOM_IN_KEY_NUMBER             KEYSCAN_KEY7
#define  PHOTO_KEY_NUMBER               KEYSCAN_KEY8
#define  VCR_PLUS_KEY_NUMBER            KEYSCAN_KEY9

#define  KEYSCAN_INFO_CHECK         2
static const uint32_t keyscan_map[][KEYSCAN_INFO_CHECK] = 
{
    0x00,0x00,               //NULL
   0x00000000,0x00000001,   //PA1-PA0  key1
   0x00000000,0x00000002,   //PA2-PA0  key2
   0x00000000,0x00000004,   //PA2-PA1  key3
   0x00000000,0x00000008,   //PA3-PA0  key4
   0x00000000,0x00000010,   //PA3-PA1  key5
   0x00000000,0x00000020,   //PA3-PA2  key6
   0x00000000,0x00000040,   //PA6-PA0  key7
   0x00000000,0x00000080,   //PA6-PA1  key8
   0x00000000,0x00000100,   //PA6-PA2  key9
//    0x00000000,0x00000200,   //PA6-PA3
//    0x00000000,0x00000400,   //PB10-PA0
//    0x00000000,0x00000800,   //PB10-PA1
//    0x00000000,0x00001000,   //PB10-PA2
//    0x00000000,0x00002000,   //PB10-PA3
//    0x00000000,0x00004000,   //PB10-PA6
//    0x00000000,0x00010000,   //PB8-PA0
//    0x00000000,0x00020000,   //PB8-PA1
//    0x00000000,0x00040000,   //PB8-PA2
//    0x00000000,0x00080000,   //PB8-PA3
//    0x00000000,0x00100000,   //PB8-PA6
//    0x00000000,0x00200000,   //PB8-PB10
//    0x00000000,0x00400000,   //PB9-PA0
//    0x00000000,0x00800000,   //PB9-PA1
//    0x00000000,0x01000000,   //PB9-PA2
//    0x00000000,0x02000000,   //PB9-PA3
//    0x00000000,0x04000000,   //PB9-PA6
//    0x00000000,0x08000000,   //PB9-PB10
//    0x00000000,0x10000000,   //PB9-PB8
//    0x00000001,0x00000000,   //PA0  L
//    0x00000002,0x00000000,   //PA1  L
//    0x00000004,0x00000000,   //PA2  L
//    0x00000008,0x00000000,   //PA3  L
//    0x00000010,0x00000000,   //PA6  L
//    0x00000200,0x00000000,   //PA5  L
//    0x00000020,0x00000000,   //PB10 L
//    0x00000040,0x00000000,   //PB8  L
//    0x00000080,0x00000000,   //PB9  L
//    0x00000800,0x00000000,   //PB1  L
//    0x00010000,0x00000000,   //PA0  H   key37
    // 0x00020000,0x00000000,   //PA1  H   key38
    // 0x00040000,0x00000000,   //PA2  H   key39
    // 0x00080000,0x00000000,   //PA3  H   key40
//	  0x02000000,0x00000000,   //PA5  H
//    0x00100000,0x00000000,   //PA6  H
//    0x00200000,0x00000000,   //PB10 H
//    0x00400000,0x00000000,   //PB8  H
//    0x00800000,0x00000000,   //PB9  H   key44
//    0x08000000,0x00000000,   //PB1  H

    0x00,0x00,              //NULL

}; 

    
/* Public macro -------------------------------------------------------------*/
static const uint16_t key_map_encode[] = 
{ 
    0x0000,    //NULL
     
    0x00A0,//VCR PLUS  
    0X006F,//亮度增加
    0x022D,//AC Zoom In
    0x0221,//AC search
    0x00B0,//play/pause
    0x022E,//AC Zoom Out
    0x00B6,//Up
    0x0044,//Left 
    0x0041,//Pick  
    0x0045,//Right 
    0x00B5,//Donw 
    0x00E9,//Vol_up
    0x00EA,//Vol_down
     
    // 0x0030,//Power 
//    0x0221,//AC search 
//    0x0224,//AC Back    
//    0x0223,//Home    
//    0x0040,//Menu 
//    0x0077,//Chromecast netflix
//    0x0078,//Chromecast YouTube
//    0x0079,
//    0x0089,
    
//    0x0069,//netflix
//    0x006a,//YouTube
//    0x006b,//Google Play
//    0x006c,//Prime Video    

//    0x0000, // C1
//    0x0000, // C2
//    0x0000, // C3
//    0x0000, // C4
//    0x00E2,//Mute  
};
/* Public variables ---------------------------------------------------------*/
enum app_hid_report_idx
{
    APP_HID_EMPTY_REPORT_IDX, // = 0x00
    
    APP_HID_KEYBOARD_REPORT_ID,
    APP_HID_CONSUMER_REPORT_ID,    
    APP_HID_MOUSE_REPORT_ID,    
    // APP_HID_AUDIO_REPORT_ID,
    // APP_HID_OUTPUT_REPORT_ID,
    APP_HID_TOUCHSCREEN_REPORT_ID,
};

static const uint8_t app_hid_report_map[] =
{
    // //Keyboard
    // 0x05, 0x01,
    // 0x09, 0x06,
    // 0xA1, 0x01,
    // 0x05, 0x07,
    // 0x09, 0x06,
    // 0xA1, 0x01,
    // 0x85, APP_HID_KEYBOARD_REPORT_ID,  /// REPORT ID (1)
    // 0x95, 0x08,
    // 0x75, 0x08,
    // 0x15, 0x00,
    // 0x25, 0xFF,
    // 0x19, 0x00,
    // 0x29, 0xFF,
    // 0x81, 0x00,
    // 0xC0, 
    
    // // Report ID 2: Advanced buttons
    0x05, 0x0C,       // Usage Page (Consumer)
    0x09, 0x01,       // Usage (Consumer Control)
    0xA1, 0x01,       // Collection (Application)
    0x85, APP_HID_CONSUMER_REPORT_ID,       // Report Id (1)
    0x19, 0x00,       //Usage minimum
    0x2A, 0x9C, 0x02, //Usage maximum
    0x15, 0x00,       // Logical minimum
    0x26, 0x9C, 0x02, // Logical maximum
    0x75, 0x10,       // Report Size 
    0x95, 0x01,       // Report Count   
    0x81, 0x00,       // Input 
    0xC0,             // End Collection

    // 0x09, 0xCD,       // Usage (Play/Pause)        //test, for audio final    
    // 0x09, 0xB6,       // Usage (Scan Previous Track)
    // 0x09, 0xB5,       // Usage (Scan Next Track)
    // 0x09, 0xEA,       // Usage (Volume Down)
    // 0x09, 0xE9,       // Usage (Volume Up)
    // 0x09, 0xE2,       // Usage (Mute)
    // 0x09, 0xCC,       // Usage (Stop eject)    
    // 0x09, 0xB7,       // Usage (Stop) 
    // 0x81, 0x06,       // Input (Data,Value,Relative,Bit Field)

    // 0xC0,             // End Collection
    

    // 0x05, 0x0C,       // Usage Page (Consumer)
    // 0x09, 0x01,       // Usage (Consumer Control)
    // 0xA1, 0x01,       // Collection (Application)
    // 0x85, APP_HID_CONSUMER_REPORT_ID,       // Report Id (2)
    // 0x15, 0x00,       // Logical minimum (0)
    // 0x25, 0x01,       // Logical maximum (1)
    // 0x75, 0x01,       // Report Size (1)
    // 0x95, 0x09,       // Report Count (9)

    // 0x09, 0xCD,       // Usage (Play/Pause)        //test, for audio final    
    // // 0x09, 0xB6,       // Usage (Scan Previous Track)
    // 0x09, 0x65,       // Usage (SnapShot)
    // // 0x09, 0xB5,       // Usage (Scan Next Track)
    // 0x09, 0xA0,       // Usage (VCR PLUS)
    // // 0x09, 0x22D,       // Usage (AC Zoom In)
    // 0x09, 0xEA,       // Usage (Volume Down)
    // 0x09, 0xE9,       // Usage (Volume Up)
    // 0x09, 0xE2,       // Usage (Mute)
    // 0x09, 0xCC,       // Usage (Stop eject)    
    // 0x09, 0xB7,       // Usage (Stop)
    // 0x81, 0x06,       // Input (Data,Value,Relative,Bit Field)
  
    // 0xC0,              // End Collection


    /**
     *  --------------------------------------------------------------------------
     *  Bit      |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
     *  --------------------------------------------------------------------------
     *  Byte 0   |               Not Used                | Middle| Right | Left  |
     *  --------------------------------------------------------------------------
     *  Byte 1   |                     X Axis Relative Movement                  |
     *  --------------------------------------------------------------------------
     *  Byte 2   |                     Y Axis Relative Movement                  |
     *  --------------------------------------------------------------------------
     *  Byte 3   |                     Wheel Relative Movement                   |
     *  --------------------------------------------------------------------------
     */

    0x05, 0x01,     /// USAGE PAGE (Generic Desktop)
    0x09, 0x02,     /// USAGE (Mouse)
    
    0xA1, 0x01,     /// COLLECTION (Application)
    
    0x85, APP_HID_MOUSE_REPORT_ID,     /// REPORT ID (3) - MANDATORY
    0x09, 0x01,     ///     USAGE (Pointer)
    0xA1, 0x00,     ///     COLLECTION (Physical)

    /**
     * ----------------------------------------------------------------------------
     * BUTTONS
     * ----------------------------------------------------------------------------
     */
    0x05, 0x09,     ///         USAGE PAGE (Buttons)
    0x19, 0x01,     ///         USAGE MINIMUM (1)
    0x29, 0x08,     ///         USAGE MAXIMUM (8)
    0x15, 0x00,     ///         LOGICAL MINIMUM (0)
    0x25, 0x01,     ///         LOGICAL MAXIMUM (1)
    0x75, 0x01,     ///         REPORT SIZE (1)
    0x95, 0x08,     ///         REPORT COUNT (8)
    0x81, 0x02,     ///         INPUT (Data, Variable, Absolute)

    /**
     * ----------------------------------------------------------------------------
     * MOVEMENT DATA
     * ----------------------------------------------------------------------------
     */
    0x05, 0x01,     ///         USAGE PAGE (Generic Desktop)
    0x16, 0x08, 0xFF, ///       LOGICAL MINIMUM (-255)
    0x26, 0xFF, 0x00, ///       LOGICAL MAXIMUM (255)
    0x75, 0x10,     ///         REPORT SIZE (16)
    0x95, 0x02,     ///         REPORT COUNT (2)
    0x09, 0x30,     ///         USAGE (X)
    0x09, 0x31,     ///         USAGE (Y)
    0x81, 0x06,     ///         INPUT (Data, Variable, Relative)

    0x15, 0x81,     ///         LOGICAL MINIMUM (-127)
    0x25, 0x7F,     ///         LOGICAL MAXIMUM (127)
    0x75, 0x08,     ///         REPORT SIZE (8)
    0x95, 0x01,     ///         REPORT COUNT (1)
    0x09, 0x38,     ///         USAGE (Wheel)
    0x81, 0x06,     ///         INPUT (Data, Variable, Relative)

    0xC0,           ///     END COLLECTION (Physical)
    0xC0,           /// END COLLECTION (Application)


    //  // Report ID 2: Advanced buttons
    // 0x05, 0x0C,       // Usage Page (Consumer)
    // 0x09, 0x01,       // Usage (Consumer Control)
    // 0xA1, 0x01,       // Collection (Application)
    // 0x85, APP_HID_AUDIO_REPORT_ID,       // Report Id (4)
    // 0x15, 0x00,       // Logical minimum (0)
    // 0x25, 0x01,       // Logical maximum (1)
    // 0x75, 0x01,       // Report Size (1)
    // 0x95, 0x08,       // Report Count (8)

    // 0x09, 0xCD,       // Usage (Play/Pause)        //test, for audio final    
    // 0x09, 0xB6,       // Usage (Scan Previous Track)
    // 0x09, 0xB5,       // Usage (Scan Next Track)
    // 0x09, 0xEA,       // Usage (Volume Down)
    // 0x09, 0xE9,       // Usage (Volume Up)
    // 0x09, 0xE2,       // Usage (Mute)
    // 0x09, 0xCC,       // Usage (Stop eject)    
    // 0x09, 0xB7,       // Usage (Stop) 
    // 0x81, 0x06,       // Input (Data,Value,Relative,Bit Field)
  
    // 0xC0,              // End Collection
    
    // #ifdef APP_HID_ENCODER_SBC
    // //hid audio
    // 0x06, 0x01, 0xff,
    // 0x09, 0x01, /*    Usage (Consumer Control) */
    // 0xA1, 0x01, /*    COLLECTION (Application) */
    // 0x85, APP_HID_AUDIO_REPORT_ID_DAT, /*    report ID  */
    // 0x75, 0x08, /*    Report Size (8) */
    // 0x95, 0xff, /*    Report Count (255) */
    // 0x15, 0x80, /*    Logical Minimum (0x80) */
    // 0x25, 0x7f, /*    Logical Minimum (0x7f) */
    // 0x81, 0x22, /*    Input () */
    // 0xc0,
    // #endif
    
    // 0xC0,

    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x04, // Usage (Touch Screen)
    0xA1, 0x01, // Collection (Application)
    0x85, APP_HID_TOUCHSCREEN_REPORT_ID, /* REPORT_ID (4) */

    0x05, 0x0D, //   Usage Page (Digitizer)
    0x09, 0x22, //   Usage (Finger)
    0xA1, 0x02, //   Collection (Logical)
    0x05, 0x0D, //     Usage Page (Digitizer)
    0x09, 0x42, /* USAGE (TIP SWITCH) */
    0x15, 0x00, //     Logical Minimum......... (0)
    0x25, 0x01, //     Logical Maximum......... (1)
    0x75, 0x01, //     Report Size............. (1)
    0x95, 0x01, //     Report Count............ (1)
    0x81, 0x02, //     Input...................(Data, Variable, Absolute)
    0x75, 0x07, //     Report Size............. (7)
    0x95, 0x01, //     Report Count............ (1)
    0x81, 0x01, //     Input...................(Constant)

    0x09, 0x51, /* USAGE (Contact Identifier) */
    0x75, 0x08, //     Report Size............. (8)
    0x95, 0x01, //     Report Count............ (1)
    0x81, 0x02, //     Input...................(Data, Variable, Absolute)

    0x05, 0x01, //     Usage Page (Generic Desktop)
    0x09, 0x30, //     Usage (X)
    0x15, 0x00, //     Logical Minimum......... (0)
    /*48 49 50*/
    0x26, (uint8_t)DEF_DESKTOP_X_MAX, (uint8_t)(DEF_DESKTOP_X_MAX >> 8), /* LOGIC_MAX (0X0800) */
    0x75, 0x10,                                                          //     Report Size............. (16)
    0x95, 0x01,                                                          //     Report Count............ (1)
    0x81, 0x02,                                                          //     Input...................(Data, Variable, Absolute)
    0x09, 0x31,                                                          //     Usage (Y)
    0x15, 0x00,                                                          //     Logical Minimum......... (0)
    /*61 62 63*/
    0x26, (uint8_t)DEF_DESKTOP_Y_MAX, (uint8_t)(DEF_DESKTOP_Y_MAX >> 8), /* LOGIC_MAX (0X0800) */
    0x75, 0x10,                                                          //     Report Size............. (16) 64 65
    0x95, 0x01,                                                          //     Report Count............ (1)  66 67
    0x81, 0x02,                                                          //     Input...................(Data, Variable, Absolute) 68 69
    0xC0,                                                                //   End Collection 70
    0xc0,                


    

};


typedef struct {
    uint8_t button;     // 鼠标按键编码
    int8_t wheel;       // 滚轮滚动值
    int16_t x;          // X 坐标移动量
    int16_t y;          // Y 坐标移动量
} mouse_action_t;

static const mouse_action_t mouse_map_encode[] = {
    {0x00, 0, 0, 0},   // 无操作
    {0x01, 0, 0, 0},   // 左键
    {0x02, 0, 0, 0},   // 右键
    {0x04, 0, 0, 0},   // 中键
    {0x00, 1, 0, 0},   // 滚轮向上
    {0x00, -1, 0, 0},  // 滚轮向下
    {0x00, 0, 10, 0},  // 鼠标向右移动
    {0x00, 0, -10, 0}, // 鼠标向左移动
    {0x00, 0, 0, 10}, // 鼠标向上移动
    {0x00, 0, 0, -10}, // 鼠标向下移动
};





/* Public function prototypes -----------------------------------------------*/
void KEYSCAN_Configuration(uint8_t key_mask, uint8_t mode, uint8_t dts, uint8_t wts, bool int_en);
void app_keyscan_init(void);
void app_keyscan_msg_handler(void);
void app_keyscan_released_handler(uint16_t const msgid);
void key_code_long_press_handler(uint32_t hid_code_to_send);
#ifdef __cplusplus
}
#endif

#endif /* __APP_KEYSCAN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
