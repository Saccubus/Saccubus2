/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */


#include <utility>
#include <iostream>
#include <sstream>
#include <memory>
#include <nekomata/logging/Exception.h>
#include <nekomata/parser/Parser.h>
#include "../tree/Node.h"

#include "niwangoLexer.h"
#include "niwangoParser.h"
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
			throw logging::Exception(__FILE__, __LINE__, "Failed to read stream for %s", filename.c_str());
		}
		this->tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
		if(!this->tokenStream){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create token stream for %s", filename.c_str());
		}
		this->parser = niwangoParserNew(tokenStream);
		if(!this->parser){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create parser for %s", filename.c_str());
		}
	}
public:
	explicit ParserImpl():stream(0), src(), filename(), lexer(0), tokenStream(0), parser(0){}
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

	ParserImpl& fromFile(std::string const& filename)
	{
		this->filename = filename;
		stream = antlr3FileStreamNew((ANTLR3_UINT8*)filename.c_str(), ANTLR3_ENC_UTF8);
		if(!stream){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create ANTLR3 File Stream for %s", filename.c_str());
		}
		setup();
		return *this;
	}
	ParserImpl& fromString(std::string const& src, std::string const& filename, int line)
	{
		this->src = src;
		this->filename = filename;
		stream = antlr3StringStreamNew((pANTLR3_UINT8)this->src.c_str(), ANTLR3_ENC_UTF8, src.size(), (pANTLR3_UINT8)this->filename.c_str());
		if(!stream){
			throw logging::Exception(__FILE__, __LINE__, "Failed to create ANTLR3 String Stream for %s", filename.c_str());
		}
		stream->line=line;
		setup();
		return *this;
	}
	ParserImpl& fromStream(std::istream& stream_, const std::string filename){
		std::stringstream ss;
		char buff[8192];
		while(!stream_.eof()){
			stream_.read(buff, sizeof(buff));
			if ( stream_.fail() && !stream_.eof() ) {
				break;
			}
			ss.write(buff, stream_.gcount());
		}
		std::string src = ss.str();
		return fromString(src, filename, 0);
	}
public:
	std::shared_ptr<const tree::ExprNode> parseProgram()
	{
		std::shared_ptr<const tree::ExprNode> node(parser->program(parser));
		if(parser->pParser->rec->state->error)
		{
			ANTLR3_EXCEPTION* ex = parser->pParser->rec->state->exception;
			throw logging::Exception(__FILE__, __LINE__, "Parser error: %s line: %d pos: %d", ex->message, ex->line, ex->charPositionInLine);
		}
		return node;
	}
};

Parser::Parser(std::shared_ptr<ParserImpl> impl)
:impl(impl)
{
	if(!impl){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Invalid parser impl pointer.");
	}
}
Parser::~Parser()
{
}
std::shared_ptr<Parser> Parser::fromFile(std::string const& filename)
{
	std::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromFile(filename);
	std::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::shared_ptr<Parser> Parser::fromString(std::string const& src, std::string const& filename, int line)
{
	std::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromString(src, filename, line);
	std::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::shared_ptr<Parser> Parser::fromStream(std::istream& stream_, std::string const& filename)
{
	std::shared_ptr<ParserImpl> impl(new ParserImpl);
	impl->fromStream(stream_, filename);
	std::shared_ptr<Parser> parser(new Parser(impl));
	return parser;
}
std::shared_ptr<const tree::Node> Parser::parseProgram()
{
	return impl->parseProgram();
}

}}
