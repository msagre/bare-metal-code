// vi: ts=4 shiftwidth=4

#define SRAM_SIZE		((uint32_t) 0x00005000)
#define SRAM_BASE		((uint32_t) 0x20000000)
#define STACKINIT		((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef int			   int32_t;
typedef short		   int16_t;
typedef char		   int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef void(*interrupt_t)(void);
void main(void);

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};

void main(void)
{

	// DMA code
//	DEVMAP->RCC.REGs.APB2ENR |= (1 << 4);				// Enable GPIOC clock.

//	DEVMAP->GPIOs[GPIOC].REGs.CRL  = 0x33333333;			// Make low GPIOC output
//	DEVMAP->GPIOs[GPIOC].REGs.CRH  = 0x33333333;			// Make high GPIOC output
//	DEVMAP->GPIOs[GPIOC].REGs.ODR ^= -1;


	for(;;);

	return 0;
}
