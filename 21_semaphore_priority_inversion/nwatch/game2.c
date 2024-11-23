/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */
#include <stdlib.h>
#include <stdio.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core

#include "draw.h"
#include "resources.h"

#include "driver_lcd.h"
#include "driver_ir_receiver.h"
#include "driver_rotary_encoder.h"
#include "driver_mpu6050.h"

#define CAR_COUNT	3
#define CAR_WIDTH	12
#define CAR_LENGTH	15
#define ROAD_SPEED	6

#define CAR0_KEY	0x30
#define CAR1_KEY	0x18
#define CAR2_KEY	0x7a

#define UPT_MOVE_NONE	0
#define UPT_MOVE_UP		1
#define UPT_MOVE_DOWN	2

#define NOINVERT	false
#define INVERT		true

static uint32_t g_xres, g_yres, g_bpp;
static uint8_t *g_framebuffer;

static QueueHandle_t g_xQueueIR;
static SemaphoreHandle_t g_xSemTicks;

struct car 
{
	int x;
	int y;
	int control_key;
};

struct car g_cars[3] = 
{
	{0,  0, IR_KEY_1},
	{0, 17, IR_KEY_2},
	{0, 34, IR_KEY_3}
};

static const byte carImg[30] ={
	0x40,0xF8,0xEC,0x2C,0x2C,0x38,0xF0,0x10,0xD0,0x30,0xE8,0x4C,0x4C,0x9C,0xF0,
	0x02,0x1F,0x37,0x34,0x34,0x1C,0x0F,0x08,0x0B,0x0C,0x17,0x32,0x32,0x39,0x0F,
};

static const byte clearImg[30] ={
	0,0,0,0,0,0,0,0,0,0,0,0,
};

static const byte roadMarking[] ={
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
};


static void ClearCar(struct car *pcar)
{
	draw_bitmap(pcar->x, pcar->y, clearImg, 15, 16, NOINVERT, 0);
	draw_flushArea(pcar->x, pcar->y, 15, 16);
}

static void DrawCar(struct car *pcar)
{
	draw_bitmap(pcar->x, pcar->y, carImg, 15, 16, NOINVERT, 0);
	draw_flushArea(pcar->x, pcar->y, 15, 16);
}

static void CarTask1(void *params)
{
	struct car *pcar = params;
	struct ir_data idata;

	QueueHandle_t xQueueIR = xQueueCreate(10, sizeof(struct ir_data));
	RegisterQueueHandle(xQueueIR);

	DrawCar(pcar);
	
	xSemaphoreTake(g_xSemTicks, portMAX_DELAY);

	while (1)
	{
		/* Read keyValue and queue */
		// xQueueReceive(xQueueIR, &idata, portMAX_DELAY);
		// if (idata.val == pcar->control_key)

		{
			if (pcar->x < (g_xres - CAR_LENGTH))
			{
				/* Clear car */
				ClearCar(pcar);
				/* New position */
				pcar->x += 1;
				/* Draw car */
				DrawCar(pcar);
				vTaskDelay(50);
			}
			else
			{
				xSemaphoreGive(g_xSemTicks);
				vTaskDelete(NULL);
			}
		}
	}
}

static void CarTask2(void *params)
{
	struct car *pcar = params;
	struct ir_data idata;

	QueueHandle_t xQueueIR = xQueueCreate(10, sizeof(struct ir_data));
	RegisterQueueHandle(xQueueIR);

	DrawCar(pcar);

	vTaskDelay(1000);
	
	// xSemaphoreTake(g_xSemTicks, portMAX_DELAY);

	while (1)
	{
		{
			if (pcar->x < (g_xres - CAR_LENGTH))
			{
				/* Clear car */
				ClearCar(pcar);
				/* New position */
				pcar->x += 1;
				/* Draw car */
				DrawCar(pcar);
				mdelay(50);
			}
			else
			{
				// xSemaphoreGive(g_xSemTicks);
				// vTaskDelete(NULL);
			}
		}
	}
}

static void CarTask3(void *params)
{
	struct car *pcar = params;
	struct ir_data idata;

	QueueHandle_t xQueueIR = xQueueCreate(10, sizeof(struct ir_data));
	RegisterQueueHandle(xQueueIR);

	DrawCar(pcar);

	vTaskDelay(2000);
	
	xSemaphoreTake(g_xSemTicks, portMAX_DELAY);

	while (1)
	{
		{
			if (pcar->x < (g_xres - CAR_LENGTH))
			{
				/* Clear car */
				ClearCar(pcar);
				/* New position */
				pcar->x += 1;
				/* Draw car */
				DrawCar(pcar);
				vTaskDelay(50);
			}
			else
			{
				xSemaphoreGive(g_xSemTicks);
				vTaskDelete(NULL);
			}
		}
	}
}

void car_game(void) 
{
	uint16_t i, j;
	g_framebuffer = LCD_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
	g_xSemTicks = xSemaphoreCreateBinary();
	xSemaphoreGive(g_xSemTicks);
    draw_init();
    draw_end();

	/*	Draw 3 cars with road. OLED resolution: 128 x 64	*/
	for (i = 0; i < 3; i++)
	{
		/*Draw roadmark*/
		for (j = 0; j < 8; j++)
		{
			draw_bitmap(16 * j, 16 + 17 * i, roadMarking, 8, 1, NOINVERT, 0);
			draw_flushArea(16 * j, 16 + 17 * i, 8, 1);
		}
	}

	/*Create 3 car tasks*/
	xTaskCreate(CarTask1, "car1", 128, &g_cars[0], osPriorityNormal, NULL);
	xTaskCreate(CarTask2, "car2", 128, &g_cars[1], osPriorityNormal + 2, NULL);
	xTaskCreate(CarTask3, "car3", 128, &g_cars[2], osPriorityNormal + 3, NULL);

}
