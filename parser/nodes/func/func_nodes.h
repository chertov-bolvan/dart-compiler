#include <stdio.h>
#include <stdlib.h>

typedef struct FuncDeclNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  struct ParamNode* parameters;
  struct StmtNode* body;
} FuncDeclNode;

FuncDeclNode* createFuncDecl(TypeNode* type, char* id, ParamNode* parameters, StmtNode* body);


typedef struct ParamNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  struct ParamNode* next;
} ParamNode;

ParamNode* createParam(TypeNode* type, char* id);
ParamNode* addParamToList(ParamNode* list, ParamNode* newParam);