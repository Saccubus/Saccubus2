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

#include <nekomata/trans/NicosTrans.h>
#include <nekomata/logging/Exception.h>
#include <string>
#include <vector>
#include "DefaultAction.h"
#include "ButtonAction.h"
#include "NicosMessageLexer.h"
#include "NicosMessageParser.h"

namespace nekomata {
namespace trans {

class Impl
{
public:
	pANTLR3_INPUT_STREAM stream;
	pNicosMessageLexer lexer;
	pANTLR3_COMMON_TOKEN_STREAM tokenStream;
	pNicosMessageParser parser;
public:
	Impl(const std::string& str)
	:stream(0), lexer(0), tokenStream(0), parser(0){
		stream = antlr3StringStreamNew((pANTLR3_UINT8)str.c_str(), ANTLR3_ENC_UTF8, str.size(), (pANTLR3_UINT8)"Nicos");
		if(!stream){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create ANTLR3 String Stream.");
		}
		this->lexer = NicosMessageLexerNew(this->stream);
		if(!this->lexer){
			throw logging::Exception(__FILE__, __LINE__, "Failed to read stream ");
		}
		this->tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
		if(!this->tokenStream){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create token stream");
		}
		this->parser = NicosMessageParserNew(tokenStream);
		if(!this->parser){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create parser");
		}
	}
	~Impl(){
		if(stream){
			stream->free(stream);
			stream = 0;
		}
		if(lexer){
			lexer->free(lexer);
			lexer = 0;
		}
		if(tokenStream){
			tokenStream->free(tokenStream);
			tokenStream = 0;
		}
		if(parser){
			parser->free(parser);
			parser = 0;
		}
	}
public:
	std::vector<std::string> parse(){
		return parser->script(parser);
	}
};

#define DEF_ACTION(cmd, shouldBeOwner, shouldBePremium, clazz)\
	if(front==cmd && (shouldBeOwner ? isOwner : true) && (shouldBePremium ? isPremium : true) ) return clazz(vpos, mail, tokens).trans();

std::string toNiwango(const float vpos, const std::string& mail, const std::string& message, bool isOwner, bool isPremium)
{
	std::vector<std::string> tokens = Impl(message).parse();
	if(tokens.size() > 0){
		std::string front = tokens.front();
		tokens.erase(tokens.begin());
		DEF_ACTION("＠ボタン", true, true, ButtonAction);
		DEF_ACTION("＠デフォルト", false, false, DefaultAction);
	}
	return "";
}

}}
