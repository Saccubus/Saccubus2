/**
 * Nekomata
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

#include <sstream>
#include <tr1/memory>
#include <assert.h>
#include <nekomata/logging/Logging.h>

#include "Dumpable.h"
#include "../tree/Location.h"

namespace nekomata{
namespace logging
{
using std::tr1::shared_ptr;

Dumper::Dumper(std::ostream& stream)
: indent(0), stream(stream)
{
}

Dumper::~Dumper()
{
}

void Dumper::printName(const std::string& name)
{
	this->startLine();
	stream << "<<" << name << ">>" << std::endl;
}
void Dumper::printName(const std::string& name, const tree::Location& loc)
{
	this->startLine();
	stream << "<<" << name << ">>" << " (pos: " << loc.getLineNo() << "," << loc.getColNo() << ")" << std::endl;
}
void Dumper::print(const std::string& name, const std::string& member)
{
	this->startLine();
	stream << name << ":" << member << std::endl;
}
void Dumper::print(const std::string& name, const bool member)
{
	this->startLine();
	stream << name << ":" << (member?"true":"false") << std::endl;
}
void Dumper::print(const std::string& name, const double member)
{
	this->startLine();
	stream << name << ":" << member << std::endl;
}
void Dumper::printDumpable(const std::string& name, const shared_ptr<const Dumpable> member)
{
	this->startLine();
	if(member.get() == 0){
		stream << name << ": null" << std::endl;
	}else{
		stream << name << ":" << std::endl;
		this->in();
		member->dump(*this);
		this->out();
	}
}
void Dumper::printDumpableList(const std::string& name, const std::vector<shared_ptr<const Dumpable> >& memberList)
{
	std::stringstream ss;
	int i=0;
	this->startLine();
	stream << name << ":" << std::endl;
	in();
	for(std::vector<shared_ptr<const Dumpable> >::const_iterator member=memberList.begin(); member != memberList.end(); ++member, i++){
		shared_ptr<const Dumpable> item = *member;
		ss.str("");
		ss << "[" << i << "]";
		printDumpable(ss.str(), item);
	}
	out();
}
void Dumper::printDumpableList(const std::string& name, const std::map<std::string, shared_ptr<const Dumpable> >& memberList)
{
	this->startLine();
	stream << name << ":" << std::endl;
	in();
	for(std::map<std::string, shared_ptr<const Dumpable> >::const_iterator member=memberList.begin();member != memberList.end();++member){
		shared_ptr<const Dumpable> item = member->second;
		printDumpable(member->first, item);
	}
	out();
}
void Dumper::startLine()
{
	const int _indent = this->indent;
	for(int i=0;i<_indent;i++){
		stream << "    ";
	}
}
void Dumper::in()
{
	this->indent++;
}
void Dumper::out()
{
	this->indent--;
}


}}
