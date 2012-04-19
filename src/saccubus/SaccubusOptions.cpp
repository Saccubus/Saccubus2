/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SaccubusOptions.h"

namespace saccubus {
LoglevelOption::LoglevelOption(const std::string& name, logging::Logger::Level level, logging::Logger::Level* stored)
:Option(name, util::Option::Normal, util::Option::No)
,level(level)
,stored(stored)
{

}
LoglevelOption::~LoglevelOption()
{

}
void LoglevelOption::invoke(const std::string& name, const std::string* arg)
{
	*stored = level;
}

FuncOption::FuncOption(const std::string& name, Func func)
:Option(name, util::Option::Normal, util::Option::No)
,func(func)
{
}
FuncOption::~FuncOption()
{

}
void FuncOption::invoke(const std::string& name, const std::string* arg)
{
	func();
}


}
