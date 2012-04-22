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
#include "../parser/ParseUtil.h"
#include "../util/StringUtil.h"
using namespace nekomata::parser::util;
using namespace nekomata::tree;
using nekomata::util::unescapeString;
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
	a=JapString { std::string tmp=createStringFromToken($b); $val=tmp.substr(std::string("「").size(), tmp.size()-std::string("「」").size()); }
	| b=SingleString { std::string tmp=createStringFromToken($b); $val=unescapeString(tmp.substr(1, tmp.size()-2)); }
	| c=DoubleString { std::string tmp=createStringFromToken($c); $val=unescapeString(tmp.substr(1, tmp.size()-2)); }
	| d=NoSpacedString { $val=createStringFromToken($d); }
	;

JapString: '「'  ~('」')* '」';
SingleString: '\'' SingleElement* '\'';
DoubleString: '"' DoubleElement* '"';
NoSpacedString: (~(' '|'　'))*;

fragment
SingleElement
	: Escape | ~('\'' | '\\')
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

WS: (' '|'\t'|'　'|'\r'|'\n')+ {$channel=HIDDEN;} ; // ignore whitespace

