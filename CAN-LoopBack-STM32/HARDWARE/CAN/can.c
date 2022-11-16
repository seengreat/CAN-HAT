/***************************************************************************************
 * Project  :CAN-LoopBack-STM32
 * Describe :Only a CAN HAT is required to automatically self-collect in loopback mode
 * Experimental Platform :STM32F103C8T6 + CAN HAT
 * Hardware Connection :STM32F103 -> CAN HAT
 *			3V3	 ->	3V3					PA11 -> CANRX
 *			GND	 ->	GND					PA12 -> CANTX
 * Library Version :ST_V3.5
 * Author		   :Christian
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include "can.h"
#include "delay.h"
#include "usart.h"

void CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);		
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	CAN_InitStructure.CAN_TTCM=DISABLE;						
	CAN_InitStructure.CAN_ABOM=DISABLE;						
  	CAN_InitStructure.CAN_AWUM=DISABLE;						
  	CAN_InitStructure.CAN_NART=ENABLE;						
  	CAN_InitStructure.CAN_RFLM=DISABLE;						
  	CAN_InitStructure.CAN_TXFP=DISABLE;						
  	CAN_InitStructure.CAN_Mode= mode;	         			
  	
  	CAN_InitStructure.CAN_SJW=tsjw;							
  	CAN_InitStructure.CAN_BS1=tbs1; 						
  	CAN_InitStructure.CAN_BS2=tbs2;							
  	CAN_InitStructure.CAN_Prescaler=brp;            		
  	CAN_Init(CAN1, &CAN_InitStructure);            			

	CAN_FilterInitStructure.CAN_FilterNumber=0;	  			
   	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;		
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;	
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;	

  	CAN_FilterInit(&CAN_FilterInitStructure);				
}

u8 Can_Send_Msg(u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x12;				 
	TxMessage.ExtId=0x12;				
	TxMessage.IDE=CAN_Id_Standard;		
	TxMessage.RTR=CAN_RTR_Data;		 	
	TxMessage.DLC=len;					
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox=CAN_Transmit(CAN1, &TxMessage);   
	i=0;
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	
	if(i>=0XFFF)return 0;
	return 1;		
}

u8 Can_Receive_Msg(u8 *buf)
{		   		   
	u32 i;
	CanRxMsg RxMessage;
	if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	for(i=0;i<8;i++)
	buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}

