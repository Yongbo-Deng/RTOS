/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_systick.c
 * ժҪ��
 *  
 * �޸���ʷ     �汾��        Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/

#include "main.h"
#include "driver_systick.h"

/*
 * ȫ�ֱ�������
*/

volatile millis_t systick_t = 0;

/*
 *  ��������void SysTickInit(uint32_t cycle)
 *  ���������cycle,����ϵͳ�δ�ʱ������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��ϵͳ�δ�ʱ�ӵ�Ƶ�ʺ��ж����ȼ�
*/
void SysTickInit(uint32_t cycle)
{
    uint32_t init_t = 0;

    init_t = SystemCoreClock/cycle;
  
    /* ʱ��(��λ:s)=1/Ƶ��(��λ:HZ)
     * SystemCoreClockƵ��: 72MHz = 72,000,000
     * ��MCU 1������72,000,000��
     *       1ms����� 72MHz/1000 = 72000��
     * 72000���ǵδ�ʱ�ӵĳ�ʼֵ,�����¼���72000��,��������Ϊ0,�ͻ����һ���ж�
     * �δ�ʱ�ӳ�ʼֵ��Χ:1~16777216
     *
     * SystemCoreClock/1000:    1ms�ж�һ��
     * SystemCoreClock/100000:  10us�ж�һ��
     * SystemCoreClock/1000000: 1us�ж�һ��
     */
    if(HAL_SYSTICK_Config(init_t) != HAL_OK)
    {
        Error_Handler();
    }
    
    // ���õδ�ʱ���ж����ȼ������
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    // ʹ�ܵδ�ʱ���ж�
    HAL_NVIC_EnableIRQ(SysTick_IRQn);
}

/*
 *  ��������void SysTickDelay(uint16_t m)
 *  ���������m-��ʱʱ��
 *  �����������
 *  ����ֵ����
 *  �������ã��δ�ʱ��ʵ�ֵ���ʱ����
*/
void SysTickDelay(uint32_t m)
{
    //systick_t = m;
    //while(systick_t != 0);
}


uint32_t SysTickGetMs(void)
{
    return systick_t;
}

/*
 *  ��������void SysTick_Handler(void)
 *  �����������
 *  �����������
 *  ����ֵ����
 *  �������ã��δ�ʱ�����жϷ�����
*/

