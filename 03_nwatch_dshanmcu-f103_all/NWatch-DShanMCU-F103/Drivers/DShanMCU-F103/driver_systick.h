/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_systick.h
 * ժҪ��
 *  
 * �޸���ʷ     �汾��        Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
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
 *  ��������void SysTickInit(void)
 *  ���������cycle,����ϵͳ�δ�ʱ������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��ϵͳ�δ�ʱ�ӵ�Ƶ�ʺ��ж����ȼ�
*/
extern void SysTickInit(uint32_t cycle);

/*
 *  ��������void SysTickDelay(uint16_t m)
 *  ���������m-��ʱʱ��
 *  �����������
 *  ����ֵ����
 *  �������ã��δ�ʱ��ʵ�ֵ���ʱ����
*/
extern void SysTickDelay(uint32_t m);

millis_t SysTickGetMs(void);

extern volatile uint32_t systick_t;

#endif


