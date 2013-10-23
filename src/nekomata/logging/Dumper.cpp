/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <sstream>
#include <memory>
#include <assert.h>
#include <nekomata/logging/Logging.h>

#include "Dumpable.h"
#include "../tree/Location.h"

namespace nekomata{
namespace logging
{
using std::shared_ptr;

Dumper::Dumper(std::ostream& stream)
: indent(0), stream(stream)
{
}

Dumper::~Dumper()
{
}

void Dumper::printName(std::string const& name)
{
	this->startLine();
	stream << "<<" << name << ">>" << std::endl;
}
void Dumper::printName(std::string const& name, const tree::Location& loc)
{
	this->startLine();
	stream << "<<" << name << ">>" << " (pos: " << loc.getLineNo() << "," << loc.getColNo() << ")" << std::endl;
}
void Dumper::print(std::string const& name, std::string const& member)
{
	this->startLine();
	stream << name << ":" << member << std::endl;
}
void Dumper::print(std::string const& name, const bool member)
{
	this->startLine();
	stream << name << ":" << (member?"true":"false") << std::endl;
}
void Dumper::print(std::string const& name, const double member)
{
	this->startLine();
	stream << name << ":" << member << std::endl;
}
void Dumper::printDumpable(std::string const& name, const shared_ptr<const Dumpable> member)
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
void Dumper::printDumpableList(std::string const& name, const std::vector<shared_ptr<const Dumpable> >& memberList)
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
void Dumper::printDumpableList(std::string const& name, const std::map<std::string, shared_ptr<const Dumpable> >& memberList)
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
