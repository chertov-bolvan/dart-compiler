#include <stdio.h>
#include <stdlib.h>
#include "type_nodes.h"
#include "expr_nodes.h"

typedef enum StmtNodeType {
  VarDeclType, ExprType, EmptyType, 
  ForType, WhileType, DoWhileType, IfType, 
  ReturnType, BlockType, BreakType, ContinueType,

} StmtNodeType;

typedef struct StmtNode {
  int nodeId;  
  StmtNodeType type;
  
  struct TypeNode* typeNode;
  char* id;
  struct ExprNode* exprNode;

  struct VarDeclNode* varDeclNode;

  struct StmtNode* trueBranch;
  struct StmtNode* falseBranch;

  struct StmtNode* body;
  struct StmtNode* next;

} StmtNode;

StmtNode* createExprStmt(ExprNode* exprNode);
StmtNode* createVarDeclStmt(VarDeclNode* varDeclNode);
StmtNode* createBlockStmt(StmtNode* body);

StmtNode* createReturnStmt(ExprNode* exprNode);
StmtNode* createBreakStmt();
StmtNode* createContinueStmt();

StmtNode* createEmptyStmt();

StmtNode* addStmtToList(StmtNode* list, StmtNode* newStmt);


// ОБЪЯВДЕНИЕ ПЕРЕМЕННЫХ
typedef struct VarDeclaratorNode {
  int nodeId;
  char* id;
  struct ExprNode* init;
  
  struct VarDeclaratorNode* next;

} VarDeclaratorNode;


typedef enum VarDeclModifier {
  NoModifier, FinalModifier, ConstModifier,
} VarDeclModifier;


typedef struct VarDeclNode {
  VarDeclModifier modifier;
  struct TypeNode* type;

  struct VarDeclaratorNode* declarators;
} VarDeclNode;

VarDeclaratorNode* createVarDeclarator(char* id, ExprNode* init);
VarDeclaratorNode* addVarDeclaratorToList(VarDeclaratorNode* list, VarDeclaratorNode* newNode);
VarDeclNode* createVarDecl(VarDeclModifier modifier, TypeNode* typeNode, VarDeclaratorNode* declarators);
