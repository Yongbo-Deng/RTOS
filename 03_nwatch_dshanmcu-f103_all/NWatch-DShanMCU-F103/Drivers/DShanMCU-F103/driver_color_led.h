
#ifndef _DRIVER_COLOR_LED_H
#define _DRIVER_COLOR_LED_H

#include <stdint.h>

#include "common.h"

#define COLOR_LED_RED			0x00ff0000
#define COLOR_LED_GREEN		0x0000ff00
#define COLOR_LED_BLUE		0x000000ff

#define LED_FLASH_INFINITE	0
#define LED_ALL				255
#define LED_FLASH_FAST	100
#define LED_BRIGHTNESS_MAX	255

typedef enum
{
	LED_RED,
	LED_GREEN,
	LED_BLUE
} led_t;


/**********************************************************************
 * 函数名称： ColorLED_Init
 * 功能描述： 全彩LED的初始化函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void ColorLED_Init(void);

/**********************************************************************
 * 函数名称： ColorLED_Set
 * 功能描述： 全彩LED设置颜色函数
 * 输入参数： color - 24bit颜色,格式为0x00RRGGBB
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void ColorLED_Set(uint32_t color);

/**********************************************************************
 * 函数名称： ColorLED_Test
 * 功能描述： 全彩LED测试程序
 * 输入参数： 无
 * 输出参数： 无
 *            无
 * 返 回 值： 无
 * 修改日期        版本号     修改人        修改内容
 * -----------------------------------------------
 * 2023/08/04        V1.0     韦东山       创建
 ***********************************************************************/
void ColorLED_Test(void);

BOOL led_flashing(void);
void led_flash(led_t led, millis_t len, uint32_t brightness);
void led_update(void);
void led_stop(void);

#endif /* _DRIVER_COLOR_LED_H */

