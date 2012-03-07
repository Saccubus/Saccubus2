/*
 * Parser.h
 *
 *  Created on: 2012/02/28
 *      Author: psi
 */

#ifndef PARSER_H_
#define PARSER_H_

namespace nekomata {
namespace parser {
#include "../classdefs.h"
#include <tr1/memory>
#include <iostream>

class ParserImpl;
class Parser
{
private:
	/* Pimplイディオムで、ANTLR3のヘッダを隔離しています */
	std::tr1::shared_ptr<ParserImpl> impl;
	explicit Parser(std::tr1::shared_ptr<ParserImpl> impl);
public:
	~Parser();
	static std::tr1::shared_ptr<Parser> fromFile(const std::string& filename);
	static std::tr1::shared_ptr<Parser> fromString(const std::string& src, const std::string& filename="<ON MEMORY>");
	static std::tr1::shared_ptr<Parser> fromStream(std::istream& stream_, const std::string& filename);
	void parseTimeline(TimeLine<const tree::ExprNode>& scriptLine, TimeLine<const system::Comment>& commentLine);
	std::tr1::shared_ptr<const tree::ExprNode> parseProgram();
};


}}
#endif /* PARSER_H_ */
