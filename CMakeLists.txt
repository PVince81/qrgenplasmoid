cmake_minimum_required (VERSION 2.6)
project (qrgenplasmoid) 

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

INCLUDE(FindQt4)
INCLUDE(FindQREncode)

OPTION(DEVELOPMENT_MODE "Debug mode" ON)
IF(DEVELOPMENT_MODE)
  ADD_DEFINITIONS(-DDEBUG)
ENDIF(DEVELOPMENT_MODE)

# TODO: option to enable/disable standalone and plasmoid build

# Add debug symbols
SET(CMAKE_CXX_FLAGS "-g -Wall")

find_package(Qt4 REQUIRED)
find_package(QREncode REQUIRED)

SUBDIRS (src)

