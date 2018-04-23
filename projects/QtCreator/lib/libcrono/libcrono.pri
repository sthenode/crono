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
#   File: libcrono.pri
#
# Author: $author$
#   Date: 4/9/2018
#
# QtCreator .pri file for crono library libcrono
########################################################################

########################################################################
# libcrono

# libcrono TARGET
#
libcrono_TARGET = crono
libcrono_TEMPLATE = lib
libcrono_CONFIG += staticlib

# libcrono INCLUDEPATH
#
libcrono_INCLUDEPATH += \
$${crono_INCLUDEPATH} \

# libcrono DEFINES
#
libcrono_DEFINES += \
$${crono_DEFINES} \

########################################################################
# libcrono OBJECTIVE_HEADERS
#
#libcrono_OBJECTIVE_HEADERS += \
#$${CRONO_SRC}/crono/base/Base.hh \

# libcrono OBJECTIVE_SOURCES
#
#libcrono_OBJECTIVE_SOURCES += \
#$${CRONO_SRC}/crono/base/Base.mm \

########################################################################
# libcrono HEADERS
#
libcrono_HEADERS += \
$${CRONO_SRC}/xos/lib/crono/version.hpp \

# libcrono SOURCES
#
libcrono_SOURCES += \
$${CRONO_SRC}/xos/lib/crono/version.cpp \

########################################################################



