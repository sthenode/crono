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
#   File: crono.pro
#
# Author: $author$
#   Date: 4/9/2018
#
# QtCreator .pro file for crono executable crono
########################################################################
include(../../../../../build/QtCreator/crono.pri)
include(../../../../QtCreator/crono.pri)
include(../../crono.pri)
include(../../../../QtCreator/app/crono/crono.pri)

TARGET = $${crono_exe_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${crono_exe_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${crono_exe_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${crono_exe_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
SOURCES += \
$${crono_exe_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${crono_exe_HEADERS} \

# SOURCES
#
SOURCES += \
$${crono_exe_SOURCES} \
$${OBJECTIVE_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${crono_exe_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${crono_exe_LIBS} \
$${FRAMEWORKS} \


