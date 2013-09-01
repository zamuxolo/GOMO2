###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.2 (1.9.0.2)
##
##  Author    : You Name <your@email.org>
##  Project   : My Project
##  FileName  : My Project.pro
##  Date      : 2013-08-16T20:19:16
##  License   : BSD
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : http://www.mydomain.org
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

TEMPLATE = app
LANGUAGE = C++/Qt4
TARGET = $$quote(My Project)
CONFIG *= debug_and_release
BUILD_PATH = ./build

CONFIG(debug, debug|release) {
    #Debug
    CONFIG *= console
    unix:TARGET = $$join(TARGET,,,_debug)
    else:TARGET = $$join(TARGET,,,d)
    unix:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/debug/.obj/mac
    UI_DIR = $${BUILD_PATH}/debug/.ui
    MOC_DIR = $${BUILD_PATH}/debug/.moc
    RCC_DIR = $${BUILD_PATH}/debug/.rcc
} else {
    #Release
    unix:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/release/.obj/mac
    UI_DIR = $${BUILD_PATH}/release/.ui
    MOC_DIR = $${BUILD_PATH}/release/.moc
    RCC_DIR = $${BUILD_PATH}/release/.rcc
}

SOURCES *= src/main.cpp

XUP.OTHERS_PLATFORM_TARGET_DEFAULT = My Project