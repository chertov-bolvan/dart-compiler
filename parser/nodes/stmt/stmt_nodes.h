#include <stdio.h>
#include <stdlib.h>
#include "../type/type_nodes.h"
#include "../expr/expr_nodes.h"
#include "../global_id.h"

typedef enum StmtNodeType {
  VarDeclType, ExprType, EmptyType, 
  ForType, ForInType, WhileType, DoWhileType, IfType, 
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

  struct StmtNode* forInit;
  struct ExprNode* forUpd;

  struct ForInVarNode* forInVar;

  struct StmtNode* body;
  struct StmtNode* next;

} StmtNode;


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
  int nodeId;

  VarDeclModifier modifier;
  struct TypeNode* type;

  struct VarDeclaratorNode* declarators;
} VarDeclNode;


// НОДЫ ДЛЯ FORIN

typedef enum ForInVarType {
  ExistingVarType, DeclVarType
} ForInVarType;


typedef struct ForInVarNode {
  int nodeId;

  ForInVarType varType;

  struct TypeNode* type;
  char* id;

  VarDeclModifier modifier;
} ForInVarNode;


// ФУНКЦИИ

StmtNode* createExprStmt(ExprNode* exprNode);
StmtNode* createVarDeclStmt(VarDeclNode* varDeclNode);
StmtNode* createBlockStmt(StmtNode* body);

StmtNode* createReturnStmt(ExprNode* exprNode);
StmtNode* createBreakStmt();
StmtNode* createContinueStmt();

StmtNode* createEmptyStmt();

StmtNode* addStmtToList(StmtNode* list, StmtNode* newStmt);

StmtNode* createIfStmt(ExprNode* expr, StmtNode* trueBranch, StmtNode* falseBranch);
StmtNode* createWhileStmt(StmtNodeType type, ExprNode* expr, StmtNode* body);

StmtNode* createForStmt(StmtNode* forInit, ExprNode* forExpr, ExprNode* forUpd, StmtNode* body);
StmtNode* createForInStmt(ForInVarNode* forInVar, ExprNode* expr, StmtNode* body);


VarDeclaratorNode* createVarDeclarator(char* id, ExprNode* init);
VarDeclaratorNode* addVarDeclaratorToList(VarDeclaratorNode* list, VarDeclaratorNode* newNode);
VarDeclNode* createVarDecl(VarDeclModifier modifier, TypeNode* typeNode, VarDeclaratorNode* declarators);


ForInVarNode* createForInVar(ForInVarType varType, TypeNode* type, char* id, VarDeclModifier modifier);