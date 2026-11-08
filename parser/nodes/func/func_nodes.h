#include <stdio.h>
#include <stdlib.h>
#include "../type/type_nodes.h"
#include "../stmt/stmt_nodes.h"
#include "../global_id.h"

typedef struct FuncDeclNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  struct ParamNode* parameters;
  struct StmtNode* body;
} FuncDeclNode;


typedef enum ParamType {
  RequiredPositionalType, OptionalPositionType, RequiredNamedType, OptionalNamedType
} ParamType;

typedef struct ParamNode {
  int nodeId;

  struct TypeNode* type;
  char* id;

  ParamType paramType;
  struct ExprNode* defaultValue;

  struct ParamNode* next;
} ParamNode;


FuncDeclNode* createFuncDecl(TypeNode* type, char* id, ParamNode* parameters, StmtNode* body);


ParamNode* createParam(TypeNode* type, char* id, ParamType paramType, ExprNode* defaultValue);
ParamNode* addParamToList(ParamNode* list, ParamNode* newParam);