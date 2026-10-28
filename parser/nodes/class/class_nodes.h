#include <stdio.h>
#include <stdlib.h>
#include "../stmt/stmt_nodes.h"
#include "../func/func_nodes.h"
#include "../global_id.h"

typedef enum ClassModifier {
  NoClassModifier, AbstractClassModifier, FinalClassModifier, AbstractFinalClassModifier,
} ClassModifier;

typedef struct ClassDeclNode {
  int nodeId;

  ClassModifier classModifier;
  char* id;
  
  char* parentId;

  struct ClassMemberNode* classMembers;
} ClassDeclNode;


typedef enum ClassMemberType {
  FieldMemberType, MethodMemberType, GetterMemberType, SetterMemberType,
} ClassMemberType;

typedef struct ClassMemberNode {
  int nodeId;

  ClassMemberType type;

  int isStatic;

  struct VarDeclNode* varDeclNode;
  struct FuncDeclNode* funcDeclNode;
  
  struct ClassMemberNode* next;
} ClassMemberNode;


ClassDeclNode* createClassDecl(ClassModifier modifier, char* id, char* parentId, ClassMemberNode* classMembers);


ClassMemberNode* createFieldMember(int isStatic, VarDeclNode* varDeclNode);
ClassMemberNode* createMethodMember(ClassMemberType type, int isStatic, FuncDeclNode* funcDeclNode);

ClassMemberNode* addClassMemberToList(ClassMemberNode* list, ClassMemberNode* newMember);