//                                                                            //
// Author(s):                                                                 //
//   Miguel Angel Sagreras                                                    //
//                                                                            //
// Copyright (C) 2021                                                         //
//    Miguel Angel Sagreras                                                   //
//                                                                            //
// This source file may be used and distributed without restriction provided  //
// that this copyright statement is not removed from the file and that any    //
// derivative work contains  the original copyright notice and the associated //
// disclaimer.                                                                //
//                                                                            //
// This source file is free software; you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by the   //
// Free Software Foundation, either version 3 of the License, or (at your     //
// option) any later version.                                                 //
//                                                                            //
// This source is distributed in the hope that it will be useful, but WITHOUT //
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      //
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for   //
// more details at http://www.gnu.org/licenses/.                              //
//                                                                            //

#define SRAM_SIZE       ((uint32_t) 0x00005000)
#define SRAM_BASE       ((uint32_t) 0x20000000)
#define STACKINIT       ((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef void(*interrupt_t)(void);

typedef union {
    uint8_t  byte[4];
    uint16_t hword[2];
    uint32_t word;
} page[0x400/sizeof(uint32_t)];

// Memory map

enum {TIM2  = 0, TIM3  = 1, TIM4  = 2 };
enum {GPIOA = 0, GPIOB = 1, GPIOC = 2, GPIOD = 3, GPIOE = 4, GPIOF = 5 };
enum {DMA1  = 0 };
enum {CHN1  = 0, CHN2  = 1, CHN3  = 2, CHN4  = 3, CHN5  = 4, CHN6  = 5, CHN7 = 6, CHN8 = 7 };

struct {
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

    page reserved1[(0x40002800-0x40000c00)/sizeof(page)];
    page RTC;
    page WWDG;
    page IWDG;
    page reserved2[(0x40003800-0x40003400)/sizeof(page)];
    page SPI2;
    page reserved3[(0x40004400-0x40003c00)/sizeof(page)];
    page USART[2];
    page reserved4[(0x40005400-0x40004c00)/sizeof(page)];
    page I2C[2];
    page USB;
    page USBCAN_SRAM;
    page bxCAN;
    page reserved5[(0x40006c00-0x40006800)/sizeof(page)];
    page BKP;
    page PWR;
    page reserved6[(0x40010000-0x40007400)/sizeof(page)];
    
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
    page reserved7[(0x40012400-0x40011C00)/sizeof(page)];
    page ADC[2];
    page TIM1;
    page SPI1;
    page reserved8[(0x40013800-0x40013400)/sizeof(page)];
    page USART1;
    page reserved9[(0x40020000-0x40013C00)/sizeof(page)];
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
    page reservedA[(0x40021000-0x40020400)/sizeof(page)];

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

} *const DEVMAP = (void *) 0x40000000;

#define ENA_IRQ(IRQ) {NVIC->ISER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define DIS_IRQ(IRQ) {NVIC->ICER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define CLR_IRQ(IRQ) {NVIC->ICPR[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}

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
} * const NVIC = ((void *) 0xE000E100);

enum IRQs {
    IRQ_DMA1CHN2  = 12,     // DMA1 Channel 2 global Interrupt                     
    IRQ_TIM2      = 28,     // TIM2 global Interrupt                               
};

int  main(void);
void handler_dma1chn2(void);
void handler_tim2(void);

const interrupt_t vector_table[] __attribute__ ((section(".vectors"))) = {
    STACKINIT,          // 0x000 Stack Pointer
    (interrupt_t) main, // 0x004 Reset                 
    0,                  // 0x008
    0,                  // 0x00C
    0,                  // 0x010
    0,                  // 0x014
    0,                  // 0x018
    0,                  // 0x01C
    0,                  // 0x020
    0,                  // 0x024
    0,                  // 0x028
    0,                  // 0x02C
    0,                  // 0x030
    0,                  // 0x034
    0,                  // 0x038
    0,                  // 0x03C System tick timer     
    0,                  // 0x040
    0,                  // 0x044
    0,                  // 0x048
    0,                  // 0x04C
    0,                  // 0x050
    0,                  // 0x054
    0,                  // 0x058
    0,                  // 0x05C
    0,                  // 0x060
    0,                  // 0x064
    0,                  // 0x068
    0,                  // 0x06C
    handler_dma1chn2,   // 0x070 DMA1_CHN2    
    0,                  // 0x074
    0,                  // 0x078
    0,                  // 0x07C
    0,                  // 0x080
    0,                  // 0x084
    0,                  // 0x088
    0,                  // 0x08C
    0,                  // 0x090
    0,                  // 0x094
    0,                  // 0x098
    0,                  // 0x09C
    0,                  // 0x0A0
    0,                  // 0x0A4
    0,                  // 0x0A8
    0,                  // 0x0AC
    handler_tim2,       // 0x0B0 TIM2        
};

void handler_dma1chn2(void)
{

//  DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;
    DEVMAP->DMAs[DMA1].REGs.IFCR |= (0xf << 1);
    CLR_IRQ(IRQ_DMA1CHN2);
}

void handler_tim2(void)
{
//  DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;
    DEVMAP->TIMs[TIM2].REGs.SR &= ~(1 << 0);
    CLR_IRQ(IRQ_TIM2);
}

uint32_t const data[256] = {
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

int main(void)
{

    DEVMAP->RCC.REGs.CR   |= (1 << 16);                     // Enable HSE
    while (!(DEVMAP->RCC.REGs.CR & (1 << 17)));             // Wait for HSE is locked

    DEVMAP->RCC.REGs.CR   &= ~(1 << 24);                    // Disable PLL
    DEVMAP->RCC.REGs.CFGR |= (0b0100 << 18);                // Set PLLMULL to 6. Set PLL output clock to 48 Mhz 
    DEVMAP->RCC.REGs.CFGR |=  (1 << 16);                    // Select HSE as the PLL source clock
    DEVMAP->RCC.REGs.CR   |=  (1 << 24);                    // Enable PLL
    while (!(DEVMAP->RCC.REGs.CR & (1 << 25)));             // Wait for PLL is locked

    DEVMAP->RCC.REGs.CFGR |= (0b1000 << 4);                 // Set AHB HPRE division to 2. Set AHB clock to 24 Mhz 

    DEVMAP->RCC.REGs.CFGR |= (0b10 << 0);                   // Select PLL clock as the system clock
    while (!(DEVMAP->RCC.REGs.CFGR & (0b10 << 2)));         // Wait for PLL clock to be selected

    DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);                   // Enable GPIOC clock.
    DEVMAP->RCC.REGs.APB1ENR |= (1 << 0);                   // Enable TIM2 clock.
    DEVMAP->RCC.REGs.AHBENR  |= (1 << 0);                   // Enable DMA1 clock.

    DEVMAP->GPIOs[GPIOC].REGs.CRL  = 0x22222222;            // Make low GPIOC output
    DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x22222222;            // Make high GPIOC output
    DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;

    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CNDTR = sizeof(data)/sizeof(uint32_t); // Transfer size
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR  = (uint32_t) data;               // Memory source address
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CPAR  = (uint32_t) &DEVMAP->GPIOs[GPIOC].REGs.ODR; // Peripheral destination address

    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR  = 0;             // Reset CCR
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 14);    // Disable memory to memory transfer on DMA1 channel 2
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b11 << 12); // Set DMA priority to very high
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 10); // Set memory transfer size to 32-bits
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (0b10 << 8);  // Set peripheral transfer size to 32-bits
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 7);     // Enable memory increment mode
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR &= ~(1 << 6);     // Disable peripheral increment mode
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 5);     // Enable circular mode
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 4);     // Read from memory
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 2);     // Enable half transfer completed interrupt
    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |=  (1 << 1);     // Enable transfer completed interrupt
    ENA_IRQ(IRQ_DMA1CHN2);                                  // Enable DMA1 Channel2 inturrupt on NVIC

    DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= (1 << 0);      // Enable DMA

    ENA_IRQ(IRQ_TIM2);                                      // Enable TIM2 interrupt on NVIC
    DEVMAP->TIMs[TIM2].REGs.CR1  = 0x0000;                  // Reset CR1 just in case
//  DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 4);               // Down counter mode
    DEVMAP->TIMs[TIM2].REGs.PSC   = 46874;                  // fCK_PSC / (PSC[15:0] + 1)
    DEVMAP->TIMs[TIM2].REGs.ARR   = 1;
    DEVMAP->TIMs[TIM2].REGs.DIER |= (1 << 14);              // Trigger DMA request enable
    DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  8);              // Update DMA request enable
//  DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  6);              // Enable interrupt
//  DEVMAP->TIMs[TIM2].REGs.DIER |= (1 <<  0);              // Update interrupt enable

    DEVMAP->TIMs[TIM2].REGs.CR1  |= (1 << 0);               // Finally enable TIM1 module

    for(;;);

    return 0;
}
