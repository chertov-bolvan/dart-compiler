#include <stdio.h>
#include <stdlib.h>
#include "type_nodes.h"
#include "stmt_nodes.h"
#include "global_id.c"

typedef struct FuncDeclNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  struct ParamNode* parameters;
  struct StmtNode* body;
} FuncDeclNode;


typedef struct ParamNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  struct ParamNode* next;
} ParamNode;


FuncDeclNode* createFuncDecl(TypeNode* type, char* id, ParamNode* parameters, StmtNode* body);


ParamNode* createParam(TypeNode* type, char* id);
ParamNode* addParamToList(ParamNode* list, ParamNode* newParam);