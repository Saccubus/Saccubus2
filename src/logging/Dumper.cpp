/*
 * Dumper.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "Logging.h"
#include <sstream>

namespace logging
{
using std::tr1::shared_ptr;

Dumper::Dumper(std::ostream& stream)
: indent(0), stream(stream)
{
	// TODO Auto-generated constructor stub

}

Dumper::~Dumper()
{
	// TODO Auto-generated destructor stub
}

void Dumper::printName(const std::string& name)
{
	this->startLine();
	stream << "<<" << name << ">>" << std::endl;
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
void Dumper::print(const std::string& name, const int member)
{
	this->startLine();
	stream << name << ":" << member << std::endl;
}
void Dumper::printNode(const std::string& name, shared_ptr<const Dumpable>& member)
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
void Dumper::printNodeList(const std::string& name, std::vector<shared_ptr<const Dumpable> >& memberList)
{
	std::stringstream ss;
	int i=0;
	this->startLine();
	stream << name << ":" << std::endl;
	in();
	for(std::vector<shared_ptr<const Dumpable> >::const_iterator member=memberList.begin(); member != memberList.end(); ++member, i++){
		std::tr1::shared_ptr<const Dumpable> item = *member;
		ss.str("");
		ss << "[" << i << "]";
		printNode(ss.str(), item);
	}
	out();
}
void Dumper::printNodeList(const std::string& name, std::map<std::string, std::tr1::shared_ptr<const Dumpable> >& memberList)
{
	this->startLine();
	stream << name << ":" << std::endl;
	in();
	for(std::map<std::string, shared_ptr<const Dumpable> >::const_iterator member=memberList.begin();member != memberList.end();++member){
		shared_ptr<const Dumpable> item = member->second;
		printNode(member->first, item);
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


} /* namespace logging */
