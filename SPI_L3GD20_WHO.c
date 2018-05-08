/*
#include "stm32f30x.h"
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_spi.h>
#include <stdio.h>
#include <string.h>



uint8_t SPI_SendData(uint8_t dati);
uint8_t ricevuto;

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

  SPI_SendData(0x8F);
  ricevuto = SPI_SendData(0x00);
  printf("The value of WHO_AM_I register in Decimal is   %d\r\n",  ricevuto);
  printf("The value of WHO_AM_I register in Hex  is   %X\r\n",  ricevuto);

  return 1;

}

uint8_t SPI_SendData(uint8_t dati)
{
  uint32_t spixbase= 0x00;
  spixbase =(uint32_t)SPI1;
  spixbase += 0x0C;
  while((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE){}  // Waiting for transmission buffer to be empty
  *(__IO uint8_t *)spixbase = dati;
  while((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE){} // Waiting for the buffer in reception to be empty.
  return *(__IO uint8_t *)spixbase;
}

*/

