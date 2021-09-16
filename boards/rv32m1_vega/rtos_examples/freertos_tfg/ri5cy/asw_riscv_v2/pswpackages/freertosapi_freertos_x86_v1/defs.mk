
.PHONY: run g gdb vip print-srcs root

CROSS:=$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_RTEMS_PATH)/bin/sparc-rtems4.8-

AS:=$(CROSS)as
LD:=$(CROSS)ld
CC:=$(CROSS)gcc --pipe
CXX:=$(CROSS)g++ --pipe
CPP:=$(CROSS)cpp
AR:=$(CROSS)ar
NM:=$(CROSS)nm
OBJCPY:=$(CROSS)objcopy
OBJDUMP:=$(CROSS)objdump
STRIP:=$(CROSS)strip

GDB:=$(CROSS)gdb

LST:=$(TARGET).lst
ROMIMAGE:=$(TARGET).rom
BINIMAGE:=$(TARGET).bin
SRECIMAGE:=$(TARGET).srec
MAP:=$(TARGET).map

MKDIR:=mkdir
HOSTCC:=gcc

CFLAGS+= -B$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_RTEMS_PATH)/sparc-rtems4.8/leon2/lib
CFLAGS+= -mcpu=cypress -msoft-float -g -specs bsp_specs -qrtems -Wall
CXXFLAGS:= -fno-rtti -fomit-frame-pointer -fno-exceptions -fno-builtin -Wno-write-strings

CPPFLAGS+=-I$(PSWPACKAGES_ROOT_FOLDER_NAME)/$(PSWP_FOLDER_NAME)/include

ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
PLTSRCS:=$(wildcard $(PSWPACKAGES_ROOT_FOLDER_NAME)/$(PSWP_FOLDER_NAME)/src/*.c)
SRCS+=$(PLTSRCS)
OBJS+=$(patsubst %.cpp,%.o, $(patsubst %.c,%.o, $(patsubst %.S, %.o, $(patsubst $R/%, $R/bin/$(DEP_FOLDER_NAME)/%, $(PLTSRCS)))))

CFLAGS+=-O0 $(if $(filter $(PSWPACKAGES_ROOT_FOLDER_NAME)/% $(OSSWPACKAGES_ROOT_FOLDER_NAME)/%, $<), , -fprofile-arcs -ftest-coverage)
else
CFLAGS+=-O2
endif

LDFLAGS+=-lrtemscpu -lno_ext -lno_io 

ifneq (0,$(CONFIG_OSSWP_RTEMS_4_8_IMPR_DEMANDED_RTEMSAPI_4_8_IMPR_EVENT_MANAGER))
LDFLAGS+=-levent
else
LDFLAGS+=-lno_event
endif

ifneq (0,$(CONFIG_OSSWP_RTEMS_4_8_IMPR_DEMANDED_RTEMSAPI_4_8_IMPR_RATE_MONOTONIC_MANAGER))
LDFLAGS+=-lrtmon
else
LDFLAGS+=-lno_rtmon
endif

ifneq (0,$(CONFIG_OSSWP_RTEMS_4_8_IMPR_DEMANDED_RTEMSAPI_4_8_IMPR_TIMER_MANAGER))
LDFLAGS+=-ltimer
else
LDFLAGS+=-lno_timer
endif

ifneq (0,$(CONFIG_OSSWP_RTEMS_4_8_IMPR_DEMANDED_RTEMSAPI_4_8_IMPR_MSG_QUEUE_MANAGER))
LDFLAGS+=-lmsg
else
LDFLAGS+=-lno_msg
endif

ifneq (0,$(CONFIG_OSSWP_RTEMS_4_8_IMPR_DEMANDED_RTEMSAPI_4_8_IMPR_SEMAPHORE))
LDFLAGS+=-lsem
else
LDFLAGS+=-lno_sem
endif

LDFLAGS+=-lrtemsbsp --script=linkcmds

# Now we have to define the default targets for all the types of source files
# of the software packages:

$R/bin/$(DEP_FOLDER_NAME)/%.o: $R/%.c
	@echo " CC  $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MD -MP -c -o $@ $<

$R/bin/$(DEP_FOLDER_NAME)/%.o: $R/%.cpp
	@echo " CXX $<"
	@$(MKDIR) -p $(@D)
	@$(CXX) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) -MD -MP -c -o $@ $<

$R/bin/$(DEP_FOLDER_NAME)/%.o: $R/%.S
	@echo " CC  $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(ASMFLAGS) $(CPPFLAGS) -c -o $@ $<


# Once defined the default targets, we have to define the main target of the
# application, i.e. $(TARGET):

$(TARGET) : root $(OBJS)
ifneq (,$(findstring .cpp,$(suffix $(SRCS))))
	@echo " LD  $@"
	@$(CXX) -Wl,-Map,$(MAP) $(CFLAGS) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo " LST $(LST)"
	@$(OBJDUMP) -d $(TARGET) > $(LST)
else
	@echo " LD  $@"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo " LST $(LST)"
	@$(OBJDUMP) -d $(TARGET) > $(LST)
endif
	@cp $(TARGET) $(ROMIMAGE)
	@$(STRIP) $(ROMIMAGE)
	@echo " Building SRECORD $(SRECIMAGE)"
	@$(OBJCPY) -O srec $(ROMIMAGE) $(SRECIMAGE)

# To finish, we can define the g and gdb target to help us with the debugging
# process of the application.

LEON2VIP:=$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_LEON2VIP_PATH)/leon2_vip

VIP_COMMANDS_FILE:= $R/bin/$(DEP_FOLDER_NAME)/commands.txt
VIP_WORKSPACE:= $R/bin/$(DEP_FOLDER_NAME)
VIP_OPTIONS:= -workspace $(VIP_WORKSPACE) -batch $(VIP_COMMANDS_FILE) -spw
VIP_MEMCONF:= $R/bin/$(DEP_FOLDER_NAME)/memconf.cfg
VIP_MEM_BINARIES:= $R/bin/$(DEP_FOLDER_NAME)/EEPROM0.bin $R/bin/$(DEP_FOLDER_NAME)/EEPROM1.bin

RAM_SIZE_IN_BYTES := $(shell echo "obase=16;ibase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_RAM_SIZE_IN_KIB)) * 400" | bc)
PROM_SIZE_IN_BYTES := $(shell echo "obase=16;ibase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_PROM_SIZE_IN_KIB)) * 400" | bc)
CLOSED_EEPROM_SIZE_IN_BYTES := $(shell echo "obase=16;ibase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_CLOSED_EEPROM_SIZE_IN_KIB)) * 400" | bc)
OPENED_EEPROM_SIZE_IN_BYTES := $(shell echo "obase=16;ibase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_OPENED_EEPROM_SIZE_IN_KIB)) * 400" | bc)

RAM_INITIAL_ADDRESS := 0x$(shell echo "ibase=A;obase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_RAM_INITIAL_ADDRESS))" | bc)
PROM_INITIAL_ADDRESS := 0x$(shell echo "ibase=A;obase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_PROM_INITIAL_ADDRESS))" | bc)
CLOSED_EEPROM_INITIAL_ADDRESS := 0x$(shell echo "ibase=A;obase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_CLOSED_EEPROM_INITIAL_ADDRESS))" | bc)
OPENED_EEPROM_INITIAL_ADDRESS := 0x$(shell echo "ibase=A;obase=16;$(patsubst 0x%,%,$(CONFIG_BOARD_LEON2VIP_1_X_OPENED_EEPROM_INITIAL_ADDRESS))" | bc)

# Some voodoo magic to calculate the highest power of two that can store the needed coverage data
GCOV_STORAGE_SIZE := 0x$(shell echo "define f(x) { auto r; r = 1; while (r < x) {	r = r * 2 }; return r }; ibase=A;obase=16; f($(patsubst 0x%,%,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_STORAGE_SIZE)))" | bc)
GCOV_STORAGE_ADDRESS := 0x$(shell echo "ibase=A;obase=16;$(patsubst 0x%,%,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_STORAGE_ADDRESS))" | bc)

GCOV_EEPROM:=EEPROM2
GCOV_EEPROM_BINARY:=$R/bin/$(DEP_FOLDER_NAME)/$(GCOV_EEPROM).bin
GCOV_EXTRACTION_BIN:=$(PSWPACKAGES_ROOT_FOLDER_NAME)/$(PSWP_FOLDER_NAME)/tools/extraction/extraction
GCOV_EXTRACTION_SRC:=$(PSWPACKAGES_ROOT_FOLDER_NAME)/$(PSWP_FOLDER_NAME)/tools/extraction/extraction.c

LCOV:=lcov
#LCOV:=lcov --gcov-tool /usr/bin/gcov-4.6
LCOV_COVERAGE_INFO:=coverage.info
LCOV_GENHTML:=genhtml
LCOV_OUTPUT_DIR:=lcov

ROOT_FILENAME:=$(PSWPACKAGES_ROOT_FOLDER_NAME)/$(PSWP_FOLDER_NAME)/include/platform/root.h

root:
	@echo "#ifndef PLATFORM__ROOT_H" > $(ROOT_FILENAME)
	@echo "#define PLATFORM__ROOT_H" >> $(ROOT_FILENAME)
	@echo "" >> $(ROOT_FILENAME)
	@echo "#define DEP_FOLDER_NAME \"$R/bin/$(DEP_FOLDER_NAME)/\"" >> $(ROOT_FILENAME)
	@echo "" >> $(ROOT_FILENAME)
	@echo "#endif // PLATFORM__ROOT_H" >> $(ROOT_FILENAME)


vip: $(TARGET)
	@echo "***************************************"
	@echo "Iniciando VIP_LEON2..."
	@echo "***************************************"
	@echo "RAM    $(RAM_INITIAL_ADDRESS) $(RAM_SIZE_IN_BYTES) RW" > $(VIP_MEMCONF)
	@echo "EEPROM0 $(CLOSED_EEPROM_INITIAL_ADDRESS) $(CLOSED_EEPROM_SIZE_IN_BYTES) RWS" >> $(VIP_MEMCONF)
	@echo "EEPROM1 $(OPENED_EEPROM_INITIAL_ADDRESS) $(OPENED_EEPROM_SIZE_IN_BYTES) RWS" >> $(VIP_MEMCONF)
ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
	@echo "$(GCOV_EEPROM) $(GCOV_STORAGE_ADDRESS) $(GCOV_STORAGE_SIZE) RWS" >> $(VIP_MEMCONF)
endif
	@echo "PROM    $(PROM_INITIAL_ADDRESS) $(PROM_SIZE_IN_BYTES) RW" >> $(VIP_MEMCONF)
	@echo "load $(SRECIMAGE)" > $(VIP_COMMANDS_FILE)
	@echo "reg pc 0x45000000" >> $(VIP_COMMANDS_FILE)
	@echo "reg npc 0x45000004" >> $(VIP_COMMANDS_FILE)
	@echo "break 0x40325020" >> $(VIP_COMMANDS_FILE)
	@echo "continue" >> $(VIP_COMMANDS_FILE)
	@$(LEON2VIP) $(VIP_OPTIONS)

GDBINIT_FILE:=$R/bin/$(DEP_FOLDER_NAME)/gdbinit

g gdb : $(TARGET)
	@echo "Generating starting commands for gdb in file <.gdbinit> ..."
	@echo "tar extended-remote localhost:1234" > $(GDBINIT_FILE)
	@echo "load" >> $(GDBINIT_FILE)
	@echo "break Init" >> $(GDBINIT_FILE)
	$(GDB) -x $(GDBINIT_FILE) $(TARGET)

CPPCHECK:=$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_CPPCHECK_PATH)/cppcheck
CPPCHECK_FLAGS=--force --enable=all --xml --xml-version=2 $(patsubst %,-I %,$(SWI_DIRS)) \
		$(foreach source, $(SRCS), \
			$(if $(filter $(MAIN_ROOT_FOLDER_NAME)/%, $<), \
				$(patsubst %,-I$(MAIN_ROOT_FOLDER_NAME)/%/include, \
			$(firstword $(subst /, , $(strip $(patsubst $(MAIN_ROOT_FOLDER_NAME)/%, %, $<))))))) \
		$(foreach source, $(SRCS), \
			$(if $(filter $(SWPACKAGES_ROOT_FOLDER_NAME)/%, $(source)), \
				$(patsubst %,-I$(SWPACKAGES_ROOT_FOLDER_NAME)/%/include, \
			$(firstword $(subst /, , $(strip $(patsubst $(SWPACKAGES_ROOT_FOLDER_NAME)/%, %, $(source)))))), \
				$(if $(filter $(OSSWPACKAGES_ROOT_FOLDER_NAME)/%, $(source)), \
					$(patsubst %,-I$(OSSWPACKAGES_ROOT_FOLDER_NAME)/%/include, \
				$(firstword $(subst /, , $(strip $(patsubst $(OSSWPACKAGES_ROOT_FOLDER_NAME)/%, %, $(source)))))))))

CPPCHECK_HUDSON_FILE:=$R/cppcheck-result.xml

cppcheck: $(SRCS)
	@$(MKDIR) -p $R/doc/cppcheck/$(DEP_FOLDER_NAME)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --suppress=variableScope --suppress=unusedFunction $(SRCS) 2> $R/doc/cppcheck/$(DEP_FOLDER_NAME)/results_suppressUnusedFunction.xml

cppcheck-unused: $(SRCS)
	@$(MKDIR) -p $R/doc/cppcheck/$(DEP_FOLDER_NAME)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --suppress=variableScope $(SRCS) 2> $R/doc/cppcheck/$(DEP_FOLDER_NAME)/results.xml

cppcheck-hudson: $(SRCS)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --suppress=variableScope --suppress=unusedFunction $(SRCS) 2> $(CPPCHECK_HUDSON_FILE)

cppcheck-unused-hudson: $(SRCS)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --suppress=variableScope $(SRCS) 2> $(CPPCHECK_HUDSON_FILE)

print-srcs:
	@$(foreach source,$(patsubst $R/%,%,$(patsubst %.S,,$(patsubst %.c,%.gcda,$(patsubst %.cpp,%.gcda,$(SRCS) $(OSSRCS) $(MSRC))))),echo $(source);)

pswp-clean:
	@rm -rf $(MAP)
	@rm -rf $(LST)
	@rm -rf $(ROMIMAGE)
	@rm -rf $(SRECIMAGE)
	@rm -rf $(VIP_MEMCONF)
	@rm -rf $(VIP_MEM_BINARIES)
	@rm -rf $(VIP_COMMANDS_FILE)
	@rm -rf $(ROOT_FILENAME)
	@rm -rf $(GCOV_EEPROM_BINARY)
	@rm -rf $(GCOV_EXTRACTION_BIN)
	@rm -rf $(LCOV_COVERAGE_INFO)
	@rm -rf $(CPPCHECK_HUDSON_FILE)
	@rm -rf $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_OUTPUT_DIR)
	@rm -rf $(GDBINIT_FILE)
	@echo Platform cleaning done.

pswp-distclean:

run: $(TARGET)
	@echo " Running target $(TARGET)"
	@echo "RAM    $(RAM_INITIAL_ADDRESS) $(RAM_SIZE_IN_BYTES) RW" > $(VIP_MEMCONF)
	@echo "EEPROM0 $(CLOSED_EEPROM_INITIAL_ADDRESS) $(CLOSED_EEPROM_SIZE_IN_BYTES) RWS" >> $(VIP_MEMCONF)
	@echo "EEPROM1 $(OPENED_EEPROM_INITIAL_ADDRESS) $(OPENED_EEPROM_SIZE_IN_BYTES) RWS" >> $(VIP_MEMCONF)
ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
	@echo "$(GCOV_EEPROM) $(GCOV_STORAGE_ADDRESS) $(GCOV_STORAGE_SIZE) RWS" >> $(VIP_MEMCONF)
endif
	@echo "PROM    $(PROM_INITIAL_ADDRESS) $(PROM_SIZE_IN_BYTES) RW" >> $(VIP_MEMCONF)
	@echo "load $(SRECIMAGE)" > $(VIP_COMMANDS_FILE)
	@echo "reg pc 0x40000000" >> $(VIP_COMMANDS_FILE)
	@echo "reg npc 0x40000004" >> $(VIP_COMMANDS_FILE)
ifneq (,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_EXTRA_COMMANDS))
	@echo '$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_EXTRA_COMMANDS)' >> $(VIP_COMMANDS_FILE)
endif
	@echo "run 0x40000000" >> $(VIP_COMMANDS_FILE)
	@$(LEON2VIP) $(VIP_OPTIONS)
ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
	@$(HOSTCC) -g -o $(GCOV_EXTRACTION_BIN) $(GCOV_EXTRACTION_SRC)
ifeq (y, $(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_USE_REQUIRED_FILES_LIST))
	@$(GCOV_EXTRACTION_BIN) \
		$(DEP_FOLDER_NAME) \
		$(GCOV_EEPROM_BINARY) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILES) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILENAME) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILESIZE) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_REQUIRED_FILES_LIST_FILENAME)
else
	@$(GCOV_EXTRACTION_BIN) \
		$(DEP_FOLDER_NAME) \
		$(GCOV_EEPROM_BINARY) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILES) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILENAME) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILESIZE)
endif
	@$(MKDIR) -p $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_OUTPUT_DIR)
	@$(LCOV) --capture --directory $R/bin/$(DEP_FOLDER_NAME) --output-file $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO)
	@$(LCOV) --remove $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO) "$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_RTEMS_PATH)*" --output-file $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO)
	@$(LCOV_GENHTML) $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO) --output-directory $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_OUTPUT_DIR)
endif

euclid: $(TARGET)
	@echo " Running target $(TARGET)"
	@echo "RAM    $(RAM_INITIAL_ADDRESS) $(RAM_SIZE_IN_BYTES) RW" > $(VIP_MEMCONF)
	@echo "EEPROM0 0x10000000 0x200000 RWS" >> $(VIP_MEMCONF)
	@echo "EEPROM1 0x10200000 0x200000 RWS" >> $(VIP_MEMCONF)
ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
	@echo "$(GCOV_EEPROM) $(GCOV_STORAGE_ADDRESS) $(GCOV_STORAGE_SIZE) RWS" >> $(VIP_MEMCONF)
endif
	@echo "PROM    $(PROM_INITIAL_ADDRESS) $(PROM_SIZE_IN_BYTES) RW" >> $(VIP_MEMCONF)
	@echo "load $(SRECIMAGE)" > $(VIP_COMMANDS_FILE)
	@echo "reg pc 0x40000000" >> $(VIP_COMMANDS_FILE)
	@echo "reg npc 0x40000004" >> $(VIP_COMMANDS_FILE)
ifneq (,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_EXTRA_COMMANDS))
	@echo '$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_EXTRA_COMMANDS)' >> $(VIP_COMMANDS_FILE)
endif
	@echo "run 0x40000000" >> $(VIP_COMMANDS_FILE)
	@$(LEON2VIP) $(VIP_OPTIONS)
ifeq (y,$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_WITH_GCOV))
	@$(HOSTCC) -g -o $(GCOV_EXTRACTION_BIN) $(GCOV_EXTRACTION_SRC)
ifeq (y, $(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_USE_REQUIRED_FILES_LIST))
	@$(GCOV_EXTRACTION_BIN) \
		$(DEP_FOLDER_NAME) \
		$(GCOV_EEPROM_BINARY) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILES) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILENAME) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILESIZE) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_REQUIRED_FILES_LIST_FILENAME)
else
	@$(GCOV_EXTRACTION_BIN) \
		$(DEP_FOLDER_NAME) \
		$(GCOV_EEPROM_BINARY) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILES) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILENAME) \
		$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_GCOV_MAX_FILESIZE)
endif
	@$(MKDIR) -p $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_OUTPUT_DIR)
	@$(LCOV) --capture --directory $R/bin/$(DEP_FOLDER_NAME) --output-file $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO)
	@$(LCOV) --remove $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO) "$(CONFIG_PLT_RTEMSAPI_4_8_IMPR_RTEMS_4_8_IMPR_SPARC_V8_GCC_4_X_LEON_2_LEON2VIP_1_X_V1_RTEMS_PATH)*" --output-file $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO)
	@$(LCOV_GENHTML) $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_COVERAGE_INFO) --output-directory $R/bin/$(DEP_FOLDER_NAME)/$(LCOV_OUTPUT_DIR)
endif

