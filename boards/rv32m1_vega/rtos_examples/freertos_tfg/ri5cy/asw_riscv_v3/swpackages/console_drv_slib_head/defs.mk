# Label SRCS contains a list of all the source files that are to be compiled
# following the rules specifies by the chosen platform. All the source files
# included in this list are going to be compiled and linked to create the
# project executable. A common example of use for this label would be:
# 
# SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/*.c)
# SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/*.cpp)
# 
# The previous line would include in the list all the source files contained
# in the source root folder.

# SWPACKAGE_FOLDER_NAME defines the name of the folder that will be used to
# link the package in a specific project. This variable can ONLY be used
# in substitutions when adding items to the SRCS label, since it will be
# redefined by the different packages as tFhey are included.

# PROTECTED REGION ID(console_drv_slib_common_src) ENABLED START

SRCS+=

# PROTECTED REGION END

# It is also possible to perform a selective compilation of source files 
# depending on the platform for which the resource is compiled by using
# the flags defined by the framework at configuration time. These flags have a
# known syntax.

ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_LEON2VIP_1_X), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_Leon2ViP_1_x

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_leon2vip_1_x) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/leon2vip_1_x/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_TSIM_LEON2_2_X), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_TSIM_LEON2_2_x

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_tsim_leon2_2_x) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/tsim_leon2_2_x/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_3), y)
ifeq ($(CONFIG_BOARD_TSIM_LEON3_2_X), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_3_TSIM_LEON3_2_x

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_3_tsim_leon3_2_x) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_3/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_3/tsim_leon3_2_x/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_SRG_A3P_V2_0), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_srg_a3p_v2_0

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_srg_a3p_v2_0) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/srg_a3p_v2_0/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_CDPU_V1), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_cdpu_v1

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_cdpu_v1) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/cdpu_v1/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_EMULATOR_CDPU_A3P_V2_FPGA_V5_4), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_emulator_cdpu_a3p_v2_fpga_v5_4

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_emulator_cdpu_a3p_v2_fpga_v5_4) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/emulator_cdpu_a3p_v2_fpga_v5_4/*.c)


# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_V1), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_EMULATOR_CDPU_A3P_V2_FPGA_V5_4), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_v1_SPARC_v8_LEON_2_emulator_cdpu_a3p_v2_fpga_v5_4

# PROTECTED REGION ID(console_drv_slib_pbootapi_v1_pboot_v1_sparc_v8_leon_2_emulator_cdpu_a3p_v2_fpga_v5_4) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/emulator_cdpu_a3p_v2_fpga_v5_4/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_V1), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_LEON2VIP_1_X), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_v1_SPARC_v8_LEON_2_Leon2ViP_1_x

# PROTECTED REGION ID(console_drv_slib_pbootapi_v1_pboot_v1_sparc_v8_leon_2_leon2vip_1_x) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/leon2vip_1_x/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_V1), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_CDPU_V1), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_v1_SPARC_v8_LEON_2_cdpu_v1

# PROTECTED REGION ID(console_drv_slib_pbootapi_v1_pboot_v1_sparc_v8_leon_2_cdpu_v1) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/sparc_v8/leon_2/cdpu_v1/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_EUCLID_V1), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_CDPU_EUCLID_V1), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_euclid_v1_SPARC_v8_LEON_2_cdpu_euclid_v1

# PROTECTED REGION ID(console_drv_slib_pbootapi_v1_pboot_euclid_v1_sparc_v8_leon_2_cdpu_euclid_v1) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_euclid_v1/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_euclid_v1/sparc_v8/leon_2/cdpu_euclid_v1/*.c)

# PROTECTED REGION END

endif
endif
endif
endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_MP_LEON_2), y)
ifeq ($(CONFIG_BOARD_CDPU_EUCLID_V1), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_SPARC_v8_LEON_2_cdpu_euclid_v1

# PROTECTED REGION ID(console_drv_slib_rtemsapi_4_8_impr_rtems_4_8_impr_sparc_v8_leon_2_cdpu_euclid_v1) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/*.c)
SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/sparc_v8/leon_2/cdpu_euclid_v1/*.c)


# PROTECTED REGION END

endif
endif
endif
endif
endif

# It is also possible to create one or more targets to be executed before the
# compilation process. These targets should be included in the list:
# ALT_TARGETS+=

# Also, all the usual compilation and linking flags, like CFLAGS or LDFLAGS are
# available to be used. If you want to set an specific set of compilation flags
# for a certain number of source files, you should define the targets for those
# files in this very file, so that the framework will not use the default ones.

# All the configuration parameters defined for the resource can be used as
# flags for a conditional compilation. A parameter name called PARAMETER_NAME
# defines a label named CONFIG_PARAMETER_NAME whose value can be checked.

