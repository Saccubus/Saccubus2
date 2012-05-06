#
#  Nekomata
#  Copyright (C) 2012 psi
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8)
project (NEKOMATA)

SET(CMAKE_C_COMPILER g++)

#Main src directory
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules ${CMAKE_MODULE_PATH})
SET(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
SET(INC_DIR ${CMAKE_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(${INC_DIR})
FILE(GLOB_RECURSE nekomata_lib_SRCS ${SRC_DIR}/nekomata/*.cpp ${SRC_DIR}/nekomata/*.c)
FILE(GLOB_RECURSE nekomata_cli_SRCS ${SRC_DIR}/cli/*.cpp ${SRC_DIR}/cli/*.c)

ADD_EXECUTABLE(nekomata-cli ${nekomata_lib_SRCS} ${nekomata_cli_SRCS})
SET_TARGET_PROPERTIES(nekomata-cli PROPERTIES OUTPUT_NAME nekomata)
ADD_LIBRARY(nekomata STATIC ${nekomata_lib_SRCS})
SET_TARGET_PROPERTIES(nekomata PROPERTIES COMPILE_FLAGS -fPIC)

find_package(PkgConfig)

# antlr3cライブラリ
find_package (ANTLR3C REQUIRED)
include_directories(${ANTLR3C_INCLUDE_DIRS})
target_link_libraries (nekomata-cli ${ANTLR3C_LIBRARIES})

# unicode
pkg_check_modules(ICU_UC REQUIRED icu-uc)
include_directories(${ICU_UC_INCLUDE_DIRS})
link_directories(${ICU_UC_LIBRARY_DIRS})
target_link_libraries (nekomata-cli ${ICU_UC_LIBRARIES})

# install target
INSTALL(
	TARGETS nekomata-cli nekomata
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
INSTALL( DIRECTORY ${INC_DIR}/nekomata DESTINATION "include")

# uninstall target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


