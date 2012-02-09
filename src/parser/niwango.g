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
#include "ParseUtil.h"
#include "../tree/Node.h"
using namespace parse;
using namespace tree;
using std::tr1::shared_ptr;

}

program returns [shared_ptr<const ExprNode> result]
@init{
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: (
	fst=expr
	{
		resultNode=$fst.result;
	}
	(
		t=(';' | ',') nxt=expr
		{
			resultNode = shared_ptr<const ContNode>(new ContNode(createLocation($t), resultNode, $nxt.result));
		}
	)*)?;

expr returns [shared_ptr<const ExprNode> result]
@init{
	bool isLocal=false;
	bool isOp=false;
	std::string op;
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr5
	{
		resultNode = $fst.result;
	}
	(
		tok=(':=' {isLocal = true;isOp=false;}|'='{isLocal=false;isOp=false;}| assign_op {isLocal=false;isOp=true;op=$assign_op.result;})
		nxt=expr
		{
			if(isOp){
				resultNode=shared_ptr<const OpAssignNode>(new OpAssignNode(createLocation($tok), resultNode, op, $nxt.result));
			}else{
				resultNode=shared_ptr<const AssignNode>(new AssignNode(createLocation($tok), resultNode, $nxt.result, isLocal));
			}
		}
	)?
	;

assign_op returns [std::string result]
	: '+=' {$result="add";}
	| '-=' {$result="subtract";}
	| '*=' {$result="multiply";}
	| '/=' {$result="divide";}
	| '%=' {$result="modulo";}
	;
	

expr5 returns [shared_ptr<const ExprNode> result]
@init{
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr4
	{
		resultNode=$fst.result;
	}
	(
		tok='||' nxt=expr4
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocation($tok), resultNode, "or", $nxt.result));
		}
	)*
	;
expr4 returns [shared_ptr<const ExprNode> result]
@init{
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr3
	{
		resultNode=$fst.result;
	}
	(
		tok='&&' nxt=expr3
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocation($tok), resultNode, "and", $nxt.result));
		}
	)*
	;
expr3 returns [shared_ptr<const ExprNode> result]
@init{
	std::string op;
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr2
	{
		resultNode = $fst.result;
	}
	(
		tok=('<' {op="lessThan";} | '>' {op="greaterThan";} | '==' {op="equals";} | '!=' {op="notEquals";} | '<=' {op="notGreaterThan";} | '>=' {op="notLessThan";} )
		nxt=expr2
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocation($tok), resultNode, op, $nxt.result));
		}
	)*
	;
expr2 returns [shared_ptr<const ExprNode> result]
@init{
	std::string op;
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr1
	{
		resultNode = $fst.result;
	}
	(
		tok=('+' {op="add";} |'-' {op="subtract";})
		nxt=expr1
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocation($tok), resultNode, op, $nxt.result));
		}
	)*;
expr1 returns [shared_ptr<const ExprNode> result]
@init{
	std::string op;
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=term 
	{
		resultNode=$fst.result;
	}
	(
		tok=('*' {op="multiply";} | '/' {op="divide";} | '%' {op="modulo";})
		nxt=term
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocation($tok), resultNode, op, $nxt.result));
		}
	)*
	;

term returns [shared_ptr<const ExprNode> result]
	: tok=('++' t=term)
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocation($tok), termNode, "increase"));
	}
	| tok=('--' t=term)
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocation($tok), termNode, "decrease"));
	}
	| tok=('+' t=term)
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocation($tok), termNode, "plus"));
	}
	| tok=('-' t=term)
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocation($tok), termNode, "minus"));
	}
	| tok=('!' t=term)
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocation($tok), termNode, "not"));
	}
	| postfix
	{
		$result = $postfix.result;
	}
	;
postfix returns [shared_ptr<const ExprNode> result]
	: primary
	{
		$result=$primary.result;
	}
	( tok='++'
	{
		$result=shared_ptr<const PostOpNode>(new PostOpNode(createLocation($tok), $result, "increase"));
	}
	| tok='--'
	{
		$result=shared_ptr<const PostOpNode>(new PostOpNode(createLocation($tok), $result, "decrease"));
	}
	| tok=('.' name)
	{
		$result=shared_ptr<const InvokeNode>(new InvokeNode(createLocation($tok), $result, $name.result));
	}
	| tok=('[' array_idx=object_def ']')
	{
		shared_ptr<const ObjectNode> objNode = $array_idx.result;
		$result=shared_ptr<const IndexAcessNode>(new IndexAcessNode(createLocation($tok), $result, objNode));
	}
	| tok=('(' binded=object_def ')')
	{
		shared_ptr<const ObjectNode> objNode = $binded.result;
		$result=shared_ptr<const BindNode>(new BindNode(createLocation($tok), $result, objNode));
	}
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
	| tok=(name)
	{
		$result = shared_ptr<const InvokeNode>(new InvokeNode(createLocation($tok), shared_ptr<const ExprNode>(), $name.result));
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
@after{
	$result=obj;
}
	:(tok=(fst=object_element)
	{
		obj=shared_ptr<ObjectNode>(new ObjectNode(createLocation($tok)));
		obj->append($fst.name, $fst.exprNode);
	}
	(',' nxt=object_element
	{
		obj->append($nxt.name, $nxt.exprNode);
	})*)?;

object_element returns [bool hasName, std::string name, shared_ptr<const ExprNode> exprNode]
@init{
	$hasName=false;
}
	: (name {$hasName = true; $name = $name.result;} ':')?
	object_expr_list
	{
		$exprNode = $object_expr_list.result;
	}
	;
	
object_expr_list returns [shared_ptr<const ExprNode> result]
@init{
	shared_ptr<const ExprNode> resultNode;
}
@after{
	$result=resultNode;
}
	: fst=expr {resultNode = $fst.result;}
	(t=(';' nxt=expr)
		{
			resultNode = shared_ptr<const ContNode>(new ContNode(createLocation($t), resultNode, $nxt.result));
		}
	)*
	;

name returns [std::string result]
	: t=IDENT
	{
		$result= createStringFromToken($t);
	}
	;

array returns [shared_ptr<const ObjectNode> result]
@init{
	shared_ptr<const ObjectNode> resultNode;
}
@after{
	if(resultNode.get() == 0){
		resultNode = shared_ptr<ObjectNode>(new ObjectNode(createLocation($tok)));
	}
	$result=resultNode;
}
	: tok=('['
	object_def
	{
		resultNode=$object_def.result;
	}
	']');

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
