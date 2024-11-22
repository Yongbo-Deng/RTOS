/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#define OPTION_COUNT	1

static bool reset_flag = false;

static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(byte);
static display_t mDraw(void);
static void setReset(void);

void mResetOpen(void)
{
	setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, PSTR(STR_SLEEPMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);
	menuData.func.draw = mDraw;

	setPrevMenuOpen(&prevMenuData, mResetOpen);

	beginAnimation2(NULL);
}

static void mSelect(void)
{
	bool isExiting = exitSelected();
	if(isExiting && reset_flag)
	{
		appconfig_reset();
		HAL_NVIC_SystemReset(); // Restart
	}
	
	setPrevMenuExit(&prevMenuData);
	doAction(isExiting);
}

static void itemLoader(byte num)
{
	UNUSED(num);
	setMenuOption_P(0, PSTR(STR_RESET), menu_rotate, setReset);

	addBackOption();
}

static display_t mDraw(void)
{
	if(menuData.selected == 0)
	{
		char buff[2];		
		sprintf_P(buff, reset_flag ? PSTR("Y") : PSTR("N"));
		
		draw_string(buff, NOINVERT, 61, 30);
	}
	
	return DISPLAY_DONE;
}

static void setReset(void)
{
	reset_flag = !reset_flag;
}

