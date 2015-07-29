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

include_directories (./)

install(FILES
  qttvdb.h
  qttvdb_export.h
  QtTvDB
  DESTINATION ${INCLUDE_INSTALL_DIR}/qttvdb
  COMPONENT devel
)

set (qttvdb_SRCS mirrors.cpp episode.cpp banner.cpp show.cpp)

qt5_wrap_cpp(MOC_SRCS qttvdb.h)

if (UNIX)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/qttvdb.h
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/qttvdbmoc.py
    ${CMAKE_CURRENT_SOURCE_DIR}/qttvdb.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/qttvdb.h
    DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/qttvdbmoc.py
    ${CMAKE_CURRENT_SOURCE_DIR}/qttvdb.h.in
    )
endif ()

add_library (qttvdb SHARED ${MOC_SRCS} ${qttvdb_SRCS})
target_link_libraries( qttvdb Qt5::Core)

set_target_properties(qttvdb PROPERTIES
                      VERSION ${QTTVDB_LIB_MAJOR_VERSION}.${QTTVDB_LIB_MINOR_VERSION}.${QTTVDB_LIB_PATCH_VERSION}
                      SOVERSION ${QTTVDB_LIB_MAJOR_VERSION}
                      DEFINE_SYMBOL QTTVDB_MAKEDLL
                      )

install(TARGETS qttvdb
  COMPONENT libraries
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)
