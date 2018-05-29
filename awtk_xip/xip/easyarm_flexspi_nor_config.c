/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* i2c.h - definitions for the i2c-bus interface			     			 
*									     
* -----------------------------------------------------------------------------
* Copyright (C)  
* All rights reserved.
*
* Author : YunFeng Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damonzhang92@foxmail.com
*
* -----------------------------------------------------------------------------
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/**
 * \file
 * \brief sim spi driver
 * 
 * \internal
 * \par Modification History
 * - 1.00 17-11-18  yunfeng.zhang, first implementation.
 * - 2.00 18-05-10  yunfeng.zhang, modified for issi boot.
 * \endinternal
 */


#include "imxrt_boot_config.h"

/*******************************************************************************
 * Config define                   
 ******************************************************************************/
#define QSPI_MX25L064           1
#define QSPI_IS25LP064A 		2

#define EASYARM_RT1052_FLASH   	QSPI_IS25LP064A

/*******************************************************************************
 * Private define region: constant & MACRO defined here                              
 ******************************************************************************/

/*******************************************************************************
 * extern region: extern global variable & function prototype                 
 ******************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/


/*****************************************************************************
 * Public functions
 ****************************************************************************/
#if (EASYARM_RT1052_FLASH == QSPI_MX25L064)


AT_BOOT_CONFIG_SECTION(const flexspi_boot_nor_flash_config_t easyarm_flexspi_nor_config)  = {
	.memCfg = {

		.Tag = 0x42464346,   /* ascii:” FCFB” */
		.Version = 0x56010400,
		
		.readSampleClkSrc = 0x00,
		.dataHoldTime = 0x03,
		.dataSetupTime = 0x03,
		.columnAdressWidth = 0x00,

		.deviceModeCfgEnable = 0x00,    /* 0x10 ~ 0x3F  = 0x00 */
		.waitTimeCfgCommands = 0x00,

		.controllerMiscOption = 0x00000051,
		.deviceType = 0x00,
		.sflashPadType = 0x04,
		.serialClkFreq = 0x06,
		.lutCustomSeqEnable = 0x00,

		.sflashA1Size = 0x04000000,
		.sflashA2Size = 0x00000000,
		.sflashB1Size = 0x00000000,
		.sflashB2Size = 0x00000000,
		
		.dataValidTime = 0x00000000,
		.busyOffset = 0x000f,
		.busyBitPolarity = 0x0001,

		/* LUT sequence definition for Serial NOR */
		/* Read Data */
        .nor_lut_seq = {
            .Read_LUT[0] = 0x0818046B,	
            .Read_LUT[1] = 0x26043208,
            .Read_LUT[2] = 0x00000000,
            .Read_LUT[3] = 0x00000000,            
        
            /* Read Status */	
            .ReadStatus_LUT[0] = 0x24040405,	
            .ReadStatus_LUT[1] = 0x00000000,
            //.lookupTable[2 ~ 7] = 0x00000000,

            /* Write Enable */
            .WriteEnable_LUT[0] = 0x00000406,	
            .WriteEnable_LUT[1] = 0x00000000,
            //.lookupTable[2~7] = 0x00000000,

            /* Erase Sector  */
            .EraseSector_LUT[0] = 0x08180420,	
            .EraseSector_LUT[1] = 0x00000000,
            //.EraseSector_LUT[2~15] = 0x00000000,

            /* program page */
            .PageProgram_LUT[0] = 0x08180438,	
            .PageProgram_LUT[1] = 0x00002204,
            //.PageProgram_LUT[2~7] = 0x00000000,

            /* Chip Erase */
            .ChipErase_LUT[0] = 0x00000000,	
            .ChipErase_LUT[1] = 0x00000000,
            //.ChipErase_LUT[2~15] = 0x00000000,

            .Dummy_LUT[0] = 0x00000000,
            .Dummy_LUT[1] = 0x00000000,
            //.Dummy_LUT[2~3] = 0x00000000,
            /*  60 ~ 63 = 0x00000000 */
        },
        
        /* LUT sequence Index in lookup table definition for Serial NOR */
        .nor_lut_index = {
            .Read_index = 0x00000000,
            .ReadStatus_index = 0x00000102,
            .WriteEnable_index = 0x00000302,
            .EraseSector_index = 0x00000504,
            .PageProgram_index = 0x00000902,
            .ChipErase_index = 0x00000B04,
        },

	},
	.pageSize = 0x00000100,
	.sectorSize = 0x0001000,
	.ipCmdSerialClkFreq = 0x00000001,
};

#elif (EASYARM_RT1052_FLASH == QSPI_IS25LP064A)
	
AT_BOOT_CONFIG_SECTION(const flexspi_boot_nor_flash_config_t easyarm_flexspi_nor_config)  = {
	.memCfg = {

		.Tag = 0x42464346,   /* ascii:” FCFB” */
		.Version = 0x56010400,
		
        
		.readSampleClkSrc = 0x00,
		.dataHoldTime = 0x03,
		.dataSetupTime = 0x03,
		.columnAdressWidth = 0x00,

		.deviceModeCfgEnable = 0x00,    /* 0x10 ~ 0x3F  = 0x00 */
		.waitTimeCfgCommands = 0x10,   //0x00 wu 

		.controllerMiscOption = 0x00000000,
		.deviceType = 0x01,
		.sflashPadType = 0x04,
		.serialClkFreq = 0x07,
		.lutCustomSeqEnable = 0x00,

		.sflashA1Size = 0x00800000,
		.sflashA2Size = 0x00000000,
		.sflashB1Size = 0x00000000,
		.sflashB2Size = 0x00000000,
		
		.dataValidTime = 0x00000000,
		.busyOffset = 0x000f,
		.busyBitPolarity = 0x0001,

		/* LUT sequence definition for Serial NOR */
		/* Read Data */
        .nor_lut_seq = {
            .Read_LUT[0] = 0x0818046B,	
            .Read_LUT[1] = 0x26043208,
            .Read_LUT[2] = 0x00000000,
            .Read_LUT[3] = 0x00000000,            
        
            /* Read Status */	
            .ReadStatus_LUT[0] = 0x24040405,	
            .ReadStatus_LUT[1] = 0x00000000,
            //.lookupTable[2 ~ 7] = 0x00000000,

            /* Write Enable */
            .WriteEnable_LUT[0] = 0x00000406,	
            .WriteEnable_LUT[1] = 0x00000000,
            //.lookupTable[2~7] = 0x00000000,

            /* Erase Sector  */
            .EraseSector_LUT[0] = 0x08180420,	
            .EraseSector_LUT[1] = 0x00000000,
            //.EraseSector_LUT[2~15] = 0x00000000,

            /* program page */
            .PageProgram_LUT[0] = 0x08180438,	
            .PageProgram_LUT[1] = 0x00002204,
            //.PageProgram_LUT[2~7] = 0x00000000,

            /* Chip Erase */
            .ChipErase_LUT[0] = 0x00000000,	
            .ChipErase_LUT[1] = 0x00000000,
            //.ChipErase_LUT[2~15] = 0x00000000,

            .Dummy_LUT[0] = 0x00000000,
            .Dummy_LUT[1] = 0x00000000,
            //.Dummy_LUT[2~3] = 0x00000000,
            /*  60 ~ 63 = 0x00000000 */
        },
        
        /* LUT sequence Index in lookup table definition for Serial NOR */
        .nor_lut_index = {
            .Read_index = 0x00000000,
            .ReadStatus_index = 0x00000102,
            .WriteEnable_index = 0x00000302,
            .EraseSector_index = 0x00000504,
            .PageProgram_index = 0x00000902,
            .ChipErase_index = 0x00000B04,
        },

	},
	.pageSize = 0x00000100,
	.sectorSize = 0x0001000,
	.ipCmdSerialClkFreq = 0x00000001,
};
#else
	#error FlashType not supported.
#endif

AT_BOOT_IVT_DATA_SECTION(const boot_image_data_structure_t easyarm_flexspi_nor_boot_data) = {
	
	.start = 0x60000000,
	.length = 0x00800000,
	.plugin = 0x00000000,
};


#if 0
//config tcm = 512 - 64KB
AT_BOOT_IVT_DCD_SECTION(const boot_image_dcd_t device_config_data[]) = {
	BOOT_DCD_HADER(0xd2,0x0018,0x40), 				//{Tag = 0xD2, Length = 0x0018; Version = 0x40 }
	
	BOOT_DCD_WRITE_CMD_HEADER(0x0014,0x04),					/*{Write cmd:Tag = 0xcc,
	                                         Length = 0x0014;(containing the length of the Write Data Command )
											 Parameter = 0x04, (flags[7:3],bytes[2:0])
								   } */
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400ac044,0x5FFFFFFF),   //0x400a c044 = 0x5FFFFFFF
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400ac040,0x00200007)
};

#endif

/* config semc sdram enable */
AT_BOOT_IVT_DCD_SECTION(const boot_image_dcd_t device_config_data[]) = {
	BOOT_DCD_HADER(0xd2,0x03FC,0x40), 				//{Tag = 0xD2, Length = 0x0018; Version = 0x40 }
	
	BOOT_DCD_WRITE_CMD_HEADER(0x02F4,0x04),		    /*{Write cmd:Tag = 0xcc,
	                                         		Length = 0x0014;(containing the length of the Write Data Command )
											 		Parameter = 0x04, (flags[7:3],bytes[2:0])
								   					} */
	/* Enable all peripheral clk CCM_CCGR0-6 = 0xFFFFFFFF*/
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC068,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC06C,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC070,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC074,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC078,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC07C,0xFFFFFFFF),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC080,0xFFFFFFFF),

	/* config semc clk = 144MHz */
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400D8030,0x00002001),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400D8100,0x00210000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x400FC014,0x00010D40),

	/* Config IOMUX */
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8014, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8018, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F801C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8020, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8024, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8028, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F802C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8030, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8034, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8038, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F803C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8040, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8044, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8048, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F804C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8050, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8054, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8058, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F805C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8060, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8064, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8068, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F806C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8070, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8074, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8078, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F807C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8080, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8084, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8088, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F808C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8090, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8094, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8098, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F809C, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80A0, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80A4, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80A8, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80AC, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80B0, 0x00000010), // EMC_39, DQS PIN, enable SION
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80B4, 0x00000000),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F80B8, 0x00000000),

	// PAD ctrl
	// drive strength = 0x7 to increase drive strength
	// otherwise the data7 bit may fail.
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8204, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8208, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F820C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8210, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8214, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8218, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F821C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8220, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8224, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8228, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F822C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8230, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8234, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8238, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F823C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8240, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8244, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8248, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F824C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8250, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8254, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8258, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F825C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8260, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8264, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8268, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F826C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8270, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8274, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8278, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F827C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8280, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8284, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8288, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F828C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8290, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8294, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F8298, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F829C, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F82A0, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F82A4, 0x000110F9),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x401F82A8, 0x000110F9),

	/* Config SDR Controller Registers */
	/* disable semc */
	BOOT_DCD_WRITE_CMD_HEADER(0x000C,0x14),		    /*{Write cmd:Tag = 0xcc,
	                                         		Length = 0x0014;(containing the length of the Write Data Command )
											 		Parameter = 0x04, (flags[7:3],bytes[2:0])
								   					} */
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0000, 0x00000002), // MCR (0x402F0000 &= ~0x00000002)

	/* config semc */
	BOOT_DCD_WRITE_CMD_HEADER(0x0084,0x04),		    /*{Write cmd:Tag = 0xcc,
	                                         		Length = 0x0014;(containing the length of the Write Data Command )
											 		Parameter = 0x04, (flags[7:3],bytes[2:0])
								   					} */
	/* Config SDR Controller Registers */
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0000, 0x10000004), // MCR  enable semc master
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0008, 0x00030524), // BMCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F000C, 0x06030524), // BMCR1
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0010, 0x8000001B), // BR0, 32MB
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0014, 0x8200001B), // BR1, 32MB
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0004, 0x00000008),  // IOCR, SEMC_CCSX0 as SDRAM_CS1
	
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0040,0x00000F31), // SDRAMCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0044,0x00652922), // SDRAMCR1
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0048,0x00010920), // SDRAMCR2
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F004C,0x50210A08), // SDRAMCR3
	/*
		0x402F0074 = 0x00652922, 
		0x402F0078 = 0x00010920, 
		0x402F007C = 0x50210A08, 
	*/
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0080,0x00000021), // DBICR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0084,0x00888888), // DBICR1
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0094,0x00000002), // IPCR1
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0098,0x00000000), // IPCR2
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0090,0x80000000), // IPCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F009C,0xA55A000F), // IPCMD, SD_CC_IPREA

	/* WaitIpCmdDone */
	BOOT_DCD_CHECK_CMD_HEADER(0x000C,0x1C),	
	BOOT_DCD_CHECK_CMD_ADDR_VAL(0x402F003C, 0x00000001),

	BOOT_DCD_WRITE_CMD_HEADER(0x0014,0x04),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0090,0x80000000), // IPCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F009C,0xA55A000C), // SD_CC_IAF
	/* WaitIpCmdDone */
	BOOT_DCD_CHECK_CMD_HEADER(0x000C,0x1C),	
	BOOT_DCD_CHECK_CMD_ADDR_VAL(0x402F003C, 0x00000001),

	BOOT_DCD_WRITE_CMD_HEADER(0x0014,0x04),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0090,0x80000000), // IPCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F009C,0xA55A000C), // SD_CC_IAF
	/* WaitIpCmdDone */
	BOOT_DCD_CHECK_CMD_HEADER(0x000C,0x1C),	
	BOOT_DCD_CHECK_CMD_ADDR_VAL(0x402F003C, 0x00000001),

	BOOT_DCD_WRITE_CMD_HEADER(0x001C,0x04),
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F00A0,0x00000033), // IPTXDAT
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F0090,0x80000000), // IPCR0
	BOOT_DCD_WRITE_CMD_ADDR_VAL(0x402F009C,0xA55A000A), // SD_CC_IMS
	/* WaitIpCmdDone */
	BOOT_DCD_CHECK_CMD_HEADER(0x000C,0x1C),	
	BOOT_DCD_CHECK_CMD_ADDR_VAL(0x402F003C, 0x00000001),
};



AT_BOOT_IVT_SECTION(const boot_image_ivt_t easyarm_flexspi_nor_ivt) = {
	
    .header = BOOT_IMAGE_HADER(0xD1, 0x0020, 0x41),
	.entry = 0x60002000,  //text start
	.dcd = ((uint32_t)(device_config_data)),
	.boot_data = ((uint32_t)(&easyarm_flexspi_nor_boot_data)),
	.self = 0x60001000,
	.csf = 0x00000000,

	.reserved1 = 0x00000000,
	.reserved2 = 0x00000000,
};

/*******************************************************************************
 * main code region: function implement                                        
 ******************************************************************************/


/* end of file */


