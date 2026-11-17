#pragma once

#include "nodes/global/global_nodes.h"

void printProgramDot(ProgramNode* node);
void printTopLevelDeclDot(TopLevelDeclNode* node);
void printTypeDot(TypeNode* node);
void printExprDot(ExprNode* node);
void printArgDot(ArgNode* node);
void printStmtDot(StmtNode* node);
void printVarDeclDot(VarDeclNode* node);
void printVarDeclaratorDot(VarDeclaratorNode* node);
void printForInVarDot(ForInVarNode* node);
void printFuncDeclDot(FuncDeclNode* node);
void printParamDot(ParamNode* node);
void printClassDeclDot(ClassDeclNode* node);
void printClassMemberDot(ClassMemberNode* node);
void printConstructorDeclDot(ConstructorDeclNode* node);
void printSuperConstructorDot(SuperConstructorNode* node);
