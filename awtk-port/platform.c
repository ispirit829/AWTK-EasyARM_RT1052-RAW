/**
 * File:   platform.c
 * Author: AWTK Develop Team
 * Brief:  platform dependent function of aworks
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-05-23 li xianjing <xianjimli@hotmail.com> created
 *
 */
#include "base/mem.h"
#include "base/timer.h"
#include "base/platform.h"

uint32_t g_systick_count = 0;
void SysTick_Handler(void)
{
	g_systick_count++;
}
void delay_ms(uint32_t ms)
{
	uint32_t dest_systick_count = g_systick_count + ms;
	while (g_systick_count < dest_systick_count)
	{;}
}

uint32_t get_time_ms() {
  return g_systick_count;
}

void sleep_ms(uint32_t ms) {
  delay_ms(ms);
}

static char s_tk_mem[4 * 1024 * 1024];

ret_t platform_prepare(void) {
  timer_init(get_time_ms);
  tk_mem_init(s_tk_mem, sizeof(s_tk_mem));

  return RET_OK;
}
