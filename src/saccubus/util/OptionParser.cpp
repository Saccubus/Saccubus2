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

#include "OptionParser.h"
#include "StringUtil.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace util {

OptionParser::OptionParser() {
	// TODO Auto-generated constructor stub

}

OptionParser::~OptionParser() {
	for(std::vector<Option*>::const_iterator it = this->opts.begin(); it != opts.end(); ++it){
		delete *it;
	}
}

void OptionParser::add(Option* opt)
{
	this->opts.push_back(opt);
}

void OptionParser::parse(int argc, char** argv, std::vector<std::string>& left)
{
	for(int i = 0; i < argc; ++i){
		std::string current(argv[i]);
		if(!util::startsWith(current, "--")){
			left.push_back(current);
			continue;
		}
		current = current.substr(2);
		bool parsed = false;
		for(std::vector<Option*>::const_iterator it = this->opts.begin(); it != opts.end(); ++it){
			Option* const opt = *it;
			if(Option::Normal == opt->type() && current != opt->name()){
				continue;
			}else if(Option::Prefix == opt->type() && !util::startsWith(current, opt->name())){
				continue;
			}
			// 次の引数の有無
			bool haveArgument = i != argc-1 || !util::startsWith(argv[i+1], "--");
			if(!haveArgument && Option::Require == opt->argument() ){ //かつ引数必須
				throw logging::Exception(__FILE__, __LINE__, "You need an argument for %s", current.c_str());
			}

			if(haveArgument){
				const std::string opt_str(argv[++i]);
				opt->invoke(current, &opt_str);
			}else{
				opt->invoke(current, 0);
			}
		}
		if(!parsed){
			left.push_back(current);
		}
	}
}

Option::Option(const std::string& name, enum Type t, enum Argument a)
{
	this->name(name);
	this->type(t);
	this->argument(a);
}
Option::~Option(){

}

}}
