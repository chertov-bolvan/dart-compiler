#include "func_nodes.h"

FuncDeclNode* createFuncDecl(TypeNode* type, char* identifier, ParamNode* parameters, StmtNode* body) {
  FuncDeclNode* result = calloc(1, sizeof(FuncDeclNode));

  result->id = globalId++;

  result->type = type;
  result->identifier = identifier;
  result->parameters = parameters;
  result->body = body;

  return result;
}


ParamNode* createParam(TypeNode* type, char* identifier) {
  ParamNode* result = calloc(1, sizeof(ParamNode));

  result->id = globalId++;

  result->type = type;
  result->identifier = identifier;

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