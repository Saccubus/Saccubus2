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

#ifndef NEKOMATA_PARSER_H_
#define NEKOMATA_PARSER_H_
#include <nekomata/classdefs.h>
#include <tr1/memory>
#include <iostream>

namespace nekomata {
namespace parser {

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
	std::tr1::shared_ptr<const tree::Node> parseProgram();
};


}}
#endif /* NEKOMATA_PARSER_H_ */
