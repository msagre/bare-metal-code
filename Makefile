TARGET ?= adc
SRCS = $(TARGET).c

OBJS =  $(addsuffix .o, $(basename $(SRCS)))
INCLUDES = -I.

LINKER_SCRIPT = stm32.ld

CFLAGS += -mcpu=cortex-m3 -mthumb # Processor setup
CFLAGS += -O2 # Optimization ON
CFLAGS += -g2 # Generate debug info
CFLAGS += -fno-common
CFLAGS += -Wall # Turn on warnings
#CFLAGS += -pedantic # more warnings
CFLAGS += -Wsign-compare
CFLAGS += -mfloat-abi=soft -fsingle-precision-constant
CFLAGS += -Wcast-align
#CFLAGS += -Wconversion # neg int const implicitly converted to uint
CFLAGS += -fomit-frame-pointer # Do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -march=armv7-m
LDFLAGS += -nostartfiles
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,--gc-sections # Linker garbage collector
LDFLAGS += -T$(LINKER_SCRIPT)

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size
DBG = $(CROSS_COMPILE)gdb

all: clean $(SRCS) build size
	@echo "Successfully finished..."

build: $(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).lst

$(TARGET).elf: $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	@echo "Building" $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	@echo "Building" $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.hex: %.elf
	@$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	@$(OBJCOPY) -O binary $< $@

%.lst: %.elf
	@$(OBJDUMP) -x -S $(TARGET).elf > $@

size: $(TARGET).elf
	@$(SIZE) $(TARGET).elf

erase:
	@st-flash erase
	@st-flash reset

flash: $(TARGET).bin
	@st-flash erase
	@st-flash write $(TARGET).bin 0x8000000
	@st-flash reset

debug:
	@$(DBG) -tui --eval-command="target extended-remote :4242" \
	--eval-command="layout asm" \
	--eval-command="layout regs" \
	 $(TARGET).elf

clean: 
	@echo "Cleaning..."
	@rm -f adc.elf dma.elf # $(TARGET).elf
	@rm -f adc.bin dma.bin # $(TARGET).bin
	@rm -f adc.map dma.map # $(TARGET).map
	@rm -f adc.hex dma.hex # $(TARGET).hex
	@rm -f adc.lst dma.lst # $(TARGET).lst
	@rm -f adc.o   dma.o   # $(TARGET).o

.PHONY: all build size clean flash debug
