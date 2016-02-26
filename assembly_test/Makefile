TARGET = assembly_test
ARCH="/usr/local/gcc-arm-none-eabi-5_2-2015q4/bin/arm-none-eabi-"
FLASH_SIZE=262144
FLASH_ROW_SIZE=256
FLASH_ARRAY_SIZE=65536
EE_ARRAY=64
EE_ROW_SIZE=16
OPTIMIZATION = -O0
INCLUDE_DIR=../../mono_buildsystem/include
CYPRESS_DIR=$(INCLUDE_DIR)/../Generated_Source/PSoC
LINKER_SCRIPT=${INCLUDE_DIR}/cm3gcc.ld
BUILD_DIR=build
MONO_FRAMEWORK_PATH =../../mono_framework
MBED_PATH=../../mbedcomp
MBED_FS=../../mbed/libraries/fs
COMP_LIB=../../mono_buildsystem/lib/CyComponentLibrary.a
CYPRESS_LIB=../../mono_buildsystem/lib/monoCyLib.a
PARALLEL_CYPRESS=../../mono_parallel_display
# MBED_LIB=../../mbedcomp/mbedlib.a
# MONO_LIB=../../mono_framework/monolib2.a
USE_PARALLEL_DISPLAY=false

OBJECTS =		$(patsqubst %.c,%.o,$(wildcard *.c)) \
				$(patsubst %.cpp,%.o,$(wildcard *.cpp))

MBED_OBJECTS =	$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/common/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/common/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/target_cypress/*.c))
				
MBED_FS_OBJECTS=$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/sd/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/fat/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/fat/ChaN/*.cpp))
				
MBED_INCLUDES =	$(MBED_PATH) \
				$(MBED_PATH)/api \
				$(MBED_PATH)/hal \
				$(MBED_PATH)/target_cypress \
				$(MBED_FS)/sd \
				$(MBED_FS)/fat \
				$(MBED_FS)/fat/ChaN

MONO_OBJECTS =	$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ui/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ui/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/wireless/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/wireless/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/media/*.cpp))
				

MONO_INCLUDES =	$(MONO_FRAMEWORK_PATH) \
				$(MONO_FRAMEWORK_PATH)/display \
				$(MONO_FRAMEWORK_PATH)/display/ui \
				$(MONO_FRAMEWORK_PATH)/wireless \
				$(MONO_FRAMEWORK_PATH)/media

ifeq ($(USE_PARALLEL_DISPLAY),true)
	MONO_OBJECTS += $(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/hx8340/*.cpp))
	MONO_INCLUDES += $(MONO_FRAMEWORK_PATH)/display/hx8340
	CYPRESS_LIB = $(PARALLEL_CYPRESS)/lib/monoCyLib.a
	INCLUDE_DIR = $(PARALLEL_CYPRESS)/include
else
	MONO_OBJECTS += $(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ili9225g/*.cpp))
	MONO_INCLUDES += $(MONO_FRAMEWORK_PATH)/display/ili9225g 
endif				

SYS_OBJECTS = 	$(patsubst %.c,%.o,$(wildcard $(CYPRESS_DIR)/*.c)) \
				$(patsubst %.s,%.o,$(wildcard $(CYPRESS_DIR)/*Gnu.s))

TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/, $(OBJECTS))				
MBED_TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/mbed, $(subst $(MBED_PATH),,$(MBED_OBJECTS)))
MBED_FS_TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/mbed, $(subst $(MBED_FS),,$(MBED_FS_OBJECTS)))
MONO_TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/mono, $(subst $(MONO_FRAMEWORK_PATH),, $(MONO_OBJECTS)))

TARGET_HEADERS =	$(wildcard ./*.h) \
					$(wildcard ./*.hpp)
MBED_HEADERS =		$(foreach path,$(MBED_INCLUDES),$(wildcard $(path)/*.h))
MONO_HEADERS =		$(foreach path,$(MONO_INCLUDES),$(wildcard $(path)/*.h))


CC=$(ARCH)gcc
CXX=$(ARCH)g++
LD=$(ARCH)gcc
AS=$(ARCH)gcc
AR=$(ARCH)ar
RANLIB=$(ARCH)ranlib
STRIP=$(ARCH)strip
OBJCOPY=$(ARCH)objcopy
OBJDUMP=$(ARCH)objdump
COPY=cp
MKDIR=mkdir
MONOPROG=~/Dropbox/monocode/monoprog/build/monoprog
ELFTOOL='C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\bin\cyelftool.exe'
INCS = -I . $(addprefix -I, $(MONO_INCLUDES) $(MBED_INCLUDES) $(INCLUDE_DIR)) 
CDEFS= #-DMONO_NO_USB
ASDEFS=
AS_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb -mthumb-interwork -march=armv7-m
CC_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb $(OPTIMIZATION) -mthumb-interwork -fno-common -fmessage-length=0 -ffunction-sections -fdata-sections -march=armv7-m
ONLY_C_FLAGS = -std=gnu99 
ONLY_CPP_FLAGS = -std=gnu++98 -fno-rtti -fno-exceptions
LDSCRIPT = -T $(LINKER_SCRIPT)
LD_FLAGS = -g -mcpu=cortex-m3 -mthumb -march=armv7-m -fno-rtti -Wl,--gc-sections -specs=nano.specs 
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(USE_PARALLEL_DISPLAY),true)
CDEFS += -DMONO_DISP_CTRL_HX8340
endif

#"libs/CyCompLib.a"
#   -mfix-cortex-m3-ldrd -u _printf_float -u _scanf_float
COPY_FLAGS = -j .text -j .eh_frame -j .rodata -j .ramvectors -j .noinit -j .data -j .bss -j .stack -j .heap -j .cyloadablemeta

all: $(BUILD_DIR) $(TARGET).elf

$(BUILD_DIR):
	@echo "creating build directory"
	@mkdir -p ./$(BUILD_DIR)

# %.cpp: %.h
# 	@echo "Header dependency $<"

$(BUILD_DIR)/mono/slre.o: $(MONO_FRAMEWORK_PATH)/slre.c
	@echo "Compiling SLRE C: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(ONLY_C_FLAGS) -Wno-char-subscripts $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/mono/%.o: $(MONO_FRAMEWORK_PATH)/%.cpp $(MONO_HEADERS)
	@echo "Compiling mono C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/mbed/%.o: $(MBED_PATH)/%.c $(MBED_HEADERS)
	@echo "Compiling mbed C: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(ONLY_C_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/mbed/%.o: $(MBED_PATH)/%.cpp $(MBED_HEADERS)
	@echo "Compiling mbed C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<
	
$(BUILD_DIR)/mbed/fat/%.o: $(MBED_FS)/fat/%.cpp $(MBED_HEADERS)
	@echo "Compiling mbed fs C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/mbed/sd/%.o: $(MBED_FS)/sd/%.cpp $(MBED_HEADERS)
	@echo "Compiling mbed fs C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/%.o: %.c $(TARGET_HEADERS)
	@echo "Compiling C: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(ONLY_C_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp $(TARGET_HEADERS)
	@echo "Compiling C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(TARGET).elf: $(CYPRESS_LIB) $(MBED_TARGET_OBJECTS) $(MBED_FS_TARGET_OBJECTS) $(MONO_TARGET_OBJECTS) $(TARGET_OBJECTS) 
	@echo "Linking $(notdir $@)"
	@$(LD) -Wl,--start-group -o $@ $^ $(CYPRESS_LIB) -mthumb -march=armv7-m -mfix-cortex-m3-ldrd "-Wl,-Map,mono_project.map" -T $(LINKER_SCRIPT) -g -specs=nano.specs "-u\ _printf_float" $(LD_SYS_LIBS) -Wl,--gc-sections -Wl,--end-group

$(TARGET).hex: $(TARGET).elf
	$(ELFTOOL) -C $^ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)
	$(OBJCOPY) -O ihex $(COPY_FLAGS) $< $@
	$(ELFTOOL) -B $^ --flash_size $(FLASH_SIZE) --flash_array_size $(FLASH_ARRAY_SIZE) --flash_row_size $(FLASH_ROW_SIZE) --ee_array $(EE_ARRAY) --ee_row_size $(EE_ROW_SIZE)

$(TARGET):  $(OBJS)  ${LINKER_SCRIPT}
	@echo "Other link: $(OBJS)"
	$(LD) $(LDSCRIPT) $(OBJS) -o $@
	

systemFiles:
	@echo $(SYS_OBJECTS)
	
appFiles:
	@echo $(TARGET_OBJECTS)

mbedFiles:
	@echo $(MBED_TARGET_OBJECTS)

monoFiles:
	@echo $(MONO_TARGET_OBJECTS)

includeFiles: 
	@echo $(INCS)
	
headers:
	@echo $(TARGET_HEADERS) $(MONO_HEADERS) $(MBED_HEADERS)

install: $(TARGET).elf
	@python reboot.py
	@echo "Programming app to device..."
	$(MONOPROG) -p $(TARGET).elf --verbose=2

clean:
	$(RM) $(TARGET).elf $(TARGET).bin $(TARGET_OBJECTS) $(MBED_TARGET_OBJECTS) $(MBED_FS_TARGET_OBJECTS) $(MONO_TARGET_OBJECTS)

summary: $(TARGET).elf
	$(ELFTOOL) -S $(TARGET).elf
	

## $(LD) -Wl,--start-group $(LD_FLAGS) libs/CyCompLib.a $(LDSCRIPT) -o $@ $^ -Wl,--end-group $(LD_SYS_LIBS)
## $(ELFTOOL) -C $@ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)