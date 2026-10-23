#include "global_nodes.h"

ProgramNode* createProgram(TopLevelDeclNode* topLevelDeclNode) {
  ProgramNode* result = calloc(1, sizeof(ProgramNode));

  result->nodeId = globalId++;

  result->topLevelDeclNode = topLevelDeclNode;

  return result;
}


TopLevelDeclNode* createTopLevelVarDecl(VarDeclNode* varDeclNode) {
  TopLevelDeclNode result = calloc(1, sizeof(TopLevelDeclNode));

  result->nodeId = globalId++;

  result->type = TopLevelVarDeclType;
  result->varDeclNode = varDeclNode;

  return result;
}

TopLevelDeclNode* createTopLevelFuncDecl(FuncDeclNode* funcDeclNode) {
  TopLevelDeclNode result = calloc(1, sizeof(TopLevelDeclNode));

  result->nodeId = globalId++;

  result->type = TopLevelFuncDeclType;
  result->funcDeclNode = funcDeclNode;

  return result;
}

// TopLevelDeclNode* createTopLevelClassDecl(ClassDeclNode* classDeclNode) {
//   TopLevelDeclNode result = calloc(1, sizeof(TopLevelDeclNode));

//   result->nodeId = globalId++;

//   result->type = TopLevelClassDeclType;
//   result->classDeclNode = classDeclNode;

//   return result;
// }

TopLevelDeclNode* addTopLevelDeclToList(TopLevelDeclNode* list, TopLevelDeclNode* newTopLevelDecl) {
  TopLevelDeclNode* current = list;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = newTopLevelDecl;

  return list;
}