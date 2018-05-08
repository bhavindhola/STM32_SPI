/*
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
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  GPIOE->MODER |= 0x00000040; //PE3 in general purpose
  GPIOA->MODER |= 0x0000A800; //PA5 PA6 PA7 in alternate function.
  GPIOA->OSPEEDR |= 0x00005400; //SPEED FOR GPIOA to 10 MHz - medium speed.
  GPIOA->AFR[0] |= 0x55500000; //We select alternate function 5 which is the SPI (Check the datasheet).
  GPIOE->BSRR |= (1<<3); //Brining PE3 to 1 to select the CS of the SPI. We want to bring it to 1 so that we can go though the configuration phase.

  //Configuration phase.

  SPI1->I2SCFGR &= 0xF7FF;
  SPI1->CR1 |= SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_MSTR; //Selecting software driven and master mode.
  SPI1->CR1 |= SPI_CR1_BR_1; //Bode rate equal to 72MHz / 8 . We do this because the gyroscope can't go faster than 10MHz.
  SPI1->CR2 |= SPI_CR2_FRXTH; //RXNE event is generated ifthe FIFO level is greater than or equal to 1/4 (8-bit)
  SPI1->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0; //Configuration to 8-bit  0111.
  SPI1->CR1 |= SPI_CR1_SPE;

  GPIOE->BSRR |= (1 << 19);
  SPI_SendData(0x8F);//Write on registry CTRL_REG1
  who = SPI_SendData(0x00);//Activate normal mode, Xen,Yen,Zen
  GPIOE->BSRR |= 1<<3;
  printf("the receive data is %d\n",  who);
  printf("the receive data in hex  is %x\n",  who);

  GPIOE->BSRR |= (1 << 19);
  SPI_SendData(0x20);//Write on registry CTRL_REG1
  SPI_SendData(0x0F);//Activate normal mode, Xen,Yen,Zen
  GPIOE->BSRR |= 1<<3;

  GPIOE->BSRR |= 1<<19;
  SPI_SendData(0x23); //Write on CTRL_REG2
  SPI_SendData(0x30); //2000 DPS
  GPIOE->BSRR |= 1<<3;

  while(1)
  {
	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xA8);
	  x_l = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xA9);
	  x_h = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xAA);
	  y_l = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xAB);
	  y_h = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xAC);
	  z_l = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

	  GPIOE->BSRR |= 1<<19;
	  SPI_SendData(0xAD);
	  z_h = SPI_SendData(0x00);
	  GPIOE->BSRR |= 1<<3;

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
*/
