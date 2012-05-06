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
find_path(ICU_INCLUDE_DIRS NAMES unicode/unistr.h)
find_library(ICU_LIBRARIES NAMES icuuc)
INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ICU DEFAULT_MSG ICU_LIBRARIES ICU_INCLUDE_DIRS)

