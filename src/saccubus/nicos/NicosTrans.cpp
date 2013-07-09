/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */

#include "./NicosTrans.h"
#include <nekomata/logging/Exception.h>
#include <string>
#include <vector>
#include "DefaultAction.h"
#include "ButtonAction.h"
#include "ReplaceAction.h"
#include "NicosMessageLexer.h"
#include "NicosMessageParser.h"

#include <iostream>

namespace saccubus {
namespace nicos {

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
	if((front == cmd) && (shouldBeOwner ? com.layer() == layer::item::Comment::Forked : true) && (shouldBePremium ? com.isPremium() : true) ) return clazz(com, tokens).trans();

std::string toNiwango(layer::item::Comment const& com)
{
	std::vector<std::string> tokens = Impl(com.message()).parse();
	if(tokens.size() > 0){
		std::string const front ( tokens.front() );
		tokens.erase(tokens.begin());
		DEF_ACTION(std::string(u8"＠デフォルト"), true, false, DefaultAction);
		DEF_ACTION(std::string(u8"＠ボタン"), true, true, ButtonAction);
		DEF_ACTION(std::string(u8"＠置換"), true, false, ReplaceAction);
	}
	return "";
}

}}
