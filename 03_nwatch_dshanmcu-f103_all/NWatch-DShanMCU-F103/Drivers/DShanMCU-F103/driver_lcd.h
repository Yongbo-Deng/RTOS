/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_oled.h
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2023.8.04      v01         百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_LCD_H
#define __DRIVER_LCD_H

#include <stdint.h>

#include "common.h"

typedef enum
{
	DISPLAY_ON,
	DISPLAY_OFF,
	DISPLAY_SLEEP,
}DisPlay_State_t;

/*
 *  函数名：LCD_Init
 *  功能描述：初始化LCD
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 */
void LCD_Init(void);


/*
 *  函数名：LCD_Clear
 *  功能描述：清屏函数
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
void LCD_Clear(void);

/*
 *  函数名：LCD_PutChar
 *  功能描述：显示一个字符
 *  输入参数：x --> x坐标
 *            y --> y坐标
 *            c -->   显示的字符
 *  输出参数：无
 *  返回值：无
*/
void LCD_PutChar(uint8_t x, uint8_t y, char c);


/*
 *  函数名：LCD_PrintString
 *  功能描述：显示一个字符串
 *  输入参数：x --> x坐标
 *            y --> y坐标
 *            str -->   显示的字符串
 *  输出参数：无
 *  返回值：打印了多少个字符
*/
int LCD_PrintString(uint8_t x, uint8_t y, const char *str);

/*
 *  函数名：OLED_ClearLine
 *  功能描述：清除一行
 *  输入参数：x - 从这里开始
 *            y - 清除这行
 *  输出参数：无
 *  返回值：无
 */
void LCD_ClearLine(uint8_t x, uint8_t y);

/*
 *  LCD_PrintHex
 *  功能描述：以16进制显示数值
 *  输入参数：x - x坐标
 *            y - y坐标
 *            val -   显示的数据
 *            pre -   非零时显示"0x"前缀
 *  输出参数：无
 *  返回值：打印了多少个字符
 */
int LCD_PrintHex(uint8_t x, uint8_t y, uint32_t val, uint8_t pre);

/*
 *  LCD_PrintSignedVal
 *  功能描述：以10进制显示一个数值
 *  输入参数：x --> x坐标(0~15)
 *            y --> y坐标(0~7)
 *            val -->   显示的数据
 *  输出参数：无
 *  返回值：打印了多少个字符
 */
int LCD_PrintSignedVal(uint8_t x, uint8_t y, int32_t val);

/**********************************************************************
 *  LCD_GetFrameBuffer
 *  功能描述：获得LCD的Framebuffer
 *  输入参数：无
 *  输出参数：pXres/pYres/pBpp - 用来保存分辨率、bpp
 *  返回值：Framebuffer首地址
 * -----------------------------------------------
 * 2023/08/31        V1.0     韦东山       创建
 ***********************************************************************/
void * LCD_GetFrameBuffer(uint32_t *pXres, uint32_t *pYres, uint32_t *pBpp);

/**********************************************************************
 *  LCD_Flush
 *  功能描述：把Framebuffer的数据全部刷新到LCD
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 * -----------------------------------------------
 * 2023/08/31        V1.0     韦东山       创建
 ***********************************************************************/
void LCD_Flush(void);

/**********************************************************************
 *  LCD_ClearFrameBuffer
 *  功能描述：把Framebuffer的数据全部清零
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 * -----------------------------------------------
 * 2023/08/31        V1.0     韦东山       创建
 ***********************************************************************/
void LCD_ClearFrameBuffer(void);


/**********************************************************************
 * 函数名称： LCD_Test
 * 功能描述： LCD测试程序
 * 输入参数： 无
 * 输出参数： 无
 *            无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人        修改内容
 * -----------------------------------------------
 * 2023/08/03        V1.0     韦东山       创建
 ***********************************************************************/
void LCD_Test(void);

void LCD_SetDisPlay(DisPlay_State_t flag);
void LCD_SetDisplayBacklight(uint8_t brightness);
void LCD_SetColorTurn(uint8_t flag);
void LCD_SetDisplayTurn(uint8_t flag);

#endif /* __DRIVER_LCD_H */

