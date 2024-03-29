/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Inhr2.H
**     Project   : Echo
**     Processor : 56858
**     Component : FreescaleSSI
**     Version   : Component 01.039, Driver 01.13, CPU db: 2.87.105
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/21/2018, 6:47 PM
**     Abstract  :
**         This bean implements encapsulation of CPU internal 
**         Synchronous Serial Interface peripheral functionality. 
**          It is allowed to communicate with a variety of serial 
**          devices, including industry-standard codecs, other CPUs, etc 
**          by this bean.
**     Settings  :
**
**         Serial channel              : ESSI0
**
**         Mode                        : Synchronous
**         Network mode                : Enabled
**
**         Receiver                    :
**             Width                   : 16 bits
**             Capture clock edge      : falling
**             MSB first               : yes
**             Frame rate              : 2
**             Rx FIFO                 : Enabled
**                 Size                : 8
**                 Threshold           : 8
**             Receive clock signal    :
**                 Direction           : Input
**
**         Transmitter                 :
**             Width                   : 16 bits
**             Capture clock edge      : rising
**             MSB first               : yes
**             Frame rate              : 2
**             Tx FIFO                 : Enabled
**                 Size                : 8
**                 Threshold           : 8
**             Transmit clock signal   :
**                 Direction           : Input
**             Frame sync signal       :
**                 Direction           : Input
**                 Active state        : High
**                 Frame sync length   : a one-bit
**                 Frame sync initiated : one bit before the data
**
**         Receiver and Transmitter    :
**             High speed mode
**                 DIV4DIS             : divide-by-1
**
**         Initialization              :
**             Communication           : Enabled
**             Event                   : Enabled
**
**         Registers                   :
**             Input buffer            : ESSI_0_SRX [2096675]
**             Output buffer           : ESSI_0_STX0 [2096672]
**             Control register        : ESSI_0_SSR [2096676]
**             Control register        : ESSI_0_SCR2 [2096677]
**             Control register        : ESSI_0_SCR3 [2096678]
**             Control register        : ESSI_0_SCR4 [2096679]
**             Status register         : ESSI_0_SSR [2096676]
**             Rx Control register     : ESSI_0_SRXCR [2096681]
**             Tx Control register     : ESSI_0_STXCR [2096680]
**             FIFO Control/Status register : ESSI_0_SFCSR [2096683]
**             Rx slot mask A register : ESSI_0_RSMA [2096686]
**             Rx slot mask B register : ESSI_0_RSMB [2096687]
**             Tx slot mask A register : ESSI_0_TSMA [2096684]
**             Tx slot mask B register : ESSI_0_TSMB [2096685]
**
**         Receive interrupt           :
**             Vector name             : INT_ESSI0_Rx
**             Priority                : 1
**         Overrun receive interrupt   :
**             Vector name             : INT_ESSI0_RxWE
**             Priority                : 1
**         Receive last slot interrupt :
**             Vector name             : INT_ESSI0_RxLS
**             Priority                : 1
**         Transmit interrupt          :
**             Vector name             : INT_ESSI0_Tx
**             Priority                : 1
**         Underrun transmit interrupt :
**             Vector name             : INT_ESSI0_TxWE
**             Priority                : 1
**         Transmit last slot interrupt :
**             Vector name             : INT_ESSI0_TxLS
**             Priority                : 1
**
**         Used pins                   :
**         ------------------------------------------------------
**             Function    | Number (on package) |    Name
**         ------------------------------------------------------
**            Receive data |         132         | GPIOC1_SRD0
**           Transmit data |         131         | GPIOC0_STD0
**          Transmit clock |         133         | GPIOC2_SCK0
**               Control 2 |         136         | GPIOC5_SC02
**         ------------------------------------------------------
**
**     Contents  :
**         Enable    - byte Inhr2_Enable(void);
**         Disable   - byte Inhr2_Disable(void);
**         RecvBlock - byte Inhr2_RecvBlock(Inhr2_TComData *Ptr, word Size, word *Rcv);
**         SendBlock - byte Inhr2_SendBlock(Inhr2_TComData *Ptr, word Size, word *Snd);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Inhr2
#define __Inhr2

/* MODULE Inhr2. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "Cpu.h"


#ifndef __BWUserType_Inhr2_TStatus
#define __BWUserType_Inhr2_TStatus
  typedef union {
    word status;
    struct {
      bool TxBufEmpty  : 1;            /* Transmit buffer (Tx FIFO) empty */
      bool RxBufFull   : 1;            /* Rx buffer (Rx FIFO) full */
      bool RxFrameSync : 1;            /* Receive frame sync */
      bool TxFrameSync : 1;            /* Transmit frame sync */
      bool             : 1;
      bool             : 1;
      bool TxEmpty     : 1;            /* Transmit data register empty */
      bool RxReady     : 1;            /* Receive data ready */
      bool             : 1;
      bool             : 1;
      bool RxLastSlot  : 1;            /* Receive last slot */
      bool TxLastSlot  : 1;            /* Transmit last slot */
      bool TxBufFull   : 1;            /* Transmit buffer (Tx FIFO) full */
    } statusName;
  } Inhr2_TStatus;                     /* Status flags. For languages which don't support bit access is byte or word (depend on CPU) access only to status flags possible. */
#endif

#ifndef __BWUserType_Inhr2_TError
#define __BWUserType_Inhr2_TError
  typedef union {
    word err;
    struct {
      bool             : 1;
      bool             : 1;
      bool             : 1;
      bool             : 1;
      bool UnderRun    : 1;            /* Transmit underrun error */
      bool OverRun     : 1;            /* Receive overrun error */
      bool TxBufUndf   : 1;            /* Output SW buffer overrun error (only if output buffer is enabled) */
      bool RxBufOvf    : 1;            /* Input SW buffer overrun error (only if input buffer is enabled) */
      bool TxFIFO1     : 1;            /* The state of FIFO 1 is not same as FIFO 0 */
      bool TxFIFO2     : 1;            /* The state of FIFO 2 is not same as FIFO 0 or if FIFO 0 is desabled, as FIFO 1 */
    } errName;
  } Inhr2_TError;                      /* Error flags. For languages which don't support bit access is byte or word (it depends on CPU) access only to error flags possible. */
#endif

#ifndef __BWUserType_Inhr2_TComData
#define __BWUserType_Inhr2_TComData
  typedef word Inhr2_TComData;         /* User type for communication. Size of this type depends on the communication data witdh. */
#endif

#ifndef __BWUserType_Inhr2_TDataBlocks
#define __BWUserType_Inhr2_TDataBlocks
  typedef struct {                     /* Pointers to data blocks for all transmitters. */
    Inhr2_TComData* Block0;            /* Pointer to data block to send via transmitter 0. This pointer is ignored if the transmitter 0 is disabled (Transmit data pin is disabled). */
    Inhr2_TComData* Block1;            /* Pointer to data block to send via transmitter 1. This pointer is ignored if the transmitter 1 is disabled (Control pin 0 isn't used for transmit data signal 1). */
    Inhr2_TComData* Block2;            /* Pointer to data block to send via transmitter 2. This pointer is ignored if the transmitter 2 is disabled (Control pin 1 isn't used for transmit data signal 2). */
  } Inhr2_TDataBlocks;
#endif

#define Inhr2_EOF 0                    /* Empty character */


#define Inhr2_INP_BUF_SIZE 32          /* Input buffer size */
#define Inhr2_OUT_BUF_SIZE 32          /* Output buffer size */

byte Inhr2_Enable(void);
/*
** ===================================================================
**     Method      :  Inhr2_Enable (component FreescaleSSI)
**
**     Description :
**         Enable the bean - it starts sending and receiving. Events
**         may be generated ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device does not work in
**                           the active speed mode
** ===================================================================
*/

byte Inhr2_Disable(void);
/*
** ===================================================================
**     Method      :  Inhr2_Disable (component FreescaleSSI)
**
**     Description :
**         Disable the bean - it stops the sending and receiving. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device does not work in
**                           the active speed mode
** ===================================================================
*/

byte Inhr2_RecvBlock(Inhr2_TComData *Ptr,word Size,word *Rcv);
/*
** ===================================================================
**     Method      :  Inhr2_RecvBlock (component FreescaleSSI)
**
**     Description :
**         If any data received, this method returns the block of
**         the data and its length (and incidental error), otherwise
**         it returns error code (it does not wait for data). This
**         method is available only if the receiver is enabled.
**         DMA mode:
**         If DMA controller is available on selected CPU and
**         receiver is configured to use DMA controller then this
**         method only sets selected DMA channel. Status of the DMA
**         transfer can be then checked using method GetCharsInRxBuf.
**         See typical usage for details about communication using
**         DMA.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of received data.
**                           The data is justified to left.
**         Size            - Size of the block
**       * Rcv             - Pointer to real number of the received
**                           data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - It was not possible to
**                           read requested number of bytes from
**                           buffer
** ===================================================================
*/

byte Inhr2_SendBlock(Inhr2_TComData *Ptr,word Size,word *Snd);
/*
** ===================================================================
**     Method      :  Inhr2_SendBlock (component FreescaleSSI)
**
**     Description :
**         Send a block of characters to the channel. This method is
**         available only if one transmitter is enabled. It is
**         determined by properties Transmitter(s), Transmit data
**         pin, Control pin 0 use for and Control pin 1 use for.
**         DMA mode:
**         If DMA controller is available on selected CPU and
**         transmitter is configured to use DMA controller then this
**         method only sets selected DMA channel. Status of the DMA
**         transfer can be then checked using method GetCharsInTxBuf.
**         See typical usage for details about communication using
**         DMA.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send.
**                           The data is justified to left.
**         Size            - Size of the block
**       * Snd             - Pointer to number of data that are sent
**                           (moved to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device does not work in
**                           the active speed mode
**                           ERR_DISABLED - The device is disabled
**                           (only if interrupt service is disabled
**                           or if output buffer is set to 0 or if
**                           transmit DMA is available and enabled)
**                           ERR_TXFULL - It was not possible to send
**                           requested number of bytes
** ===================================================================
*/

void Inhr2_InterruptRx(void);
/*
** ===================================================================
**     Method      :  Inhr2_InterruptRx (component FreescaleSSI)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void Inhr2_InterruptRxWE(void);
/*
** ===================================================================
**     Method      :  Inhr2_InterruptRxWE (component FreescaleSSI)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void Inhr2_InterruptTx(void);
/*
** ===================================================================
**     Method      :  Inhr2_InterruptTx (component FreescaleSSI)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void Inhr2_InterruptTxWE(void);
/*
** ===================================================================
**     Method      :  Inhr2_InterruptTxWE (component FreescaleSSI)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void Inhr2_Init(void);
/*
** ===================================================================
**     Method      :  Inhr2_Init (component FreescaleSSI)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END Inhr2. */

#endif /* ifndef __Inhr2 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
