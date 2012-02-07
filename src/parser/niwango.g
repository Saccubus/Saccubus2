grammar niwango;

options {
	language=C;
}

@header {
#include <string>
#include <iostream>
#include "./ParseUtil.h"
#include "../tree/Node.h"
using namespace parse;
using namespace tree;
}

program// returns [const ExprNode* result]
	: (expr ((';' | ',') expr)*)?;

expr// returns [const ExprNode* result]
options{ backtrack=true; }
	: term ((':='|'=') expr)
	| expr5
	;

expr5// returns [const ExprNode* result]
	: expr4 ('||' expr4)*
	;
expr4// returns [const ExprNode* result]
	: expr3 ('&&' expr3)*
	;
expr3// returns [const ExprNode* result]
	: expr2
	( ('<' | '>' | '==' | '!=' | '<=' | '>=' ) expr2)*
	;
expr2// returns [const ExprNode* result]
	: expr1
	( ('+'|'-') expr1)*;
expr1// returns [const ExprNode* result]
	: term
	( ('*' | '/' | '%') term)*;

term// returns [const ExprNode* result]
	: '++' term
	| '--' term
	| '+' term
	| '-' term
	| '!' term
	| postfix
	;
postfix// returns [const ExprNode* result]
	: primary
	( '++'
	| '--'
	| '.' name
	| '[' args ']'
	| '(' args ')'
	)*
	;
primary// returns [const ExprNode* result]
	: literal
	| array
	| name
	| '(' expr')'
	;

args
	:(arg (',' arg)*)?;
arg
	: (name ':')? expr (';' expr)*;

name returns [const NameNode* result]
	: t=IDENT
	{
		return new NameNode(createLocation($t), createStringFromToken($t));
	}
	;

array// returns [const ArrayNode* result]
	: '['(expr (',' expr)*)? ']';

literal returns [const LiteralNode* result]:
	i=integer
	{
		$result = $i.result;
	}
	| b=boolean
	{
		$result = $b.result;
	}
	| s=string
	{
		$result = $s.result;
	};

boolean returns [const BoolLiteralNode* result]
	: lt='true'
	{
		$result = new BoolLiteralNode(createLocation($lt), true);
	}
	| lt='false'
	{
		$result = new BoolLiteralNode(createLocation($lt), false);
	}
	;
integer returns [const IntegerLiteralNode* result]
	: str=(INT_LITERAL | HEX_LITERAL | OCT_LITERAL)
	{
		int num = strtol(createStringFromToken($str).c_str(), 0, 0);
		$result = new IntegerLiteralNode(createLocation($str), num);
		
	};
string returns [const StringLiteralNode* result]
	: str=(STRING_SINGLE | STRING_DOUBLE)
	{
		$result = new StringLiteralNode(createLocation($str), createStringFromToken($str));
	}
	;

//---------------------------------------------------------------------------------------------------------------------

INT_LITERAL: ('1'..'9' DIGIT*) | '0';

HEX_LITERAL:
	'0' ('x'|'X') HEX_DIGIT+;

fragment HEX_DIGIT:
	('0'..'9'|'A'..'F'|'a'..'f');

OCT_LITERAL :
	'0' (OCT_DIGIT)+;
fragment OCT_DIGIT :
	'0'..'7';

IDENT:
	LETTER (LETTER | DIGIT)*;

fragment
LETTER:
	'A'..'Z'
	| 'a'..'z'
	| '_'
	| '@'
	| '$'
	;
fragment
DIGIT :
  '0'..'9';

STRING_SINGLE
	: '\'' t=STRING_SINGLE_ELEMENT* {SETTEXT($t->tokText.text);} '\'';
fragment
STRING_SINGLE_ELEMENT: ESC_SEQ | ~('\\'|'\''|'\r'|'\n');

STRING_DOUBLE
	: '"' t=STRING_DOUBLE_ELEMENT* {SETTEXT($t->tokText.text);} '"';

fragment
STRING_DOUBLE_ELEMENT: ESC_SEQ | ~('\\'|'"'|'\r'|'\n');

fragment
ESC_SEQ
	:'\\'
		( 'b' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\b")); }
		| 't' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\t")); }
		| 'n' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\n")); }
		| 'f' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\f")); }
		| 'r' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\r")); }
		| '"' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"\"")); }
		| '\'' { SETTEXT(GETTEXT()->factory->newStr8(GETTEXT()->factory, (pANTLR3_UINT8)"'")); }
		)?
	;

WS: (' ' |'\n' |'\r' )+ {$channel=HIDDEN;} ; // ignore whitespace
