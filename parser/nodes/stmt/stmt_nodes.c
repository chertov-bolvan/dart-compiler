#include "stmt_nodes.h"

StmtNode* createExprStmt(ExprNode* exprNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = ExprType;
  result->exprNode = exprNode;

  return result;
}

StmtNode* createVarDeclStmt(VarDeclNode* varDeclNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = VarDeclType;
  result->varDeclNode = varDeclNode;
  
  return result;
}

StmtNode* createBlockStmt(StmtNode* body) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = BlockType;
  result->body = body;

  return result;
}


StmtNode* createReturnStmt(ExprNode* exprNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = ReturnType;
  result->exprNode = exprNode;

  return result;
}

StmtNode* createBreakStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = BreakType;

  return result;
}

StmtNode* createContinueStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = ContinueType;

  return result;
}


StmtNode* createEmptyStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = EmptyType;

  return result;
}


StmtNode* addStmtToList(StmtNode* list, StmtNode* newStmt) {
  StmtNode* current = list;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = newStmt;

  return list;
}


StmtNode* createIfStmt(ExprNode* expr, StmtNode* trueBranch, StmtNode* falseBranch) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = IfType;
  result->exprNode = expr;
  result->trueBranch = trueBranch;
  result->falseBranch = falseBranch;

  return result;
}

StmtNode* createWhileStmt(StmtNodeType type, ExprNode* expr, StmtNode* body) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = type;
  result->exprNode = expr;
  result->body = body;

  return result;
}

StmtNode* createForStmt(StmtNode* forInit, ExprNode* forExpr, ExprNode* forUpd, StmtNode* body) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = ForType;
  result->forInit = forInit;
  result->exprNode = forExpr;
  result->forUpd = forUpd;
  result->body = body;

  return result;
}

StmtNode* createForInStmt(ForInVarNode* forInVar, ExprNode* expr, StmtNode* body) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->nodeId = globalId++;

  result->type = ForInType;
  result->forInVar = forInVar;
  result->exprNode = expr;
  result->body = body;

  return result;
}


// ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ
VarDeclaratorNode* createVarDeclarator(char* id, ExprNode* init) {
  VarDeclaratorNode* result = calloc(1, sizeof(VarDeclaratorNode));

  result->nodeId = globalId++;

  result->id = id;
  result->init = init;

  return result;
}

VarDeclaratorNode* addVarDeclaratorToList(VarDeclaratorNode* list, VarDeclaratorNode* newNode) {
  VarDeclaratorNode* current = list;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = newNode;

  return list;
}

VarDeclNode* createVarDecl(VarDeclModifier modifier, TypeNode* typeNode, VarDeclaratorNode* declarators) {
  VarDeclNode* result = calloc(1, sizeof(VarDeclNode));

  result->nodeId = globalId++;

  result->modifier = modifier;
  result->type = typeNode;
  result->declarators = declarators;

  return result;
}


// FOR IN

ForInVarNode* createForInVar(ForInVarType varType, TypeNode* type, char* id, VarDeclModifier modifier) {
  ForInVarNode* result = calloc(1, sizeof(ForInVarNode));

  result->nodeId = globalId++;

  result->varType = varType;
  result->type = type;
  result->id = id;
  result->modifier = modifier;

  return result;
}