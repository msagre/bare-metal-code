//																			  //
// Author(s):																  //
//	 Miguel Angel Sagreras													  //
//																			  //
// Copyright (C) 2021														  //
//	  Miguel Angel Sagreras													  //
//																			  //
// This source file may be used and distributed without restriction provided  //
// that this copyright statement is not removed from the file and that any	  //
// derivative work contains  the original copyright notice and the associated //
// disclaimer.																  //
//																			  //
// This source file is free software; you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by the   //
// Free Software Foundation, either version 3 of the License, or (at your	  //
// option) any later version.												  //
//																			  //
// This source is distributed in the hope that it will be useful, but WITHOUT //
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or	  //
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for   //
// more details at http://www.gnu.org/licenses/.							  //
//																			  //

#ifdef GCC
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#endif

#define SRAM_SIZE ((uint32_t) 0x00005000)
#define SRAM_BASE ((uint32_t) 0x20000000)
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))

#ifndef _STDINT_H
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#endif

typedef void(*interrupt_t)(void);

typedef union {
	uint8_t  byte[4];
	uint16_t hword[2];
	uint32_t word;
} word_t;

typedef word_t page[0x400/sizeof(uint32_t)];

// Memory map

enum {TIM2	= 0, TIM3  = 1, TIM4  = 2 };
enum {GPIOA = 0, GPIOB = 1, GPIOC = 2, GPIOD = 3, GPIOE = 4, GPIOF = 5 };
enum {DMA1	= 0 };
enum {CHN1	= 0, CHN2  = 1, CHN3  = 2, CHN4  = 3, CHN5	= 4, CHN6  = 5, CHN7 = 6, CHN8 = 7 };
enum {ADC1	= 0 };
struct DEVMAP_t {
	union {
		struct {
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMCR;
			uint32_t DIER;
			uint32_t SR;
			uint32_t EGR;
			uint32_t CCMR1;
			uint32_t CCMR2;
			uint32_t CCER;
			uint32_t CNT;
			uint32_t PSC;
			uint32_t ARR;
			uint32_t RES1;
			uint32_t CCR1;
			uint32_t CCR2;
			uint32_t CCR3;
			uint32_t CCR4;
			uint32_t BDTR;
			uint32_t DCR;
			uint32_t DMAR;
		} REGs;
		page reserved;
	} TIMs[3];

	word_t reserved1[(0x40002800-0x40000c00)/sizeof(word_t)];
	page RTC;
	page WWDG;
	page IWDG;
	word_t reserved2[(0x40003800-0x40003400)/sizeof(word_t)];
	page SPI2;
	word_t reserved3[(0x40004400-0x40003c00)/sizeof(word_t)];
	page USART[2];
	word_t reserved4[(0x40005400-0x40004c00)/sizeof(word_t)];
	page I2C[2];
    union {
        struct {
            uint32_t EPR[8];
            uint32_t reserved[8];
            uint32_t CNTR;
            uint32_t ISTR;
            uint32_t FNR;
            uint32_t DADDR;
            uint32_t BTABLE;
        } REGs;
        page reserved;
    } USB;
	union {
		uint32_t MEM[512/sizeof(uint16_t)];
		struct {
			uint32_t ADDR_TX;
			uint32_t COUNT_TX;
			uint32_t ADDR_RX;
			uint32_t COUNT_RX;
		} ENTRY[8];
        page reserved;
	} USBCAN_SRAM;
	page bxCAN;
	word_t reserved5[(0x40006c00-0x40006800)/sizeof(word_t)];
	page BKP;
	page PWR;
	word_t reserved6[(0x40010000-0x40007400)/sizeof(word_t)];

	page AFIO;
	page EXTI;

	union {
		struct {
			uint32_t CRL;
			uint32_t CRH;
			uint32_t IDR;
			uint32_t ODR;
			uint32_t BSRR;
			uint32_t BRR;
			uint32_t LCKR;
		} REGs;
		page reserved;
	} GPIOs[5];
	word_t reserved7[(0x40012400-0x40011C00)/sizeof(word_t)];
	union {
		struct {
			uint32_t SR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMPR1;
			uint32_t SMPR2;
			uint32_t JOFR;
			uint32_t HTR;
			uint32_t LTR;
			uint32_t SQR1;
			uint32_t SQR2;
			uint32_t SQR3;
			uint32_t JSQR;
			uint32_t JDR;
			uint32_t DR;
		} REGs;
		page reserved;
	} ADC[2];
	page TIM1;
	page SPI1;
	word_t reserved8[(0x40013800-0x40013400)/sizeof(word_t)];
	union  {
		struct {
			uint32_t SR;
			uint32_t DR;
			uint32_t BRR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t CR3;
			uint32_t GTPR;
		} REGs;
		page reserved;
	} USART1;
	word_t reserved9[(0x40020000-0x40013C00)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISR;
			uint32_t IFCR;
			struct {
				uint32_t CCR;
				uint32_t CNDTR;
				uint32_t CPAR;
				uint32_t CMAR;
				uint32_t RESERVED;
			} CHN[8];
		} REGs;
		page reserved;
	} DMAs[1];
	word_t reservedA[(0x40021000-0x40020400)/sizeof(word_t)];

	union {
		struct {
			uint32_t CR;
			uint32_t CFGR;
			uint32_t CIR;
			uint32_t APB2RSTR;
			uint32_t APB1RSTR;
			uint32_t AHBENR;
			uint32_t APB2ENR;
			uint32_t APB1ENR;
			uint32_t BDCR;
			uint32_t CSR;
			uint32_t AHBRSTR;
			uint32_t CFGR2;
		} REGs;
		page reserved;
	} RCC;
	word_t reservedB[(0x40022000-0x40021400)/sizeof(word_t)];
	union {
		struct {
			uint32_t ACR;
			uint32_t KEYR;
			uint32_t OPTKEYR;
			uint32_t SR;
			uint32_t CR;
			uint32_t AR;
			uint32_t reserved;
			uint32_t OBR;
			uint32_t WRPR;
		} REGs;
		page reserved;
	} FLASH;
}
#ifndef USBRAM
volatile *const DEVMAP = (void *) 0x40000000;
#else
DEVMAPs;
volatile struct DEVMAP_t *const DEVMAP = &DEVMAPs;
#endif

#define ENA_IRQ(IRQ) {CTX->NVIC.REGs.ISER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define DIS_IRQ(IRQ) {CTX->NVIC.REGs.ICER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define CLR_IRQ(IRQ) {CTX->NVIC.REGs.ICPR[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}

struct {
	word_t reversed0[(0xe000e010-0xe0000000)/sizeof(word_t)];
	union {
		struct {
			uint32_t CSR;
			uint32_t RVR;
			uint32_t CVR;
			uint32_t CALIB;
		} REGs;
	} SYSTICK;
	word_t reversed1[(0xe000e100-0xe000e020)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISER[8];
			uint32_t RES0[24];
			uint32_t ICER[8];
			uint32_t RES1[24];
			uint32_t ISPR[8];
			uint32_t RES2[24];
			uint32_t ICPR[8];
			uint32_t RES3[24];
			uint32_t IABR[8];
			uint32_t RES4[56];
			uint8_t  IPR[240];
			uint32_t RES5[644];
			uint32_t STIR;
		} REGs;
	} NVIC;
} volatile *const CTX = ((void *) 0xE0000000);

enum IRQs {
	IRQ_DMA1CHN2  = 12,
	IRQ_ADC1_2	  = 18,
	IRQ_USBHIGH	  = 19,
	IRQ_USBLOW	  = 20,
	IRQ_TIM2	  = 28,
	IRQ_USART1	  = 37
};

int  main(void);
void handler_systick(void);
void handler_dma1chn2(void);
void handler_adc1_2(void);
void handler_tim2(void);
void handler_usart1(void);
void handler_usbhp(void);
void handler_usblow(void);

const interrupt_t vector_table[] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
	0,														// 0x0000_0008
	0,														// 0x0000_000C

	0,														// 0x0000_0010
	0,														// 0x0000_0014
	0,														// 0x0000_0018
	0,														// 0x0000_001C

	0,														// 0x0000_0020
	0,														// 0x0000_0024
	0,														// 0x0000_0028
	0,														// 0x0000_002C

	0,														// 0x0000_0030
	0,														// 0x0000_0034
	0,														// 0x0000_0038
	handler_systick,										// 0x0000_003C

	0,														// 0x0000_0040
	0,														// 0x0000_0044
	0,														// 0x0000_0048
	0,														// 0x0000_004C
	0,														// 0x0000_0050
	0,														// 0x0000_0054
	0,														// 0x0000_0058
	0,														// 0x0000_005C
	0,														// 0x0000_0060
	0,														// 0x0000_0064
	0,														// 0x0000_0068
	0,														// 0x0000_006C
	0,														// 0x0000_0070 DMA1_CHN2
	0,														// 0x0000_0074
	0,														// 0x0000_0078
	0,														// 0x0000_007C
	0,														// 0x0000_0080
	0,														// 0x0000_0084
	0,														// 0x0000_0088
	handler_usbhp,										// 0x0000_008C
	handler_usblow,											// 0x0000_0090
	0,														// 0x0000_0094
	0,														// 0x0000_0098
	0,														// 0x0000_009C
	0,														// 0x0000_00A0
	0,														// 0x0000_00A4
	0,														// 0x0000_00A8
	0,														// 0x0000_00AC
	0														// 0x0000_00B0 TIM2
};

volatile uint32_t blink_count;
void handler_systick() {
	static uint32_t dly;
	static uint32_t bcntr;
	static uint32_t cntr;

	if (cntr++ >= (dly & 0xfff)) {
		if (bcntr < 2*blink_count) {
			DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;
			dly = 500;
			bcntr++;
		} else {
			DEVMAP->GPIOs[GPIOC].REGs.ODR = -1;
			dly = 1000;
			bcntr = 0;
		}
		cntr = 0;
	}
}

void delay_ms(uint32_t ticks) {
	for (uint32_t i = 0; i < ticks; i++) {
		while(!(CTX->SYSTICK.REGs.CSR & (1 << 16)));
	}
}

#define USBREGs (&DEVMAP->USB.REGs)

// void handler_usblow(void)
// {
	// CLR_IRQ(IRQ_USBLOW);
// }

#define SHORT2CHAR(w16) (w16&0xff), (w16>>8)&0xff
#define TOUTF16(w8)     (w8 &0xff), 0x00

const uint8_t device_dscptr[] __attribute__((aligned(1))) ={
	0x12,   // bLength
	0x01,   // bDescriptorType
	SHORT2CHAR(0x0110), // bcdUSB
	0x00,   // bDeviceClass
	0x00,   // bDeviceSubClass
	0x00,   // bDeviceProtocol
	0x40,   // bMaxPacketSize0
	SHORT2CHAR(0x1234),  // idVendor
	SHORT2CHAR(0xabcd),  // idProduct
	SHORT2CHAR(0x0100),  // bcdDevice
	// 0x01,    // iManufacturer
	0x00,    // iManufacturer
	0x00,    // iProduct
	0x00,    // iSerialNumber
	0x01};    // bNumConfigurations
const uint8_t config_dscptr[]  __attribute__((aligned(1)))= {
	0x09,    // bLength
	0x02,    // bDescriptorType
	SHORT2CHAR(0x0020), // wTotalLength
	0x01,    // bNumInterfaces
	0x01,    // bConfigurationValue
	0x00,    // iConfiguration
	0xc0,    // bmAttribute
	0x32};    // MaxPower
const uint8_t interface_dscptr []  __attribute__((aligned(1)))= {
	0x09,    // bLength
	0x04,    // bDescriptorType
	0x00,    // bInterfaceNumber
	0x00,    // bAlternateSetting
	0x02,    // bNumEndpoints
	0x00,    // bInterfaceClass
	0x00,    // bInterfaceSubClass
	0x00,    // bIntefaceProtocol
	0x00};   // iInterface
const uint8_t endpoint_dscptr []  __attribute__((aligned(1)))= {
	0x07,     // bLength
	0x05,     // bDescriptorType
	0x01,     // bEndpointAddress
	0x02,     // bmAttibutes
	SHORT2CHAR(0x0040),  // wMaxPacketSize
	0x00,     // bInterval
	0x07,     // bLength
	0x05,     // bDescriptorType
	0x81,     // bEndpointAddress
	0x02,     // bmAttibutes
	SHORT2CHAR(0x0040),  // wMaxPacketSize
	0x00};    // Interval

const uint8_t string_dscptr[]  __attribute__((aligned(1)))= {
	0x04,    // 
	0x03,    // bDescriptorType
	SHORT2CHAR(0x0409), // 
	0x12,    // 
	0x03,    // bDescriptorType
	TOUTF16('H'),
	TOUTF16('D'),
	TOUTF16('L'),
	TOUTF16('4'),
	TOUTF16('F'),
	TOUTF16('P'),
	TOUTF16('G'),
	TOUTF16('A')};

const int descriptor_length = sizeof(device_dscptr)+ sizeof(config_dscptr)+ sizeof(interface_dscptr)+ sizeof(endpoint_dscptr);

void mem2usbcpy (uint32_t dst, const uint8_t *src, uint32_t length)
{
	uint32_t i;

	for (i = 0; i < length/sizeof(uint16_t); i++) {
		DEVMAP->USBCAN_SRAM.MEM[dst+i] = (src[2*i+1] << 8) + src[2*i];
	}
	if (descriptor_length%2) {
		DEVMAP->USBCAN_SRAM.MEM[i] = src[2*i];
	}
}

void handler_usbhp(void)
{
	CLR_IRQ(IRQ_USBHIGH);
	blink_count = 5;
}

void xxx()
{
	const uint16_t tm = 0b0111100001110000;
	uint16_t ep = USBREGs->EPR[0];
	ep = (0b01 << 9) | (~tm & ep & ~(0b11 << 9));
	USBREGs->EPR[0] = ep;
}

void handler_usblow(void)
{
	uint16_t xx;
    if ((USBREGs->ISTR & (1 << 10))) {
		xxx();
        USBREGs->ISTR = ~(1 << 10);  // Clear interrupt
		if (!(USBREGs->ISTR & (1 << 10))){
		}
		// USBREGs->EPR[0] |= ((USBREGs->EPR[0]^(0b11 << 12)) & (0b11 << 12)); // STAT_RX
		// USBREGs->EPR[0] |= ((USBREGs->EPR[0]^(0b11 <<  4)) & (0b11 <<  4)); // STAT_TX
		// if ((USBREGs->EPR[0] >> 9) & 0b11) {
		USBREGs->EPR[0] = -1;
		// blink_count = (USBREGs->EPR[0] >> 9) & 0b11;
		// blink_count = (USBREGs->ISTR >> 10) & 0b11;
		if (USBREGs->EPR[0]) {
		// if (xx & (0b11 << 9)) {
			blink_count = 4;
			// blink_count = ((USBREGs->EPR[0] >> 9) & 0b11);
		}
        USBREGs->DADDR = (1 << 7); // Enable function
    } else {
    }
	CLR_IRQ(IRQ_USBLOW);
}

int main(void)
{

 #ifdef GCC
	for (int i =0; i < descriptor_length; i++ )
		printf("%02x ", device_dscptr[i]);
	putchar('\n');
	printf("USBRAM    %8p\n", (void*)&DEVMAP->USBCAN_SRAM);
	printf("USBCNTR   %8p\n", (void*)&USBREGs->CNTR);
	printf("USBISTR   %8p\n", (void*)&USBREGs->ISTR);
	printf("BTABLE    %8p\n", (void*)&DEVMAP->USBCAN_SRAM.ENTRY);
	printf("ADDR0_TX  %8p\n", (void*)&DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX );
	printf("COUNT0_TX %8p\n", (void*)&DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX);
#ifdef USBRAM
	DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX  = sizeof(DEVMAP->USBCAN_SRAM.ENTRY)/(sizeof(uint32_t)/sizeof(uint16_t));
	DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX = descriptor_length;
	DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_RX  = DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX+DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX;
	DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_RX = 64;
	printf("ADDR0_TX  %x\n", DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX);
	printf("COUNT0_TX %x\n", DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX);
	printf("ADDR0_RX  %x\n", DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_RX);
	printf("COUNT0_RX %x\n", DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_RX);
	mem2usbcpy (sizeof(DEVMAP->USBCAN_SRAM.ENTRY)/sizeof(uint32_t), device_dscptr, descriptor_length);
	for (int i =0; i < 50; i++) {
		printf("DATA %02x : 0x%08x\n", i, DEVMAP->USBCAN_SRAM.MEM[i]);
	}

	printf("ADDR_TX %d\n", DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX);
#endif
	exit(0);
#endif
	// PCLK code
	DEVMAP->RCC.REGs.CR   |= (1 << 16);						// Enable HSE
	while (!(DEVMAP->RCC.REGs.CR & (1 << 17)));				// Wait for HSE is locked

	DEVMAP->RCC.REGs.CR   &= ~(1 << 24);					// Disable PLL
	DEVMAP->RCC.REGs.CFGR |= (0b0111 << 18);				// Set PLLMULL to 9. Set PLL output clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR |=  (1 << 16);					// Select HSE as the PLL source clock
	DEVMAP->RCC.REGs.CR   |=  (1 << 24);					// Enable PLL
	while (!(DEVMAP->RCC.REGs.CR & (1 << 25)));				// Wait for PLL to lock

	DEVMAP->FLASH.REGs.ACR |= (0b010 << 0);					// Set FLASH WAIT STATE to 2
	DEVMAP->RCC.REGs.CFGR  |= (0b0000 << 4);				// Set AHB HPRE division to 1. Set AHB clock to 72 Mhz
	DEVMAP->RCC.REGs.CFGR  |= (0b100 << 8);					// Set APB1 PPRE1 division to 2. Set AHB clock to 36 Mhz

	DEVMAP->RCC.REGs.CFGR |= (0b10 << 0);					// Select PLL clock as the system clock
	while (!(DEVMAP->RCC.REGs.CFGR & (0b10 << 2)));			// Wait for PLL clock to be selected
	DEVMAP->RCC.REGs.CFGR &= ~(1 << 22);				    // Set USBPRE to 1.5

	// Init systick
    CTX->SYSTICK.REGs.RVR = (CTX->SYSTICK.REGs.CALIB & ((1 << 24)-1));
    CTX->SYSTICK.REGs.CSR = (0 << 2)|(1 << 1)|(1 << 0);
    CTX->SYSTICK.REGs.CVR = 0;

	DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);					// Enable GPIOC clock.
	DEVMAP->GPIOs[GPIOC].REGs.CRH = 0x3 << ((13-8)*4);      // Make high GPIOC PIN 13 output
	DEVMAP->GPIOs[GPIOC].REGs.ODR = -1;

	// USB 
	DEVMAP->RCC.REGs.APB1ENR |= (1 << 23);					// Enable USB clock.
    USBREGs->CNTR &= ~(1 <<  1);                            // Exit Power Down
	delay_ms(1000);
	mem2usbcpy (sizeof(DEVMAP->USBCAN_SRAM.ENTRY)/sizeof(uint32_t), device_dscptr, descriptor_length);
    ENA_IRQ(IRQ_USBLOW);
    ENA_IRQ(IRQ_USBHIGH);
	blink_count = 2;
    // USBREGs->CNTR |=  (1 << 15);                           // Correct transfer interrupt mask enabled
    // USBREGs->CNTR |=  (1 << 10);                           // Reset Mask
    USBREGs->CNTR &= ~(1 <<  0);                           // Clear USB Reset
	DEVMAP->USB.REGs.BTABLE = 0;
	DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX  = sizeof(DEVMAP->USBCAN_SRAM.ENTRY)/(sizeof(uint32_t)/sizeof(uint16_t));
	DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX = descriptor_length;
	DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_RX  = DEVMAP->USBCAN_SRAM.ENTRY[0].ADDR_TX+DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_TX;
	DEVMAP->USBCAN_SRAM.ENTRY[0].COUNT_RX = 64;
	for(;;) {
		if (USBREGs->CNTR & (1 <<  0))
			blink_count = 3;
		else
			blink_count = 4;
	}

	return 0;
}
