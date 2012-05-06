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

# 

pkg_check_modules(PC_PYTHON QUIET python3)
include_directories(${PC_PYTHON_INCLUDE_DIRS})
link_directories(${PC_PYTHON_LIBRARY_DIRS})

if(PC_PYTHON_FOUND)
	set(PYTHON_INCLUDE_DIRS ${PC_PYTHON_INCLUDE_DIRS})
	set(PYTHON_LIBRARY_DIRS ${PC_PYTHON_LIBRARY_DIRS})
	set(PYTHON_LIBRARIES ${PC_PYTHON_LIBRARIES})
else()
	find_path(PYTHON_INCLUDE_DIRS NAMES Python.h)
	find_library(PYTHON_LIBRARIES NAMES python32)
	INCLUDE(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(PYTHON DEFAULT_MSG PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)
endif()

#MARK_AS_ADVANCED(PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)

