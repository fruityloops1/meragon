#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

export PORTLIBS	:=	$(PORTLIBS_PATH)/armv6k $(PORTLIBS_PATH)/3ds
#export PORTLIBS	:=	$(DEVKITPRO)/portlibs/arm
export PATH		:=	$(DEVKITARM)/bin:$(PORTLIBS)/bin:$(PATH)
CTRULIB := $(DEVKITPRO)/libctru

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKEFILE_DIR := $(dir $(MAKEFILE_PATH))

export AEABI_LIB_DIR := $(DEVKITARM)/arm-none-eabi/lib/armv6k/fpu
export LIBGCC_DIR := $(DEVKITARM)/lib/gcc/arm-none-eabi/12.1.0/armv6k/fpu

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX		:=	arm-none-eabi-

export CC	:=	$(PREFIX)gcc
export CXX	:=	$(PREFIX)g++
export AS	:=	$(PREFIX)as
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy
export OBJDUMP	:=	$(PREFIX)objdump


#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
TARGET		:=	newcode
BUILD		:=	build
SOURCES		:=	source source/Camera source/Factory source/MapObj source/Scene source/al/LiveActor
INCLUDES	:=	include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -mfpu=vfpv2

CFLAGS	:=	-g -Wall -O2 -mword-relocations \
			-fomit-frame-pointer -ffunction-sections -fshort-wchar \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM11 -D_3DS

CXXFLAGS	:= $(CFLAGS) -fno-exceptions -fno-rtti -std=gnu++20

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-T $(LINKERSCRIPT) -T $(SYMBOLSCRIPT) -g $(ARCH) -nostartfiles -nolibc -nodefaultlibs -Wl,--rpath="$(CURDIR)/../lib/" -Wl,--no-demangle -Wl,--no-wchar-size-warning -Wl,-Map,$(notdir $*.map)

LIBS	:= -L $(AEABI_LIB_DIR) -L $(LIBGCC_DIR) -lgcc -lc -lgcc -lstdc++ -lsysbase -lc -lctru -lc -lm

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(CTRULIB)

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export LINKERSCRIPT 	:=$(CURDIR)/linker.x
export SYMBOLSCRIPT 	:=$(CURDIR)/$(BUILD)/syms.ld
export SYMBOLSDIR 	:=$(CURDIR)/symbols

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cc)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(CPPFILES:.cc=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)


.PHONY: $(BUILD) clean
  
#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
 
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(LINKERSCRIPT) $(TARGET).elf $(TARGET).bin $(TARGET).sym

#---------------------------------------------------------------------------------
else
 
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------


ifeq ($(strip $(CODEADDR)),)
$(error "The code destination has to be defined. CODEADDR=<address>")
endif


#---------------------------------------------------------------------------------
# Linker Script Template
#---------------------------------------------------------------------------------

define LINKERSCRIPT_TEMPLATE
OUTPUT_ARCH(arm)

SECTIONS
{
    . = $(CODEADDR);
    .text : {
        __text_start = . ;
        *(.text)
        *(.text.*)
		KEEP (*(.text.hooks))
        *(.rodata)
        *(.data)
        *(.bss)
        *(COMMON)
        __text_end  = . ;
		__end__ = __text_end;
    }
}
endef
export LINKERSCRIPT_TEMPLATE

#---------------------------------------------------------------------------------

all: $(OUTPUT).bin $(OUTPUT).sym
	
$(OUTPUT).bin : $(OUTPUT).elf
	$(OBJCOPY) -O binary $< $@
	@echo built ... $(notdir $@)

$(OUTPUT).sym : $(OUTPUT).elf
	$(OBJDUMP) -t $< > $@
	@echo written the symbol table ... $(notdir $@)

#---------------------------------------------------------------------------------
%.elf: $(OFILES)
	@echo generating linker script
	@echo "$$LINKERSCRIPT_TEMPLATE" > $(LINKERSCRIPT)
	@echo generating symbol script
	find $(SYMBOLSDIR) -type f -name '*.sym' -exec cat {} + >syms.ld
	
	@echo linking $(notdir $@)
	$(LD)  $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

#---------------------------------------------------------------------------------
%.o: %.cc
	@echo $(notdir $<)
	$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) -c $< -o $@ $(ERROR_FILTER)
	
#---------------------------------------------------------------------------------
%.o: %.c
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)
	
#---------------------------------------------------------------------------------
%.o: %.s
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

-include $(DEPSDIR)/*.d
 
#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
	
