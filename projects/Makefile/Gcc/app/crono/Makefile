########################################################################
# Copyright (c) 1988-2018 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: Makefile
#
# Author: $author$
#   Date: 8/8/2018
#
# generic Gcc Makefile for crono Executable crono
########################################################################


#
# target
#
crono_exe_EXETARGET = crono

########################################################################

#
# user c++ flags
#
crono_exe_USRCXXFLAGS += \
${crono_USRCXXFLAGS} \

#
# user defines
#
crono_exe_USRDEFINES += \
${crono_USRDEFINES} \

#
# user includes
#
crono_exe_USRINCLUDES += \
${crono_USRINCLUDES} \

#
# user libdirs
#
crono_exe_USRLIBDIRS += \
${crono_USRLIBDIRS} \

########################################################################

#
# Executable .c sources
#
#crono_exe_EXE_C_SOURCES += \
#${CRONO_SRC}/crono/base/Base.c \

#
# Executable .cc sources
#
#crono_exe_EXE_CC_SOURCES += \
#${CRONO_SRC}/crono/base/Base.cc \

#
# Executable .cxx sources
#
#crono_exe_EXE_CXX_SOURCES += \
#${CRONO_SRC}/crono/base/Base.cxx \

#
# Executable .cpp sources
#
crono_exe_EXE_CPP_SOURCES += \
${CRONO_SRC}/xos/logger/interface.cpp \
${CRONO_SRC}/xos/console/logger.cpp \
${CRONO_SRC}/xos/app/console/crono/main.cpp \

#
# Executable .m sources
#
#crono_exe_EXE_M_SOURCES += \
#${CRONO_SRC}/crono/base/Base.m \

#
# Executable .mm sources
#
#crono_exe_EXE_MM_SOURCES += \
#${CRONO_SRC}/crono/base/Base.mm \


########################################################################

#
# Executable libraries
#
crono_exe_LIBS += \
${crono_LIBS}



