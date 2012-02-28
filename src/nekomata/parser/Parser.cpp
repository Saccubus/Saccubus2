/*
 * Parser.cpp
 *
 *  Created on: 2012/02/28
 *      Author: psi
 */

#include "nekomata/parser/niwangoLexer.h"
#include "nekomata/parser/niwangoParser.h"
#include "Parser.h"
#include "../logging/Exception.h"
#include <iostream>
#include <sstream>
#include <tr1/memory>

namespace nekomata {
namespace parser {

class ParserImpl {
private:
	pANTLR3_INPUT_STREAM stream;
	std::string src;
	std::string filename;
	pniwangoLexer lexer;
	pANTLR3_COMMON_TOKEN_STREAM tokenStream;
	pniwangoParser parser;
private:
	void setup()
	{
		this->lexer = niwangoLexerNew(this->stream);
		if(!this->lexer){
			throw nekomata::logging::Exception(__FILE__, __LINE__, "Failed to read stream for %s", filename);
		}
		this->tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
		if(!this->tokenStream){
			throw nekomata::logging::Exception(__FILE__, __LINE__, "Failed to create token stream for %s", filename);
		}
		this->parser = niwangoParserNew(tokenStream);
		if(!this->parser){
			throw nekomata::logging::Exception(__FILE__, __LINE__, "Failed to create parser for %s", filename);
		}
	}
public:
	ParserImpl():stream(0), src(), filename(), lexer(0), tokenStream(0), parser(0){}
	virtual ~ParserImpl()
	{
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

	Parser& fromFile(const std::string& filename)
	{
		this->filename = filename;
		stream = antlr3FileStreamNew((ANTLR3_UINT8*)filename.c_str(), ANTLR3_ENC_UTF8);
		if(!stream){
			throw nekomata::logging::Exception(__FILE__, __LINE__, "Failed to create ANTLR3 File Stream for %s", filename.c_str());
		}
		setup();
		return *this;
	}
	Parser& fromString(const std::string& src, const std::string& filename="<ON MEMORY>")
	{
		this->src = src;
		this->filename = filename;
		stream = antlr3StringStreamNew((pANTLR3_UINT8)this->src.c_str(), ANTLR3_ENC_UTF8, this->filename.size(), (pANTLR3_UINT8)this->filename.c_str());
		if(!stream){
			throw nekomata::logging::Exception(__FILE__, __LINE__, "Failed to create ANTLR3 String Stream for %s", filename.c_str());
		}
		setup();
		return *this;
	}
	Parser& fromStream(std::istream& stream_, const std::string filename){
		std::stringstream ss;
		char buff[8192];
		while(1){
			stream_ >> buff;
			if(stream_.eof()){
				break;
			}
			ss << buff;
		}
		return fromString(ss.str(), filename);
	}
public:
	std::tr1::shared_ptr<nekomata::timeline::TimeLine> parseTimeline();
	std::tr1::shared_ptr<const ExprNode> parseProgram();
};

Parser::Parser(std::tr1::shared_ptr<ParserImpl> impl)
:impl(impl)
{
	if(!impl){
		throw nekomata::logging::Exception(__FILE__, __LINE__, "[BUG] Invalid parser impl pointer.");
	}
}
Parser::~Parser()
{
}
std::tr1::shared_ptr<Parser> Parser::fromFile(const std::string& filename)
{
	std::tr1::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromFile(filename);
	std::tr1::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::tr1::shared_ptr<Parser> Parser::fromString(const std::string& src, const std::string& filename)
{
	std::tr1::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromString(src, filename);
	std::tr1::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::tr1::shared_ptr<Parser> Parser::fromStream(std::istream& stream_, const std::string filename)
{
	std::tr1::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromStream(stream_, filename);
	std::tr1::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::tr1::shared_ptr<nekomata::timeline::TimeLine> Parser::parseTimeline()
{
	return impl->parseTimeline();
}
std::tr1::shared_ptr<const nekomata::tree::ExprNode> Parser::parseProgram()
{
	return impl->parseProgram();
}


} /* namespace parser */
} /* namespace nekomata */
