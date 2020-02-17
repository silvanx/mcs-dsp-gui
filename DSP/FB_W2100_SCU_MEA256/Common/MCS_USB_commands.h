// keep_internal
// shared between windows and embedded devices

#ifndef _MCS_USB_COMMANDS_H_
#define _MCS_USB_COMMANDS_H_

/*! \cond internal */

/*! \file
 * \brief Structures needed for communication with the STG200x
 */

#ifndef __C30

#ifndef __18CXX
#ifndef __TMS320C28XX__
#ifndef __TMS320C55XX__
#ifndef _TMS320C6X
#ifndef __C51__
#pragma pack(1)
#endif
#endif
#endif
#endif
#endif
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "MCS_USB_def.h"

#define MCS_VENDOR_ID          0x1E26
#define CYPRESS_VENDOR_ID      0x04B4

#define ALA_VC3_VENDOR_ID	0x1234

// Product IDs

// Product IDs for Ala Vendor ID
#define ALA_VC3_PRODUCT_ID	0x0002

// Prduct IDs for Cypress Vendor ID

#define CY_FX1_PRODUCT_ID  0x6473
#define CY_FX2_PRODUCT_ID  0x8613
#define CY_FX3_PRODUCT_ID  0x00F3

// Product ID for MC_Card
#define MCS_PRODUCT_ID_MC_CARD 0x80E8

// Product IDs for MCS Vendor ID

// Range 0xA1xx for Campden instrumenst
#define MCS_PRODUCT_ID_CAMPDEN_CI4600EPHYS_VIDEO_DATA_INTEGRATOR  0xA100

// Range 0xB1xx for HEKA
#define MCS_PRODUCT_ID_HEKA_LIH30 0xB101

// Range 0xCxxx for MCS
#define MCS_PRODUCT_ID_STG     0xc104

#define MCS_PRODUCT_ID_MEAUSB     0xc204 // only used with old Vendor ID 0xabcd
#define MCS_PRODUCT_ID_OCTOPOT 0xc205
#define MCS_PRODUCT_ID_TERSENS 0xc206
#define MCS_PRODUCT_ID_DOTRIAPOT 0xc207
#define MCS_PRODUCT_ID_ME256_OLD_UNUSED_DONOTUSE  0xc208 // changed to 0xc504 (MCS_PRODUCT_ID_ME256) to have all MEA products in the 0xc5xx range

#define MCS_PRODUCT_ID_HLA     0xc209

#define MCS_PRODUCT_ID_STG400x 0xc240
#define MCS_PRODUCT_ID_STG4002 0xc241
#define MCS_PRODUCT_ID_STG4004 0xc242
#define MCS_PRODUCT_ID_STG4008 0xc243

#define MCS_PRODUCT_ID_STG400x_OPTO 0xc244
#define MCS_PRODUCT_ID_STG4002_OPTO 0xc245
#define MCS_PRODUCT_ID_STG4004_OPTO 0xc246
#define MCS_PRODUCT_ID_STG4008_OPTO 0xc247

#define MCS_PRODUCT_ID_STG400x_REV_E 0xc248

#define MCS_PRODUCT_ID_STG3008_FA 0xc24b

#define MCS_PRODUCT_ID_STG500x 0xc250

#define MCS_PRODUCT_ID_MULTIWELLOPTOSTIM 0xc260

#define MCS_PRODUCT_ID_STG_RANGE_END 0xc280

#define MCS_PRODUCT_ID_GENERIC 0xc300

#define MCS_PRODUCT_ID_PGA     0xc301

#define MCS_PRODUCT_ID_PCX     0xC321
#define MCS_PRODUCT_ID_TCX     0xC322
#define MCS_PRODUCT_ID_FCX     0xC323
#define MCS_PRODUCT_ID_FCB     0xC324
#define MCS_PRODUCT_ID_TC01    0xC325
#define MCS_PRODUCT_ID_TC02    0xC326

#define MCS_PRODUCT_ID_RETINA_LED 0xC330
#define MCS_PRODUCT_ID_RETINA_AMS_DONGLE 0xC331
#define MCS_PRODUCT_ID_OKUVISION_STIMULATOR 0xC332
#define MCS_PRODUCT_ID_RETINAIMPLANT_EXTERNBCTESTER 0xC333
#define MCS_PRODUCT_ID_RIAG_TRIGGERBOX_IMS 0xC334
#define MCS_PRODUCT_ID_RIAG_TRIGGERBOX_AMS 0xC335
#define MCS_PRODUCT_ID_RIAG_TRIGGERBOX_AMS3 0xC336
#define MCS_PRODUCT_ID_RETINAIMPLANT_EXTERNDTESTER 0xC337
#define MCS_PRODUCT_ID_RIAG_FUNKDONGLES 0xC338
#define MCS_PRODUCT_ID_RIAG_EXTERNSTESTER 0xC339
#define MCS_PRODUCT_ID_RIAG_DONGLES 0xC33A
#define MCS_PRODUCT_ID_RIAG_TRIGGERBOX_R5 0xC33B

#define MCS_PRODUCT_ID_FYI 0xC350
#define MCS_PRODUCT_ID_HEPARAT 0xC351

#define MCS_PRODUCT_ID_MEA_SWITCH 0xC401
#define MCS_PRODUCT_ID_MEA_IMPEDANCE 0xC402
#define MCS_PRODUCT_ID_CHANNELTEST 0xC403
#define MCS_PRODUCT_ID_SW2TO64 0xC404
#define MCS_PRODUCT_ID_PERISTALTIC_PUMP 0xC405
#define MCS_PRODUCT_ID_MEA_SWITCH_2_1 0xC406
#define MCS_PRODUCT_ID_MEA_SWITCH_4_2 0xC407
#define MCS_PRODUCT_ID_PPS4plus1 0xC408
#define MCS_PRODUCT_ID_PPS5 0xC409
#define MCS_PRODUCT_ID_PPS2 0xC40A
#define MCS_PRODUCT_ID_PPS5_DIG 0xC40B

#define MCS_PRODUCT_ID_MEA_CLEAN 0xC410
#define MCS_PRODUCT_ID_MEA_COAT 0xC411
#define MCS_PRODUCT_ID_MULTIWELL_ICC 0xC412
#define MCS_PRODUCT_ID_MBC08 0xC413
#define MCS_PRODUCT_ID_PPC 0xC414

#define MCS_PRODUCT_ID_MEA1060    0xc501 
#define MCS_PRODUCT_ID_MEA_SANOFI 0xc502
#define MCS_PRODUCT_ID_ME16_C54xx 0xc503 // TI C54xx based design
#define MCS_PRODUCT_ID_ME256      0xc504
#define MCS_PRODUCT_ID_ME128      0xc505
#define MCS_PRODUCT_ID_ME64       0xc506
#define MCS_PRODUCT_ID_ME32       0xc507
#define MCS_PRODUCT_ID_ME16       0xc508

#define MCS_PRODUCT_ID_MEA2100_MINI_USB_DEVELOP  0xc520

#define MCS_PRODUCT_ID_MEA256     0xc540
#define MCS_PRODUCT_ID_MEA2100    0xc541
#define MCS_PRODUCT_ID_MEA2100_32 0xc542
#define MCS_PRODUCT_ID_MEA21_LITE 0xc543
#define MCS_PRODUCT_ID_MULTIWELL  0xc544
#define MCS_PRODUCT_ID_MEA2100_256	0xc545
#define MCS_PRODUCT_ID_ME2100	  0xc546
#define MCS_PRODUCT_ID_MEA2100_BETA_SCREEN 0xc547
#define MCS_PRODUCT_ID_MEA2100_MINI 0xc548
#define MCS_PRODUCT_ID_TBSI_DACQ  0xC549
#define MCS_PRODUCT_ID_MULTIWELL_MEA_MINI 0xC54A
#define MCS_PRODUCT_ID_MULTIBOOT  0xc550
#define MCS_PRODUCT_ID_WPA8       0xc580
#define MCS_PRODUCT_ID_WPA4       0xc581
#define MCS_PRODUCT_ID_WPA16      0xc582
#define MCS_PRODUCT_ID_WPA32      0xc583
#define MCS_PRODUCT_ID_W2100      0xc588
#define MCS_PRODUCT_ID_NEUROCHIP  0xc5a0

#define MCS_PRODUCT_ID_WPA        0xC580
#define MCS_PRODUCT_ID_WPA_MASK   0xFFF8

#define MCS_PRODUCT_ID_USB_TEST 0xC600
#define MCS_PRODUCT_ID_SOFTWAREDONGLE 0xC601

#define MCS_PRODUCT_ID_PATHIDENT 0xC701
#define MCS_PRODUCT_ID_NF_GEN 0xC702
#define MCS_PRODUCT_ID_SAFEIS 0xC703
#define MCS_PRODUCT_ID_ENCAPSULATOR 0xC704
#define MCS_PRODUCT_ID_NEUROCHIP_CONFIG 0xC705
#define MCS_PRODUCT_ID_MEASURETABLE 0xC706
#define MCS_PRODUCT_ID_PEDOTER 0xC707

#define MCS_PRODUCT_ID_ROBOOCYTE2 0xC801
#define MCS_PRODUCT_ID_ROBOINJECT 0xC802
#define MCS_PRODUCT_ID_HICLAMP 0xC803
#define MCS_PRODUCT_ID_PATCHSERVER 0xC804
#define MCS_PRODUCT_ID_DILUTOR 0xC805
#define MCS_PRODUCT_ID_HICLAMP4UART 0xC806
#define MCS_PRODUCT_ID_USSING_TER 0xC807

#define MCS_PRODUCT_ID_IM16S16KRA 0xC901
#define MCS_PRODUCT_ID_IM64KRB 0xC902
#define MCS_PRODUCT_ID_IS32KRA 0xC903
#define MCS_PRODUCT_ID_IM64KRC 0xC904
#define MCS_PRODUCT_ID_IM16S8KRA 0xC905
#define MCS_PRODUCT_ID_IM16KRC 0xC906
#define MCS_PRODUCT_ID_SMARTIMPLANT 0xC907
#define MCS_PRODUCT_ID_POSITION_IMP 0xC908
#define MCS_PRODUCT_ID_POSITION_BASE 0xC909

//Range 0xD1xx for Warner devices
#define MCS_PRODUCT_ID_WARNER_VALVE_CONTROL 0xD101
#define MCS_PRODUCT_ID_WARNER_TEER_MACHINE 0xD111
#define MCS_PRODUCT_ID_WARNER_USSING 0xD121

/* Vendor requests */

#define STG_START          0x18
#define STG_STOP           0x19
/* bitmask of devices to start and stop */
    #define STARTSTOP_DEVICE_STG     0x0001
    #define STARTSTOP_DEVICE_DACQ    0x0002
    #define STARTSTOP_DEVICE_DACQ_D0 0x0002
    #define STARTSTOP_DEVICE_DACQ_D1 0x0004
    #define STARTSTOP_DEVICE_DACQ_D2 0x0008
    #define STARTSTOP_DEVICE_DACQ_D3 0x0010
	#define STARTSTOP_DEVICE_DACQ_VMASK 0x001e // 4bit for virtual MEA devices
	#define STOP_OPTION_SAVESTOP 0x80 /* Stop only if bypass is not active */

#define SET_DACQ_SAMPLERATE 0x23


#define DACQ_COMMAND        0x25
	#define SET_TRIGGERPERIOD    0x00
	#define SET_TRIGGERMASKVALUE 0x01
	#define DACQ_UART_COMMAND    0x10
	#define DACQ_SET_POTI        0x20
	#define DACQ_GET_POTI        0x21

#define TER_COMMAND         0x26
	#define TER_SET_DAC_VALUE   0x00
	#define TER_SET_MODE		0x01
	#define TER_SET_CHANNEL		0x02

#define PGA_COMMAND			0x27
	#define PGA_SETGAIN        0x01
	#define PGA_APPLYGAIN		0x02


	#define PGA_DEFINE_NUMFREQRANGE      0x21 /* int32 */
	#define PGA_DEFINE_FREQRANGE         0x22 /* int32 index, int32 low, int32 high, int32 gain */
	#define PGA_DEFINE_NUMAMPLIFICATIONS 0x23 /* int32 */
	#define PGA_DEFINE_AMPLIFICATION     0x24 /* int32 index, int32 amplification, int32 poti1, int32 poti2 */


	#define PGA_GET_NUMFREQRANGE      0x81
	#define PGA_GET_FREQRANGE	      0x82
	#define PGA_GET_NUMAMPLIFICATIONS 0x83
	#define PGA_GET_AMPLIFICATION     0x84
	#define PGA_GET_GAIN              0x85

#define MCS_CONTROL_COMMAND     0x28
    #define CX_SET_CHANNELS_C   0x00
    #define CX_SET_CHANNELS_M   0x01
    #define CX_SET_CONTRAST     0x02

	#define CX_SET_SP           0x10  // per channel property
    #define CX_SET_DEVICE       0x11
    #define CX_SET_ON_OFF       0x12
    #define CX_SET_CALI         0x13
	#define CX_SET_P            0x18  // per device property
	#define CX_SET_I            0x19
	#define CX_SET_D            0x1a
    #define CX_SET_MAXP         0x1b
    #define CX_SET_DEVNAME      0x1c
    #define CX_SET_DEVICETYPE   0x1d
    #define CX_SET_INTERNAL_ON_OFF 0x1e

    #define CX_SET_DEVICE_DEFAULT  0x20  // restore device to mcs default
    #define CX_SET_CHANNEL_DEFAULT 0x21  // restore channel to mcs default
    #define CX_FACTORY_RESET       0x23

	#define CX_SET_HEATER_LIMIT 0x50
	#define CX_SET_ENABLE_HEATER_LIMIT 0x51
	#define CX_SET_ENABLE_THERMOCOUPLE 0x52
    #define CX_SET_SENSOR_TYPE 0x53

	#define CX_GET_CHANNELS_C   0x80  // get number of control channels
    #define CX_GET_CHANNELS_M   0x81  // get number of measure only channels
    #define CX_GET_CONTRAST     0x82  // display contrast
	#define CX_GET_VAL          0x83
	#define CX_GET_UNIT         0x84
    #define CX_GET_BOARD_TEMP   0x85
    #define CX_GET_VOLTI        0x86
    #define CX_GET_NUM_DEVICES  0x87
    #define CX_GET_VAL_HIRES    0x88 // get value in higher resolution
	#define CX_GET_VAL_HEATER	0x89 // get temp of the heater element
	#define CX_GET_HAS_THERMO   0x8a // query if the device includes a thermocouple

	#define CX_GET_SP           0x90  // per channel property
    #define CX_GET_DEVICE       0x91
    #define CX_GET_ON_OFF       0x92
    #define CX_GET_CALI         0x93
 	#define CX_GET_P            0x98  // per device property
	#define CX_GET_I            0x99
	#define CX_GET_D            0x9a
    #define CX_GET_MAXP         0x9b
    #define CX_GET_DEVNAME      0x9c
    #define CX_GET_DEVICETYPE   0x9d
    #define CX_GET_INTERNAL_ON_OFF 0x9e

	#define CX_GET_SP_MIN       0xa0
    #define CX_GET_CALI_MIN     0xa3
	#define CX_GET_P_MIN        0xa8
	#define CX_GET_I_MIN        0xa9
	#define CX_GET_D_MIN        0xaa
    #define CX_GET_MAXP_MIN     0xab
    #define CX_GET_HEATER_LIMIT_MIN     0xac

	#define CX_GET_SP_MAX       0xb0
    #define CX_GET_CALI_MAX     0xb3
	#define CX_GET_P_MAX        0xb8
	#define CX_GET_I_MAX        0xb9
	#define CX_GET_D_MAX        0xba
    #define CX_GET_MAXP_MAX     0xbb
    #define CX_GET_HEATER_LIMIT_MAX     0xbc

	#define CX_GET_SP_DECP      0xc0
    #define CX_GET_CALI_DECP    0xc3
	#define CX_GET_P_DECP       0xc8
	#define CX_GET_I_DECP       0xc9
	#define CX_GET_D_DECP       0xca
    #define CX_GET_MAXP_DECP    0xcb
    #define CX_GET_HEATER_LIMIT_DECP    0xcc

	#define CX_GET_HEATER_LIMIT 0xd0
	#define CX_GET_ENABLE_HEATER_LIMIT 0xd1
	#define CX_GET_ENABLE_THERMOCOUPLE 0xd2
    #define CX_GET_SENSOR_TYPE 0xd3

    #define CX_GET_RES_X        0xf0
    #define CX_GET_RES_S        0xf1
    #define CX_GET_RES_1        0xf2
    #define CX_GET_RES_2        0xf3
    #define CX_GET_PWR_SET      0xf4
    #define CX_GET_PWR_OUT      0xf5
    #define CX_GET_DUTY         0xf6
    #define CX_GET_U_OUT        0xf7
    #define CX_GET_I_OUT        0xf8
    #define CX_GET_R_OUT        0xf9
    #define CX_GET_P_OUT        0xfa
    #define CX_GET_CURR         0xfb

	#define PIDCONTROL_MAX_DEVNAME 24

#define STG200x_COMMAND    0x29  // interface change: we collect all STG only commands under this Request Id, compability with Firmware < 2.30 STG200x devices has been dropped in McsUsbDLL 3.3.17 (20.5.2019)
	#define STG200x_SETUP_TRIGGER      0x11
	#define STG200x_CHANNEL_RESET      0x12
	#define STG200x_CHANNEL_DATA       0x13  // to extra endpoint
	#define STG200x_SYNC_RESET         0x14
	#define STG200x_SYNC_DATA          0x15  // to extra endpoint
	#define STG200x_SET_CAPACITY       0x16
	#define STG200x_GET_AVAILABLE_MEM  0x17  // return the memory avaiable in the current segment (former name: STG200x_GET_MEM)
    #define STG200x_SET_STGOUTPUT      0x18
	#define STG200x_STG_RESET_STATUS   0x20
    #define STG200x_CLEAR_MULTIPLEXED_DATA 0x21 // currently only on HEKA IH3.0

	#define STG200x_SET_OUTPUTRATE     0x23
	#define STG200x_DISABLE_TRIGGER    0x25
	#define STG200x_ENABLE_TRIGGER     0x26
	#define STG200x_DISABLE_AUTORESET  0x27
	#define STG200x_ENABLE_AUTORESET   0x28

	#define STG200x_GET_UVAL           0x30
	#define STG200x_GET_IVAL           0x31
	#define STG200x_GET_DAC_RESOLUTION 0x32  // query the number of bits the DAC has, if not implemented  assume a value of 13
	#define STG200x_GET_T_RESOLUTION   0x33
	#define STG200x_GET_BOOSTPRETIME   0x34  // return the time the W2100 boost needs to power up

	#define STG200x_SET_URANGE		   0x38
	#define STG200x_SET_URESOLUTION    0x39
	#define STG200x_SET_IRANGE         0x3a
	#define STG200x_SET_IRESOLUTION    0x3b
	#define STG200x_STORE_RESRANGE     0x3c // store range and resolution data in eeprom

	#define STG200x_GET_PROGRAM_INFO   0x41
	#define STG200x_SET_PROGRAM_INFO   0x42
	#define STG200x_GET_SWEEP_COUNT    0x44
	#define STG200x_GET_TRIGGERMAP     0x45
	#define STG200x_GET_OUTPUTRATE     0x46
	#define STG200x_GET_CAPACITY       0x47

	#define STG200x_GET_NUMBER_ANALOGOUT	0x48
	#define STG200x_GET_NUMBER_SYNCOUT		0x49
	#define STG200x_GET_NUMBER_TRIGGER   	0x4a
	#define STG200x_HAS_PREAMPLIFIER    	0x4b
	#define STG200x_GET_NUMBER_HWDACPATH    0x4c
	#define STG200x_GET_STIMSOURCES_PER_ELECTRODE    0x4d
	#define STG200x_STIMULATION_LAYOUT_CONFIGURATION 0x4e
    #define STG200x_GET_MULTIPLEXED_CHANNELS_IN_BLOCK 0x4f // currently only on HEKA IH3.0

    #define STG200x_GET_MEMORY_USAGE_DAC    0x50
    #define STG200x_GET_MEMORY_USAGE_SYNC   0x51

	#define STG200x_COMMAND_DOWNLOADMODE    0x61
	#define STG200x_COMMAND_STREAMINGMODE   0x62

	#define STG200x_COMMAND_CONT_MODE_OFF 0x63
	#define STG200x_COMMAND_CONT_MODE_ON  0x64

	#define STG200x_MULTIFILE_MODE_OFF    0x65
	#define STG200x_MULTIFILE_MODE_ON     0x66

	#define STG200x_SET_VOLTAGE_MODE     0x67  // not needed and not implemented on old STG200x series
	#define STG200x_SET_CURRENT_MODE     0x68  // not needed and not implemented on old STG200x series
	#define STG200x_SET_MEASUREMENT_MODE 0x69  // only for STG3008-FA (with Filter Amplifier)

	#define STG200x_SEGMENT_DEFINE       0x80
	#define STG200x_SEGMENT_SELECT       0x81
	#define STG200x_SEGMENT_START        0x83  // SEGMENT_SELECT && STG_START
	#define STG200x_GET_TOTALMEM         0x84  // get total memory of the STG
	#define STG200x_GET_MAX_NUM_SEGMENTS 0x85

	#define STG200x_SETUP_RETRIGGER_MODE 0x86  // reaction on trigger while running

	#define STG200x_GET_STIMMEM_DESTADDR  0x87
	#define STG200x_GET_STIMMEM_CLEARADDR 0x88

	#define STG200x_DIGOUT_MODE          0x89  // configure the function of the digout port
	#define STG200x_DIGOUT_VALUE         0x8a  // the pattern on the digout port
	#define STG200x_DIGIN_VALUE          0x8b  // the pattern on the digin port

	#define STG200x_SYNCOUT_MAP          0x8c // map betwenn internal and external syncout, allows mapping of more than one internal syncout to the external pin

	#define STG200x_DEBUG_CHANNELDATA    0x90
    #define STG200x_GET_EEPROM_ID        0x91

	// these commands are new in the TI-DSP Stg implementation
	#define STG200x_QUERY_TRIGGERSTATUS  0xa0
    #define STG200x_SET_OUTPUTMAP        0xa1
	// commands for the STG30008-FA
	#define STG200x_FA_AMPLIFICATION     0xa2 // for STG3008-FA
	#define STG200x_AUTOCALIB_DISABLE    0xa3 // for STG3008-FA and STG400x with new Analog Firmware (Release 2011)

	 // commands for the MEA21 sideband to electrode mapping
	#define STG200x_ELECTRODE_SIDEBAND   0xa4
    
    #define STG200x_BLANKING_ENABLE      0xa5
	#define STG200x_TRIGGER_SOURCE       0xa6
    #define STG200x_ENABLE_PROTECTION_SWITCH         0xa7   // was: STG200x_STIMULATION_ENABLE
    #define STG200x_GET_NUM_STIMULATION_ELECTRODES 0xa8

    #define STG200x_ELECTRODE_SIDEBAND_EX        0xa9
    #define STG200x_BLANKING_ENABLE_EX           0xaa
    #define STG200x_ENABLE_PROTECTION_SWITCH_EX  0xab

    #define STG200x_GET_MODULETEMP       0xb0
	#define STG200x_GET_MODULECURRENT    0xb1

	#define STG200x_CAN_DISABLE_CALIBRATION       0xc0
	#define STG200x_HAS_LOW_CURRENTSWITCH_LATENCY 0xc1
	#define STG200x_CAN_DISABLE_CURRENTSWITCH     0xc2
	#define STG200x_GET_MODULE_TYPE               0xc3

    // select headstage to which the STG commands are sent
    #define STG200x_MEA21_SELECT_HS      0xd0

    // commands for the MEA2100 Listmode
    #define STG200x_MEA21_LISTMODE_INDEXRANGE    0xe0
    #define STG200x_MEA21_LISTMODE_TRIGGERSOURCE 0xe1
    #define STG200x_MEA21_LISTMODE_START         0xe2
    #define STG200x_MEA21_LISTMODE_STOP          0xe3

	#define STG200x_MULTIWELL_DAC_AMPLIFICATION  0xf0

    #define STG200x_MULTIWELL_OPTOSTIM_WAVELENGTH				0xF1
	#define STG200x_MULTIWELL_OPTOSTIM_MAX_CURRENT				0xF2
	#define STG200x_MULTIWELL_OPTOSTIM_MAX_DURATION				0xF3
	#define STG200x_MULTIWELL_OPTOSTIM_MAX_CURRENT_DUTY_CYCLE	0xF4
	#define STG200x_MULTIWELL_OPTOSTIM_PERMANENT_CURRENT		0xF5
	#define STG200x_MULTIWELL_OPTOSTIM_COLOR_RGB				0xF6
	#define STG200x_MULTIWELL_OPTOSTIM_COLOR_STR				0xF7

	// commands for the MEA21 output mapping
	#define STG200x_ELECTRODE_DAC_MUX    0x200  // use bit 0..7 of wValue for slice (listmode index)
	#define STG200x_ELECTRODE_ENABLE     0x300  // use bit 0..7 of wValue for slice (listmode index)

    #define STG200x_CMOS_DAC_SELECT      0x400

	#define STG200x_REPEAT_PATTERN		 0x500  // set/get how many times the stimulation pattern shall be repeated; introduced for wireless headstage 

	// commands for the DIGOUT stimulator of the IFB device
	#define STG200x_DIGOUT_CLEARDATA	0x600
	#define STG200x_DIGOUT_APPENDDATA	0x601
	#define STG200x_DIGOUT_NUMBER_OF_CHANNELS	0x602
    // 0x603 unused
	#define STG200x_DIGOUT_GLOBAL_REPEAT	0x604
    #define STG200x_DIGOUT_START_TRIGGER_SLOPE 0x605
    #define STG200x_DIGOUT_STOP_TRIGGER_SLOPE 0x606

    #define STG200x_EXTERNALELECTRODE_ENABLE     0x700  // use bit 0..7 of wValue for slice (listmode index)

    #define STG200x_ELECTRODE_DAC_MUX_EX          0xA00  // use bit 0..7 of wValue for slice (listmode index)
    #define STG200x_ELECTRODE_ENABLE_EX           0xE00  // use bit 0..7 of wValue for slice (listmode index)


#define STIMULATOR_COMMAND    0x2a              //  new (2018) generic stimulator commands, extend STG200x_COMMAND
    #define STIMULATOR_DAC_OFFSET        0x10
    #define STIMULATOR_BURN_DAC_OFFSET   0x11




/* end of STG200x commands */

#define MEA21_COMMAND          0x2d // Use only bit 0...7 for Command, other bits are for Virtual Device
    #define MEA_GROUP_IDCOUNT                0x01 // Number of Groups supported by this device
    #define MEA_GROUP_SUPPORTEDID            0x02 // GroupID by count supported by this device
    #define MEA_GROUP_NUMBEROFCHANNELS       0x03 // Number of Channels for a requested Group supported by this device
    #define MEA_GROUP_TYPE                   0x04 // Analog = 1, Digital = 2, Frame Context = 3
    #define MEA_GROUP_ENABLECHANNELS         0x05 // Set/Get a Group(s) Channel Bitwise
    #define MEA_GROUP_SAMPLESIZE             0x07 // bit width, (un-)signed Enumerations: SampleSize

    #define CMOSMEA_GROUP_DIGITRESOLUTION    0x0A // Get Resolution per Digit of Analog Value
    #define CMOSMEA_GROUP_VALUEUNIT          0x0B // Physical Unit of Analog Value
    #define CMOSMEA_GROUP_DCOFFSET           0x0D // Get DC Offset of Analog Value
    #define CMOSMEA_GROUP_HWPROP_ADCBITWIDTH 0x0E // Get the HW Bit width of data source
    #define CMOSMEA_GROUP_CHANNEL_BITMASK_SELECT 0x0C // legacy call, do not use in future!!


#define MEA_COMMAND         0x2e
    #define MEA_ENABLE_DIGITALIN             0x01
    #define MEA_SET_DIGITALOUT               0x02
    #define MEA_SET_NUMBEROFCHANNELS         0x03
    #define MEA_ENABLE_TIMESTAMP             0x04
    #define MEA_ENABLE_CHECKSUM              0x05
    #define MEA_SET_AUDIO                    0x06
    #define MEA_RESET_CHANNELMAP             0x07
    #define MEA_SET_CHANNELMAP               0x08
    #define MEA_GET_AUDIO                    0x09
    #define MEA_SET_SELECTED_CHANNELS        0x0A
    #define MEA_SET_RF_LOST_BEHAVIOUR        0x0B
    #define MEA_SET_HEADSTAGE_ON_OFF         0x0C
    #define MEA_SET_IVOLTAGERANGE            0x0D  // index of new voltagerange
    #define MEA_RFFREQUENCY_HEADSTAGE        0x0E
    #define MEA_RFFREQUENCY_RECEIVER         0x0F
    #define MEA_SERIALNUMBER_HEADSTAGE       0x10
    #define MEA_SELECT_HEADSTAGE             0x11
    #define MEA_SCAN_FOR_HEADSTAGES          0x12
    #define MEA_GET_SCAN_HEADSTAGES_RESULT   0x13
    #define MEA_FILTER_PARAMETERS_SHORT      0x14
    #define MEA_HAS_CHECKSUM                 0x15
    #define MEA_RESET_FILTER                 0x16
    #define MEA_SET_DATAMODE                 0x17
    #define MEA_MEA21_DIGOUT_SOURCE          0x18
    #define MEA_MEA21_DIGSTREAM_SOURCE       0x19
    #define MEA_MEA21_ADAPTER_TYPE           0x1A
    #define MEA_MEA21_MEA_LAYOUT             0x1B
    #define MEA_WPA_TYPE                     0x1C
    #define MEA_WPA_DEBUG_MODE               0x1D
    #define MEA_WPA_SET_RF_POWER             0x1E
    #define MEA_MEA21_DACQTRIGGER_SOURCE     0x1F
    #define MEA_DC_FILTER_ENABLE             0x20
    #define MEA_HS_FILTER_ENABLE             0x21
    #define MEA_CMOS_SOURCE_DRAIN_PARAM      0x22
    #define MEA_CMOS_SOURCE_GATE_PARAM       0x23
    #define MEA_CMOS_SOURCE_BULK_PARAM       0x24
    #define MEA_CMOS_BATH_PARAM              0x25
    #define MEA_CMOS_GATE_PARAM              0x26
    #define MEA_CMOS_GNDI_PARAM              0x27
    #define MEA_CMOS_VDDI_PARAM              0x28
    #define MEA_CMOS_VDD3I_PARAM             0x29
    #define MEA_CMOS_UPDATE_TRANSISTOR_PARAM 0x2F
    #define MEA_CMOS_ADC_INPUT_OFFSET        0x30
    #define MEA_CMOS_COLUMN_BITMASK          0x31
    #define MEA_CMOS_ROW_BITMASK             0x32
    #define MEA_CMOS_POWER_CHIP_PARAM        0x33
    #define MEA_CMOS_CHIPTYPE_PARAM          0x34
    #define MEA_CMOS_VOPS_PARAM              0x35
    #define MEA_CMOS_BATH_CTRL               0x36
    #define MEA_DC_FILTER_SETUP              0x37
    #define MEA_HS_FILTER_SETUP              0x38
    #define MEA_CMOS_NEUROCHIP_MEMACCESS     0x39
    #define MEA_CMOS_NEUROCHIP_MEMSIZE       0x3A
    #define MEA_SET_DIGITALDATA              0x3B
    #define MEA_CMOS_MAX_COLUMNS             0x3C
    #define MEA_CMOS_PCSC_CTRL               0x3D
    #define MEA_DC_FILTER_RESET              0x3E
    #define MEA_CMOS_VOPS_RESETTIMER         0x3F

	#define MEA_SET_BANDWIDTH_BY_INDEX       0x40
	#define MEA_SET_DSP_HIPASS_BY_INDEX      0x41
	#define MEA_AMPLIFIER_SETTLE             0x42
	#define MEA_SET_INTAN_REGISTER           0x43
	#define MEA_SET_DIAGNOSTIC_MODE          0x44
	#define MEA_BEGIN_IMPEDANCE_CHECK        0x45

	#define MEA_W2100_GET_AVAILABLE_HS       0x50
	#define MEA_W2100_SELECT_HS              0x51
	#define MEA_W2100_GET_SELECTED_HS_STATE  0x52
	#define MEA_W2100_HS_SERIALNUMBER        0x53
	#define MEA_W2100_HS_TYPE			     0x54
	#define MEA_W2100_BATTERY_STATE          0x55
	#define MEA_W2100_POWER_MODE             0x56
	#define MEA_W2100_USER_DEFINED_NAME      0x57
	#define MEA_W2100_USER_DEFINED_NAME_FROM_SELECTED_HS 0x58
	#define MEA_W2100_MULTI_HEADSTAGE_MODE	 0x59
	#define MEA_W2100_SAMPLING_ACTIVE		 0x5A
	#define MEA_W2100_HS_SET_TO_SLEEP        0x5B
	#define MEA_W2100_GET_STIMULUS_PARAMETER 0x5C
	#define MEA_W2100_SET_ANALOG_OUT_CHANNEL 0x5D
	#define MEA_W2100_SET_ANALOG_OUT_FILTER  0x5E
	#define MEA_W2100_DAC_RANGE              0x5F

	#define MEA_MW_PLATE_STATE               0x60
    #define MEA_MW_PLATE_LOCK                0x61
    #define MEA_MW_PLATE_TYPE                0x62
		#define MEA_MW_INDEX_PLATE_CLAMP_CLOSE	 0x00
		#define MEA_MW_INDEX_PLATE_CLAMP_OPEN	 0x01
		#define MEA_MW_INDEX_PLATE_CLAMP_STOP    0x02
		#define MEA_MW_INDEX_PLATE_CLAMP_LOCK    0x00
		#define MEA_MW_INDEX_PLATE_CLAMP_UNLOCK  0x01

    #define MEA_GET_FILTER_CONFIGURATION     0x63
    #define MEA_MW_PLATE_MUX                 0x64
    #define MEA_MW_PLATE_TYPE_IS_VALID       0x65
    #define MEA_SET_FILTER_CONFIGURATION     0x66
    #define MEA_STORE_FILTER_CONFIGINMEM     0x67
    #define MEA_ERASE_FILTER_CONFIGINMEM     0x68

    #define MEA_W2100_GENERATOR_PERIOD  0x70
    #define MEA_W2100_GENERATOR_PULSE_LENGTH 0x71
    #define MEA_W2100_GENERATOR_MODE_SELECT 0x72

	#define MEA_W2100_ENABLE_ACCEL_GYRO 0x78
	#define MEA_W2100_ACCEL_GYRO_DESIREDGRATE 0x79
	#define MEA_W2100_ACCEL_GYRO_CURRENTRATE 0x7A
	#define MEA_W2100_ACCEL_RANGE 0x7B
	#define MEA_W2100_GYRO_RANGE 0x7C

    #define MEA_DIGOUT_STG_START_TRIGGER_SOURCE 0x80
    #define MEA_DIGOUT_STG_STOP_TRIGGER_SOURCE 0x81

	#define MEA_DIGSTREAMTORECEIVER_SOURCE 0x84
	#define MEA_W2100_DIGTRIGGER_SLOPE 0x85
    
    #define MEA_SCU_AVAILABLE_HEADSTAGES         0x90
    #define MEA_SCU_MAX_CHANNELS_PER_HEADSTAGE   0x91
    #define MEA_SCU_MAX_NUMBER_OF_HEADSTAGES     0x92
    #define MEA_SCU_GET_HEADSTAGE_ID             0x93
	#define MEA_SCU_MAX_STIMULUS_CHANNELS_PER_HEADSTAGE   0x94
    #define MEA_SCU_DACQ_LEGACY_MODE             0x95
    #define MEA_SCU_HEADSTAGE_POWER              0x96
    #define MEA_SCU_HEADSTAGE_HAS_POWERSWITCHES  0x97

    #define MEA_SCU_HEADSTAGE_IS_AVAILABLE       0x98
    #define MEA_SCU_HEADSTAGE_SERIALNUMBER       0x99
    #define MEA_SCU_HEADSTAGE_ANALOG_CHANNELS    0x9A
    #define MEA_SCU_HEADSTAGE_STIMULUS_CHANNELS  0x9B

	#define MEA_SCU_HEADSTAGE_REFERENCE_ELECTRODE_SWITCHSTATE    0x9C
	#define MEA_SCU_HEADSTAGE_REFERENCE_ELECTRODE_MODE	0x9D

	#define MEA_SCU_HEADSTAGE_GAIN                     0xA0
    #define MEA_SCU_HEADSTAGE_ADC_RANGE                0xA1
    #define MEA_SCU_HEADSTAGE_ADC_BITS                 0xA2
    #define MEA_SCU_HEADSTAGE_DAC_VOLTAGE_RANGE        0xA3
    #define MEA_SCU_HEADSTAGE_DAC_VOLTAGE_RESOLUTION   0xA4
    #define MEA_SCU_HEADSTAGE_DAC_CURRENT_RANGE        0xA5
    #define MEA_SCU_HEADSTAGE_DAC_CURRENT_RESOLUTION   0xA6
    #define MEA_SCU_HEADSTAGE_DAC_BITS                 0xA7

	#define MEA_SCU_ANALOG_OUT_ENABLE    0xB0
	#define MEA_SCU_ANALOG_OUT_DAC_RANGE 0xB1
	#define MEA_SCU_ANALOG_OUT_ADC_RANGE 0xB2
	#define MEA_SCU_ANALOG_OUT_AUTOMATIC 0xB3
	#define MEA_SCU_ANALOG_OUT_CHANNELS  0xB4
    #define MEA_SCU_HAS_ANALOG_OUT       0xB5

    #define MEA_SCU_HAS_GALVANIC_ISOLATION 0xC0

#define OCTOPOT_COMMAND     0x2f
// subids for OCTOPOT_COMMAND
	#define OCTOPOT_SET_BATHCLAMP		0x01
	#define OCTOPOT_SET_DAC_VALUE      	0x02
	#define OCTOPOT_SET_DAC_AUTOCONTROL	0x03
	#define OCTOPOT_SET_PID_PARAMETER  	0x04
	#define OCTOPOT_SET_RAMP_PARAMETER 	0x05
	#define OCTOPOT_RAMP_START         	0x06

	#define OCTOPOT_SET_DAC_OFFSET      0x07
	#define OCTOPOT_SET_ADC_OFFSET      0x08
	#define OCTOPOT_BURN_DAC_OFFSET     0x09
	#define OCTOPOT_BURN_ADC_OFFSET     0x10
	#define OCTOPOT_RESET_DAC_OFFSET    0x11
	#define OCTOPOT_RESET_ADC_OFFSET    0x12

	#define OCTOPOT_SET_SINE_PARAMETER  0x13
	#define OCTOPOT_SINE_START          0x14

	#define OCTOPOT_SET_PATTERN_LIST_ENTRY 0x15
	#define OCTOPOT_PATTERN_LIST_START     0x16

	#define OCTOPOT_SET_ADC_GPIO0		0x1f
	#define OCTOPOT_SET_ADC_GPIO1		0x20
// end of subids

#define RETINA_LED		0x30
	#define RETINA_SET_TRIGGER		    0x01 /* enable/disable trigger */
	#define RETINA_SET_LED				0x03 /* set pattern on LED Array */
	#define RETINA_SET_TABLEPOINTER 	0x04 /* set table pointer to entry */
	#define RETINA_CLEAR_TABLE			0x05 /* delete table */
	#define RETINA_ADD_TABLE_ENTRY		0x06 /* add table enry, 8 byte data, 2 byte repeat */
	#define RETINA_SET_REPEAT   		0x07 /* global repeat of table, 2 byte */
	#define RETINA_SET_LUMI				0x08 /* luminosity, 2 byte */
    #define RETINA_SET_PERSISTENCY      0x09 /* Nachleuchtzeit in ms */
    #define RETINA_ADD_LOOP_ENTRY       0x10 /* add a loop entry to the table */
    #define RETINA_GET_TABLEPOINTER     0x84 /* retrieve current position of the table pointer */
/* + callback for current table position */

#define MCS_FLUID_COMMAND  0x31
    #define FLUID_SET_VALVE             0x01 /* Set Valve */
    #define FLUID_SET_DIGOUT            0x02
    #define FLUID_SET_PWM               0x03 /* Set PWM in 1/1000 steps */
	#define FLUID_SET_SINGLE_VALVE		0x04 /* Sets a single Valve */
	#define FLUID_CALIBRATE_TERMO       0x21 /* Calibrate Temperature */
	#define FLUID_SET_NANOVOLTPERKELVIN 0x22

    #define FLUID_GET_VALVE             0x81
    #define FLUID_GET_DIGOUT            0x82
    #define FLUID_GET_PWM               0x83
	#define FLUID_GET_SINGLE_VALVE		0x84 /* Gets a single Valve */
    #define FLUID_GET_ADC               0x90
    #define FLUID_GET_DIGIN             0x91
    #define FLUID_GET_REF_TEMP          0x92 /* Temp at reference point */
    #define FLUID_GET_THERMO_TEMP       0x93 /* Differential Temp of ThermoCouple */
    #define FLUID_GET_CHANNEL_TEMP      0x94 /* Absolute Temp */
    #define FLUID_GET_THERMO_CALIB      0xa1 
	#define FLUID_GET_NANOVOLTPERKELVIN 0xa2


#define HEKA_LIH3_COMMAND    0x32
    #define LIH3_DUMMY_COMMAND           0x01
    #define LIH3_GET_EEPROM_BYTE         0x02
    #define LIH3_SAMPLE_INTERVAL         0x03
    #define LIH3_EEPROM_START_COMADDR    0x04
    #define LIH3_EEPROM_PAGE             0x05
    #define LIH3_ADC_OFFSET              0x06
    #define LIH3_CLIPPING                0x07
    #define LIH3_DIGITAL_IO              0x08
    #define LIH3_SEND_COMMAND            0x09
    #define LIH3_DACQ_RUN_STATUS         0x0A
    #define LIH3_MIN_SAMPLEINTERVAL      0x0B
    #define LIH3_SAMPLEINTERVAL_STEPSIZE 0x0C
    #define LIH3_DAC_USE_IDLE_VALUE      0x0D
    #define LIH3_DAC_IDLE_VALUE          0x0E


/* starting with our our Vendor ID (0x1e..)
 The "GET_VERSION (0x43)" call changed its parameters
 and is renamed to "GET_FIRMWARE_VERSION".
 Now, depending on req_index, the destination is choosen,
 and the return value is a single 32bit integer

 The Hardware Revision is queried now with the new
 "GET_HW_REVISION" call, which returns a string
*/

#define GET_IDENT            0x40

#define GET_DESTINATION_INFO 0x41     // supported for all devices with our new Vendor ID
	#define GET_NUM_DESTINATIONS            0x00
	#define GET_DESTINATION_CODE            0x01
	#define GET_DESTINATION_NAME_BY_IDX     0x02
	#define GET_DESTINATION_NAME_BY_CODE    0x03
	#define GET_DESTINATION_TARGETADDRESS   0x04

    #define DESTINATION_SERIALNUMBER        0x08

    #define MULTIBOOT_GET_IMAGE_ID			0x11
	#define MULTIBOOT_GET_SELECTED_IMAGE	0x12
    #define MULTIBOOT_SELECT_IMAGE          0x13
    #define MULTIBOOT_GET_CYPRESS_IMAGE_ID  0x14

    #define GET_HEADSTAGE_ID                0x21
    #define GET_HEADSTAGE_PRESENT           0x22
    #define GET_HEADSTAGE_ACTIVE            0x23
    #define RESCAN_HEADSTAGE                0x24

#define GET_FIRMWARE_VERSION 0x43   // has MCSUSB_DEST_... as wValue
#define GET_HW_REVISION      0x44   // new for all devices with our real Vendor ID
#define GET_DACQ_SAMPLERATE   0x46

#define SOFTWARE_KEY_COMMAND 0x47
	#define GET_SOFTWARE_KEY 0x01
	#define SET_SOFTWARE_KEY 0x02

#define MISC_USB_COMMAND1 0x4a  // Device specific commands (1) ==> to save request numbers
							   // Devices use the upper 8 bits of wValue / commands use the 8 lower bits
	#define MEA_SWITCH_MISC_COMMAND 	0x0100
		#define MEA_SWITCH_GET_NUMBER		(MEA_SWITCH_MISC_COMMAND | 0x01) /* gets the number of meas to switch to: 1 or 2 */
		#define MEA_SWITCH_SET_NUMBER		(MEA_SWITCH_MISC_COMMAND | 0x02) /* sets the number of meas to switch to: 1 or 2 */
    	#define MEA_SWITCH_GET_PATTERN		(MEA_SWITCH_MISC_COMMAND | 0x03) /* gets the current pattern */
		#define MEA_SWITCH_SET_PATTERN		(MEA_SWITCH_MISC_COMMAND | 0x04) /* sets the current pattern */
	
		// commands for the MCS ChannelTest
		#define MEA_CHANNELTEST_SET_WAVEFORM    (MEA_SWITCH_MISC_COMMAND | 0x30) /* sets the waveform for Amplifier test (sine/square) */
        #define MEA_CHANNELTEST_SET_FREQUENCY   (MEA_SWITCH_MISC_COMMAND | 0x31) /* sets the frequency for Amplifier test */
        #define MEA_CHANNELTEST_SET_AMPLITUDE   (MEA_SWITCH_MISC_COMMAND | 0x32) /* sets the amplitude for Amplifier test */
		#define MEA_CHANNELTEST_SET_ATTENUATION (MEA_SWITCH_MISC_COMMAND | 0x33) /* sets the attenutation */
   
	#define MEA_IMPEDANCE_MISC_COMMAND	0x0200
		#define MEA_IMPEDANCE_RANGE					(MEA_IMPEDANCE_MISC_COMMAND | 0x06) 
		#define MEA_IMPEDANCE_FREQUENCY				(MEA_IMPEDANCE_MISC_COMMAND | 0x07) /* impedance sampling test frequency; unit: Hz */
		#define MEA_IMPEDANCE_START_MEASUREMENT		(MEA_IMPEDANCE_MISC_COMMAND | 0x08) /* starts the measurement on the given channels */
		#define MEA_IMPEDANCE_GET_READY				(MEA_IMPEDANCE_MISC_COMMAND | 0x09) /* checks if the the measurement is ready */
        #define MEA_IMPEDANCE_GET_ARRAYSIZE			(MEA_IMPEDANCE_MISC_COMMAND | 0x0A) /* get the current array size */
		#define MEA_IMPEDANCE_GET_RESULT			(MEA_IMPEDANCE_MISC_COMMAND | 0x0B) /* gets the result of one period */
		#define MEA_IMPEDANCE_GET_ADAPTERCODE		(MEA_IMPEDANCE_MISC_COMMAND | 0x0C) /* gets the code of the adapter */
			
	#define SW2TO64_MISC_COMMAND 	0x0300
		#define SW2TO64_GET_NUMBER		(SW2TO64_MISC_COMMAND | 0x01) /* gets the number of channels of the device */
		#define SW2TO64_SET_NUMBER		(SW2TO64_MISC_COMMAND | 0x02) /* Not used */
    	#define SW2TO64_GET_CHANNELS	(SW2TO64_MISC_COMMAND | 0x03) /* gets the current channel settings */
		#define SW2TO64_SET_CHANNELS	(SW2TO64_MISC_COMMAND | 0x04) /* sets the current channel settings */
	    #define SW2TO64_GET_CHANNEL		(SW2TO64_MISC_COMMAND | 0x05) /* gets the current setting of one channel */
		#define SW2TO64_SET_CHANNEL		(SW2TO64_MISC_COMMAND | 0x06) /* sets the current setting of one channel */

	#define SERIAL_PORT_MISC_COMMAND  0x0400
		#define SERIAL_PORT_SEND            	(SERIAL_PORT_MISC_COMMAND | 0x01) /* send a line that is equivalent to a COM line */
		#define SERIAL_PORT_RECEIVE	            (SERIAL_PORT_MISC_COMMAND | 0x02) /* gets an answer from the last command send */
        #define SERIAL_PORT_BYTES_AVAILABLE     (SERIAL_PORT_MISC_COMMAND | 0x03) /* gets the number of bytes available in the receive buffer */

	#define PATHIDENT_MISC_COMMAND 0x0500
		#define PATHIDENT_SET_VALUES	(PATHIDENT_MISC_COMMAND | 0x01)
		#define PATHIDENT_MEASURE		(PATHIDENT_MISC_COMMAND | 0x02)

	#define OKUVISION_STIMULATOR_MISC_COMMAND 0x0600
		#define OKUVISION_STIMULATOR_PULSEFORM				(OKUVISION_STIMULATOR_MISC_COMMAND | 0x01)
		#define OKUVISION_STIMULATOR_MAX_POWER				(OKUVISION_STIMULATOR_MISC_COMMAND | 0x03)
		#define OKUVISION_STIMULATOR_MAX_VOLTAGE			(OKUVISION_STIMULATOR_MISC_COMMAND | 0x04)
		#define OKUVISION_STIMULATOR_CHECK_VOLTAGE			(OKUVISION_STIMULATOR_MISC_COMMAND | 0x06)
		#define OKUVISION_STIMULATOR_GETVOLTAGE				(OKUVISION_STIMULATOR_MISC_COMMAND | 0x07)
		#define OKUVISION_STIMULATOR_DACOFFSET				(OKUVISION_STIMULATOR_MISC_COMMAND | 0x08)
		#define OKUVISION_STIMULATOR_RTC					(OKUVISION_STIMULATOR_MISC_COMMAND | 0x09)
		#define OKUVISION_STIMULATOR_STATUS					(OKUVISION_STIMULATOR_MISC_COMMAND | 0x10)
		#define OKUVISION_STIMULATOR_CURRENTFACTOR			(OKUVISION_STIMULATOR_MISC_COMMAND | 0x11)

	#define NF_GEN_MISC_COMMAND 0x0700
		#define NF_GEN_SET_VALUES	(NF_GEN_MISC_COMMAND | 0x01)

	#define SAFEIS_MISC_COMMAND 0x0800
		#define SAFEIS_SET_SWITCHES			(SAFEIS_MISC_COMMAND | 0x01)
		#define SAFEIS_SET_ADC_CHANNELS 	(SAFEIS_MISC_COMMAND | 0x02)
		#define SAFEIS_SET_ADC_SAMPLEPOS	(SAFEIS_MISC_COMMAND | 0x03)
		#define SAFEIS_SET_DAC_MODE			(SAFEIS_MISC_COMMAND | 0x04)
		#define SAFEIS_SET_DAC_PULSEFORM	(SAFEIS_MISC_COMMAND | 0x05)
		#define SAFEIS_SET_DAC_PERIODE		(SAFEIS_MISC_COMMAND | 0x06) 

	#define GILSON_BRIDGE_MISC_COMMAND 0x0900
		#define GILSON_BRIDGE_CONNECT_SLAVE 	(GILSON_BRIDGE_MISC_COMMAND | 0x01)
		#define GILSON_BRIDGE_SEND_IMMEDIATE 	(GILSON_BRIDGE_MISC_COMMAND | 0x02)
		#define GILSON_BRIDGE_SEND_BUFFERED 	(GILSON_BRIDGE_MISC_COMMAND | 0x03)
		#define GILSON_BRIDGE_GET_LAST_ANSWER 	(GILSON_BRIDGE_MISC_COMMAND | 0x04)
		
	#define EXTERN_BC_TESTER_MISC_COMMAND 0x0A00
		#define EXTERN_BC_TESTER_SET_CALIB		(EXTERN_BC_TESTER_MISC_COMMAND | 0x01)

	#define SOFTWAREDONGLE_MISC_COMMAND 0x0B00
		#define SOFTWAREDONGLE_CODE				(SOFTWAREDONGLE_MISC_COMMAND | 0x01)

	#define PPS_MISC_COMMAND       0x0C00
    #define PPS_MISC_QUERY_COMMAND 0x0D00  // triggers a corresponding PPS_MISC_COOMAND towards the PPS2 Display
		//#define PPS_PUMP_MODE					(PPS_MISC_COMMAND | 0x01)
		#define PPS_PUMP_MAXSPEED				(PPS_MISC_COMMAND | 0x02)
		#define PPS_PUMP_SPEEDUNIT				(PPS_MISC_COMMAND | 0x03)
		#define PPS_PUMP_MODE_TYPE				(PPS_MISC_COMMAND | 0x04)
		#define PPS_PUMP_COUPLE					(PPS_MISC_COMMAND | 0x05)
		#define PPS_PUMP_ENABLE_SPEEDRATIO		(PPS_MISC_COMMAND | 0x06)
		#define PPS_PUMP_MANUALONOFF			(PPS_MISC_COMMAND | 0x10)
		#define PPS_PUMP_FUNCTIONSPEED			(PPS_MISC_COMMAND | 0x11)
		#define PPS_PUMP_SPEEDRATIO				(PPS_MISC_COMMAND | 0x12)
		#define PPS_PUMP_FASTONOFF				(PPS_MISC_COMMAND | 0x13)
		#define PPS_PUMP_FASTSPEED				(PPS_MISC_COMMAND | 0x14)
		#define PPS_ANALOGVOLTAGE				(PPS_MISC_COMMAND | 0x21)
		#define PPS_USE_BUBBLEDETECTOR			(PPS_MISC_COMMAND | 0x22)
		//#define PPS_DIGITAL_IN					(PPS_MISC_COMMAND | 0x23) // ?
		//#define PPS_DIGITAL_OUT					(PPS_MISC_COMMAND | 0x24) // ?
		#define PPS_GET_SUPPLYVOLTAGE			(PPS_MISC_COMMAND | 0x30)
		#define PPS_GET_ANALOGVOLTAGE			(PPS_MISC_COMMAND | 0x31)
		#define PPS_GET_DIGITALIN				(PPS_MISC_COMMAND | 0x32)
		#define PPS_GET_BUBBLESTATE				(PPS_MISC_COMMAND | 0x33)

    #define MEA_CLEAN_COMMAND 0x0E00
        #define MEA_CLEAN_START_STOP (MEA_CLEAN_COMMAND | 0x01)
        #define MEA_CLEAN_SLOPE      (MEA_CLEAN_COMMAND | 0x02)
        #define MEA_CLEAN_CYCLES     (MEA_CLEAN_COMMAND | 0x03)
        #define MEA_CLEAN_UMIN       (MEA_CLEAN_COMMAND | 0x04)
        #define MEA_CLEAN_UMAX       (MEA_CLEAN_COMMAND | 0x05)
        #define MEA_CLEAN_UOUTPUT    (MEA_CLEAN_COMMAND | 0x06)
        #define MEA_CLEAN_CYCLENOW   (MEA_CLEAN_COMMAND | 0x07)

    #define MEA_COAT_COMMAND 0x0E80
        #define MEA_COAT_START_STOP (MEA_COAT_COMMAND | 0x01)
        #define MEA_COAT_SLOPE      (MEA_COAT_COMMAND | 0x02)
        #define MEA_COAT_DURATION   (MEA_COAT_COMMAND | 0x03)
        #define MEA_COAT_IMAX       (MEA_COAT_COMMAND | 0x04)
        #define MEA_COAT_IOFFSET    (MEA_COAT_COMMAND | 0x05)
        #define MEA_COAT_IOUTPUT    (MEA_COAT_COMMAND | 0x06)
        #define MEA_COAT_TINPLATEAU (MEA_COAT_COMMAND | 0x07)
        #define MEA_COAT_PAUSEDURATION (MEA_COAT_COMMAND | 0x08)
        #define MEA_COAT_TINPAUSE   (MEA_COAT_COMMAND | 0x09)
        #define MEA_COAT_CYCLES     (MEA_COAT_COMMAND | 0x0a)
        #define MEA_COAT_CYCLENOW   (MEA_COAT_COMMAND | 0x0b)

	#define EXTERN_D_TESTER_MISC_COMMAND 0x0F00
		#define EXTERN_D_TESTER_GET_DATABLOCK		(EXTERN_D_TESTER_MISC_COMMAND | 0x01)

    #define MBC08_MISC_COMMAND           0x1000
		#define MBC08_CHARGE_CURRENT	(MBC08_MISC_COMMAND | 0x01)
		#define	MBC08_DISCHARGE_CURRENT (MBC08_MISC_COMMAND | 0x02)
        #define	MBC08_FINALDISCHARGE_VOLTAGE (MBC08_MISC_COMMAND | 0x03)
		#define MBC08_DISCHARGE_CAPACITY     (MBC08_MISC_COMMAND | 0x04)
		#define MBC08_BATT_VOLTAGE		(MBC08_MISC_COMMAND | 0x05)
		#define MBC08_RESET_CHANNEL		(MBC08_MISC_COMMAND | 0x06)
		#define MBC08_CHANNELS			(MBC08_MISC_COMMAND | 0x07)
		#define MBC08_CHARGING_MODE	    (MBC08_MISC_COMMAND | 0x08)
		#define MBC08_CAPACITY_TEST		(MBC08_MISC_COMMAND | 0x09)
		#define MBC08_CHANNEL_STATE		(MBC08_MISC_COMMAND | 0x0A)
        #define MBC08_CHARGE_CAPACITY   (MBC08_MISC_COMMAND | 0x0B)
        #define MBC08_SP_DISCHARGE_CURRENT (MBC08_MISC_COMMAND | 0x0C)
        #define MBC08_CHARGE_P_COEFF    (MBC08_MISC_COMMAND | 0x0D)
        #define MBC08_RATED_CAPACITY_VOLATILE (MBC08_MISC_COMMAND | 0x0E)
        #define MBC08_RATED_CAPACITY    (MBC08_MISC_COMMAND | 0x0F)

    // #define *_MISC_COMMAND 0x1100 // is free

	#define PPC_MISC_COMMAND       0x1200
    #define PPC_MISC_QUERY_COMMAND 0x1300  // triggers a corresponding PPC_MISC_COOMAND towards the PPC Display
    #define PPC_MISC_COMMAND_MASK  0xFF00
		//#define PPC_PUMP_MODE					(PPC_MISC_COMMAND | 0x01)
		#define PPC_PUMP_SPEEDUNIT				(PPC_MISC_COMMAND | 0x03)
		#define PPC_PUMP_MODE_TYPE				(PPC_MISC_COMMAND | 0x04)
        #define PPC_VALVE_ACTIVE				(PPC_MISC_COMMAND | 0x05)
        #define PPC_LOAD_PRESSURE				(PPC_MISC_COMMAND | 0x06)
        #define PPC_BUSY                        (PPC_MISC_COMMAND | 0x07)
        #define PPC_FIRE_PRESSURE_PULSE         (PPC_MISC_COMMAND | 0x08)
        #define PPC_MEASURE_RESERVOIR           (PPC_MISC_COMMAND | 0x09)

		#define PPC_ANALOGVOLTAGE				(PPC_MISC_COMMAND | 0x20)
		#define PPC_PRESSURERANGES				(PPC_MISC_COMMAND | 0x21)
		//#define PPC_DIGITAL_IN					(PPC_MISC_COMMAND | 0x23) // ?
		//#define PPC_DIGITAL_OUT					(PPC_MISC_COMMAND | 0x24) // ?
		#define PPC_GET_SUPPLYVOLTAGE			(PPC_MISC_COMMAND | 0x30)
		#define PPC_GET_ANALOGVOLTAGE			(PPC_MISC_COMMAND | 0x31)
		#define PPC_GET_DIGITALIN				(PPC_MISC_COMMAND | 0x32)

		#define PPC_GETPRESSURE					(PPC_MISC_COMMAND | 0x80 | 20)	// The same Commands exit on the MCSBUS and are feed through
		#define PPC_GETREGULATORSPEED			(PPC_MISC_COMMAND | 0x80 | 21)
		#define PPC_SOLLPRESSURE				(PPC_MISC_COMMAND | 0x80 | 22)
		#define PPC_REGULATORONOFF				(PPC_MISC_COMMAND | 0x80 | 23)
		#define PPC_REGULATORFACTORS			(PPC_MISC_COMMAND | 0x80 | 24)
		#define PPC_SETPRESSUREOFFSET			(PPC_MISC_COMMAND | 0x80 | 25)
		#define PPC_REGULATORSTATUS				(PPC_MISC_COMMAND | 0x80 | 26)
		#define PPC_ROTATE_PERISTALTIC			(PPC_MISC_COMMAND | 0x80 | 27)
		#define PPC_MOVE_PERISTALTIC			(PPC_MISC_COMMAND | 0x80 | 28)
		#define PPC_SETTIMEOUTS					(PPC_MISC_COMMAND | 0x80 | 29)

    #define PEDOTER_MISC_COMMAND    0x1400
        #define PEDOTER_COMMAND                 (PEDOTER_MISC_COMMAND | 0x01)

    // #define *_MISC_COMMAND 0x1500 - 0x1E00 // are free

    #define DEVICE_STATE_PUSH_TRIGGER_STATUS    0x1F00

    #define WVC_MISC_COMMAND       0x2000
        #define WVC_DISPLAY_QUERY               (WVC_MISC_COMMAND | 0x00)  // only used between display and control unit
        #define WVC_VALVE_ACTIVE                (WVC_MISC_COMMAND | 0x01)
        #define WVC_VALVE_MODE                  (WVC_MISC_COMMAND | 0x02)
        #define WVC_VALVE_ACTIVE_MAP            (WVC_MISC_COMMAND | 0x03)
        #define WVC_VALVE_MANUAL_STATE          (WVC_MISC_COMMAND | 0x04)
        #define WVC_VALVE_MANUAL_STATE_MAP      (WVC_MISC_COMMAND | 0x05)
        #define WVC_VALVE_MANUAL_GROUP          (WVC_MISC_COMMAND | 0x06)

        #define WVC_VALVE_ANALOG_THRESHOLD_LOW  (WVC_MISC_COMMAND | 0x08)
        #define WVC_VALVE_ANALOG_THRESHOLD_HIGH (WVC_MISC_COMMAND | 0x09)

        #define WVC_DIGITAL_PORT_DIRECTION      (WVC_MISC_COMMAND | 0x10)
        #define WVC_VALVE_DIGITAL_IN_INVERT     (WVC_MISC_COMMAND | 0x11)
        #define WVC_VALVE_DIGITAL_IN_CHANNEL    (WVC_MISC_COMMAND | 0x12)
        #define WVC_DIGITAL_OUT_INVERT          (WVC_MISC_COMMAND | 0x13)
        #define WVC_DIGITAL_OUT_VALVE_CHANNEL   (WVC_MISC_COMMAND | 0x14)

        #define WVC_SET_DEFAULT_PARAMETER       (WVC_MISC_COMMAND | 0x18)

        #define WVC_VALVE_IS_OPEN               (WVC_MISC_COMMAND | 0x20)
        #define WVC_VALVE_IS_OPEN_DIGITAL_MODE  (WVC_MISC_COMMAND | 0x21)
        #define WVC_VALVE_IS_OPEN_ANALOG_MODE   (WVC_MISC_COMMAND | 0x22)
        #define WVC_EXTERN_ANALOG_VOLTAGE       (WVC_MISC_COMMAND | 0x23)

        #define WVC_TABLE_ENTRY                 (WVC_MISC_COMMAND | 0x30)
        #define WVC_TABLE_CLEAR                 (WVC_MISC_COMMAND | 0x31)
        #define WVC_TABLE_LOAD                  (WVC_MISC_COMMAND | 0x32)
        #define WVC_TABLE_STORE                 (WVC_MISC_COMMAND | 0x33)
        #define WVV_TABLE_NAME                  (WVC_MISC_COMMAND | 0x34)
        #define WVC_TABLE_ENTRY_CHANGED         (WVC_MISC_COMMAND | 0x35)
        #define WVV_TABLE_NAME_BY_INDEX         (WVC_MISC_COMMAND | 0x36)

        #define WVC_ACTIVE_RUNNING_TABLE_NUMBER (WVC_MISC_COMMAND | 0x38)
        #define WVC_CURRENT_EDIT_TABLE_NUMBER   (WVC_MISC_COMMAND | 0x39)

        #define WVC_TABLE_STEP_TIME             (WVC_MISC_COMMAND | 0x40)
        #define WVC_TABLE_STEP                  (WVC_MISC_COMMAND | 0x41)
        #define WVC_TABLE_STEP_ALL              (WVC_MISC_COMMAND | 0x42)

        #define WVC_NUMBER_OF_VALVES            (WVC_MISC_COMMAND | 0x50)
        #define WVC_NUMBER_OF_DIGITALPORTS      (WVC_MISC_COMMAND | 0x51)
        #define WVC_TABLESIZE                   (WVC_MISC_COMMAND | 0x52)
        #define WVC_NUMBER_OF_TABLES            (WVC_MISC_COMMAND | 0x53)

        #define WVC_CONNECTED_NUMBER_OF_VALVES  (WVC_MISC_COMMAND | 0x58)

        #define WVC_GET_BOARD_REVISION          (WVC_MISC_COMMAND | 0x60)

        #define WVC_DISPLAY_MODE                (WVC_MISC_COMMAND | 0x81)

        //#define MANUAL_TRIGGER // bitmap ?

        // DeviceTester commands
        #define WVC_DEVICETESTER_MASK                         (0xFFF0)
        #define WVC_DEVICETESTER_COMMAND                      (WVC_MISC_COMMAND | 0xF0)
        #define WVC_DEVICETESTER_SET_ADC                      (WVC_MISC_COMMAND | 0xF1)
        #define WVC_DEVICETESTER_SETGET_TRIGGERSYNC           (WVC_MISC_COMMAND | 0xF2)
        #define WVC_DEVICETESTER_SET_TRIGGERSYNC_DIRECTION    (WVC_MISC_COMMAND | 0xF3)
        #define WVC_DEVICETESTER_SETGET_IO                    (WVC_MISC_COMMAND | 0xF4)
        #define WVC_DEVICETESTER_SET_IO_DIRECTION             (WVC_MISC_COMMAND | 0xF5)

    #define POSITIONIMP_MISC_COMMAND 0x3000
        #define POSITIONIMP_CONNECT                   (POSITIONIMP_MISC_COMMAND | 0x00)
        #define POSITIONIMP_RFFREQUENCY               (POSITIONIMP_MISC_COMMAND | 0x01)
        #define POSITIONIMP_DEVICELIST                (POSITIONIMP_MISC_COMMAND | 0x02)
        #define POSITIONIMP_DEVICEID                  (POSITIONIMP_MISC_COMMAND | 0x03)

    #define TEER_MISC_COMMAND 0x3100
    #define TEER_MISC_COMMAND_MASK 0xFF00
        #define TEER_PERIOD                           (TEER_MISC_COMMAND | 0x01)
        #define TEER_AMPLITUDE                        (TEER_MISC_COMMAND | 0x02)
        #define TEER_WAVEFORM                         (TEER_MISC_COMMAND | 0x03)
	    //#define TEER_SAMPLE                           (TEER_MISC_COMMAND | 0x04)
		#define TEER_CLAMP_MODE                       (TEER_MISC_COMMAND | 0x05)
		#define TEER_START_SAMPLING                   (TEER_MISC_COMMAND | 0x06)
		#define TEER_IS_SAMPLING_FINISHED             (TEER_MISC_COMMAND | 0x07) 
		#define TEER_CONTROL_PARAMS                   (TEER_MISC_COMMAND | 0x08)
        #define TEER_STOP_SAMPLING                    (TEER_MISC_COMMAND | 0x09)
		#define TEER_GET_BUFFER                       (TEER_MISC_COMMAND | 0x0A)
		#define TEER_GET_COMPLIANCE_VOLTAGE_BUFFER    (TEER_MISC_COMMAND | 0x0B)
		#define TEER_GET_MAX_CHUNKSIZE_BYTE           (TEER_MISC_COMMAND | 0x0C)
		#define TEER_GET_BYTES_PER_SAMPLE             (TEER_MISC_COMMAND | 0x0D)
		#define TEER_GET_NUMBER_OF_AVAILABLE_SAMPLES  (TEER_MISC_COMMAND | 0x0E)
		#define TEER_BUFFER_INDEX                     (TEER_MISC_COMMAND | 0x0F)
        #define TEER_GET_ADAPTER_CODE                 (TEER_MISC_COMMAND | 0x10)
        #define TEER_GET_POSITION_CODE                (TEER_MISC_COMMAND | 0x11)
        #define TEER_SET_EXTERNAL_LED                 (TEER_MISC_COMMAND | 0x12)
        #define TEER_CURRENT_ENABLE                   (TEER_MISC_COMMAND | 0x13)
        #define TEER_UPTIME_SEC                       (TEER_MISC_COMMAND | 0x14)
        #define TEER_INTERNAL_CALIBRATION             (TEER_MISC_COMMAND | 0x15)
        #define TEER_DAC_ZERO                         (TEER_MISC_COMMAND | 0x16) 
        #define TEER_CANCEL_INTERNAL_CALIBRATION      (TEER_MISC_COMMAND | 0x17)

    #define USSING_MISC_COMMAND 0x3200
    #define USSING_MISC_COMMAND_MASK 0xFF00
		#define USSING_CHANNELS_PER_CHAMBER			  (USSING_MISC_COMMAND | 0x01)
		#define USSING_GET_MAX_CHAMBERS				  (USSING_MISC_COMMAND | 0x02)
		#define USSING_GET_AVAILABLE_CHAMBERS         (USSING_MISC_COMMAND | 0x03)
        #define USSING_IS_CHAMBER_AVAILABLE           (USSING_MISC_COMMAND | 0x04)
        //#define USSING_SET_PULSE                      (USSING_MISC_COMMAND | 0x05)
        #define USSING_HIGH_CURRENT_MODE              (USSING_MISC_COMMAND | 0x06)
	    #define USSING_CLAMP_MODE                     (USSING_MISC_COMMAND | 0x07)
		#define USSING_CALIB_FINISHED                 (USSING_MISC_COMMAND | 0x08)
        #define USSING_U1_OFFSET                      (USSING_MISC_COMMAND | 0x09)
        #define USSING_U2_OFFSET                      (USSING_MISC_COMMAND | 0x0A)
        #define USSING_U1_REFERENCE                   (USSING_MISC_COMMAND | 0x0B)
        #define USSING_U2_REFERENCE                   (USSING_MISC_COMMAND | 0x0C) 
        #define USSING_CONTROL_P                      (USSING_MISC_COMMAND | 0x0D)
        #define USSING_CONTROL_I                      (USSING_MISC_COMMAND | 0x0E)
	    #define USSING_CONTROL_D                      (USSING_MISC_COMMAND | 0x0F)
        #define USSING_DAC_ZERO                       (USSING_MISC_COMMAND | 0x10)
        #define USSING_AMPS_PER_DIGIT_LOW             (USSING_MISC_COMMAND | 0x11)
        #define USSING_AMPS_PER_DIGIT_HIGH            (USSING_MISC_COMMAND | 0x12)
        #define USSING_LO_CURRENT_RANGE_PAMP          (USSING_MISC_COMMAND | 0x13)
        #define USSING_VOLTS_PER_DIGIT                (USSING_MISC_COMMAND | 0x14) 
        #define USSING_UNITS_PER_DIGIT                (USSING_MISC_COMMAND | 0x15)
        #define USSING_UNIT_METRIC_PREFIX             (USSING_MISC_COMMAND | 0x16)
        #define USSING_UNIT_NAME                      (USSING_MISC_COMMAND | 0x17)
        #define USSING_UNIT_DESC                      (USSING_MISC_COMMAND | 0x18)
        #define USSING_HI_CURRENT_RANGE_NAMP          (USSING_MISC_COMMAND | 0x19)
        #define USSING_UPTIME_SEC                     (USSING_MISC_COMMAND | 0x1A)
        #define USSING_IDLE_VOLTAGE                   (USSING_MISC_COMMAND | 0x1B)
        #define USSING_IDLE_CURRENT                   (USSING_MISC_COMMAND | 0x1C)
        #define USSING_ENABLE_VOLTAGE_CLAMP           (USSING_MISC_COMMAND | 0x1D)
        #define USSING_ENABLE_CURRENT_CLAMP           (USSING_MISC_COMMAND | 0x1E)
        #define USSING_SET_PULSE_AMP                  (USSING_MISC_COMMAND | 0x1F)
        #define USSING_SET_PULSE_DUR                  (USSING_MISC_COMMAND | 0x20)


#define MISC_USB_COMMAND2 0x4b  // Device specific commands (2)
#define MISC_USB_COMMAND3 0x4c  // Device specific commands (3)
#define MISC_USB_COMMAND4 0x4d  // Device specific commands (4)

#define QUERY_UINT32			0x4e
// values for query_uint32
    #define GET_UINT32_NUMBER_OF_AVAIL_ANALOG_CHANNELS    0x000E
    #define GET_UINT32_NUMBER_OF_AVAIL_DIGITAL_CHANNELS   0x000F
    #define GET_UINT32_NUMBER_OF_CHANNELS   0x0010
	#define GET_UINT32_GAIN                 0x0011 // was GET_UINT32_AMPLIFICATION; Amplification = Value, when bit 31 is set Amplification =  Value/1000
	#define GET_UINT32_ADC_OFFSET			0x0012
	#define GET_UINT32_DAC_OFFSET			0x0013
	#define GET_UINT32_ENUMERATION_SPEED	0x0014
	#define GET_UINT32_USB_VERSION			0x0015  // not used any more
	#define GET_UINT32_IVOLTAGERANGE        0x0016  // index of currently set voltagerange
    #define GET_UINT32_DATAMODE             0x0017  // MEA21: 16, 24 or 32 bit data mode
    #define GET_UINT32_MEA21_USB_PORT       0x0018  // 0 or 1 for USB Port 1 or 2

	#define GET_UINT32_AVAILABLE_DATAMODES  0x0019  // bitmask 1: 16 bit, 2: 24 bit MC_Rack, 4: 24 bit, 8: 32 bit
	#define GET_UINT32_ADC_FORMAT           0x001a  // format of the ADC data (12 / 16 / 24 bit)
	#define GET_UINT32_ANALOG_GAIN          0x001b  // on the MEA2100, the gain of the analog inputs on the IFB, Gain = Value/1000

	#define GET_UINT32_MAX_SAMPLING_FREQUENCY	   0x0020
	#define GET_UINT32_BYTES_PER_MICROFRAME		   0x0021
	#define GET_UINT32_IS_MEA					   0x0022
    #define GET_UINT32_SAMPLING_FREQUENCY_STEPSIZE 0x0023

	#define GET_UINT32_NUMBER_OF_ANALOG_CHANNELS 0x0101
	#define GET_UINT32_NUMBER_OF_DIGITAL_CHANNELS 0x0102
	#define GET_UINT32_NUMBER_OF_CHECKSUM_CHANNELS 0x0103
	#define GET_UINT32_NUMBER_OF_TIMESTAMP_CHANNELS 0x0104
	#define GET_UINT32_NUMBER_OF_CHANNELS_IN_BLOCK 0x010f

	#define GET_UINT32_NUMBER_OF_AUDIO_CHANNELS 0x0120
	
	#define GET_UINT32_VOLTAGERANGE_BY_INDEX    0x0130  // list of available voltageranges
	#define GET_UINT32_SAMPLERATES_BY_INDEX     0x0131  // list of available samplerates
	
	#define GET_UINT32_UPPER_FREQ_BY_INDEX      0x0140
	#define GET_UINT32_LOWER_FREQ_BY_INDEX      0x0141
	#define GET_UINT32_DSP_HIPASS_BY_INDEX      0x0142
	#define GET_UINT32_INTAN_REGISTER           0x0143
	#define GET_UINT32_IMPEDANCE_RESULT         0x0144

    #define GET_UINT32_PLL_LOCK_STATUS   0x0150

	#define GET_UINT32_XILINX_FLASH_OFFSET       0x0201
	#define GET_UINT32_XILINX_FLASH_READ_COMMAND 0x0202

	#define GET_UINT32_USB_LAST_ERROR 0x0301
	#define GET_UINT32_RF_CONNECTION_STATUS 0x0302
	#define GET_UINT32_REQUIRED_ALTERNATE_SETTINGS 0x0303
	#define GET_UINT32_DEVICE_CANNOT_STALL_OUT_REQUEST 0x0304

	#define GET_UINT32_IMPLANTAT_VOLTAGE 0x0401

	#define GET_UINT32_FLAGA_PRE           0xf001
	#define GET_UINT32_FLAGB_PRE           0xf002
	#define GET_UINT32_FLAGC_PRE           0xf003
	#define GET_UINT32_FLAGA_POST          0xf004
	#define GET_UINT32_FLAGB_POST          0xf005
	#define GET_UINT32_FLAGC_POST          0xf006

#define COMMAND_UPLOAD       0x50		// has MCSUSB_DEST_... as wValue
#define COMMAND_FLASH        0x51		// has MCSUSB_DEST_... as wValue
#define COMMAND_EEPROM       0x52
#define COMMAND_COLDSTART    0x53		// has MCSUSB_DEST_... as wValue
#define COMMAND_BOARD_EEPROM 0x54
#define COMMAND_SETSERIAL    0x55


#define COMMAND_FOR_PIC 0x56
    #define COMMAND_USB_COLDSTART  0x01     // not used any more
    #define COMMAND_TMS_COLDSTART  0x02     // not used any more
    #define COMMAND_PIC2_COLDSTART 0x04     // not used any more
    #define COMMAND_BACKUP_EEPROM  0x10     // not used any more
    #define COMMAND_RESTORE_EEPROM 0x11     // not used any more
    #define COMMAND_ERASE_EEPROM   0x12     // not used any more
    #define COMMAND_FLASH_PIC     0x20      // not used any more
    #define COMMAND_RELAY_MODE    0x21      // releay i2c commands to 2nd pic
    #define COMMAND_POWER_TRANSFORMER 0x30  // turn pwm for transformer on or off
    #define COMMAND_ENABLE_SERIAL 0x40      // not used any more
    #define COMMAND_PIC_READ_ADC0 0x81
    #define COMMAND_PIC_READ_ADC1 0x82      // used with index  from COMMAND_PIC_READ_ADC0
    #define COMMAND_PIC_READ_VERSION 0x90   // not used any more
    #define COMMAND_PIC_GET_FLASHSIZE 0x91  // not used any more

#define COMMAND_PIC_READ_MEMORY 0x57

#define COMMAND_CYPRESS_USB		0x58
	#define CYPRESS_USB_INPKTEND    0x01
	#define CYPRESS_USB_FIFORESET   0x11
	#define CYPRESS_USB_SETEP2ISOINPKTS 0x21
	#define CYPRESS_USB_BULK_ERASE_AVAIL 0x80
	#define CYPRESS_USB_BULK_ERASE  0x81

#define COMMAND_FOR_PIC2 0x59
#define COMMAND_FOR_PIC3 0x5a


#define COMMAND_DOWNLOAD_EX  0x60 // extension to COMMAND_DOWNLOAD, so that it works on any target and addresses > 24bit
#define COMMAND_DOWNLOAD 	 0x61 
#define COMMAND_FLASHMODE    0x62 // supported for all PIC devices with our new Vendor ID, tell a pic to enter flashmode 
#define COMMAND_GET_FLASHSIZE 0x63 // supported for all PIC devices with our new Vendor ID, query the available flash memory

#define COMMAND_HARDWARE_TEST	 0x64
	#define COMMAND_TXN_TEST_MEMORY_WRITE           0x01  // Check the memory of the TXN module: Write Values
	#define COMMAND_TXN_TEST_MEMORY_READ_AND_CHECK  0x02  // Check the memory of the TXN module: Read Values and Check

	#define COMMAND_TXN_SETSERIALNUMBER 0x11 // Sets the internal serial number of the TXN module
	#define COMMAND_TXN_GETSERIALNUMBER 0x12 // Gets the internal serial number of the TXN module

    #define COMMAND_WRITE_REGISTER 0x21  // Write to a Register (used on Xilinx FPGA devices)
    #define COMMAND_READ_REGISTER  0x22  // Read from a Register (used on Xilinx FPGA devices)
	
	#define COMMAND_WRITE_REGISTER_TS_0 0x30  // Write to a Register (used on Xilinx FPGA devices) - time slot 0
	#define COMMAND_WRITE_REGISTER_TS_1 0x31  // Write to a Register (used on Xilinx FPGA devices) - time slot 1
	#define COMMAND_WRITE_REGISTER_TS_2 0x32  // Write to a Register (used on Xilinx FPGA devices) - time slot 2
	#define COMMAND_WRITE_REGISTER_TS_3 0x33  // Write to a Register (used on Xilinx FPGA devices) - time slot 3
	/* 0x34 - 0x3F reserved in W2100 */
    
	#define COMMAND_READ_REGISTER_TS_0  0x40  // Read from a Register (used on Xilinx FPGA devices) - time slot 0
	#define COMMAND_READ_REGISTER_TS_1  0x41  // Read from a Register (used on Xilinx FPGA devices) - time slot 1
	#define COMMAND_READ_REGISTER_TS_2  0x42  // Read from a Register (used on Xilinx FPGA devices) - time slot 2
	#define COMMAND_READ_REGISTER_TS_3  0x43  // Read from a Register (used on Xilinx FPGA devices) - time slot 3
	/* 0x44 - 0x4F reserved in W2100 */

#define COMMAND_RADIO_CONTROL	0x65
	#define COMMAND_RADIO_HAS_RADIO_CONTROL		0x01
	#define COMMAND_RADIO_GET_DEVICE_NAMES		0x02
	#define COMMAND_RADIO_CONNECT_DEVICE		0x03
	#define COMMAND_RADIO_DISCONNECT_DEVICE		0x04
	#define COMMAND_RADIO_STILL_CONNECTED		0x05
	#define COMMAND_RADIO_SET_FREQUENCY			0x06
	#define COMMAND_RADIO_GET_FREQUENCY			0x07


#define COMMAND_MCSBUS 0x66 // Commands send to the MCSBUS

// *** AB Commands ***

	#define MCSBUS_COMMAND_LEGACY  0x0080 // This bit was always set for AB commands, only needed in firmware to catch old DLL version which send COMMAND_MCSBUS as COMMAND_ROBO
	#define MCSBUS_USB		       0x0040 // distingish between MCSBUS short commands and USB commands
	#define MCSBUS_OUT_SET_COMMAND 0x00
	#define MCSBUS_IN_GET_COMMAND  0x20

	#define MCSBUS_BUSNUMBER_SHIFT 13 // The bus number is shifted to this position in the index;
	#define MCSBUS_BUSNUMBER_MASK (7 << MCSBUS_BUSNUMBER_SHIFT)

	#define MCSBUS_MC_COMMAND_SHIFT 3 // 1 bit for 2 axis +  2 bit for size
	#define MCSBUS_VM_COMMAND_SHIFT 4 // 2 bit for 4 channels + 2 bit for size
	// in MotorControl Mode, bit 2 selects the axis
	// in Voltage Mode, bit 2 selects the side, bit 3 selects the subchannel 
	// 00: Channel 0
	// 01: Channel 2
	// 10: Channel 1
	// 11: Channel 3
	// this allows the module to operate one side in MC mode and the other in Voltage mode

	// McsBus USB Commands // only 4 bits for usb (different to short commands), because both commands needs to be handled
	// Eeprom
	#define MCSBUS_EEPROM_PARAMETER	            (0x00 << MCSBUS_VM_COMMAND_SHIFT)
	#define MCSBUS_PARAMETER					(0x08 << MCSBUS_VM_COMMAND_SHIFT)
		#define MCSBUS_PARAMETER_INDEX_MODE						 0  // define the mode (MotorControl, Voltage, ..

		#define MCSBUS_PARAMETER_INDEX_MC_SCALINGFACTOR		     1
		#define MCSBUS_PARAMETER_INDEX_MC_MAXSPEED			     2
		#define MCSBUS_PARAMETER_INDEX_MC_MAXTRAVEL			     3
		#define MCSBUS_PARAMETER_INDEX_MC_CURRENT			     4
		#define MCSBUS_PARAMETER_INDEX_MC_MAXCURRENT		     5
		#define MCSBUS_PARAMETER_INDEX_MC_REGULATORGAIN		     6
		#define MCSBUS_PARAMETER_INDEX_BUSADDRESS			     7	// must be implemented in all MCSBUS devices
		#define MCSBUS_PARAMETER_INDEX_MC_MAXACCELERATION	     8
		#define MCSBUS_PARAMETER_INDEX_MC_STANDBYCURRENT	     9
		#define MCSBUS_PARAMETER_INDEX_MC_STANDBYTIME		    10
		#define MCSBUS_PARAMETER_INDEX_MC_BREAKCURRENT		    11
		#define MCSBUS_PARAMETER_INDEX_MC_CONFIG			    12
		#define MCSBUS_PARAMETER_INDEX_MC_DEFAULTSPEED		    13
		#define MCSBUS_PARAMETER_INDEX_MC_DEFAULTACCELERATION	14
		#define MCSBUS_PARAMETER_INDEX_MC_REFERENCECURRENT	    15
		#define MCSBUS_PARAMETER_INDEX_MC_CURRENTMODE			16
		#define MCSBUS_PARAMETER_INDEX_MC_AXISREVISION		    17
		#define MCSBUS_PARAMETER_INDEX_HWREVISION				18 

		#define MCSBUS_PARAMETER_INDEX_VM_MAX_POS_CURRENT       30
		#define MCSBUS_PARAMETER_INDEX_VM_MAX_NEG_CURRENT       31
		#define MCSBUS_PARAMETER_INDEX_VM_MAX_POS_VOLTAGE		32
		#define MCSBUS_PARAMETER_INDEX_VM_MAX_NEG_VOLTAGE		33

		#define MCSBUS_PARAMETER_INDEX_AXIS_PARAMETER			64 // only for command MCSBUS_EEPROM_PARAMETER
		// ... 78   15 Axis Parameter indices per axis
        #define MCSBUS_PARAMETER_INDEX_SPEED_UNIT               64 // This position of axis parameter is used for SPEED UNIT

	#define MCSBUS_SENSOR						(0x01 << MCSBUS_VM_COMMAND_SHIFT) // to modules connected via i2c slave to AB_RevA module
																				  // index bits 8 .. 12 are used in some commands to select channel
		#define MCSBUS_SENSOR_INDEX_MINIMAL_THRESHOLD			1	// Bubble detector
		#define MCSBUS_SENSOR_INDEX_DETECTION_THRESHOLD			2
		#define MCSBUS_SENSOR_INDEX_LATENCY						3
		#define MCSBUS_SENSOR_INDEX_BUBBLE_STATUS				10
		#define MCSBUS_SENSOR_INDEX_LATENCY_COUNTER				11
		#define MCSBUS_SENSOR_INDEX_RESTART						12
		#define MCSBUS_SENSOR_INDEX_DETECTORVALUE				13

		#define MCSBUS_SENSOR_INDEX_GETPRESSURE					20	// FYI pressure module, PressureRegulator8 module
		#define MCSBUS_SENSOR_INDEX_GETREGULATORSPEED			21
		#define MCSBUS_SENSOR_INDEX_SOLLPRESSURE				22
		#define MCSBUS_SENSOR_INDEX_REGULATORONOFF				23
		#define MCSBUS_SENSOR_INDEX_REGULATORFACTORS			24
		#define MCSBUS_SENSOR_INDEX_SETPRESSUREOFFSET			25
		#define MCSBUS_SENSOR_INDEX_REGULATORSTATUS				26
		#define MCSBUS_SENSOR_INDEX_ROTATE_PERISTALTIC			27
		#define MCSBUS_SENSOR_INDEX_MOVE_PERISTALTIC			28
		#define MCSBUS_SENSOR_INDEX_SETTIMEOUTS					29
		// reserved bit 8 to 10 is used as index to the motor

		#define MCSBUS_SENSOR_INDEX_GET4ADC						30  // Patch Server DAC ADC module
		#define MCSBUS_SENSOR_INDEX_SET4DAC						31
        #define MCSBUS_SENSOR_INDEX_4ADC_MODE                   32
        #define MCSBUS_SENSOR_INDEX_GET4ADC_AVERAGE             33
        #define MCSBUS_SENSOR_INDEX_CATCHAMP_AVERAGE_SHIFT      34
        #define MCSBUS_SENSOR_INDEX_GET2ANALOGINPUT             35
        #define MCSBUS_SENSOR_INDEX_GET2DIGITALINPUT            36

		#define MCSBUS_SENSOR_INDEX_GETBUFFER					40  // Patch Server get data buffer
		#define MCSBUS_SENSOR_INDEX_SETPIEZO					41  

		#define MCSBUS_SENSOR_INDEX_SETDAC						50  // Patch Server DAC ADC module DAC programm
		// reserved - 53

		#define MCSBUS_SENSOR_INDEX_SAMPLEPERIODE				60  // Patch Server DAC ADC module
		#define MCSBUS_SENSOR_INDEX_SYNCSTART					61  // Patch Server DAC ADC module start in sync

		#define MCSBUS_SENSOR_INDEX_CATCHAMP_DACAMPLITUDE		70
		#define MCSBUS_SENSOR_INDEX_CATCHAMP_DACOFFSET			71
        #define MCSBUS_SENSOR_INDEX_CATCHAMP_ADCMEAN            72
		#define MCSBUS_SENSOR_INDEX_CATCHAMP_ADCVALUE			73
		#define MCSBUS_SENSOR_INDEX_CATCHAMP_ADCVALUE_H			74
		#define MCSBUS_SENSOR_INDEX_CATCHAMP_ADCVALUE_L			75
        #define MCSBUS_SENSOR_INDEX_CATCHAMP_PWM_ENABLE         76
        #define MCSBUS_SENSOR_INDEX_CATCHAMP_DAC_ENABLE         77

        #define MCSBUS_SENSOR_INDEX_TACTSWITCH_GETSTATE         90
        #define MCSBUS_SENSOR_INDEX_TACTSWITCH_DISPLAY          91
        #define MCSBUS_SENSOR_INDEX_TACTSWITCH_SET_LEDS         92

        #define MCSBUS_SENSOR_INDEX_PROGRAM                    100
        #define MCSBUS_SENSOR_INDEX_PROGRAM_PRESSURE           101
        #define MCSBUS_SENSOR_INDEX_PROGRAM_PRESSURE_STEPS     102
        #define MCSBUS_SENSOR_INDEX_PROGRAM_DURATION           103
        #define MCSBUS_SENSOR_INDEX_PROGRAM_SIZE               104
        #define MCSBUS_SENSOR_INDEX_PROGRAM_REPEAT             105

// max allowed value for index: 255

	#define MCSBUS_TEMP_SENSOR					(0x02 << MCSBUS_VM_COMMAND_SHIFT)
		#define MCSBUS_TEMP_SENSOR_INDEX_TEMPERATUR					1
		// reserved - 5
		#define MCSBUS_TEMP_SENSOR_INDEX_NANOVOLTPERKELVIN			0x10
		#define MCSBUS_TEMP_SENSOR_INDEX_GET_THERMO_VOLTAGE			0x11
		// reserved - 0x15
		#define MCSBUS_TEMP_SENSOR_INDEX_GET_THERMO_TEMP			0x21
		// reserved - 0x25
		#define MCSBUS_TEMP_SENSOR_INDEX_OFFSET						0x31
		// reserved - 0x35

	#define MCSBUS_EXTENSION					(0x03 << MCSBUS_VM_COMMAND_SHIFT)
		#define MCSBUS_EXTENSION_INDEX_LED							1

	#define MCSBUS_FYI_EXTENSION				(0x04 << MCSBUS_VM_COMMAND_SHIFT)
		#define MCSBUS_FYI_EXTENSION_VALVES							1
//		#define MCSBUS_FYI_EXTENSION_HEATER							2
		#define MCSBUS_FYI_EXTENSION_DIO							3
		#define MCSBUS_FYI_EXTENSION_DATADIR						4
		#define MCSBUS_FYI_EXTENSION_SINGLE_HEATER					5
		// reserved - 9

//	SEE_ABOVE after MCSBUS_EEPROM_PARAMETER		(0x08 << MCSBUS_VM_COMMAND_SHIFT)

	// McsBus Short Commands 
	// for AB Module in MotorControl mode
	#define MCSBUS_MC_ONOFF					(0x00 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_SPEED					(0x01 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_ACCELERATION			(0x02 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_CURRENT				(0x03 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_MAXTRAVEL				(0x04 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_CURRENTPOSITION		(0x05 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_NEWPOSITION			(0x06 << MCSBUS_MC_COMMAND_SHIFT)
	
	#define MCSBUS_MC_MOVEMENT				(0x07 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_REFERENCE				(0x08 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_STOPMOVEMENT          (0x09 << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_CURRENTSPEED			(0x0a << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_CURRENTMODE			(0x0b << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_PHASE					(0x0c << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_PHASEOFFSET			(0x0d << MCSBUS_MC_COMMAND_SHIFT)
	#define MCSBUS_MC_SETSUBCHANNEL			(0x0e << MCSBUS_MC_COMMAND_SHIFT)
	//0x0f
	//0x10
	//0x11 
	//...
    //0x1f

	// for AB Module in Voltage mode
	#define MCSBUS_VM_ONOFF		            (0x00 << MCSBUS_VM_COMMAND_SHIFT)
	#define MCSBUS_VM_VOLTAGE				(0x01 << MCSBUS_VM_COMMAND_SHIFT)
	//0x02
	//...
	//0x0f

#define COMMAND_ROBO 0x67 // All commands for Robo class devices
// Other Robo Commands (bit 7 set is not allowed here, because this is for MCSBUS_COMMAND)

	#define COMMAND_ROBO_FIND_REFERENCE	0x0100 
	#define COMMAND_ROBO_MOVEABS		0x0200
	#define COMMAND_ROBO_STOPMOVEMENT   0x0300

	#define COMMAND_ROBO_XYPLANEPREPARATION 0x0400

	#define COMMAND_ROBO_USB_INTERRUPT_BUFFER 0x0700

	#define COMMAND_ROBO_AIRVALVE		0x0800

// Setting on pic32 general
	#define COMMAND_ROBO_SETTINGS		0x0b00
		#define COMMAND_ROBO_SETTINGS_INDEX_HWREVISION				0x00
		#define COMMAND_ROBO_SETTINGS_INDEX_CONFIG					0x01
		#define COMMAND_ROBO_SETTINGS_INDEX_MINPRESSUREWAITTIME		0x02
		#define COMMAND_ROBO_SETTINGS_INDEX_MINPRESSURE				0x03
		#define COMMAND_ROBO_SETTINGS_INDEX_MAXPRESSUREWAITTIME		0x04
		#define COMMAND_ROBO_SETTINGS_INDEX_MINNOPRESSUREWAITTIME	0x05
		#define COMMAND_ROBO_SETTINGS_INDEX_MAXNOPRESSURE			0x06
		#define COMMAND_ROBO_SETTINGS_INDEX_MAXNOPRESSUREWAITTIME	0x07

		#define COMMAND_ROBO_SETTINGS_INDEX_FIRMWAREVERSION 0x20 // Not implemented as command, eeprom pos
    
    #define COMMAND_USER_SETTINGS       0x0C00

// Measured values on robo main
	#define COMMAND_ROBO_MAIN_MEASURE			0x1000
		#define COMMAND_ROBO_MAIN_MEASURE_VALUES	(COMMAND_ROBO_MAIN_MEASURE | 0x01)
		#define COMMAND_ROBO_MAIN_MEASURE_LIMITS	(COMMAND_ROBO_MAIN_MEASURE | 0x02)
		#define COMMAND_ROBO_MAIN_MEASURE_ERROR		(COMMAND_ROBO_MAIN_MEASURE | 0x03)

			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_ERROR			0x01
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_VALVES		0x02
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_RS485A		0x03
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_RS485B		0x04
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_AIRVALVE		0x05
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_I_AIRVALVE		0x06
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_12V			0x07 
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_AIRPRESSURE		0x08
			#define COMMAND_ROBO_MAIN_MEASURE_INDEX_V_5V			0x09

// Settings on pic32 for axes
	#define	COMMAND_ROBO_PARAMETER_AXIS			0x1100
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEMETHOD		0x00
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_REFERENCEOFFSET			0x01
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEFASTSPEED	0x02
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEFASTACCEL	0x03
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEFINESPEED	0x04
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEFINEACCEL	0x05
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_SEARCHREFERENCEMOVEOUT	0x06
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_CONFIG					0x07
		#define COMMAND_ROBO_PARAMETER_AXIS_INDEX_PHASE0					0x08 // internal usage

	#define COMMAND_ROBO_GETPHASES				0x1200

	#define COMMAND_ROBO_SEND_BROADCAST			0x1300

	#define COMMAND_ROBO_FYI				    0x1400
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_REGULATORONOFF					0x00
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_SOLLTEMP						0x01
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_PCOEFF							0x02
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_ICOEFF							0x03
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_MAXPOWER						0x04

		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_PROGRAM_VALVE1					0x05
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_PROGRAM_VALVE2					0x06
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_PROGRAM_LENGTH					0x07
		#define COMMAND_ROBO_FYI_PARAMETER_INDEX_PROGRAM_STATE					0x08


	#define COMMAND_ROBO_MCSBUS 0x4000

#define COMMAND_FILTERFEEDBACK_CONTROL 0x68
	// Use higher 8bit for commands
	#define COMMAND_FILTERFEEDBACK_BASE		0x0000
		#define COMMAND_FILTERFEEDBACK_SET_FILTERFEEDBACK						0x0000
		#define COMMAND_FILTERFEEDBACK_GET_SAMPLETIMERCOUNT						0x0001
		#define COMMAND_FILTERFEEDBACK_SET_DIGITALMAPPING						0x0002
	#define COMMAND_FILTERFEEDBACK_SET_FILTER_PARAMETER		0x0100   // lower 8bit are filter number
	#define COMMAND_FILTERFEEDBACK_SET_CHANNELFILTER		0x0200
	#define COMMAND_FILTERFEEDBACK_SPIKEDETECTOR			0x0300
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_SPIKEDETECTOR_THRESHOLD	0x0300
		#define COMMAND_FILTERFEEDBACK_SET_SPIKEDETECTOR_THRESHOLD				0x0301
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_SPIKEDETECTOR_SLOPE		0x0310
		#define COMMAND_FILTERFEEDBACK_SET_SPIKEDETECTOR_SLOPE					0x0311
	#define COMMAND_FILTERFEEDBACK_RATEDETECTOR				0x0400
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_RATECOUNTER				0x0400
		#define COMMAND_FILTERFEEDBACK_SET_RATECOUNTER							0x0401
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_RATEDETECTOR				0x0410
		#define COMMAND_FILTERFEEDBACK_SET_RATEDETECTOR							0x0411
	#define COMMAND_FILTERFEEDBACK_LOGIC					0x0500
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_LOGIC						0x0500
		#define COMMAND_FILTERFEEDBACK_SET_LOGIC								0x0501
	#define COMMAND_FILTERFEEDBACK_TRIGGER					0x0600
		#define COMMAND_FILTERFEEDBACK_SET_NUMBER_OF_TRIGGER					0x0600
		#define COMMAND_FILTERFEEDBACK_SET_TRIGGER								0x0601
	#define COMMAND_FILTERFEEDBACK_ANALOGSOURCE				0x0700  // lower 8bit are AnalogSource Enumeration (HS1, HS2, ...)

#define COMMAND_CLAMPAMP 0x69
	#define COMMAND_CLAMPAMP_SIMULATION             0x0002

	#define COMMAND_CLAMPAMP_RAMP					0x0011
	#define COMMAND_CLAMPAMP_RECORDINGNUMBER        0x0012

	#define COMMAND_CLAMPAMP_GET_SERIALNUMBER		0x0141

	#define COMMAND_CLAMPAMP_GET_RESISTANCE_C		0x0156	// Resistance on current electrode
	#define COMMAND_CLAMPAMP_GET_RESISTANCE_V		0x0157  // Resistance on voltage electrode
	#define COMMAND_CLAMPAMP_GET_CAPACITY_C         0x0158  // Capacity on current electrode
	#define COMMAND_CLAMPAMP_GET_CAPACITY_V         0x0159  // Capacity on voltage electrode
	#define COMMAND_CLAMPAMP_GET_CAPACITY_X         0x015a  // Capacity between current and voltage electrode

	#define COMMAND_CLAMPAMP_GET_UV					0x015c  // Voltage on voltage electrode
	#define COMMAND_CLAMPAMP_GET_UC					0x015d  // Voltage on current electrode
	#define COMMAND_CLAMPAMP_GET_IC					0x015e  // Current on current electrode

	#define COMMAND_CLAMPAMP_RESTART				0x0160

	#define COMMAND_CLAMPAMP_CONFIGURATION			0x0170
	#define COMMAND_CLAMPAMP_UCLAMP					0x0171
	#define COMMAND_CLAMPAMP_ICLAMP					0x0172
	#define COMMAND_CLAMPAMP_PGAIN					0x0173	
	#define COMMAND_CLAMPAMP_IGAIN					0x0174	
	#define COMMAND_CLAMPAMP_FILTER					0x0175	
	#define COMMAND_CLAMPAMP_CONFIGURATIONBIT		0x0176  // For bitwise get or set of configuration (status)

	#define COMMAND_CLAMPAMP_CROSSTALK				0x017A  
	#define COMMAND_CLAMPAMP_XGAIN					0x017B
	#define COMMAND_CLAMPAMP_UV_OFS       			0x017c
	#define COMMAND_CLAMPAMP_UC_OFS       			0x017d
	#define COMMAND_CLAMPAMP_IC_OFS       			0x017e
	#define COMMAND_CLAMPAMP_CX_OPT					0x017f

	#define COMMAND_CLAMPAMP_COMP					0x0180
	#define COMMAND_CLAMPAMP_GET_NUV_MS				0x018C
	#define COMMAND_CLAMPAMP_GET_NUC_MS				0x018D
	#define COMMAND_CLAMPAMP_GET_NIC_MS				0x018E

	#define COMMAND_CLAMPAMP_TABLE_DEF_BGN			0x0200
	#define COMMAND_CLAMPAMP_TABLE_DEF_END			0x0201
	#define COMMAND_CLAMPAMP_TABLE_WAIT				0x0202
	#define COMMAND_CLAMPAMP_TABLE_RUN				0x0210
	#define COMMAND_CLAMPAMP_TABLE_STOP				0x0211

	#define COMMAND_CLAMPAMP_DOWNSAMPLE_FACTOR		0x0400
	#define COMMAND_CLAMPAMP_FILTER_COEFFS			0x0401
	#define COMMAND_CLAMPAMP_FILTERCHANNEL_MASK     0x0402

	#define COMMAND_CLAMPAMP_USB_INTERRUPT_BUFFER   0x0700

	#define COMMAND_CLAMPAMP_DIGOUT					0x0800

	#define COMMAND_CLAMPAMP_EMU_ELECTRODE_RESIST	0x4001
	#define COMMAND_CLAMPAMP_EMU_CELL_CAPACITY		0x4003
	#define COMMAND_CLAMPAMP_EMU_CELL_RESIST		0x4004
	#define COMMAND_CLAMPAMP_EMU_CELL_POTENTIAL		0x4005
	
	#define COMMAND_CLAMPAMP_EMU_NOISE				0x4011

	#define COMMAND_CLAMPAMP_SET_DISPLAY			0x5001
	#define COMMAND_CLAMPAMP_SET_SCREEN				0x5002
	#define COMMAND_CLAMPAMP_UPDATE_DISPLAY			0x5003

	#define COMMAND_CLAMPAMP_GETSET_COMMAND			0xF000 // - 0xF0FF  OR with the command to/from ClampAmp
		#define COMMAND_CLAMPAMP_GETSET_COMMAND_MASK	0xFF00
		#define COMMAND_CLAMPAMP_GETSET_VALUE_MASK		0x00FF


#define CLAMPAMP_INTERNAL_GETSET_DIGOUT    0x20  // Internal command in robo_omapl138 to get and set the digouts, this command is NOT send to the ClampAmp
#define CLAMPAMP_INTERNAL_GET_VERSION      0x40
#define CLAMPAMP_INTERNAL_GET_SER_NO       0x41
#define CLAMPAMP_INTERNAL_GET_FLASH_SRC    0x42
#define CLAMPAMP_INTERNAL_GET_FLASH_DST    0x43
#define CLAMPAMP_INTERNAL_GET_FLASH_LEN    0x44
#define CLAMPAMP_INTERNAL_GET_FLASH_STATUS 0x45

#define CLAMPAMP_INTERNAL_FLASH_WP_CLEAR   0x46
#define CLAMPAMP_INTERNAL_FLASH_WP_SET     0x47

#define CLAMPAMP_INTERNAL_FLASH_ERASE      0x48
#define CLAMPAMP_INTERNAL_FLASH_GET_ID     0x49
#define CLAMPAMP_INTERNAL_FLASH_COPY       0x4a
#define CLAMPAMP_INTERNAL_START_XMODEM     0x4e

#define CLAMPAMP_INTERNAL_GET_STATUS       0x50
#define CLAMPAMP_INTERNAL_GET_VOLTAGE_SP   0x51
#define CLAMPAMP_INTERNAL_GET_CURRENT_SP   0x52
#define CLAMPAMP_INTERNAL_GET_GAIN_P	   0x53
#define CLAMPAMP_INTERNAL_GET_GAIN_I       0x54
#define CLAMPAMP_INTERNAL_GET_FILTER       0x55
#define CLAMPAMP_INTERNAL_GET_RESI_V       0x56
#define CLAMPAMP_INTERNAL_GET_RESI_C       0x57
#define CLAMPAMP_INTERNAL_GET_CAPA_V       0x58
#define CLAMPAMP_INTERNAL_GET_CAPA_C       0x59
#define CLAMPAMP_INTERNAL_GET_CAPA_X       0x5a
#define CLAMPAMP_INTERNAL_GET_GAIN_X       0x5b
#define CLAMPAMP_INTERNAL_GET_ADC_V        0x5c
#define CLAMPAMP_INTERNAL_GET_ADC_C        0x5d
#define CLAMPAMP_INTERNAL_GET_DAC_C        0x5e

#define CLAMPAMP_INTERNAL_RESTART          0x60
#define CLAMPAMP_INTERNAL_SET_FLASH_SRC    0x62
#define CLAMPAMP_INTERNAL_SET_FLASH_DST    0x63
#define CLAMPAMP_INTERNAL_SET_FLASH_LEN    0x64
#define CLAMPAMP_INTERNAL_SET_FLASH_STATUS 0x65

#define CLAMPAMP_INTERNAL_SET_STATUS       0x70
#define CLAMPAMP_INTERNAL_SET_VOLTAGE_SP   0x71
#define CLAMPAMP_INTERNAL_SET_CURRENT_SP   0x72
#define CLAMPAMP_INTERNAL_SET_GAIN_P	   0x73
#define CLAMPAMP_INTERNAL_SET_GAIN_I       0x74
#define CLAMPAMP_INTERNAL_SET_FILTER       0x75

#define CLAMPAMP_INTERNAL_SET_CROSSTALK    0x7A
#define CLAMPAMP_INTERNAL_SET_GAIN_X       0x7B
#define CLAMPAMP_INTERNAL_SET_UV_OFS       0x7c
#define CLAMPAMP_INTERNAL_SET_UC_OFS       0x7d
#define CLAMPAMP_INTERNAL_SET_IC_OFS       0x7e
#define CLAMPAMP_INTERNAL_SET_CX_OPT       0x7f

#define CLAMPAMP_INTERNAL_GET_NUV_MS       0x8C
#define CLAMPAMP_INTERNAL_GET_NUC_MS       0x8D
#define CLAMPAMP_INTERNAL_GET_NIC_MS       0x8E

#define CLAMPAMP_INTERNAL_MAX_FIRMWARE_SIZE_WORDS   0x4000		// 16384 16 bit words == 32768 bytes

#define CLAMPAMP_INTERNAL_MAX_NACK_COUNT   8             // accept maximum 8 NACKs from ClampAmp


#define COMMAND_ACCESS_REGISTER_32	       0x6A


#define COMMAND_MCSUSB_DEVELOP 0x70 /* to be used for development purposes to send all kind of data to the device */

#define GET_PRODUCT          0x71   /* used in STG200x and Cytoamp from linux  */
#define GET_MANUFACTURER     0x72   /* used in STG200x and Cytoamp from linux  */
#define GET_SERIALNUMBER     0x73   /* used in STG200x and Cytoamp from linux  */
#define GET_BCDDEVICE        0x74   /* used in STG200x and Cytoamp from linux  */
#define GET_BOARD_EEPROM     0x75   /* read content of Board EEPROM on STG200x  */
#define GET_ASCII_VERSION    0x76   /* used in STG200x and Cytoamp from linux  */
#define GET_BUILT_DATE       0x77   /* used in STG200x and Cytoamp from linux  */
#define GET_BUILT_TIME       0x78   /* used in STG200x and Cytoamp from linux  */

#define COMMAND_CYPRESS_FIRMWARE_LOAD 0xa0 /* Cypress build in Firmware load */

// Multiwell plate type definitions
#define HS_PLATETYPE_AUTO_DETECT 0xffffffff
#define HS_PLATETYPE_0    0
#define HS_PLATETYPE_6    6
#define HS_PLATETYPE_7    7
#define HS_PLATETYPE_33   33
#define HS_PLATETYPE_36   36
#define HS_PLATETYPE_40   40
#define HS_PLATETYPE_44   44
#define HS_PLATETYPE_48   48
#define HS_PLATETYPE_126  126
#define HS_PLATETYPE_193  193              
#define HS_PLATETYPE_195  195              
#define HS_PLATETYPE_224  224
#define HS_PLATETYPE_232  232               
#define HS_PLATETYPE_244  244



#endif

/********************************************************************/


// -------------------------------------------------------------------------------------------






// -------------------------------------------------------------------------------------------

/*! Structure to define the memory layout of the current segment.
 * Used by STG200x_SetCapacity()
 */

 /* for the new STG, the capacity is passed as a pointer to uint32 
    with the following definition:

typedef struct new_capacity {
	uint32_t channels;				// number of channels we define
	uint32_t channel_data[channels];  // one entry for each channel
	uint32_t syncouts;                // number of sync_out we define
	uint32_t capacity_data[syncouts]; // one entry for each sync_out
} new_capacity;

*/


// -------------------------------------------------------------------------------------------


typedef struct programinfo_t {
	char  info[STG200x_PROGINFO_LENGTH]   ;
} programinfo_t;


// -------------------------------------------------------------------------------------------

/*! Structure for version information of the STG.
 *  Used by STG200x_GetVersionInfo()
 *
 */

typedef struct version {
	char  swmajor;                         /*!<  major number of the software in STG firmware */
	char  swminor;                         /*!<  minor number of the software in STG firmware */
	char  hwversion[MCS_USB_VERSION_LENGTH];   /*!<  hardware revision of the STG as found in onboard EEPROM */
} version;





/*! Structure holds a bitmap of triggers which are to be enabled or disabled
 *  bit 0 to 3 : Trigger 0 to 3
 *  bit 4      : Front Side button
 */

// TMS320F6413 aligns uint32 to 4 byte boundaries, and we need more than 8 bits:
typedef struct new_endistrigger_t {
    uint32_t triggermask;  /*!< Bitmap of triggers to enable or disable */
    uint32_t triggercount; /*!< Number of allowed trigger */
} new_endistrigger_t;


/*! Structure holds the segment number and
 *  a bitmap of triggers which are started or stopped.
 *  Used by STG200x_SegmentStart().
 *
 */


typedef struct segmentstart_t {
	uint32_t segment      ;  /*!< Segment number to switch to before starting the STG */
    uint8_t  triggermap   ;  /*!< Bitmap of triggers to start (see ::startstop) */
} segmentstart_t;



// -------------------------------------------------------------------------------------------


/*! Structure to define the connection between trigger,
 * channels and syncout.
 * Used by STG200x_SetupTrigger().
 */

typedef struct new_setuptrigger_t {
	uint32_t	channelmap;
	uint32_t	syncmap;
	uint32_t	repeat;
	uint32_t	digoutmap;
	uint32_t	autostart;
} new_setuptrigger_t;


/*! Structure which holds to current sweep and tigger count.
 * Used by STG200x_GetSweepCount().
 */
typedef struct new_sweepcount_t {
	uint32_t sweeps;
	uint32_t triggers;
} new_sweepcount_t;



// -------------------------------------------------------------------------------------------

/*! Structure which holds data for channels and syncout
 * Only used internally.
 */

#ifndef __C51__
typedef struct channeldata_t {
    uint16_t   command             ;  /*!< command (needed for bulk transfer) */
    uint16_t   channel             ;  /*!< channel for which the data is */
    uint16_t   len                 ;  /*!< number of data points */
    int16_t    data[STG200x_DATA_BLOCKSIZE]  ;  /*!< list of data   */
} channeldata_t;
#endif

#ifndef __C51__
typedef struct syncoutdata_t {
    uint16_t   command             ;  // command (needed for bulk out)
    uint16_t   syncout             ;  // syncout for which the data is
    uint16_t   len                 ;  // number of data points
    int16_t    data[STG200x_DATA_BLOCKSIZE]  ;  // list of data  
} syncoutdata_t;
#endif

// -------------------------------------------------------------------------------------------

typedef struct filtersetup {
    int64_t B0;  // Filter Coefficients for MEA System B0 in Q1.62
    int64_t B1;  // Filter Coefficients for MEA System B1 in Q1.62
    int64_t A1;  // Filter Coefficients for MEA System A1 in Q1.62
    int64_t B2;  // Filter Coefficients for MEA System B2 in Q1.62
    int64_t A2;  // Filter Coefficients for MEA System A2 in Q1.62
} filtersetup;

// -------------------------------------------------------------------------------------------

/*! Structure for information on STG resolution. 
 *  Used by STG200x_GetIVal() and STG200x_GetUVal() 
 *
 */

typedef struct getval_t {
    uint32_t  range               ;  /*!< range of Voltage or Current outputs in mV and uA */
    uint32_t  res                 ;  /*!< resolution of Voltage or Current outputs in mV and uA */
} getval_t;


// -------------------------------------------------------------------------------------------

/*! Structure for information on STG.
 *  Used by STG200x_GetIdent()
 *
 */

typedef struct getident {
    char   buffer[MCS_USB_IDENT_LENGTH];
} getident;


// -------------------------------------------------------------------------------------------

/*! Structure to hold data to be sent to STG.
 *  Used by STG200x_UploadBlock()
 *
 */


#ifndef __C51__
typedef struct upload_block {
    uint16_t  block_address         ;  /*!< Block destination address */
    char    data[MCS_USB_UL_BLOCKSIZE]   ;  /*!< list of data */
} upload_block;
#endif


// -------------------------------------------------------------------------------------------

//
// the flash_command structure must NOT be a multiple of 8 bytes
// STG200x Firmware revision ealier than 2.30 have a bug and
// can not handle transfers on EP0 with a packet size of multiple of 8
//
typedef struct flash_command {
    uint32_t  flash_addr;
    uint32_t  flash_size;
	uint16_t  dummy;    // dummy entry to avoid multiple of 8 size, DO NOT DELETE!!
} flash_command;


/*! Structure to hold information about the current trigger status of the STG.
 *
 */

typedef struct trigger_status_t {
	uint8_t  active_map;      /*!< Bitmap of currently active tiggers */
	uint8_t  finished_map;    /*!< Bitmap of finished trigger */
	uint8_t  armed_map;       /*!< Bitmap of armed triggers (for single mode) */
	uint8_t  reserved2;       /*!< reserved */
} trigger_status_t;

/*! Structure used to reset the ::trigger_status of the STG.
 *  Used by STG200x_ResetStatus().
 */

typedef struct reset_status_t {
	uint8_t  reserved0;       /*!< reserved */
	uint8_t  finished_map;    /*!< Bitmap of triggers for which status is to be reset to zero */
	uint8_t  reserved1;       /*!< reserved */
	uint8_t  reserved2;       /*!< reserved */
} reset_status_t;



typedef struct retrigger_mode_t {
	uint32_t  same_trigger;
	uint32_t  other_trigger;
} retrigger_mode_t;




/* data format in the user <-> kernel interface */

typedef struct dev_channeldata {
	uint16_t channel[STG200x_NUM_CHANNELS];
	uint8_t  digout;
	uint8_t  syncout;
} dev_channeldata;

union device_data_record
{
	struct {
		uint8_t   geraet  [32];
		uint8_t   typ     [32];
		uint8_t   firma   [32];
		uint8_t   jahr    [8];
		
		uint8_t   ser_no  [32];
		uint8_t   hw_stand[32];
		uint8_t   sw_stand[32];

		uint8_t   gap1    [8];
		uint8_t   gap2    [16];

		uint8_t   baud;
		
		uint8_t   echo;
		uint8_t   debug;

		uint8_t   gap3   [5];
		uint8_t   gap4   [24];

		int16_t   offset_1;
		int16_t   offset_2;
		int16_t   offset_3;
		int16_t   offset_4;
		int16_t   offset_5;
		int16_t   offset_6;
		int16_t   offset_7;
	    int16_t   offset_8;

		uint16_t  ures;
		uint16_t  ires;
		uint16_t  pres;

		uint16_t  urange;
		uint16_t  irange;
		uint32_t  prange;

		uint8_t   gap5[50];
		
		uint8_t   dig_init;
		uint8_t   trig_slope;
		uint8_t   sweep_mode;
		uint8_t   sync_mode;
		uint8_t   prgdat_valid;

		uint8_t   gap6[137];
		
		uint8_t   password[32];

		uint8_t   checksum;
		uint8_t   komplement;
	} device_data;
	unsigned char field[512];
};

union  active_map_record {
	struct {
		uint8_t  channel;
		uint8_t  syncout;
		uint16_t digout;
	} active_map;
	uint32_t all;
};

typedef struct outputMap_t {
    int32_t  channel[STG200x_NUM_CHANNELS]   ;  /*!< Capacity in bytes for each channel */
} outputMap_t;


typedef struct s_uint16 {
	uint16_t value;
} s_uint16;

typedef struct s_uint32 {
	uint32_t value;
} s_uint32;

typedef struct s_2uint32 {
	uint32_t value1;
	uint32_t value2;
} s_2uint32;

typedef struct s_3uint32 {
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;
} s_3uint32;

typedef struct s_4uint32 {
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;
	uint32_t value4;
} s_4uint32;

typedef struct s_1uint32_2uint16 {
	uint32_t value1;
	uint16_t value2;
	uint16_t value3;
} s_1uint32_2uint16;

typedef struct s_int32 {
	int32_t value;
} s_int32;

typedef struct s_2int32 {
	int32_t value1;
	int32_t value2;
} s_2int32;

typedef struct s_3int32 {
	int32_t value1;
	int32_t value2;
	int32_t value3;
} s_3int32;

typedef struct s_4int32 {
	int32_t value1;
	int32_t value2;
	int32_t value3;
	int32_t value4;
} s_4int32;

typedef struct s_samplerate {
	uint32_t rate;     /*  samplerate in Hz */
	uint32_t oversample;
} s_samplerate;

typedef struct s_setaudio {
	int32_t channel;
	int32_t amplification;
} s_setaudio;

typedef struct s_channelmap{
	uint8_t position;
	uint8_t channel;
} s_channelmap;

typedef struct s_setdacvalue {
	uint16_t channel;
	int32_t value;	// PJ: extended to 32bit, still compatible to old request, since lower 16 bit are at the same possition
} s_setdacvalue;

typedef struct s_setdacautocontrol {
	uint16_t channel;
} s_setdacautocontrol;

typedef struct s_setpidparameter {
    uint16_t channel;  ///< channel
    int16_t const_p;   ///< P for PI control
    int16_t const_i;   ///< I for PI control
    int16_t shift_p;   ///< number of bits to shift P
	int16_t shift_i;
} s_setpidparameter;

typedef struct s_rampstart {
	int16_t channelmap;
} s_rampstart;

typedef struct s_sinestart {
	int16_t channelmap;
} s_sinestart;

typedef struct s_patternliststart {
	int16_t channelmap;
} s_patternliststart;

typedef struct s_setrampparameter {
	uint16_t channel;
	int16_t ramp_start;
	int16_t ramp_min;
	int16_t ramp_max;
	int32_t ramp_slope;
	int32_t ramp_pause;
	int32_t ramp_slope2; // new for dotria, 2nd step
	uint32_t ramp_samples; // number of samples after which a ramp should stop
} s_setrampparameter;

typedef struct s_setsineparameter {
	uint16_t channel;
	int16_t amplitude;
} s_setsineparameter;

typedef struct s_setpatternlistentry {
	uint16_t channel;
	uint16_t position;
	uint32_t duration;
	int32_t  value;
} s_setpatternlistentry;

typedef struct s_setbathclamp {
	uint16_t enable;
} s_setbathclamp;

typedef struct s_resetoffset {
	uint16_t channel;
} s_resetoffset;

typedef struct s_setdacoffset {
	uint16_t channel;
	int16_t  dac_offset;
} s_setdacoffset;

typedef struct s_setadcoffset {
	uint16_t channel;
	int32_t  adc_offset;
} s_setadcoffset;

typedef struct s_setchannelswitch {
	uint16_t channel;
	uint16_t state;
} s_setchannelswitch;

typedef struct s_setfilterfeedback {
	uint8_t on;
	uint16_t digoutmask;
	uint16_t diginmask;
} s_setfilterfeedback;

typedef struct s_ClampAmpRamp
{
	int32_t  ramp_start;
	int32_t  ramp_end;
	uint32_t ramp_steps;
	uint32_t ramp_mode; // 0 = Current Clamp; 1 = Voltage Clamp
} s_ClampAmpRamp;

typedef struct s_SpikeDetectorThreshold
{
	unsigned short position;
	unsigned short sourcechannel;
	unsigned short resultchannel;
	unsigned short trigger;
	unsigned short totzeit;
	int threshold1; 
	int threshold2;
	short slope;
} s_SpikeDetectorThreshold;

typedef struct s_FilterAttributesOneSet
{
    // Filter coeficients
    uint64_t ULongA1;
    uint64_t ULongA2;
    uint64_t ULongB0;
    uint64_t ULongB1;
    uint64_t ULongB2;
    // Filter infos
    uint32_t CornerFrequency_mHz;
    uint32_t Info;
    uint32_t Order;
    uint32_t FilterBand;
    uint32_t FilterFamily;
    uint32_t FilterType;
    uint32_t FilterActive;
} s_FilterAttributesOneSet;

typedef struct s_FilterAttributesTwoSets
{
    // Filter coeficients Filter 1
    uint64_t ULongA1_1;
    uint64_t ULongA2_1;
    uint64_t ULongB0_1;
    uint64_t ULongB1_1;
    uint64_t ULongB2_1;
    // Filter coeficients Filter 2
    uint64_t ULongA1_2;
    uint64_t ULongA2_2;
    uint64_t ULongB0_2;
    uint64_t ULongB1_2;
    uint64_t ULongB2_2;
    // Filter infos
    uint32_t CornerFrequency_mHz;
    uint32_t Info;
    uint32_t Order;
    uint32_t FilterBand;
    uint32_t FilterFamily;
    uint32_t FilterType;
    uint32_t FilterActive;
} s_FilterAttributesTwoSets;



/*
typedef struct s_detectorstruct {
};
*/
#ifndef __C30
#ifndef __18CXX
#ifndef __TMS320C28XX__
#ifndef __TMS320C55XX__
#ifndef _TMS320C6X
#ifndef __C51__
#pragma pack()
#endif
#endif
#endif
#endif
#endif
#endif

#endif

/*! \endcond */
