#include <stdio.h>
#include <stdlib.h>
#include "stmt_nodes.h"
#include "func_nodes.h"
//#include "class_nodes.h"
#include "global_id.c"

typedef struct ProgramNode {
  int nodeId;

  struct TopLevelDeclNode* topLevelDeclNode;
} ProgramNode;


typedef enum TopLevelDeclType {
  TopLevelVarDeclType, TopLevelFuncDeclType, TopLevelClassDeclType,  
} TopLevelDeclType;

typedef struct TopLevelDeclNode {
  int nodeId;

  TopLevelDeclType type;

  struct VarDeclNode* varDeclNode;
  struct FuncDeclNode* funcDeclNode;
  //struct ClassDeclNode* classDeclNode;

  struct TopLevelDeclNode* next;
} TopLevelDeclNode;


ProgramNode* createProgram(TopLevelDeclNode* topLevelDeclNode);


TopLevelDeclNode* createTopLevelVarDecl(VarDeclNode* varDeclNode);
TopLevelDeclNode* createTopLevelFuncDecl(FuncDeclNode* funcDeclNode);
//TopLevelDeclNode* createTopLevelClassDecl(ClassDeclNode* classDeclNode);

TopLevelDeclNode* addTopLevelDeclToList(TopLevelDeclNode* list, TopLevelDeclNode* newTopLevelDecl);