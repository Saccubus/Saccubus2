grammar niwango;

options {
	language=C;
	output=AST;
}

program: (expr ((';' | ',') expr)*)?;

expr:
	expr5 ((':=' | '=' | '+=' | '-=' | '*=' | '/=' | '%=') expr5)*;

expr5:
	expr4 ('||' expr4)*
	;
expr4:
	expr3 ('&&' expr3)*
	;
expr3:
	expr2
	( ('<' | '>' | '==' | '!=' | '<=' | '>=' ) expr2)*
	;
expr2:
	expr1
	( ('+'|'-') expr1)*;
expr1:
	term
	( ('*' | '/' | '%') term)*;


term:
	  '++' term 
	| '--' term
	| '+' term
	| '-' term
	| '!' term
	| postfix
	;
postfix: primary
	( '++'
	| '--'
	| '.' name
	| '[' expr ']'
	| '(' args ')'
	)*
	;
primary:
	literal
	| ident
	| '(' expr')'
	;

args: (arg (',' arg)*)?;
arg: (name ':')? expr (';' expr)*;

name: ident;

ident: IDENT;

literal:
	number
	| bool
	| array
	| string;

bool: TRUE | FALSE;
array: '[' (expr (',' expr)*)? ']';
number: INT_LITERAL | HEX_LITERAL | OCT_LITERAL;
string: STRING_SINGLE | STRING_DOUBLE;

TRUE: 'true';
FALSE: 'false';

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
	;
fragment
DIGIT :
  '0'..'9';

STRING_SINGLE:
	'\'' STRING_SINGLE_ELEMENT* '\'';
fragment
STRING_SINGLE_ELEMENT:
	ESC_SEQ
	|~('\\'|'\''|'\r'|'\n')
	;

STRING_DOUBLE: '"' STRING_DOUBLE_ELEMENT* '"';
fragment
STRING_DOUBLE_ELEMENT:
	ESC_SEQ
	|~('\\'|'"'|'\r'|'\n')
	;

fragment
ESC_SEQ: '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\'')?;  

WS: (' ' |'\n' |'\r' )+ {$channel=HIDDEN;} ; // ignore whitespace
