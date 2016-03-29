/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <cinamo/String.h>
#include "OptionParser.h"
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
		if(!cinamo::startsWith(current, "--")){
			left.push_back(current);
			continue;
		}
		current = current.substr(2);
		bool parsed = false;
		for(std::vector<Option*>::const_iterator it = this->opts.begin(); it != opts.end(); ++it){
			Option* const opt = *it;
			if(Option::Normal == opt->type() && current != opt->name()){
				continue;
			}else if(Option::Prefix == opt->type() && !cinamo::startsWith(current, opt->name())){
				continue;
			}
			// 次の引数の有無
			bool haveArgument = i != argc-1 && !cinamo::startsWith(argv[i+1], "--");
			if(!haveArgument && Option::Require == opt->argument() ){ //かつ引数必須
				throw logging::Exception(__FILE__, __LINE__, "You need an argument for %s", current.c_str());
			}

			if(haveArgument){
				if(opt->argument() != Option::No){
					const std::string opt_str(argv[++i]);
					opt->invoke(current, &opt_str);
				}else{
					opt->invoke(current, 0);
				}
			}else{
				opt->invoke(current, 0);
			}
		}
		if(!parsed){
			left.push_back(current);
		}
	}
}

Option::Option(std::string const& name, enum Type t, enum Argument a)
{
	this->name(name);
	this->type(t);
	this->argument(a);
}
Option::~Option(){

}

}}
