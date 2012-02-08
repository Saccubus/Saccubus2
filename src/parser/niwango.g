grammar niwango;

options {
	language=C;
}

@includes {
#undef __cplusplus
}

@header {
#include <string>
#include <iostream>
#include <tr1/memory>
#include "./ParseUtil.h"
#include "../tree/Node.h"
using namespace parse;
using namespace tree;
using std::tr1::shared_ptr;

}

program returns [shared_ptr<const ExprNode> result]
	: (expr ((';' | ',') expr)*)?;

expr returns [shared_ptr<const ExprNode> result]
	: expr5 ((':='|'=') expr5)?
	;

expr5 returns [shared_ptr<const ExprNode> result]
	: expr4 ('||' expr4)*
	;
expr4 returns [shared_ptr<const ExprNode> result]
	: expr3 ('&&' expr3)*
	;
expr3 returns [shared_ptr<const ExprNode> result]
	: expr2
	( ('<' | '>' | '==' | '!=' | '<=' | '>=' ) expr2)*
	;
expr2 returns [shared_ptr<const ExprNode> result]
	: expr1
	( ('+'|'-') expr1)*;
expr1 returns [shared_ptr<const ExprNode> result]
	: term
	( ('*' | '/' | '%') term)*;

term returns [shared_ptr<const ExprNode> result]
	: '++' term
	| '--' term
	| '+' term
	| '-' term
	| '!' term
	| postfix
	;
postfix returns [shared_ptr<const ExprNode> result]
	: primary
	( '++'
	| '--'
	| '.' name
	| '[' object_def ']'
	| '(' object_def ')'
	)*
	;
primary returns [shared_ptr<const ExprNode> result]
	: literal
	{
		$result = $literal.result;
	}
	| array
	{
		$result = $array.result;
	}
	| name
	{
		shared_ptr<const NameNode> nameNode = $name.result;
		$result = shared_ptr<const SlotNode>(new SlotNode(nameNode->location(), shared_ptr<const ExprNode>(), nameNode));
	}
	| '(' expr ')'
	{
		$result = $expr.result;
	}
	;

object_def returns [shared_ptr<const ObjectNode> result]
@init{
	shared_ptr<ObjectNode> obj;
}
	:(fst=object_element
	{
		if($fst.nameNode.get() == 0){
			obj=shared_ptr<ObjectNode>(new ObjectNode($fst.exprNode->location()));
		}else{
			obj=shared_ptr<ObjectNode>(new ObjectNode($fst.nameNode->location()));
		}
		$result=obj;
		obj->append($fst.nameNode, $fst.exprNode);
	}
	(',' nxt=object_element
	{
		obj->append($nxt.nameNode, $nxt.exprNode);
	})*)?;

object_element returns [shared_ptr<const NameNode> nameNode, shared_ptr<const ExprNode> exprNode]
	: (name {$nameNode = $name.result;} ':')?
	object_expr_list
	{
		$exprNode = $object_expr_list.result;
	}
	;
	
object_expr_list returns [shared_ptr<const ExprNode> result]
	:expr (';' expr)*;

name returns [shared_ptr<const NameNode> result]
	: t=IDENT
	{
		$result= shared_ptr<const NameNode>(new NameNode(createLocation($t), createStringFromToken($t)));
	}
	;

array returns [shared_ptr<const ObjectNode> result]
	: '['
	object_def
	{
		$result=$object_def.result;
	}
	']';

literal returns [shared_ptr<const LiteralNode> result]:
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

boolean returns [shared_ptr<const BoolLiteralNode> result]
	: lt='true'
	{
		$result = shared_ptr<const BoolLiteralNode>(new BoolLiteralNode(createLocation($lt), true));
	}
	| lt='false'
	{
		$result = shared_ptr<const BoolLiteralNode>(new BoolLiteralNode(createLocation($lt), false));
	}
	;
integer returns [shared_ptr<const IntegerLiteralNode> result]
	: str=(INT_LITERAL | HEX_LITERAL | OCT_LITERAL)
	{
		int num = strtol(createStringFromToken($str).c_str(), 0, 0);
		$result = shared_ptr<const IntegerLiteralNode>(new IntegerLiteralNode(createLocation($str), num));
		
	};
string returns [shared_ptr<const StringLiteralNode> result]
	: str=(STRING_SINGLE | STRING_DOUBLE)
	{
		$result = shared_ptr<const StringLiteralNode>(new StringLiteralNode(createLocation($str), createStringFromToken($str)));
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
