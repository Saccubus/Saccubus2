/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */
 grammar NicosMessage;

options {
  language = C;
}
@includes {
#undef __cplusplus
}

@header {
#include <string>
#include <vector>
#include <cinamo/String.h>
#include "../../nekomata/parser/ParseUtil.h"
using namespace nekomata::parser::util;
using namespace nekomata::tree;
}

script returns [std::vector<std::string> val]
@init {
	std::vector<std::string> vec;
}
@after{
	$val = vec;
}
	: ( str = string
	{
		vec.push_back($str.val);
	}
	)*;

string returns [std::string val]:
	a=JapString { std::string tmp=createStringFromToken($a); $val=tmp.substr(std::string("\u300c").size(), tmp.size()-std::string("\u300c\u300d").size()); }
	| b=SingleString { std::string tmp=createStringFromToken($b); $val=tmp.substr(1, tmp.size()-2); }
	| c=DoubleString { std::string tmp=createStringFromToken($c); $val=unescapeString(tmp.substr(1, tmp.size()-2)); }
	| d=NoSpacedString { $val=createStringFromToken($d); }
	;

JapString: '\u300c'  ~('\u300d')* '\u300d';
SingleString: '\'' SingleElement* '\'';
DoubleString: '"' DoubleElement* '"';
NoSpacedString: (~(' '|'\u3000'))*;

fragment
SingleElement
	: ~('\'')
	;

fragment
DoubleElement
	: Escape | ~('\"' | '\\')
	;
fragment
Escape
	:'\\'
		( 'b'
		| 't'
		| 'n'
		| 'f'
		| 'r'
		| '\"'
		| '\''
		| '\\'
		)?
	;

WS: (' '|'\t'|'\u3000'|'\r'|'\n')+ {$channel=HIDDEN;} ; // ignore whitespace

