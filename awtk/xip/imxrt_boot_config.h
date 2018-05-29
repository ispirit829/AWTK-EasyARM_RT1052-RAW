/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* flexspi_boot_config.h - definitions for flexspi boot config block     			 
*									     
* -----------------------------------------------------------------------------
* Copyright (C) Damon Zhang
* All rights reserved.
*
* Author : Yunfeng Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damoncheung@foxmail.com
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
 * \brief imx rt boot config block
 * 
 * \internal
 * \par Modification History
 * - 1.00 17-11-18  yunfeng.zhang, first implementation.
 * \endinternal
 */


#include "board.h"
#include "fsl_common.h"

/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/*******************************************************************************
 * Public define region: constant & MACRO defined here                              
 ******************************************************************************/
#if (defined(__ICCARM__))

#define AT_BOOT_CONFIG_SECTION(var) var @"boot.config"
#define AT_BOOT_IVT_SECTION(var) var @"boot.ivt"
#define AT_BOOT_IVT_DATA_SECTION(var) var @"boot.data"
#define AT_BOOT_IVT_DCD_SECTION(var) var @"boot.dcd"

#elif(defined(__ARMCC_VERSION))

#define AT_BOOT_CONFIG_SECTION(var)     __attribute__((section("boot.config"), used)) var
#define AT_BOOT_IVT_SECTION(var)        __attribute__((section("boot.ivt"), used)) var
#define AT_BOOT_IVT_DATA_SECTION(var)   __attribute__((section("boot.data"), used)) var
#define AT_BOOT_IVT_DCD_SECTION(var)   __attribute__((section("boot.dcd"), used)) var

#elif(defined(__GNUC__))

#define AT_BOOT_CONFIG_SECTION(var) __attribute__((section("boot.config"), used)) var
#define AT_BOOT_IVT_SECTION(var) __attribute__((section("boot.ivt"), used)) var
#define AT_BOOT_IVT_DATA_SECTION(var) __attribute__((section("boot.data"), used)) var
#define AT_BOOT_IVT_DCD_SECTION(var) __attribute__((section("bootk.dcd"), used)) var

#else
#error Toolchain not supported.
#define AT_BOOT_CONFIG_SECTION(var) var
#define AT_BOOT_IVT_SECTION(var)  var
#define AT_BOOT_IVT_DATA_SECTION(var)   var
#endif
/*******************************************************************************
 * Private define region: constant & MACRO defined here                              
 ******************************************************************************/
/**
 * \brief switch 32-bit uint
 *
 * \par example
 * \code
 *  uint32_t a = 0x12345678;
 *  uint32_t b;
 *
 *  b = AM_LONGSWAP(a); //b=0x78563412
 * \endcode
 */
#define UINT32_SWAP(x)  ((((x) & 0xff) << 24) | \
                        ((((x) >> 8) & 0xff) << 16) | \
                        ((((x) >> 16) & 0xff) << 8)  | \
                        ((((x) >> 24) & 0xff)))

/*******************************************************************************
 * extern region: extern global variable & function prototype                 
 ******************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
/*
 * flexspi boot config
 */
typedef struct flexspi_boot_config {
	uint32_t Tag;               		/** \brief 0x000:0x42464346, ascii:” FCFB” */
	uint32_t Version;           		/** \brief 0x004:0x56010000 / 0x56010100 "V1.00/1.10"*/
	uint32_t Reserved0;         		/** \brief 0x008:Reserved */
	uint8_t  readSampleClkSrc;			/** \brief 0x00C:0 – internal loopback 
														 1 – loopback from DQS pad 
														 3 – Flash provided DQS */
	uint8_t  dataHoldTime;				/** \brief 0x00D:Serial Flash CS Hold Time Recommend default value is 0x03 */
	uint8_t  dataSetupTime;				/** \brief 0x00E:Serial Flash CS setup time Recommended default value is 0x03 */
	uint8_t  columnAdressWidth;			/** \brief 0x00F:3 – For HyperFlash 
	                                                     12/13 – For Serial NAND, see datasheet to find correct value 
														 0 – Other devices */
	uint8_t  deviceModeCfgEnable;		/** \brief 0x010:Device Mode Configuration Enable feature
													     0 – Disabled
														 1 – Enabled */
	uint8_t  Reserved1;					/** \brief 0x011:Reserved */
	uint16_t waitTimeCfgCommands;		/** \brief 0x013:Wait time for all configuration commands, unit 100us. */
	uint32_t deviceModeSeq;				/** \brief 0x014:Sequence parameter for device mode configuration */
	uint32_t deviceModeArg;				/** \brief 0x018:Device Mode argument, effective only when deviceModeCfgEnable = 1 */
	uint8_t  configCmdEnable;			/** \brief 0x01C:Config Command Enable feature 
														 0 – Disabled
														 1 – Enabled */
	uint8_t  Reserved2[3];     			/** \brief 0x01D:Reserved */
	uint32_t configCmdSeqs[4];			/** \brief 0x020:Sequences for Config Command, allow 4 separate configuration command sequences. */
	uint32_t cfgCmdArgs[4];				/** \brief 0x030:Arguments for each separate configuration command sequence. */
	uint32_t controllerMiscOption;		/** \brief 0x040:Bit0 – differential clock enable
													     Bit1 – CK2 enable, must set to 0 in this silicon
														 Bit2 – ParallelModeEnable, must set to 0 for this silicon
													     Bit3 – wordAddressableEnable
													     Bit4 – Safe Configuration Frequency
																enable set to 1 for the devices that support DDR
																Read instructions
														 Bit5 – Pad Setting Override Enable
														 Bit6 – DDR Mode Enable, 
														        set to 1 for device supports DDR read command */
	uint8_t  deviceType;				/** \brief 0x044: 1 – Serial NOR 2 – Serial NAND */
	uint8_t  sflashPadType;				/** \brief 0x045: 1 – Single pad
														  2 – Dual pads
														  4 – Quad pads
														  8 – Octal pads */
	uint8_t  serialClkFreq;				/** \brief 0x046:Chip specific value, for this silicon
														  1 – 30 MHz
														  2 – 50 MHz
														  3 – 60 MHz
														  4 – 75 MHz
														  5 – 80 MHz
														  6 – 100 MHz
														  7 – 133 MHz
														  8 – 166 MHz
														  Other value: 30 MHz */
	uint8_t  lutCustomSeqEnable;		/** \brief 0x047: 0 – Use pre-defined LUT sequence index and number
														  1 - Use LUT sequence parameters provided in this block */
	uint8_t  Reserved3[8];     			/** \brief 0x048:Reserved */
	uint32_t sflashA1Size;				/** \brief 0x050:For SPI NOR, 
													     need to fill with actual size For SPI NAND,
														 need to fill with actual size * 2 */
	uint32_t sflashA2Size;				/** \brief 0x054:The same as above */
	uint32_t sflashB1Size;				/** \brief 0x058:The same as above */
	uint32_t sflashB2Size;				/** \brief 0x05C:The same as above */
	uint32_t csPadSettingOverride;		/** \brief 0x060:Set to 0 if it is not supported */
	uint32_t sclkPadSettingOverride;	/** \brief 0x064:Set to 0 if it is not supported */
	uint32_t dataPadSettingOverride;	/** \brief 0x068:Set to 0 if it is not supported */
	uint32_t dqsPadSettingOverride;		/** \brief 0x06C:Set to 0 if it is not supported */
	uint32_t timeoutInMs;				/** \brief 0x070:Maximum wait time during read busy status 
														 0 – Disabled timeout checking feature Other value – Timeout
														 if the wait time exceeds this value. */
	uint32_t commandInterval;			/** \brief 0x074:Unit: ns Currently, it is used for SPI NAND only at high frequency */
	uint32_t dataValidTime;				/** \brief 0x078:Time from clock edge to data valid edge, unit ns. This field
														 is used when the FlexSPI Root clock is less than 100 MHz 
														 and the read sample clock source is device
														 provided DQS signal without CK2 support.
														 [31:16] data valid time for DLLB in terms of 0.1 ns
														 [15:0] data valid time for DLLA in terms of 0.1 ns */
	uint16_t busyOffset;				/** \brief 0x07C:busy bit offset, valid range : 0-31 */
	uint16_t busyBitPolarity;			/** \brief 0x07E:0 – busy bit is 1 if device is busy
														 1 – busy bit is 0 if device is busy */
	union {								/* Each LUT sequence consists of up to 8 instructions = 8 * uint16_t = 4 * uint32_t */
		uint32_t lookupTable[64];		/** \brief 0x080:Lookup table 
														[15:10] : OPCODE
														[ 9: 8] : NUM_PADS
														[ 7: 0] : OPERAND */		
		struct serial_nor_lut_seq {                              
			uint32_t Read_LUT[4];              
			uint32_t ReadStatus_LUT[8];
			uint32_t WriteEnable_LUT[8];
			uint32_t EraseSector_LUT[16];
			uint32_t PageProgram_LUT[8];
			uint32_t ChipErase_LUT[16];
			uint32_t Dummy_LUT[4];
		} nor_lut_seq;
		struct serial_nand_lut_seq {                              
			uint32_t ReadFromCache_LUT[4];              
			uint32_t ReadStatus_LUT[8];
			uint32_t WriteEnable_LUT[4];
			uint32_t ReadFromCacheOdd_LUT[4];
			uint32_t BlockErase_LUT[16];
			uint32_t ProgramLoad_LUT[4];
			uint32_t ProgramLoadOdd_LUT[4];
			uint32_t ReadPage_LUT[8];
			uint32_t ReadEccStatus_LUT[4];
			uint32_t ProgramExecute_LUT[8];
		} nand_lut_seq;
	};

	union {
		uint32_t lutCustomSeq[12];			/** \brief 0x180:Customized LUT sequence, see below table for details.
		                                                     FLEXSPI_BOOT_LUT_CUSTOM_SEQ_INDEX(seq_index, seq_num) */
		struct serial_nor_lut_index {      
			uint32_t Read_index;              
			uint32_t ReadStatus_index;
			uint32_t WriteEnable_index;
			uint32_t EraseSector_index;
			uint32_t PageProgram_index;
			uint32_t ChipErase_index;
			uint32_t Dummy_index;
		} nor_lut_index;
		struct serial_nand_lut_index {                              
			uint32_t ReadFromCache_index;              
			uint32_t ReadStatus_index;
			uint32_t WriteEnable_index;
			uint32_t ReadFromCacheOdd_index;
			uint32_t BlockErase_index;
			uint32_t ProgramLoad_index;
			uint32_t ProgramLoadOdd_index;
			uint32_t ReadPage_index;
			uint32_t ReadEccStatus_index;
			uint32_t ProgramExecute_index;
		} nand_lut_index;
	};
	uint8_t  Reserved4[16];     		/** \brief 0x1B0:Reserved for future use */
} flexspi_boot_config_t;

/* Each LUT sequence consists of up to 8 instructions = 4byte = uint32_t */
#define FLEXSPI_BOOT_LUT_CUSTOM_SEQ_INDEX(seq_index, seq_num)  ( (uint32_t) ( ( (seq_index) << 8 ) | (seq_num) ) )

/*
 * flexspi boot nor flash config
 */
typedef struct flexspi_boot_nor_flash_config {
	flexspi_boot_config_t memCfg;     /** \brief FlexSPI Configuration block */
	uint32_t pageSize;           /** \brief 0x1C0:Page size in terms of bytes, not used by ROM */
	uint32_t sectorSize;		 /** \brief 0x1C4:Sector size in terms of bytes, not used by ROM */
	uint32_t ipCmdSerialClkFreq; /** \brief 0x1C8:Chip specific value, not used by ROM */
	uint8_t  Reserved0[52];      /** \brief 0x1CC:Reserved */
} flexspi_boot_nor_flash_config_t;

#define FLEXSPI_BOOT_NOR_FLASH_CONFIG_BLOCK_SIZE	(sizeof(struct flexspi_boot_nor_flash_config))
/*
 *  flexspi boot nand flash config
 */
typedef struct flexspi_boot_nand_flash_config {
	flexspi_boot_config_t memCfg;   /** \brief FlexSPI Configuration block */
	uint32_t pageDataSize;         
	uint32_t pageTotalSize;
	uint32_t pagesPerBlock;
	uint8_t  bypassReadStatus;
	uint8_t  bypassEccRead;
	uint8_t  hasMultiPlanes;
	uint8_t  skippOddBlocks;
	uint8_t  eccCheckCustomEnable;
	uint8_t  ipCmdSerialClkFreq;
	uint16_t readPageTimeUs;
	uint32_t eccStatusMask;
	uint32_t eccFailureMask;
	uint32_t blocksPerDevice;
	uint8_t  Reserved0[32];     /** \brief 0x1ED:Reserved */
} flexspi_boot_nand_flash_config_t;

#define FLEXSPI_BOOT_NAND_FLASH_CONFIG_BLOCK_SIZE	(sizeof(struct flexspi_boot_nand_flash_config))


/*
 *  Boot Data structure
 */
typedef struct boot_image_data_structure {
	uint32_t start;					/** \brief 0x00: Absolute address of the bootable image  */
	uint32_t length;				/** \brief 0x04: Size of the bootable image */
	uint32_t plugin;				/** \brief 0x08: Plugin flag, set to 0 if it is a normal boot image */
} boot_image_data_structure_t;

/*
 *  IVT data structure
 */
typedef struct boot_image_ivt {

    uint32_t header;	            /** \brief 0x00:BOOT_IMAGE_HADER(tag, length, version) */
	uint32_t entry;					/** \brief 0x04: Absolute address of the first instruction to execute from the image,
	 			     								 or the vector address of the image  */
	uint32_t reserved1;             /** \brief 0x08:Reserved for future use, set to 0 */
	uint32_t dcd;                   /** \brief 0x0c: Absolute address of the image DCD. 
													 It is optional, so this field can be set to NULL if no DCD is required.*/
	uint32_t boot_data;				/** \brief 0x10: Absolute address of the boot data  */
	uint32_t self;					/** \brief 0x14: Absolute address of the IVT.   */
	uint32_t csf;					/** \brief 0x18: Absolute address of the Command Sequence File (CSF) used by the HAB library */
	uint32_t reserved2;				/** \brief 0x1c: Reserved, set to 0   */
} boot_image_ivt_t;

#define BOOT_IMAGE_HADER(tag, length, version) ( (uint32_t) ( (tag) | ((length & 0xFF) << 16) | ((length >> 8) & 0xFF) | ((version) << 24) ) )


/*
 *  DCD   structure
 * @{
 */

typedef uint32_t boot_image_dcd_t;

#define BOOT_DCD_HADER(tag, length, version) ( (uint32_t) ( (uint32_t) ( (tag) | ((length & 0xFF) << 16) | (((length >> 8) & 0xFF) << 8 ) | ((version) << 24) ) ))

/**
	Write cmd:
		Tag = 0xcc,
		Length = 0x0014;(containing the length of the Write Data Command )
		Parameter = 0x04, (flags[7:3],bytes[2:0]),detail see rm doc
*/
#define BOOT_DCD_WRITE_CMD_HEADER(length,Parameter)  \
            	( (uint32_t) ( (0xCC) | ((length & 0xFF) << 16) | (((length >> 8) & 0xFF) << 8) | ((Parameter) << 24) ) )

#define BOOT_DCD_WRITE_CMD_ADDR_VAL(addr, val)   (UINT32_SWAP(addr)), (UINT32_SWAP(val))

/**
	Check cmd:
		Tag = 0xcf,
		Length = 0x0014;(containing the length of the Write Data Command )
		Parameter = 0x04, (flags[7:3],bytes[2:0]) ,detail see rm doc
*/
#define BOOT_DCD_CHECK_CMD_HEADER(length,Parameter)  \
            	( (uint32_t) ( (0xCF) | ((length & 0xFF) << 16) | (((length >> 8) & 0xFF) << 8) | ((Parameter) << 24) ) )

#define BOOT_DCD_CHECK_CMD_ADDR_VAL(addr, val)   (UINT32_SWAP(addr)), (UINT32_SWAP(val))

/* @} End DCD structure */





/*
** End of section using anonymous unions
*/
#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*******************************************************************************
 * main code region: function implement                                        
 ******************************************************************************/


/* end of file */


