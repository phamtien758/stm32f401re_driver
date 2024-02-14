COMPILER := arm-none-eabi-gcc
CPU := cortex-m4
CFLAGS := -mthumb -Wall -O0 -mcpu=$(CPU)
LINKER_SCRIPT_FILE = ./system/STM32F401RETX_FLASH.ld
INCLUDE1 := ./Inc
INCLUDE2 := ../GPIO/driver
INCLUDE3 := ../EXTI/driver
INCLUDE4 := ../NVIC/driver
INCLUDE5 := ../spi/driver
INCLUDE := -I$(INCLUDE1) -I$(INCLUDE2) -I$(INCLUDE3) -I$(INCLUDE4) -I$(INCLUDE5)
OUTPUT_DIR := output
ELF_FILE := out.elf

OZONE_DIR := D:/SEGGER/Ozone/Ozone.exe
OZONE_CFG := ozone_config.jdebug

SRC_FILE = system/startup_stm32f401retx.s
SRC_FILE += ../GPIO/driver/gpio.c
SRC_FILE += system/syscalls.c
SRC_FILE += system/sysmem.c
SRC_FILE += Src/stub.c
SRC_FILE += ../$(MODULE)/test/$(TEST_FILE).c
SRC_FILE += ../EXTI/driver/external_interrupt.c
SRC_FILE += ../NVIC/driver/interrupt.c
SRC_FILE += ../SPI/driver/spi.c

# Object files
OBJEC = $(OUTPUT_DIR)/startup_stm32f401retx.o
OBJEC += $(OUTPUT_DIR)/gpio.o
OBJEC += $(OUTPUT_DIR)/syscalls.o
OBJEC += $(OUTPUT_DIR)/sysmem.o
OBJEC += $(OUTPUT_DIR)/stub.o
OBJEC += $(OUTPUT_DIR)/$(TEST_FILE).o
OBJEC += $(OUTPUT_DIR)/external_interrupt.o
OBJEC += $(OUTPUT_DIR)/interrupt.o
OBJEC += $(OUTPUT_DIR)/spi.o

# Make object files
mk_obj: make_dir $(OBJEC)

$(OUTPUT_DIR)/startup_stm32f401retx.o: system/startup_stm32f401retx.s
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/gpio.o: ../GPIO/driver/gpio.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/syscalls.o: system/syscalls.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/sysmem.o: system/sysmem.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/stub.o: Src/stub.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/external_interrupt.o: ../EXTI/driver/external_interrupt.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/interrupt.o: ../NVIC/driver/interrupt.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/spi.o: ../SPI/driver/spi.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/$(TEST_FILE).o: ../$(MODULE)/test/$(TEST_FILE).c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

# Load elf to target board
debug: build
	$(OZONE_DIR) -project $(OZONE_CFG)

# Make elf file for debug
build: make_dir
	$(COMPILER) -g $(CFLAGS) -T $(LINKER_SCRIPT_FILE) $(INCLUDE) $(SRC_FILE) -o $(OUTPUT_DIR)/$(ELF_FILE)

# Create output folder
make_dir:
	mkdir -p $(OUTPUT_DIR)

# Clean all output
clean:
	rm -rf $(OUTPUT_DIR)
	rm -rf ozone_config.jdebug.user