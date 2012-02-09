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
void EvalWalker::walk(const tree::BoolLiteralNode & node)
{
}
EvalWalker::~EvalWalker()
{
}
void EvalWalker::walk(const tree::IntegerLiteralNode & node)
{
}
void EvalWalker::walk(const tree::StringLiteralNode & node)
{
}
void EvalWalker::walk(const tree::AssignNode & node)
{
}
void EvalWalker::walk(const tree::OpAssignNode & node)
{
}
void EvalWalker::walk(const tree::IndexAcessNode & node)
{
}
void EvalWalker::walk(const tree::BindNode & node)
{
}
void EvalWalker::walk(const tree::PostOpNode & node)
{
}
void EvalWalker::walk(const tree::PreOpNode & node)
{
}
void EvalWalker::walk(const tree::BinOpNode & node)
{
}
void EvalWalker::walk(const tree::ObjectNode & node)
{
}
void EvalWalker::walk(const tree::InvokeNode & node)
{
}
void EvalWalker::walk(const tree::ContNode & node)
{
}
}
