#include "type_nodes.h"
#include "expr_nodes.h"
#include "stmt_nodes.h"

StmtNode* createExprStmt(ExprNode* exprNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = ExprType;
  result->exprNode = exprNode;

  return result;
}

StmtNode* createVarDeclStmt(VarDeclNode* varDeclNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = VarDeclType;
  result->varDeclNode = varDeclNode;
  
  return result;
}

StmtNode* createBlockStmt(StmtNode* body) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = BlockType;
  result->body = body;

  return result;
}


StmtNode* createReturnStmt(ExprNode* exprNode) {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = ReturnType;
  result->exprNode = exprNode;

  return result;
}

StmtNode* createBreakStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = BreakType;

  return result;
}

StmtNode* createContinueStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

  result->type = ContinueType;

  return result;
}


StmtNode* createEmptyStmt() {
  StmtNode* result = calloc(1, sizeof(StmtNode));

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


// ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ
VarDeclaratorNode* createVarDeclarator(char* id, ExprNode* init) {
  VarDeclaratorNode* result = calloc(1, sizeof(VarDeclaratorNode));

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

  result->modifier = modifier;
  result->type = typeNode;
  result->declarators = declarators;

  return result;
}