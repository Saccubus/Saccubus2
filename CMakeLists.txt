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
project (SACCUBUS)

#Main src directory
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules ${CMAKE_MODULE_PATH})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE saccubus_base_SRCS ${SRC_DIR}/saccubus/*.cpp)

#ソースフォルダの設定
file(GLOB_RECURSE saccubus_cli_SRCS ${SRC_DIR}/entry_points/cli/*.cpp)
file(GLOB_RECURSE saccubus_ffmpeg_SRCS ${SRC_DIR}/entry_points/ffmpeg/*.cpp)
file(GLOB_RECURSE saccubus_test_SRCS ${SRC_DIR}/entry_points/test/*.cpp)

#実行バイナリ
add_executable(SaccubusCLI ${saccubus_base_SRCS} ${saccubus_cli_SRCS})
add_library(Saccubus SHARED ${saccubus_base_SRCS} ${saccubus_ffmpeg_SRCS})
SET_TARGET_PROPERTIES(Saccubus PROPERTIES PREFIX "")

find_package(PkgConfig)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
target_link_libraries(SaccubusCLI ${LIBXML2_LIBRARIES})
target_link_libraries(Saccubus ${LIBXML2_LIBRARIES})
add_definitions(${LIBXML2_DEFINITIONS})

find_package(Python REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYRHON_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${PYTHON_LIBRARIES})
target_link_libraries(Saccubus ${PYTHON_LIBRARIES})

pkg_check_modules(CAIRO REQUIRED cairo)
include_directories(${CAIRO_INCLUDE_DIRS})
link_directories(${CAIRO_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${CAIRO_LIBRARIES})
target_link_libraries(Saccubus ${CAIRO_LIBRARIES})

pkg_check_modules(FREETYPE REQUIRED freetype2)
include_directories(${FREETYPE_INCLUDE_DIRS})
link_directories(${FREETYPE_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${FREETYPE_LIBRARIES})
target_link_libraries(Saccubus ${FREETYPE_LIBRARIES})

pkg_check_modules(FONTCONFIG REQUIRED fontconfig)
include_directories(${FONTCONFIG_INCLUDE_DIRS})
link_directories(${FONTCONFIG_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${FONTCONFIG_LIBRARIES})
target_link_libraries(Saccubus ${FONTCONFIG_LIBRARIES})

pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${SDL2_LIBRARIES})
target_link_libraries(Saccubus ${SDL2_LIBRARIES})

#######################################################################################################################

# ねこまた
find_package (Nekomata REQUIRED)
include_directories(${NEKOMATA_INCLUDE_DIR})
target_link_libraries(SaccubusCLI ${NEKOMATA_LIBRARIES})
target_link_libraries(Saccubus ${NEKOMATA_LIBRARIES})

# [ねこまた] antlr3cライブラリ
find_package (ANTLR3C REQUIRED)
include_directories(${ANTLR3C_INCLUDE_DIRS})
target_link_libraries(SaccubusCLI ${ANTLR3C_LIBRARIES})
target_link_libraries(Saccubus ${ANTLR3C_LIBRARIES})

# [ねこまた] Unicodeライブラリ
pkg_check_modules(ICUUC REQUIRED "icu-uc")
include_directories(${ICUUC_INCLUDE_DIRS})
link_directories(${ICUUC_LIBRARY_DIRS})
target_link_libraries(SaccubusCLI ${ICUUC_LIBRARIES})
target_link_libraries(Saccubus ${ICUUC_LIBRARIES})

find_package(GTest)
if (GTEST_FOUND)
	#enable_testing()
	#ADD_EXECUTABLE(SaccubusTest ${saccubus_base_SRCS} ${saccubus_test_SRCS})
	#include_directories(${GTEST_INCLUDE_DIRS})
	#target_link_libraries(SaccubusTest ${GTEST_BOTH_LIBRARIES})
	#add_test(AllTests SaccubusTest)
	#target_link_libraries(SaccubusTest ${LIBXML2_LIBRARIES})
	#target_link_libraries(SaccubusTest ${PYTHON_LIBRARIES})
	#target_link_libraries(SaccubusTest ${CAIRO_LIBRARIES})
	#target_link_libraries(SaccubusTest ${FREETYPE_LIBRARIES})
	#target_link_libraries(SaccubusTest ${FONTCONFIG_LIBRARIES})
	#target_link_libraries(SaccubusTest ${ICU_UC_LIBRARIES})
	#target_link_libraries(SaccubusTest ${SDL_LIBRARY})
	#target_link_libraries(SaccubusTest ${ANTLR3C_LIBRARIES})
	#target_link_libraries(SaccubusTest ${NEKOMATA_LIBRARIES})
endif()



