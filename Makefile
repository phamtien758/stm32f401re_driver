COMPILER := arm-none-eabi-gcc
CPU := cortex-m4
CFLAGS := -mthumb -Wall -O0 -mcpu=$(CPU)
LINKER_SCRIPT_FILE = common/from_ST/STM32F401RETX_FLASH.ld

INCLUDE := -I ./driver/inc
OUTPUT_DIR := output
ELF_FILE := out.elf

# Ozone debugger
OZONE_DIR := D:/SEGGER/Ozone/Ozone.exe
OZONE_CFG := ozone_config.jdebug

# Source file directory
SRC_FILE = common/from_ST/startup_stm32f401retx.s
SRC_FILE += common/from_ST/syscalls.c
SRC_FILE += common/from_ST/sysmem.c
SRC_FILE += driver/src/stub.c
SRC_FILE += driver/src/gpio.c
SRC_FILE += driver/src/external_interrupt.c
SRC_FILE += driver/src/interrupt.c
SRC_FILE += test/$(MODULE)/$(TEST_FILE).c

# Object files
OBJEC = $(OUTPUT_DIR)/startup_stm32f401retx.o
OBJEC += $(OUTPUT_DIR)/gpio.o
OBJEC += $(OUTPUT_DIR)/syscalls.o
OBJEC += $(OUTPUT_DIR)/sysmem.o
OBJEC += $(OUTPUT_DIR)/stub.o
OBJEC += $(OUTPUT_DIR)/external_interrupt.o
OBJEC += $(OUTPUT_DIR)/interrupt.o
OBJEC += $(OUTPUT_DIR)/$(TEST_FILE).o

# Make object files
mk_obj: make_dir $(OBJEC)

$(OUTPUT_DIR)/startup_stm32f401retx.o: common/from_ST/startup_stm32f401retx.s
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/syscalls.o: common/from_ST/syscalls.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/sysmem.o: common/from_ST/sysmem.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/gpio.o: driver/src/gpio.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/stub.o: driver/src/stub.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/external_interrupt.o: driver/src/external_interrupt.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/interrupt.o: driver/src/interrupt.c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

$(OUTPUT_DIR)/$(TEST_FILE).o: test/$(MODULE)/$(TEST_FILE).c
	$(COMPILER) -c $(CFLAGS) $(INCLUDE) $^ -o $@

# Load .elf to target board and start debug
debug: build
	$(OZONE_DIR) -project $(OZONE_CFG)

# Create .elf file
build: make_dir
	$(COMPILER) -g $(CFLAGS) -T $(LINKER_SCRIPT_FILE) $(INCLUDE) $(SRC_FILE) -o $(OUTPUT_DIR)/$(ELF_FILE)

# Create output folder
make_dir:
	mkdir -p $(OUTPUT_DIR)

# Clean all output
clean:
	rm -rf $(OUTPUT_DIR)
	rm -rf ozone_config.jdebug.user