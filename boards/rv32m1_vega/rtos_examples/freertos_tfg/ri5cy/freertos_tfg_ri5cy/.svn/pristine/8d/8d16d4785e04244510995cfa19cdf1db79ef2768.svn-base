# Label SRCS contains a list of all the source files that are to be compiled
# following the rules specifies by the chosen platform. All the source files
# included in this list are going to be compiled and linked to create the
# project executable. A common example of use for this label would be:
# 
# SRCS+=$(wildcard $(OSSWPACKAGE_FOLDER_NAME)/src/*.c)
# SRCS+=$(wildcard $(OSSWPACKAGE_FOLDER_NAME)/src/*.cpp)
# 
# The previous line would include in the list all the source files contained
# in the source root folder.

# OSSWPACKAGE_FOLDER_NAME defines the name of the folder that will be used to
# link the package in a specific project. This variable can ONLY be used
# in substitutions when adding items to the SRCS label, since it will be
# redefined by the different packages as they are included.

# PROTECTED REGION ID(rtems_common_src) ENABLED START

SRCS+=$(wildcard $(OSSWPACKAGE_FOLDER_NAME)/src/*.cpp)

# PROTECTED REGION END

# It is also possible to perform a selective compilation of source files 
# depending on the platform for which the resource is compiled by using
# the flags defined by the framework at configuration time. These flags have a
# known syntax.


ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_COMPILER_GCC_4_X), y)
ifeq ($(CONFIG_MP_LEON_2), y)
# List of files to compile for the supported platform
# SPARC_v8_GCC_4_x_LEON_2_any

# PROTECTED REGION ID(rtems_sparc_v8_gcc_4_x_leon_2_any) ENABLED START

SRCS+=

# PROTECTED REGION END

endif
endif
endif
ifeq ($(CONFIG_ARCH_SPARC_V8), y)
ifeq ($(CONFIG_COMPILER_GCC_4_X), y)
ifeq ($(CONFIG_MP_LEON_3), y)
# List of files to compile for the supported platform
# SPARC_v8_GCC_4_x_LEON_3_any

# PROTECTED REGION ID(rtems_sparc_v8_gcc_4_x_leon_3_any) ENABLED START

SRCS+=

# PROTECTED REGION END

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
