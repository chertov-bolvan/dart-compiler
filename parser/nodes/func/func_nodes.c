#include "func_nodes.h"

FuncDeclNode* createFuncDecl(TypeNode* type, char* id, ParamNode* parameters, StmtNode* body) {
  FuncDeclNode* result = calloc(1, sizeof(FuncDeclNode));

  result->nodeId = globalId++;

  result->type = type;
  result->id = id;
  result->parameters = parameters;
  result->body = body;

  return result;
}


ParamNode* createParam(TypeNode* type, char* id) {
  ParamNode* result = calloc(1, sizeof(ParamNode));

  result->nodeId = globalId++;

  result->type = type;
  result->id = id;

  return result;
}

ParamNode* addParamToList(ParamNode* list, ParamNode* newParam) {
  ParamNode* current = list;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = newParam;

  return list;
}