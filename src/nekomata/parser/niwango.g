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
#include <cstdlib>
#include "ParseUtil.h"
#include "../tree/Node.h"
#include "../timeline/TimeLine.h"
using namespace nekomata::parser::util;
using namespace nekomata::tree;
using namespace nekomata::timeline;
using std::tr1::shared_ptr;
typedef pANTLR3_COMMON_TOKEN Token;
}

time_line returns [shared_ptr<TimeLine> result]
@init{
	shared_ptr<TimeLine> timeLine = shared_ptr<TimeLine>(new TimeLine());
}
@after{
	$result=timeLine;
}
	: (time_point
	{
		timeLine->insertLast($time_point.time, $time_point.node);
	}
	)*
	;

time_point returns [float time, shared_ptr<const ExprNode> node]
	: numeric ':' (~(':'))*  ':' '/' program
	{
		$time=$numeric.result->getLiteral();
		$node=$program.result;
	}
	;

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
			resultNode = shared_ptr<const ContNode>(new ContNode(createLocationFromToken($t), resultNode, $nxt.result));
		}
	)*)?
	(';' | ',')?;

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
		(tok=':=' {isLocal = true;isOp=false;}|tok='='{isLocal=false;isOp=false;}| assign_op {isLocal=false;isOp=true;op=$assign_op.result;})
		nxt=expr
		{
			if(isOp){
				resultNode=shared_ptr<const OpAssignNode>(new OpAssignNode(createLocationFromToken($assign_op.token), resultNode, op, $nxt.result));
			}else{
				resultNode=shared_ptr<const AssignNode>(new AssignNode(createLocationFromToken($tok), resultNode, $nxt.result, isLocal));
			}
		}
	)?
	;

assign_op returns [std::string result, Token token]
	: tok='+=' {$result="add";$token=$tok;}
	| tok='-=' {$result="subtract";$token=$tok;}
	| tok='*=' {$result="multiply";$token=$tok;}
	| tok='/=' {$result="divide";$token=$tok;}
	| tok='%=' {$result="modulo";$token=$tok;}
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
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocationFromToken($tok), resultNode, "or", $nxt.result));
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
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocationFromToken($tok), resultNode, "and", $nxt.result));
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
		(tok='<' {op="lessThan";} | tok='>' {op="greaterThan";} | tok='==' {op="equals";} | tok='!=' {op="notEquals";} | tok='<=' {op="notGreaterThan";} | tok='>=' {op="notLessThan";} )
		nxt=expr2
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocationFromToken($tok), resultNode, op, $nxt.result));
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
		(tok='+' {op="add";} |tok='-' {op="subtract";})
		nxt=expr1
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocationFromToken($tok), resultNode, op, $nxt.result));
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
		(tok='*' {op="multiply";} | tok='/' {op="divide";} | tok='%' {op="modulo";})
		nxt=term
		{
			resultNode=shared_ptr<const BinOpNode>(new BinOpNode(createLocationFromToken($tok), resultNode, op, $nxt.result));
		}
	)*
	;

term returns [shared_ptr<const ExprNode> result]
	: tok='++' t=term
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocationFromToken($tok), termNode, "increase"));
	}
	| tok='--' t=term
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const PreOpNode>(new PreOpNode(createLocationFromToken($tok), termNode, "decrease"));
	}
	| tok='+' t=term
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const InvokeNode>(new InvokeNode(createLocationFromToken($tok), termNode, "plus"));
	}
	| tok='-' t=term
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const InvokeNode>(new InvokeNode(createLocationFromToken($tok), termNode, "minus"));
	}
	| tok='!' t=term
	{
		shared_ptr<const ExprNode> termNode = $t.result;
		$result=shared_ptr<const InvokeNode>(new InvokeNode(createLocationFromToken($tok), termNode, "not"));
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
		$result=shared_ptr<const PostOpNode>(new PostOpNode(createLocationFromToken($tok), $result, "increase"));
	}
	| tok='--'
	{
		$result=shared_ptr<const PostOpNode>(new PostOpNode(createLocationFromToken($tok), $result, "decrease"));
	}
	| tok='.' name
	{
		$result=shared_ptr<const InvokeNode>(new InvokeNode(createLocationFromToken($tok), $result, $name.result));
	}
	| tok='[' array_idx=object_def ']'
	{
		shared_ptr<const ObjectNode> objNode = $array_idx.result;
		$result=shared_ptr<const IndexAcessNode>(new IndexAcessNode(createLocationFromToken($tok), $result, objNode));
	}
	| tok='(' binded=object_def ')'
	{
		shared_ptr<const ObjectNode> objNode = $binded.result;
		$result=shared_ptr<const BindNode>(new BindNode(createLocationFromToken($tok), $result, objNode));
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
	| name
	{
		$result = shared_ptr<const InvokeNode>(new InvokeNode(createLocationFromToken($name.token), shared_ptr<const ExprNode>(), $name.result));
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
	:((fst=object_element)
	{
		obj=shared_ptr<ObjectNode>(new ObjectNode(createLocationFromNode($fst.exprNode)));
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
	((t=';' nxt=expr)
		{
			resultNode = shared_ptr<const ContNode>(new ContNode(createLocationFromToken($t), resultNode, $nxt.result));
		}
	)* (';')?
	;

name returns [std::string result, Token token]
	: t=IDENT
	{
		$result= createStringFromToken($t);
		$token=$t;
	}
	;

array returns [shared_ptr<const ObjectNode> result]
@init{
	shared_ptr<const ObjectNode> resultNode;
}
@after{
	if(resultNode.get() == 0){
		resultNode = shared_ptr<ObjectNode>(new ObjectNode(createLocationFromToken($tok)));
	}
	$result=resultNode;
}
	: tok='['
	object_def
	{
		resultNode=$object_def.result;
	}
	']';

literal returns [shared_ptr<const LiteralNode> result]:
	n=numeric
	{
		$result = $n.result;
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
		$result = shared_ptr<const BoolLiteralNode>(new BoolLiteralNode(createLocationFromToken($lt), true));
	}
	| lt='false'
	{
		$result = shared_ptr<const BoolLiteralNode>(new BoolLiteralNode(createLocationFromToken($lt), false));
	}
	;
numeric returns [shared_ptr<const NumericLiteralNode> result]
	: (str=INT_LITERAL | str=HEX_LITERAL | str=OCT_LITERAL)
	{
		int num = strtol(createStringFromToken($str).c_str(), 0, 0);
		$result = shared_ptr<const NumericLiteralNode>(new NumericLiteralNode(createLocationFromToken($str), num));
	}
	| str=FLOAT_LITERAL
	{
		double num = atof(createStringFromToken($str).c_str());
		$result = shared_ptr<const NumericLiteralNode>(new NumericLiteralNode(createLocationFromToken($str), num));
	}
	;
string returns [shared_ptr<const StringLiteralNode> result]
	: (t=STRING_SINGLE | t=STRING_DOUBLE)
	{
		std::string str = createStringFromToken($t);
		//FIXME: ちょっと醜い。どうにかならないかな。
		$result = shared_ptr<const StringLiteralNode>(new StringLiteralNode(createLocationFromToken($t), str.substr(1, str.length()-2)));
	}
	;

//---------------------------------------------------------------------------------------------------------------------
FLOAT_LITERAL
    :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '.' ('0'..'9')+ EXPONENT?
    |   ('0'..'9')+ EXPONENT
    ;

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

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
	: '\'' t=STRING_SINGLE_ELEMENT* '\'';

fragment
STRING_SINGLE_ELEMENT: ESC_SEQ | ~('\\'|'\''|'\r'|'\n');

STRING_DOUBLE
	: '"' t=STRING_DOUBLE_ELEMENT*
'"';

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
