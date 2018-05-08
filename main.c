#include "stm32f30x.h"
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_spi.h>
#include <stdio.h>
#include <string.h>




int16_t x,y,z;

uint8_t SPI_SendData(uint8_t data);
uint8_t x_l = 0;
uint8_t x_h = 0;
uint8_t y_l = 0;
uint8_t y_h = 0;
uint8_t z_l = 0;
uint8_t z_h = 0;
uint8_t who = 0;
uint8_t status = 0;
uint8_t temp = 0;


int main(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  SPI_InitTypeDef SPI_InitStructure;
	  SystemInit();

	  // RCC settings
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE );
	  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOE, ENABLE ); //Enabling PE
	  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE ); //Enabling PA

	  // PA5, PA6 and PA7 are SPI pins
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_5);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_5);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_5);

	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  // Chip Select pin
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  // Configure and enable the SPI peripheral
	  SPI_I2S_DeInit(SPI1);
	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //SSM
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // MSTR
	  SPI_Init(SPI1, &SPI_InitStructure);

	  SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);// SSI

	  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);

	  SPI_DataSizeConfig(SPI1, SPI_DataSize_8b);

	  SPI_Cmd(SPI1, ENABLE);

  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
  SPI_SendData(0x8F);//Write on registry CTRL_REG1
  who = SPI_SendData(0x00);//Activate normal mode, Xen,Yen,Zen
  GPIO_SetBits(GPIOE,GPIO_Pin_3);
  printf("the receive data is %d\n",  who);
  printf("the receive data in hex  is %x\n",  who);

  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
  SPI_SendData(0x20);//Write on registry CTRL_REG1
  SPI_SendData(0x0F);//Activate normal mode, Xen,Yen,Zen
  GPIO_SetBits(GPIOE,GPIO_Pin_3);

  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
  SPI_SendData(0x23); //Write on CTRL_REG2
  SPI_SendData(0x30); //2000 DPS
  GPIO_SetBits(GPIOE,GPIO_Pin_3);

  while(1)
  {
	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xA8);
	  x_l = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xA9);
	  x_h = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xAA);
	  y_l = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xAB);
	  y_h = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xAC);
	  z_l = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	  SPI_SendData(0xAD);
	  z_h = SPI_SendData(0x00);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3);

	  x= (((int16_t)((uint16_t)(x_h*256) + x_l)));
	  y= (((int16_t)((uint16_t)(y_h*256) + y_l)));
	  z= (((int16_t)((uint16_t)(z_h*256) + z_l)));

	  printf("The distance in X direction is  %d \r \n",  x);
	  printf("The distance in Y direction is  %d\r \n",  y);
	  printf("The distance in Z direction is  %d\r \n",  z);
	  printf("\r\n");
	  printf("\r\n");
	  printf("\r\n");
	  for(int i=0;i<500;i++);

  }

  return 1;
}

uint8_t SPI_SendData(uint8_t data)
{
  uint32_t spixbase = 0x00;
  spixbase = (uint32_t)SPI1;
  spixbase += 0x0C;
  while((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE){}
  *(__IO uint8_t *)spixbase = data;
  while((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE){}
  return *(__IO uint8_t *)spixbase;
}
