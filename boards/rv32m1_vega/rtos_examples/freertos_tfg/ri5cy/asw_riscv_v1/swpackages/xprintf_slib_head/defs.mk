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
# redefined by the different packages as they are included.

# PROTECTED REGION ID(xprintf_slib_common_src) ENABLED START

SRCS+=

# PROTECTED REGION END

# It is also possible to perform a selective compilation of source files 
# depending on the platform for which the resource is compiled by using
# the flags defined by the framework at configuration time. These flags have a
# known syntax.

ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_6), y)
ifeq ($(CONFIG_OS_RTEMS_4_6_5), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_6_RTEMS_4_6_5_any_any_any

# PROTECTED REGION ID(xprintf_slib_rtemsapi_4_6_rtems_4_6_5_any_any_any) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_6/rtems_4_6_5/*.c)

# PROTECTED REGION END

endif
endif
ifeq ($(CONFIG_OSAPI_POSIX_V13), y)
ifeq ($(CONFIG_OS_LINUX_2_6), y)
# List of files to compile for the supported platform
# POSIX_v13_Linux_2_6_any_any_any

# PROTECTED REGION ID(xprintf_slib_posix_v13_linux_2_6_any_any_any) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/posix_v13/linux_2_6/*.c)

# PROTECTED REGION END

endif
endif
ifeq ($(CONFIG_OSAPI_RTEMSAPI_4_8_IMPR), y)
ifeq ($(CONFIG_OS_RTEMS_4_8_IMPR), y)
# List of files to compile for the supported platform
# RTEMSAPI_4_8_impr_RTEMS_4_8_impr_any_any_any

# PROTECTED REGION ID(xprintf_slib_rtemsapi_4_8_impr_rtems_4_8_impr_any_any_any) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/rtemsapi_4_8_impr/rtems_4_8_impr/*.c)

# PROTECTED REGION END

endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_V1), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_v1_any_any_any

# PROTECTED REGION ID(xprintf_slib_pbootapi_v1_pboot_v1_any_any_any) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_v1/*.c)

# PROTECTED REGION END

endif
endif
ifeq ($(CONFIG_OSAPI_PBOOTAPI_V1), y)
ifeq ($(CONFIG_OS_PBOOT_EUCLID_V1), y)
# List of files to compile for the supported platform
# pbootapi_v1_pboot_euclid_v1_any_any_any

# PROTECTED REGION ID(xprintf_slib_pbootapi_v1_pboot_euclid_v1_any_any_any) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/pbootapi_v1/pboot_euclid_v1/*.c)

# PROTECTED REGION END

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

