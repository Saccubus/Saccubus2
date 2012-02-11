/*
 * EvalWaker.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */
#include "NodeWalker.h"
#include "../tree/Node.h"
#include <tr1/memory>
using namespace tree;
using std::tr1::shared_ptr;
namespace machine{
EvalWalker::EvalWalker()
{
}
EvalWalker::~EvalWalker()
{
}
void EvalWalker::walkIn(){

}

void EvalWalker::walkOut(){
}
void EvalWalker::walkImpl(const tree::BoolLiteralNode & node)
{
}
void EvalWalker::walkImpl(const tree::IntegerLiteralNode & node)
{
}
void EvalWalker::walkImpl(const tree::StringLiteralNode & node)
{
}
void EvalWalker::walkImpl(const tree::AssignNode & node)
{
}
void EvalWalker::walkImpl(const tree::OpAssignNode & node)
{
}
void EvalWalker::walkImpl(const tree::IndexAcessNode & node)
{
}
void EvalWalker::walkImpl(const tree::BindNode & node)
{
}
void EvalWalker::walkImpl(const tree::PostOpNode & node)
{
}
void EvalWalker::walkImpl(const tree::PreOpNode & node)
{
}
void EvalWalker::walkImpl(const tree::BinOpNode & node)
{
}
void EvalWalker::walkImpl(const tree::ObjectNode & node)
{
}
void EvalWalker::walkImpl(const tree::InvokeNode & node)
{
}
void EvalWalker::walkImpl(const tree::ContNode & node)
{
}
}
