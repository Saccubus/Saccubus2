/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <nekomata/classdefs.h>
#include <memory>
#include <iostream>

namespace nekomata {
namespace parser {

class ParserImpl;
class Parser
{
private:
	/* Pimplイディオムで、ANTLR3のヘッダを隔離しています */
	std::shared_ptr<ParserImpl> impl;
	explicit Parser(std::shared_ptr<ParserImpl> impl);
public:
	~Parser();
	static std::shared_ptr<Parser> fromFile(const std::string& filename);
	static std::shared_ptr<Parser> fromString(const std::string& src, const std::string& filename="<ON MEMORY>", int line=0);
	static std::shared_ptr<Parser> fromStream(std::istream& stream_, const std::string& filename);
	std::shared_ptr<const tree::Node> parseProgram();
};


}}

