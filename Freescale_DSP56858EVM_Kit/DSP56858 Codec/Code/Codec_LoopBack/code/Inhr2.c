/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Inhr2.C
**     Project   : Codec_LoopBack
**     Processor : 56858
**     Component : FreescaleSSI
**     Version   : Component 01.039, Driver 01.13, CPU db: 2.87.105
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2/21/2018, 6:27 PM
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

/* MODULE Inhr2. */

#include "Inhr2.h"

static bool EnUser;                    /* Enable/Disable the device */
static word InpLen;                    /* Length of input buffer's content */
static Inhr2_TComData *InpPtrR;        /* Pointer for reading from input buffer */
static Inhr2_TComData *InpPtrW;        /* Pointer for writing to input buffer */
static Inhr2_TComData InpBuffer[Inhr2_INP_BUF_SIZE]; /* Input buffer */
static word OutLen;                    /* Length of output bufer's content of the transmitter */
static Inhr2_TComData *OutPtrR;        /* Pointer for reading from output buffer of the transmitter */
static Inhr2_TComData *OutPtrW;        /* Pointer for writing to output buffer of the transmitter */
static Inhr2_TComData OutBuffer[Inhr2_OUT_BUF_SIZE]; /* Output buffer of the transmitter */
/*
** ===================================================================
**     Method      :  HWEnDi (component FreescaleSSI)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {                        /* Enable device? */
    setRegBits(ESSI_0_SCR2,(ESSI_0_SCR2_ESSIEN_MASK | ESSI_0_SCR2_RIE_MASK | ESSI_0_SCR2_TIE_MASK | ESSI_0_SCR2_RE_MASK | ESSI_0_SCR2_TE0_MASK )); /* Enable device */
  }
  else {
    clrRegBits(ESSI_0_SCR2,(ESSI_0_SCR2_ESSIEN_MASK | ESSI_0_SCR2_RIE_MASK | ESSI_0_SCR2_TIE_MASK | ESSI_0_SCR2_RE_MASK | ESSI_0_SCR2_TE0_MASK )); /* Disable device */
  }
}

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
byte Inhr2_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

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
byte Inhr2_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

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
byte Inhr2_RecvBlock(Inhr2_TComData *Ptr,word Size,word *Rcv)
{
  register word count;                 /* Reveived data counter */
  
  for (count = 0; count < Size; count++) {
    if (InpLen > 0) {                  /* Is number of received chars greater than 0? */
      EnterCritical();                 /* Disable global interrupts */
      InpLen--;                        /* Decrease number of received chars */
      *(Ptr++) = *(InpPtrR++);         /* Read the char */
      /*lint -save -e946 Disable MISRA rule (103) checking. */
      if (InpPtrR >= InpBuffer + Inhr2_INP_BUF_SIZE) { /* Is the pointer out of the receive buffer? */
        InpPtrR = InpBuffer;           /* Set pointer to the first item into the receive buffer */
      }
      /*lint -restore */
      ExitCritical();                  /* Enable global interrupts */
    }
    else {
      *Rcv = count;                    /* Return number of received chars */
      return ERR_RXEMPTY;              /* Return error code */
    }
  }
  *Rcv = count;                        /* Return number of received chars */
  return ERR_OK;                       /* OK */
}

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
byte Inhr2_SendBlock(Inhr2_TComData *Ptr,word Size,word *Snd)
{
  register word count;                 /* Sent data counter */

  for (count = 0; count < Size; count++) {
    EnterCritical();                   /* Disable global interrupts */
    if (OutLen == Inhr2_OUT_BUF_SIZE) { /* Is number of chars in buffer the same as the size of transmit buffer? */
      ExitCritical();                  /* Enable global interrupts */
      *Snd = count;                    /* Return number of sended chars */
      return ERR_TXFULL;               /* Return error code */
    }
    OutLen++;                          /* Increase number of bytes in the transmit buffer */
    *(OutPtrW++) = *Ptr++;             /* Store char to buffer */
    /*lint -save -e946 Disable MISRA rule (103) checking. */
    if (OutPtrW >= OutBuffer + Inhr2_OUT_BUF_SIZE) { /* Is the pointer out of the transmit buffer? */
      OutPtrW = OutBuffer;             /* Set pointer to the first item in the transmit buffer */
    }
    /*lint -restore */
    ExitCritical();                    /* Enable global interrupts */
  }
  *Snd = count;                        /* Return number of sended chars */
  return ERR_OK;                       /* OK */
}

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
#pragma interrupt alignsp 
void Inhr2_InterruptRx(void)
{
  register word count;

  for (count = (word)getRegBitGroup(ESSI_0_SFCSR,RFCNT); count != 0; count--) {
    if (InpLen < Inhr2_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer lower than size of buffer? */
      InpLen++;                        /* Increse number of chars in the receive buffer */
      *(InpPtrW)++ = (Inhr2_TComData)getReg(ESSI_0_SRX); /* Save received char to the receive buffer */
      /*lint -save -e946 Disable MISRA rule (103) checking. */
      if (InpPtrW >= InpBuffer + Inhr2_INP_BUF_SIZE) { /* Is the pointer out of the receive buffer? */
        InpPtrW = InpBuffer;           /* Set pointer on the first item into the receive buffer */
      }
      /*lint -restore */
    }
    else {
      for (; count > 7; count--) {
        getReg(ESSI_0_SRX);            /* Dummy read the input data register */
      }
      break;                           /* Break reception and return */
    }
  }
}

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
#pragma interrupt alignsp 
void Inhr2_InterruptRxWE(void)
{
  register word count;

  getReg(ESSI_0_SSR);                  /* Dummy read status register for overrun flag clearing */
  for (count = (word)getRegBitGroup(ESSI_0_SFCSR,RFCNT); count != 0; count--) {
    if (InpLen < Inhr2_INP_BUF_SIZE) { /* Is number of bytes in the receive buffer lower than size of buffer? */
      InpLen++;                        /* Increse number of chars in the receive buffer */
      *(InpPtrW)++ = (Inhr2_TComData)getReg(ESSI_0_SRX); /* Save received char to the receive buffer */
      /*lint -save -e946 Disable MISRA rule (103) checking. */
      if (InpPtrW >= InpBuffer + Inhr2_INP_BUF_SIZE) { /* Is the pointer out of the receive buffer? */
        InpPtrW = InpBuffer;           /* Set pointer on the first item into the receive buffer */
      }
      /*lint -restore */
    }
    else {
      for (; count > 7; count--) {
        getReg(ESSI_0_SRX);            /* Dummy read the input data register */
      }
      break;                           /* Break reception and return */
    }
  }
}

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
#pragma interrupt alignsp 
void Inhr2_InterruptTx(void)
{
  register word count;

  for (count = (8 - getRegBitGroup(ESSI_0_SFCSR,TFCNT)); count != 0; count--) {
    if (OutLen) {                      /* Is number of bytes in the transmit buffer greather then 0? */
      OutLen--;                        /* Decrease number of chars in the transmit buffer */
      setReg(ESSI_0_STX0,*(OutPtrR++)); /* Store char to transmitter register */
      /*lint -save -e946 Disable MISRA rule (103) checking. */
      if (OutPtrR >= OutBuffer + Inhr2_OUT_BUF_SIZE) { /* Is the pointer out of the transmit buffer? */
        OutPtrR = OutBuffer;           /* Set pointer on the first item into the transmit buffer */
      }
      /*lint -restore */
    }   
    else {
      for (; count > 0; count--) {     /* Fill up Tx FIFO */
        setReg(ESSI_0_STX0,Inhr2_EOF); /* Store the empty char to the transmit data register */
      }
      break;
    }
  }
}

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
#pragma interrupt alignsp 
void Inhr2_InterruptTxWE(void)
{
  register word count;

  getReg(ESSI_0_SSR);                  /* Dummy read status register for underrun flag clearing */
  for (count = (8 - getRegBitGroup(ESSI_0_SFCSR,TFCNT)); count != 0; count--) {
    if (OutLen) {                      /* Is number of bytes in the transmit buffer greather then 0? */
      OutLen--;                        /* Decrease number of chars in the transmit buffer */
      setReg(ESSI_0_STX0,*(OutPtrR++)); /* Store char to transmitter register */
      /*lint -save -e946 Disable MISRA rule (103) checking. */
      if (OutPtrR >= OutBuffer + Inhr2_OUT_BUF_SIZE) { /* Is the pointer out of the transmit buffer? */
        OutPtrR = OutBuffer;           /* Set pointer on the first item into the transmit buffer */
      }
      /*lint -restore */
    }   
    else {
      for (; count > 0; count--) {     /* Fill up Tx FIFO */
        setReg(ESSI_0_STX0,Inhr2_EOF); /* Store the empty char to the transmit data register */
      }
      break;
    }
  }
}

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
void Inhr2_Init(void)
{
  /* ESSI_0_SCR2: RIE=0,TIE=0,RE=0,TE0=0,TE1=0,TE2=0,??=0,??=0,SYN=1,TSHFD=0,TSCKP=0,ESSIEN=0,NET=1,TFSI=0,TFSL=1,TEFS=1 */
  setReg16(ESSI_0_SCR2, 139U);          
  /* ESSI_0_STXCR: PSR=0,WL=3,DC=1,PM=0 */
  setReg16(ESSI_0_STXCR, 24832U);       
  /* ESSI_0_SCR3: DIV4DIS=1,RSHFD=0,RSCKP=0,RDMAE=0,TDMAE=0,RFSI=0,RFSL=1,REFS=1,RFEN=1,TFEN=1,INIT=1,??=0,??=0,SYNRST=0,RLIE=0,TLIE=0 */
  setReg16(ESSI_0_SCR3, 33760U);        
  /* ESSI_0_SCR4: ??=0,??=0,??=0,??=0,??=0,TXSF0=1,TXSF1=0,TXSF2=0,??=0,SSC1=0,SCKD=0,SCD2=0,SCD1=0,SCD0=0,OF1=0,OF0=0 */
  setReg16(ESSI_0_SCR4, 1024U);         
  /* ESSI_0_SFCSR: RFCNT=0,TFCNT=0,RFWM=8,TFWM=1 */
  setReg16(ESSI_0_SFCSR, 129U);         
  /* ESSI_0_TSMA: TSMA=65535 */
  setReg16(ESSI_0_TSMA, 65535U);        
  /* ESSI_0_TSMB: TSMB=65535 */
  setReg16(ESSI_0_TSMB, 65535U);        
  /* ESSI_0_RSMA: RSMA=65535 */
  setReg16(ESSI_0_RSMA, 65535U);        
  /* ESSI_0_RSMB: RSMB=65535 */
  setReg16(ESSI_0_RSMB, 65535U);        
  EnUser = TRUE;                       /* Enable device */
  InpLen = 0;                          /* No char in the receive buffer */
  InpPtrW = InpPtrR = InpBuffer;       /* Set pointer on the first item in the receive buffer */
  OutLen = 0;                          /* No char in the transmit buffer of the transmitter */
  OutPtrW = OutPtrR = OutBuffer;       /* Set pointer on the first item in the transmit buffer of the transmitter */
  clrRegBit(ESSI_0_SCR3,INIT);         /* The state machine is allowed to operate */
  HWEnDi();                            /* Enable/disable device according to the status flags */
}

/* END Inhr2. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
