/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Codec.H
**     Project   : Codec_LoopBack
**     Processor : 56858
**     Component : Audio_Codec_CS4218
**     Version   : Component 01.041, Driver 01.04, CPU db: 2.87.105
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/21/2018, 6:27 PM
**     Abstract  :
**         This bean implements an 16-Bit Stereo Audio Codec CS4218.
**         The CS4218 is a monolithic CMOS device for for computer
**         multimedia, automotive, and portable audio applications.
**         It performs A/D and D/A conversion, filtering, and level
**         setting, creating 4 audio inputs and 2 audio outputs for
**         a digital computer system. The digital interfaces of left
**         and right channels are multiplexed into a single serial
**         data bus with word rates up to 50 kHz per channel.
**     Settings  :
**         Type of Audio Codec        : CS4218
**         Selected device            : CODEC 0
**         Serial Intefrace Mode      : Serial mode 4
**         HW Interface
**           SSI                      : FreescaleSSI   (ESSI0)
**           RST                      : BitIO_Out      (GPIOC4_SC01)
**           CCLK                     : BitIO_Out      (GPIOE3_TXD1)
**           CCS                      : BitIO_Out      (GPIOC3_SC00)
**           CDIN                     : BitIO_Out      (GPIOE2_RXD1)
**         Fifo size                  : 32
**         Mode                       : STEREO
**         Mute                       : Disabled
**         Left Attenuation           : 0.0    [dB]
**         Right Attenuation          : 0.0    [dB]
**         Left Gain                  : 10.5   [dB]
**         Right Gain                 : 10.5   [dB]
**         Enabled in init. code      : yes
**         Events enabled in init.    : no
**     Contents  :
**         Enable  - byte Codec_Enable(void);
**         Disable - byte Codec_Disable(void);
**         Read    - byte Codec_Read(const void* pBuffer, word nBytes, word *Rcv);
**         Write   - byte Codec_Write(const void* pBuffer, word nBytes, word *Snd);
**
**     (c) Freescale Semiconductor
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Codec
#define __Codec

/* MODULE Codec. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "Inhr5.h"
#include "Inhr6.h"

#include "Cpu.h"


#ifndef __BWUserType_codec_sCfgCS4218
#define __BWUserType_codec_sCfgCS4218
  typedef struct
  {
    UWord16 RxConfig;
    UWord16 TxConfig;
  } codec_sCfgCS4215;                  /* Private data structures for the driver. */
#endif

/* THE FOLLOWING LABELS ARE USED TO CONFIGURE THE CS4218 CODEC. */
#define CODEC_MONO                     1
#define CODEC_STEREO                   2

#define CODEC_INTERRUPT_MASKED         0x0000
#define CODEC_INTERRUPT_UNMASKED       0x0800

#define CODEC_DIGITAL_OUTPUT_1_LOW     0x0000
#define CODEC_DIGITAL_OUTPUT_1_HIGH    0x0400

#define CODEC_MUTE_DISABLED            0x0000
#define CODEC_MUTE_ENABLED             0x0400

#define CODEC_LEFT_INPUT_LINE_1        0x0000
#define CODEC_LEFT_INPUT_LINE_2        0x0200

#define CODEC_RIGHT_INPUT_LINE_1       0x0000
#define CODEC_RIGHT_INPUT_LINE_2       0x0100

#define CODEC_RX_GAIN_FROM_PERCENT(x)  ((int)(((x) * 15) / 100))
#define CODEC_TX_GAIN_FROM_PERCENT(x)  ((int)(((100 - (x)) * 31) / 100))

/* CONTAINS THE DEFAULT SETTINGS FOR THE CS4218 CODEC. */
#define CODEC_MODE                     CODEC_STEREO
#define CODEC_FIFO_SIZE                32
#define CODEC_RX_FIFO_SIZE             CODEC_FIFO_SIZE
#define CODEC_TX_FIFO_SIZE             CODEC_FIFO_SIZE
#define CODEC_MASK                     CODEC_INTERRUPT_MASKED
#define CODEC_DO1                      CODEC_DIGITAL_OUTPUT_1_LOW
#define CODEC_MUTE                     CODEC_MUTE_DISABLED
#define CODEC_ISL                      CODEC_LEFT_INPUT_LINE_1
#define CODEC_ISR                      CODEC_RIGHT_INPUT_LINE_1
#define CODEC_LEFT_D2A_ATTENUATION     0 /* 0 to 31 */
#define CODEC_RIGHT_D2A_ATTENUATION    0 /* 0 to 31 */
#define CODEC_LEFT_A2D_GAIN            7 /* 0 to 15 */
#define CODEC_RIGHT_A2D_GAIN           7 /* 0 to 15 */

#define CODEC_RX_CONTROL_WORD          (CODEC_MUTE | CODEC_ISL | CODEC_ISR | (CODEC_LEFT_A2D_GAIN << 4) | CODEC_RIGHT_A2D_GAIN)
#define CODEC_TX_CONTROL_WORD          (CODEC_MASK | CODEC_DO1 | (CODEC_LEFT_D2A_ATTENUATION << 5) | CODEC_RIGHT_D2A_ATTENUATION)


byte Codec_Enable(void);
/*
** ===================================================================
**     Method      :  Codec_Enable (component Audio_Codec_CS4218)
**
**     Description :
**         Enable the bean - (Enable the Freescale SSI interface).
**     Parameters  : None
**     Returns     :
**         ---             - This method returns error codes from
**                           Enable method of inherited FreescaleSSI
**                           bean.
** ===================================================================
*/

byte Codec_Disable(void);
/*
** ===================================================================
**     Method      :  Codec_Disable (component Audio_Codec_CS4218)
**
**     Description :
**         Disable the bean - (Disable the Freescale SSI interface).
**     Parameters  : None
**     Returns     :
**         ---             - This method returns error codes from
**                           Disable method of inherited FreescaleSSI
**                           bean.
** ===================================================================
*/

byte Codec_Read(const void* pBuffer,word nBytes,word *Rcv);
/*
** ===================================================================
**     Method      :  Codec_Read (component Audio_Codec_CS4218)
**
**     Description :
**         This method reads data from the SSI interface.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pBuffer         - Pointer to the block of
**                           received data
**         nBytes          - Size of the block in bytes
**       * Rcv             - Pointer to real number of the received
**                           data
**     Returns     :
**         ---             - This method returns error codes from
**                           ReciveBlock method of inherited
**                           FreescaleSSI bean.
** ===================================================================
*/

byte Codec_Write(const void* pBuffer,word nBytes,word *Snd);
/*
** ===================================================================
**     Method      :  Codec_Write (component Audio_Codec_CS4218)
**
**     Description :
**         Send a block of characters to the SSI interface.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pBuffer         - Pointer to the block of data to
**                           write
**         nBytes          - Size of the block in bytes
**       * Snd             - Pointer to number of data that are
**                           writen (moved to buffer)
**     Returns     :
**         ---             - This method returns error codes from
**                           SendBlock method of inherited
**                           FreescaleSSI bean.
** ===================================================================
*/

void Codec_codecInit(void);
/*
** ===================================================================
**     Method      :  Codec_codecInit (component Audio_Codec_CS4218)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END Codec. */

#endif /* ifndef __Codec */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
