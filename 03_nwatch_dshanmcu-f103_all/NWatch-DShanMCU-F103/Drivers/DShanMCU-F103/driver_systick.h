/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_systick.h
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/

#ifndef __DRIVER_SYSTICK_H
#define __DRIVER_SYSTICK_H

#include "stm32f1xx_hal.h"

#define CYCLE_100MS   10
#define CYCLE_10MS    100
#define CYCLE_1MS     1000 
#define CYCLE_100US   10000
#define CYCLE_10US    100000
#define CYCLE_1US     1000000

/*
 *  函数名：void SysTickInit(void)
 *  输入参数：cycle,设置系统滴答时钟周期
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化系统滴答时钟的频率和中断优先级
*/
extern void SysTickInit(uint32_t cycle);

/*
 *  函数名：void SysTickDelay(uint16_t m)
 *  输入参数：m-延时时间
 *  输出参数：无
 *  返回值：无
 *  函数作用：滴答定时器实现的延时函数
*/
extern void SysTickDelay(uint32_t m);

millis_t SysTickGetMs(void);

extern volatile uint32_t systick_t;

#endif


