#
#  Saccubus
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
ADD_LIBRARY(nekomata ${nekomata_lib_SRCS})

# antlr3cライブラリ
find_package (ANTLR3C REQUIRED)
include_directories(${ANTLR3C_INCLUDE_DIRS})
target_link_libraries (nekomata-cli ${ANTLR3C_LIBRARIES})

# unicodeライブラリ
find_package (ICU REQUIRED)
include_directories(${ICU_INCLUDE_DIRS})
target_link_libraries (nekomata-cli ${ICU_LIBRARIES})


