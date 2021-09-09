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

# PROTECTED REGION ID(edroomtc_slib_common_src) ENABLED START

SRCS+=$(wildcard $(SWPACKAGE_FOLDER_NAME)/src/*.cpp)

# PROTECTED REGION END

# It is also possible to perform a selective compilation of source files 
# depending on the platform for which the resource is compiled by using
# the flags defined by the framework at configuration time. These flags have a
# known syntax.


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

