# Copyright (C) 2009-2011 Corentin Chary <corentin.chary@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public License
# along with this library; see the file COPYING.LIB.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.

PROJECT(qttvdb)

#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

# Stop cmake 2.6 from whining
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
IF(COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

# compile in debug mode
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
  ADD_DEFINITIONS("-DQT_NO_DEBUG_OUTPUT")
  ADD_DEFINITIONS("-DQT_NO_DEBUG_OUTPUT")
ENDIF("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")

# Find Qt4
FIND_PACKAGE( Qt4 REQUIRED )

#add extra search paths for libraries and includes
SET (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
SET (LIB_INSTALL_DIR "lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
SET (BIN_INSTALL_DIR "bin" CACHE STRING "Directory where bin will install")
SET (INCLUDE_INSTALL_DIR "include" CACHE PATH "The directory the headers are installed in")
SET (CMAKE_MODULES_INSTALL_DIR "share/apps/cmake/modules" CACHE PATH "The directory to install FindQtTvDB.cmake to")


set(QTTVDB_LIB_MAJOR_VERSION "0")
set(QTTVDB_LIB_MINOR_VERSION "4")
set(QTTVDB_LIB_PATCH_VERSION "0")

set(QTTVDB_LIB_VERSION_STRING "${QTTVDB_LIB_MAJOR_VERSION}.${QTTVDB_LIB_MINOR_VERSION}.${QTTVDB_LIB_PATCH_VERSION}")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib${LIB_SUFFIX}" )

# pkg-config
IF (NOT WIN32)
  CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/QtTvDB.pc.in
                  ${CMAKE_CURRENT_BINARY_DIR}/QtTvDB.pc
                  @ONLY)
  INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/QtTvDB.pc
           DESTINATION lib${LIB_SUFFIX}/pkgconfig
	   COMPONENT devel)
ENDIF (NOT WIN32)

# Include the cmake file needed to use qt4
IF (QTTVDB_BUILD_EXAMPLES)
  set(QT_USE_QTNETWORK TRUE)
ENDIF()
set(QT_DONT_USE_QTGUI TRUE)
set(QT_USE_QTXML TRUE)
INCLUDE( ${QT_USE_FILE} )

# Subdirs
ADD_SUBDIRECTORY(src)
IF (QTTVDB_BUILD_EXAMPLES)
  ADD_SUBDIRECTORY(examples)
ENDIF ()

add_subdirectory(cmake/modules)

# CPack
set(CPACK_VERSION_MAJOR ${QTTVDB_LIB_MAJOR_VERSION})
set(CPACK_VERSION_MINOR ${QTTVDB_LIB_MINOR_VERSION})
set(CPACK_VERSION_PATCH ${QTTVDB_LIB_PATCH_VERSION})
set(CPACK_VERSION ${QTTVDB_LIB_VERSION_STRING})
set(CPACK_PACKAGE_VERSION ${QTTVDB_LIB_VERSION_STRING})
set(CPACK_PACKAGE_CONTACT "Corentin Chary <corentin.chary@gmail.com>")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
#set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/INSTALL")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A library for using thetvdb.com XML API in Qt")
set(CPACK_PACKAGE_VENDOR "http://xf.iksaif.net/dev/qttvdb.html")
set(CPACK_SOURCE_IGNORE_FILES
  "~$"
  "^${PROJECT_SOURCE_DIR}/\\\\.git"
  "^${PROJECT_SOURCE_DIR}/build/")
#set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BUILD_DIR};qttvdb;ALL;/")
set(CPACK_COMPONENTS_ALL libraries devel)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Library")
set(CPACK_COMPONENT_DEVEL_DISPLAY_NAME "Development files")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "A library for using thetvdb.com XML API in Qt")
set(CPACK_COMPONENT_DEVEL_DESCRIPTION "Development files for QtTvDB")
set(CPACK_COMPONENT_DEVEL_DEPENDS libraries)
set(CPACK_PACKAGE_FILE_NAME "qttvdb-${CPACK_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "qttvdb-${CPACK_VERSION}")

if(NOT WIN32)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")
  ## Debian specific ##
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-core (>= 4.6), libqt4-xml (>= 4.6)")
  set(CPACK_DEBIAN_PACKAGE_BUILDS_DEPENDS "libqt4-dev (>= 4.6), cmake (>= 2.6)")
else()
  set(CPACK_GENERATOR "ZIP;NSIS")
  set(CPACK_SOURCE_GENERATOR "ZIP")
  set(CPACK_BINARY_CYGWIN "OFF")
  set(CPACK_SOURCE_CYGWIN "OFF")
  set(CPACK_PACKAGE_FILE_NAME "qttvdb-${CPACK_VERSION}-win32")
  set(CPACK_BINARY_NSIS "ON")
  set(CPACK_NSIS_MODIFY_PATH "OFF")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} QtTvDB")
  set(CPACK_NSIS_HELP_LINK "http://xf.iksaif.net/dev/qttvdb.html")
  set(CPACK_NSIS_URL_INFO_ABOUT "http://xf.iksaif.net/dev/qttvdb.html")
  set(CPACK_NSIS_CONTACT "Corentin Chary <corentin.chary@gmail.com>")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "qttvdb")
endif()

include(CPack)
