#include "class_nodes.h"

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

ClassMemberNode* addClassMemberToList(ClassMemberNode* list, ClassMemberNode* newMember) {
  ClassMemberNode* current = list;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = newMember;

  return list;
}