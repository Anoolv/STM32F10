# target binary name
TARGET := Template

#gcc cmd
CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
CPP = $(CC) -E
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size

#gcc option
CFLAGS += -mcpu=cortex-m3 -mthumb
CFLAGS += -Wall
#CFLAGS += -std=gnu99
#CFLAGS += -Wno-unused-variable 	# don't waring unused variable 
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 #use hard float uint
#CFLAGS += -nostartfiles
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Os	# optimize for size
#CFLAGS += -g	# -DDEBUG

ASFLAGS += -mthumb
ASFLAGS += -mcpu=cortex-m3

ARFLAGS = cr

LDFLAGS += -mcpu=cortex-m3 -mthumb 
#LDFLAGS += -specs=nano.specs 
#LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS += -Wl,--gc-sections 
LDFLAGS += -Wl,-Map=$(TARGET).map

#LD
LDSCRIPT = ./STM32F103ZETx_FLASH.ld


# macro for STM32
DEFS += STM32F10X_HD
DEFS += USE_STDPERIPH_DRIVER
DEFS := $(addprefix -D, $(DEFS))

# make searching paths
vpath %.s ./CMSIS/DeviceSupport/startup/gcc_ride7
vpath %.c ./CMSIS/CoreSupport ./CMSIS/DeviceSupport ./STM32F10x_StdPeriph_Driver/src ./USER/src
vpath %.h ./CMSIS/CoreSupport ./CMSIS/DeviceSupport ./STM32F10x_StdPeriph_Driver/inc ./USER/inc


# header file paths
INCS += CMSIS/CoreSupport
INCS += CMSIS/DeviceSupport
INCS += STM32F10x_StdPeriph_Driver/inc
INCS += USER/inc
INCS += USER
INCS := $(addprefix -I, $(INCS))

#.o目标变量
STARTUP := CMSIS/DeviceSupport/startup/gcc_ride7/startup_stm32f10x_hd.s
STU_OBJS := $(STARTUP:%.s=%.o)

ST_SRC =  \
CMSIS/DeviceSupport/system_stm32f10x.c \
STM32F10x_StdPeriph_Driver/src/misc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c 
ST_OBJS := $(ST_SRC:%.c=%.o)

USR_SRC =  \
USER/src/led.c \
USER/src/clock_config.c \
USER/src/usart.c \
USER/src/main.c 
USR_OBJS := $(USR_SRC:%.c=%.o)


OBJS += $(ST_OBJS)
OBJS += $(USR_OBJS)



all: $(TARGET).bin $(TARGET).hex

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary -S $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -S $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -T$(LDSCRIPT) -o $@
	$(OBJDUMP) -D -m arm $@ > $(TARGET).dis
	$(SIZE) $@


# burn: $(TARGET).bin
# 	st-flash write $< 0x08000000			#ST???

# %.o: $(STARTUP)
# 	$(CC) $(ASFLAGS) -c $< -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@
$(STU_OBJS): %.o:%.S
	$(CC) $(ASFLAGS) -o $(*).o -c $(*).s
$(OBJS): %.o:%.c
	 $(CC) $(CFLAGS) $(DEFS) $(INCS) -o $(*).o -c $(*).c


show:
	
	@echo $(OBJS)
distclean: clean
	rm -rf $(TARGET).*

clean:
	rm -f $(OBJS)
	rm -f *.bin *.dis *.elf *.hex *.map

.PHONY: all burn clean distclean
