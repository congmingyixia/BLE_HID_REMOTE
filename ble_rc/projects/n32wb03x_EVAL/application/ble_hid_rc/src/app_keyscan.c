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
 * @file app_keyscan.c
 * @author Nations Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include <stdio.h>
#include <string.h>
#include "app_keyscan.h"
#include "global_func.h"
#include "app_hid.h"
//#include "app_adc.h"
#include "prf.h"
#include "ns_timer.h"
#include "ns_log.h"
#include "ke_timer.h"
#include "app_ble.h"
//#include "app_irgen.h"
#include "ns_sleep.h"
#include "ns_sec.h"
//#include "app_batt.h"
#include "app_rdtss.h"
//#include "app_led.h"
//#include "app_store.h"
//#include "app_imu.h"
#include "ns_delay.h"
#include "app_gpio.h"
/** @addtogroup 
 * @{
 */
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
// #define KEY_LED_ID      LED_TASK_1
/* Private macro -------------------------------------------------------------*/
 const uint32_t hid_key_release  = 0;

/* Private variables ---------------------------------------------------------*/
// timer_hnd_t voice_key_timer_id; 
uint8_t key_received = 0;
uint8_t key_pressed = 0;

static uint8_t up_key_cnt = 0;
static uint8_t down_key_cnt = 0;
// 添加全局变量
volatile bool key_long_press_detected = false;  // 长按检测标志
/**
 * @brief  KEYSCAN Configuration
 * @param  @KEY_MASK     :    KEY_65, KEY_44, KEY_104
 * @param  @KEY_MODE     :    MODE_FIXED_INTV, MODE_SW_TRIG, MODE_PRESS_TRIG,
 * @param  @KEY_DTS      :   DTS_10MS ,DTS_20MS ,DTS_40MS ,DTS_80MS ,DTS_160MS, DTS_320MS, DTS_640MS, DTS_640MS_2,
 * @param  @KEY_WTS      :   WTS_0MS, WTS_32MS, WTS_64MS, WTS_96MS, WTS_128MS, WTS_160MS, WTS_192MS, WTS_224MS,
 * @param  @KEY_INT      :   INT_DIS, INT_EN
 * @return Return value
 * @note   Note
 */
void KEYSCAN_Configuration(uint8_t key_mask, uint8_t mode, uint8_t dts, uint8_t wts, bool int_en)
{
    GPIO_InitType GPIO_InitStructure; 
    KEYSCAN_InitType KEYSCAN_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* CLK EN */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC->LSCTRL |= 0x40000000;                 //keyscan clk en
    
    if(key_mask == KEY_65)
    {
        GPIO_InitStructure.Pin =     GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;        
    }
    else if(key_mask == KEY_44)
    {
        GPIO_InitStructure.Pin =     GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6;
    }
    else
    {
        GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    }
    
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_OD;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = 0; //deinit
    if(key_mask == KEY_65 ||key_mask == KEY_44)
    {
        GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;        
    }
    else
    {
        GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    }
    
    
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_OD;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    KEYSCAN_InitStructure.Mask = key_mask;
    KEYSCAN_InitStructure.Mode = mode;
    KEYSCAN_InitStructure.Wts = wts;
    KEYSCAN_InitStructure.Dts = dts;
    KEYSCAN_InitStructure.Int_en = int_en;
    KEYSCAN_Init(&KEYSCAN_InitStructure);

    if(int_en)
    {
        EXTI_InitType EXTI_InitStructure;

        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Line = EXTI_LINE13;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitPeripheral(&EXTI_InitStructure);
            
        NVIC_InitType NVIC_InitStructure;
        NVIC_DisableIRQ(KEYSCAN_IRQn);
        /* Enable the KEYSCAN Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel                   = KEYSCAN_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority           = 3;
        NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        NVIC_EnableIRQ(KEYSCAN_IRQn);
        
    }
    
    KEYSCAN_Enable(ENABLE);
    
}


/**
 * @brief  KEYSCAN irq callback
 * @param   
 * @return  
 * @note    
 */
void KEYSCAN_IRQHandler(void)
{
    uint32_t key_data[5] = {0};
    uint32_t key_scan_ctrl_reg;
    uint8_t key_value;
    
    key_scan_ctrl_reg = KEYSCAN->KEYCR;
    if(key_scan_ctrl_reg & (1<<KEY_IRP_POS))   //IRQ OCCUR
    {
        KEYSCAN->KEYCR |= (1<<KEY_IRP_POS);//KEYSCAN_ClearInterrupt();
    }
    
    if(EXTI->PEND & EXTI_LINE13)
    {
        EXTI->PEND = EXTI_LINE13;//EXTI_ClrITPendBit(EXTI_LINE13);
    }
    
//    KEYSCAN_ReadKeyData(key_data);
    key_data[0] = KEYSCAN->KEYDATA0;
    key_data[1] = KEYSCAN->KEYDATA1;
    key_data[2] = KEYSCAN->KEYDATA2;
    key_data[3] = KEYSCAN->KEYDATA3;
    key_data[4] = KEYSCAN->KEYDATA4;
    #if 0 //output keyscan reg for keyscan_map
    NS_LOG_INIT();
    NS_LOG_INFO("0x%08x,", key_data[0]);
    NS_LOG_INFO("0x%08x,", key_data[1]);
    NS_LOG_INFO("0x%08x,", key_data[2]);
    NS_LOG_INFO("0x%08x,", key_data[3]);
    NS_LOG_INFO("0x%08x,\r\n", key_data[4]);
    #endif
    for(key_value = 1; key_value < KEYSCAN_KEY_MAX; key_value++)
    {
        if(memcmp(key_data,&keyscan_map[key_value][0],(KEYSCAN_INFO_CHECK<<2)) == 0)
        {
            break;
        }
    }
    
    if(key_value != KEYSCAN_KEY_MAX)
    {
        NS_LOG_INFO("Key_value:%d\r\n", key_value);
        key_received = key_value;
        //send msg to active sending key
        ke_msg_send_basic(APP_KEY_DETECTED, TASK_APP, TASK_APP);
    }
    
}






void app_send_left_swipe_gesture(void)
{
    // 定义滑动的起始点和结束点坐标
    uint16_t start_x = 800;  // 起始X坐标（右侧）
    uint16_t start_y = 800;  // Y坐标（垂直居中）
    uint16_t end_x = 200;    // 结束X坐标（左侧）
    uint16_t end_y = 800;    // Y坐标（垂直居中）

    // 定义滑动步数
    uint8_t steps = 3;
    
    // 1. 发送触摸开始事件（手指松开）
    app_hid_send_touch_report(0, 0, start_x, start_y);
    
    // 2. 发送滑动过程中的连续坐标点
    for (uint8_t i = 1; i <= steps; i++) {
        // 计算当前步骤的坐标（线性插值）
        uint16_t current_x = start_x - ((start_x - end_x) * i / steps);
        uint16_t current_y = start_y - ((start_y - end_y) * i / steps);

        // 发送当前坐标点
        app_hid_send_touch_report(1, 0, current_x, current_y);

    }
    
    // 3. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, end_x, end_y);

}

void app_send_right_swipe_gesture(void)
{
    // 定义滑动的起始点和结束点坐标
    uint16_t start_x = 200;  // 起始X坐标（左侧）
    uint16_t start_y = 800;  // Y坐标（垂直居中）
    uint16_t end_x = 800;    // 结束X坐标（右侧）
    uint16_t end_y = 800;    // Y坐标（垂直居中）

    // 定义滑动步数
    uint8_t steps = 3;

    // 1. 发送触摸开始事件（手指松开）
    app_hid_send_touch_report(0, 0, start_x, start_y);
    
    // 2. 发送滑动过程中的连续坐标点
    for (uint8_t i = 1; i <= steps; i++) {
        // 计算当前步骤的坐标（线性插值）
        uint16_t current_x = start_x + ((end_x - start_x) * i / steps);
        uint16_t current_y = start_y + ((end_y - start_y) * i / steps);

        // 发送当前坐标点
        app_hid_send_touch_report(1, 0, current_x, current_y);

    }
    
    // 3. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, end_x, end_y);

}


void app_send_up_swipe_gesture(void)
{
    // 定义滑动的起始点和结束点坐标
    uint16_t start_x = 500;  // 起始X坐标（左侧）
    uint16_t start_y = 200;  // Y坐标（垂直居中）
    uint16_t end_x = 500;    // 结束X坐标（右侧）
    uint16_t end_y = 800;    // Y坐标（垂直居中）

    // 定义滑动步数
    uint8_t steps = 3;
    
    // 1. 发送触摸开始事件（手指松开）
    app_hid_send_touch_report(0, 0, start_x, start_y);
    
    // 2. 发送滑动过程中的连续坐标点
    for (uint8_t i = 1; i <= steps; i++) {
        // 计算当前步骤的坐标（线性插值）
        uint16_t current_x = start_x + ((end_x - start_x) * i / steps);
        uint16_t current_y = start_y + ((end_y - start_y) * i / steps);

        // 发送当前坐标点
        app_hid_send_touch_report(1, 0, current_x, current_y);

    }
    
    // 3. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, end_x, end_y);

}


void app_send_down_swipe_gesture(void)
{
    // 定义滑动的起始点和结束点坐标
    uint16_t start_x = 500;  // 起始X坐标（左侧）
    uint16_t start_y = 800;  // Y坐标（垂直居中）
    uint16_t end_x = 500;    // 结束X坐标（右侧）
    uint16_t end_y = 200;    // Y坐标（垂直居中）

    // 定义滑动步数
    uint8_t steps = 3;

    // 1. 发送触摸开始事件（手指松开）
    app_hid_send_touch_report(0, 0, start_x, start_y);
    
    // 2. 发送滑动过程中的连续坐标点
    for (uint8_t i = 1; i <= steps; i++) {
        // 计算当前步骤的坐标（线性插值）
        uint16_t current_x = start_x + ((end_x - start_x) * i / steps);
        uint16_t current_y = start_y + ((end_y - start_y) * i / steps);

        // 发送当前坐标点
        app_hid_send_touch_report(1, 0, current_x, current_y);

    }
    
    // 3. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, end_x, end_y);

}

void app_send_pick_gesture(void)
{
    // 定义点击的坐标
    uint16_t x = 500;  // X坐标（中心）
    uint16_t y = 500;  // Y坐标（中心）

    // 1. 发送触摸开始事件（手指按下）
    app_hid_send_touch_report(1, 0, x, y);

    // 2. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, x, y);

}

void app_send_shutter_gesture(void)
{
    // 定义点击的坐标
    uint16_t x = 500;  // X坐标（中心）
    uint16_t y = 840;  // Y坐标（中心）

    // 1. 发送触摸开始事件（手指按下）
    app_hid_send_touch_report(1, 0, x, y);

    // 2. 发送触摸结束事件（手指抬起）
    app_hid_send_touch_report(0, 0, x, y);
}

/**
 * @brief  key conver to hid key report and send 
 * @param  Param input key value
 * @return Return value
 * @note   Note
 */

void key_code_handler(uint32_t hid_code_to_send, bool is_long_press)
{

	  if(key_pressed == 0)
		{
			app_hid_send_consumer_report((uint8_t*)&hid_key_release);
            // app_hid_send_touch_report(0, 0, 0, 0);
			NS_LOG_INFO("hid_key_release:%x\r\n",hid_key_release);
			ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
			ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
			key_received = key_pressed;
		}
		else
		{
		//  app_hid_send_consumer_report((uint8_t*)&hid_code_to_send);
        
        if(is_long_press)
        {
            // 长按处理
            switch(hid_code_to_send)
            {
                case UP_KEY_NUMBER:  // 按键3触发音量加
                    app_hid_send_consumer_report((uint8_t*)&(key_map_encode[12]));  
                    NS_LOG_INFO("vol+ by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[12]);
                    break;
                case DOWN_KEY_NUMBER:  // 按键4触发音量减
                    app_hid_send_consumer_report((uint8_t*)&(key_map_encode[13]));  
                    NS_LOG_INFO("vol- by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[13]);
                    break;
                default:
                    break;
            }
        }
        else
   {
          // 根据不同的按键值触发不同的手势
        switch(hid_code_to_send)
          {
            case LEFT_KEY_NUMBER:  // 按键1触发左滑手势
                app_send_left_swipe_gesture();
                NS_LOG_INFO("Left swipe gesture triggered by key %d\r\n", hid_code_to_send);
                break;
                
            case RIGHT_KEY_NUMBER:  // 按键2触发右滑手势
                app_send_right_swipe_gesture();
                NS_LOG_INFO("Right swipe gesture triggered by key %d\r\n", hid_code_to_send);
                break;

            case UP_KEY_NUMBER:  // 按键3触发上滑手势
                app_send_up_swipe_gesture();
                NS_LOG_INFO("Up swipe gesture triggered by key %d\r\n", hid_code_to_send);
                break;

            case DOWN_KEY_NUMBER:  // 按键4触发下滑手势
                app_send_down_swipe_gesture();
                NS_LOG_INFO("Down swipe gesture triggered by key %d\r\n", hid_code_to_send);
                break;

            case PICK_KEY_NUMBER:  // 按键5触发点击手势
                app_send_pick_gesture();
                NS_LOG_INFO("Pick gesture triggered by key %d\r\n", hid_code_to_send);
                break;

            case ZOOM_OUT_KEY_NUMBER:  // 按键6触发减焦
                app_hid_send_consumer_report((uint8_t*)&(key_map_encode[6]));  
                NS_LOG_INFO("ZOOM_OUT by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[6]);
                break;

            case ZOOM_IN_KEY_NUMBER:  // 按键7触发加焦
                app_hid_send_consumer_report((uint8_t*)&(key_map_encode[3]));  
                NS_LOG_INFO("ZOOM_IN by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[3]);
                break;

            case PHOTO_KEY_NUMBER:  // 按键8 音量键拍照
                app_hid_send_consumer_report((uint8_t*)&(key_map_encode[13]));  
                NS_LOG_INFO("PHOTO by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[13]);

                // app_send_shutter_gesture();
                // NS_LOG_INFO("Shutter triggered by key %d\r\n", hid_code_to_send);
               break;        
            case VCR_PLUS_KEY_NUMBER:  // 按键9触发打开相机和切换拍照与录像模式
                app_hid_send_consumer_report((uint8_t*)&(key_map_encode[1]));  
                NS_LOG_INFO("VCR_PLUS by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[1]);
                break;
            default:
                break;
           }
        }

        //  NS_LOG_INFO("ble code:%x\r\n",hid_code_to_send);
       
	     LedOn(LED1_PORT,LED1_PIN); 
		}	
		
         key_pressed = 0;
}

// void key_code_long_press_handler(uint32_t hid_code_to_send)
// {
//     if(key_pressed == 0)
// 		{
// 			app_hid_send_consumer_report((uint8_t*)&hid_key_release);
//             // app_hid_send_touch_report(0, 0, 0, 0);
// 			NS_LOG_INFO("hid_key_release:%x\r\n",hid_key_release);
// 			ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
// 			ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
// 			key_received = key_pressed;
// 		}
// 		else
// 		{
//             switch(hid_code_to_send)
//         {
//             case UP_KEY_NUMBER:  // 按键3触发音量加
//                 app_hid_send_consumer_report((uint8_t*)&(key_map_encode[13]));  
//                 NS_LOG_INFO("vol+ by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[13]);
//                 break;

//             case DOWN_KEY_NUMBER:  // 按键4触发音量减
//                 app_hid_send_consumer_report((uint8_t*)&(key_map_encode[14]));  
//                 NS_LOG_INFO("vol- by key %d, ble code:%x\r\n", hid_code_to_send, key_map_encode[14]);
//                 break;

//             default:
//                 break;
//         }
//          LedOn(LED1_PORT,LED1_PIN);
//     }

//     // key_pressed = 0;
// }

// void app_keyscan_msg_handler(void)
// {
//     NS_LOG_INFO("Key received,%d\r\n",key_received);
// 	  key_pressed = key_received;
//     if(key_received == 0)
//     {
//         return;
//     }
//     else
// 	{
//     if(key_pressed != 0)
//     {
//         if (key_pressed != key_received)
//         {
//             NS_LOG_INFO("Key Pressed1,%d\r\n",key_pressed);
//             //switching key, released last one first
//             ke_timer_clear(APP_KEY_RELEASED, TASK_APP); // 清除上一次的定时器
//             ke_timer_set(APP_KEY_RELEASED, TASK_APP, 1);

//                 up_key_cnt = 0;
//                 down_key_cnt = 0;
//                 key_long_press_detected = false; // 重置长按检测标志
//         }
//         else 
//         {
            
//             // 检查是否需要长按检测
//                 if(key_received == UP_KEY_NUMBER || key_received == DOWN_KEY_NUMBER)
//                 {
//                     // 增加对应计数器
//                     if(key_received == UP_KEY_NUMBER)
//                     {
//                         up_key_cnt++;
//                     }
//                     else if(key_received == DOWN_KEY_NUMBER)
//                     {
//                         down_key_cnt++;
//                     }
                    
//                     // 检查是否达到长按阈值
//                     if((key_received == UP_KEY_NUMBER && up_key_cnt >= LONG_PRESS_CNT) ||
//                        (key_received == DOWN_KEY_NUMBER && down_key_cnt >= LONG_PRESS_CNT))
//                     {
//                         // 检测到长按
//                         if(!key_long_press_detected)
//                         {
//                             key_long_press_detected = true;
//                             key_code_handler(key_received, true);
//                             NS_LOG_INFO("Key long press detected, count: %d\r\n", 
//                             key_received == UP_KEY_NUMBER ? up_key_cnt : down_key_cnt);
//                         }
//                     }
//                     else
//                     {
//                         // 未达到长按阈值，执行短按处理
//                         key_code_handler(key_received, false);
//                     }
//                 }
             
//             }
//             else
//             {

//                 //set/reset timer for release detection
// 		       key_code_handler(key_received, false);
//                NS_LOG_INFO("Key received2,%d\r\n",key_received);
//             //  key_pressed = 0;
//             //  NS_LOG_INFO("Key Pressed3,%d\r\n",key_pressed);
//             }
//         }
//     }   
//     else
//     {
//         NS_LOG_INFO("Key Pressed4,%d\r\n",key_pressed);
//          // 未按下任何按键，清除释放检测定时器
//          ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
//          ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
//     }


// 	}
// 	if (key_pressed ==0)
// 	{    
//         NS_LOG_INFO("Key Pressed2,%d\r\n",key_pressed);
// 	     ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
//          ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
	
// 	}
	
	
//       key_received = 0;

// }

void app_keyscan_msg_handler(void)
{
    NS_LOG_INFO("Key received,%d\r\n",key_received);
    key_pressed = key_received;
    
    if(key_received == 0)
    {
        return;
    }
    else
    {
        if(key_pressed != 0)
        {
            if (key_pressed != key_received)
            {
                NS_LOG_INFO("Key Pressed1,%d\r\n",key_pressed);
                // 检测到按键切换，先释放上一个按键
                ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
                ke_timer_set(APP_KEY_RELEASED, TASK_APP, 1);
                
                // 重置计数器和长按标志
                up_key_cnt = 0;
                down_key_cnt = 0;
                key_long_press_detected = false;
            }
            else 
            {
                // 检查是否需要长按检测
                if(key_received == UP_KEY_NUMBER || key_received == DOWN_KEY_NUMBER)
                {
                    // 增加对应计数器
                    if(key_received == UP_KEY_NUMBER)
                    {
                        up_key_cnt++;
                    }
                    else if(key_received == DOWN_KEY_NUMBER)
                    {
                        down_key_cnt++;
                    }
                    
                    // 检查是否达到长按阈值
                    if((key_received == UP_KEY_NUMBER && up_key_cnt >= LONG_PRESS_CNT) ||
                       (key_received == DOWN_KEY_NUMBER && down_key_cnt >= LONG_PRESS_CNT))
                    {
                        // 检测到长按

                            key_long_press_detected = true;
                            key_code_handler(key_received, true);
                            NS_LOG_INFO("Key long press detected, count: %d\r\n", 
                                        key_received == UP_KEY_NUMBER ? up_key_cnt : down_key_cnt);
                        
                    }
                    else
                    {
                        // 未达到长按阈值，执行短按处理
                        key_code_handler(key_received, false);
                    }
                }
                else
                {
                    // 不需要长按检测的按键，直接执行短按处理
                    key_code_handler(key_received, false);
                    NS_LOG_INFO("Key received2,%d\r\n",key_received);
                }
            }
        }   
        else
        {
            NS_LOG_INFO("Key Pressed4,%d\r\n",key_pressed);
            // 未按下任何按键，清除释放检测定时器
            ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
            ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
        }
    }
    
    if (key_pressed == 0)
    {
        NS_LOG_INFO("Key Pressed2,%d\r\n",key_pressed);
        ke_timer_clear(APP_KEY_RELEASED, TASK_APP);
        ke_timer_set(APP_KEY_RELEASED, TASK_APP, KEY_RELEASE_DETECTION_DELAY);
    }
    
    key_received = 0;
}


void app_keyscan_released_handler(uint16_t const msgid)
{
   if (msgid == APP_KEY_RELEASED)
   {
       up_key_cnt = 0;
       down_key_cnt = 0;
    app_hid_send_consumer_report((uint8_t*)&hid_key_release);
         
        // app_hid_send_touch_report(0, 0, 0, 0);
  
    LedOff(LED1_PORT,LED1_PIN);
    NS_LOG_INFO("Key Released,%d\r\n",key_received);
    key_pressed = 0;

   }
}




/**
 * @brief  timeout handler of key pressing, it mean key release
 * @param   
 * @return 
 * @note   
 */


/**
 * @brief  config keyscan module
 * @param   
 * @return 
 * @note   
 */
void app_keyscan_init(void)
{
    KEYSCAN_Configuration(USER_KEYSCAN_IO_MODE, MODE_FIXED_INTV, USER_KEYSCAN_DTS, USER_KEYSCAN_WTS, INT_EN);
    
}

/**
 * @}
 */
