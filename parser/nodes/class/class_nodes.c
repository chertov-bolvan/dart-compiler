#include "class_nodes.h"

SuperConstructorNode* createSuperConstructor(char* constructorName, ArgNode* arguments) {
  SuperConstructorNode* result = calloc(1, sizeof(SuperConstructorNode));

  result->nodeId = globalId++;

  result->constructorName = constructorName;
  result->arguments = arguments;

  return result;
}


ConstructorDeclNode* createConstructorDecl(char* id, char* constructorName, ParamNode* parameters, SuperConstructorNode* superConstructor, StmtNode* body) {
  ConstructorDeclNode* result = calloc(1, sizeof(ConstructorDeclNode));

  result->nodeId = globalId++;

  result->id = id;
  result->constructorName = constructorName;
  result->parameters = parameters;
  result->superConstructor = superConstructor;
  result->body = body;

  return result;
}


ClassDeclNode* createClassDecl(ClassModifier modifier, char* id, char* parentId, ClassMemberNode* classMembers) {
  ClassDeclNode* result = calloc(1, sizeof(ClassDeclNode));

  result->nodeId = globalId++;

  result->classModifier = modifier;
  result->id = id;
  result->parentId = parentId;
  result->classMembers = classMembers;

  return result;
}


ClassMemberNode* createFieldMember(int isStatic, VarDeclNode* varDeclNode) {
  ClassMemberNode* result = calloc(1, sizeof(ClassMemberNode));

  result->nodeId = globalId++;
  
  result->type = FieldMemberType;
  result->isStatic = isStatic;
  result->varDeclNode = varDeclNode;

  return result;
}

ClassMemberNode* createMethodMember(ClassMemberType type, int isStatic, FuncDeclNode* funcDeclNode) {
  ClassMemberNode* result = calloc(1, sizeof(ClassMemberNode));

  result->nodeId = globalId++;
  
  result->type = type;
  result->isStatic = isStatic;
  result->funcDeclNode = funcDeclNode;

  return result;
}

ClassMemberNode* createConstructorMember(ConstructorDeclNode* constructorDeclNode) {
  ClassMemberNode* result = calloc(1, sizeof(ClassMemberNode));

  result->nodeId = globalId++;
  
  result->type = ConstructorMemberType;
  result->isStatic = 0;
  result->constructorDeclNode = constructorDeclNode;

  return result;
}

ClassMemberNode* addClassMemberToList(ClassMemberNode* list, ClassMemberNode* newMember) {
  ClassMemberNode* current = list;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = newMember;

  return list;
}