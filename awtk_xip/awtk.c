/**
 * File:   awtk.c
 * Author: AWTK Develop Team
 * Brief:  platform dependent function of rt1052 raw
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
 * 2018-05-29 Perry Wu <wupengyong@zlgmcu.com> created
 *
 */

#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "fsl_gpio.h"
#include "clock_config.h"
#include "fsl_lpi2c.h"
#include "fsl_ft5406_rt.h"

#include "lcd_support.h"
#include "base/lcd.h"
#include "base/mem.h"
#include "base/platform.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
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
static uint8_t awtk_touch_init(void)
{
    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    
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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern int gui_app_start(int lcd_w, int lcd_h);

/*******************************************************************************
 * Variables
 *****************************************************	*************************/
extern volatile bool s_frameDone;
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    touch_event_t touch_event;
    int touch_height;
    int touch_width;
    uint8_t frameBufferIndex = 0;
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitI2C1Pins();
    BOARD_InitSemcPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixelClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();
    SysTick_Config(SystemCoreClock/1000);
    PRINTF("ZLG AWTK GUI example start...\r\n");

    awtk_lcd_init();
    ts_id = awtk_touch_init();
    
    return gui_app_start( APP_IMG_WIDTH, APP_IMG_HEIGHT );
    
    
    
    ELCDIF_SetNextBufferAddr(APP_ELCDIF, (uint32_t)s_frameBuffer[0]);
    while (1)
    {
        memset(s_frameBuffer, 0, sizeof(s_frameBuffer[0]));
        if (ts_id == NULL) {
        ts_id = awtk_touch_init();
        }
        if (kStatus_Success != FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_height, &touch_width))
        {
          return RET_FAIL;
        }
        else if (touch_event != kTouch_Reserved)
        {
            for (int i = touch_height; i < touch_height + APP_IMG_HEIGHT/5; i++)
            {
                for (int j = touch_width; j < touch_width + APP_IMG_WIDTH/5; j++)
                {
                    s_frameBuffer[0][i][j] = 0xf800;
                }
            }
            s_frameDone = false;
            /* Wait for previous frame complete. */
            while (!s_frameDone)
            {
            }
        }
    }
}
