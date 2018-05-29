/**
 * file:   main_loop_aworks_raw.c
 * Author: AWTK Develop Team
 * brief:  main loop for aworks
 *
 * copyright (c) 2018 - 2018 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
#include "fsl_elcdif.h"
#include "fsl_lpi2c.h"
#include "fsl_ft5406_rt.h"

#include "base/idle.h"
#include "base/timer.h"
#include "lcd/lcd_mem_rgb565.h"
#include "main_loop/main_loop_simple.h"


/* Macros for the touch touch controller. */
#define BOARD_TOUCH_I2C LPI2C1

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)

#define BOARD_TOUCH_I2C_CLOCK_FREQ ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
#define BOARD_TOUCH_I2C_BAUDRATE 100000U

#define LPI2C_DATA_LENGTH 32U

#define LPI2C_MASTER_IRQ LPI2C1_IRQn
#define LPI2C_MASTER_IRQHandler LPI2C1_IRQHandler
#define BOARD_TOUCH_INT_PORT PORTA
#define BOARD_TOUCH_INT_PIN 2

/* Touch driver handle. */
static ft5406_rt_handle_t touchHandle;
static uint8_t ts_id = NULL;
static uint8_t AWTK_Touch_Init(void)
{
    lpi2c_master_config_t masterConfig = {0};
    /*
    * masterConfig.debugEnable = false;
    * masterConfig.ignoreAck = false;
    * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
    * masterConfig.baudRate_Hz = 100000U;
    * masterConfig.busIdleTimeout_ns = 0;
    * masterConfig.pinLowTimeout_ns = 0;
    * masterConfig.sdaGlitchFilterWidth_ns = 0;
    * masterConfig.sclGlitchFilterWidth_ns = 0;
    */
    LPI2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Hz = BOARD_TOUCH_I2C_BAUDRATE;

    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(BOARD_TOUCH_I2C, &masterConfig, BOARD_TOUCH_I2C_CLOCK_FREQ);

    /* Initialize the touch handle. */
    FT5406_RT_Init(&touchHandle, BOARD_TOUCH_I2C);
    ts_id ++;
    return ts_id;
}

ret_t platform_disaptch_input(main_loop_t* loop) {
    touch_event_t touch_event;
    int touch_x;
    int touch_y;
    
    if (ts_id == NULL) {
        ts_id = AWTK_Touch_Init();
    }
    
    if (kStatus_Success != FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    {
      return RET_FAIL;
    }
    else if (touch_event != kTouch_Reserved)
    {
        main_loop_post_pointer_event(loop, ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact)), touch_y,touch_x);
        return RET_OK;
    }
    return RET_OK;
}

extern uint32_t* get_online_fb(void);
extern uint32_t* get_offline_fb(void);

lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  lcd_t* lcd = lcd_mem_rgb565_create_double_fb(w, h, (uint8_t*) get_online_fb(),
      (uint8_t*) get_offline_fb());

  return lcd;
}

#include "main_loop/main_loop_raw.inc"
