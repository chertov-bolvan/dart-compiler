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


typedef struct SuperConstructorNode {
  int nodeId;

  char* constructorName;
  struct ArgNode* arguments;
} SuperConstructorNode;


typedef struct ConstructorDeclNode {
  int nodeId;

  char* id;
  char* constructorName;

  struct ParamNode* parameters;
  struct SuperConstructorNode* superConstructor;
  struct StmtNode* body;
} ConstructorDeclNode;


typedef enum ClassMemberType {
  FieldMemberType, MethodMemberType, GetterMemberType, SetterMemberType, ConstructorMemberType,
} ClassMemberType;

typedef struct ClassMemberNode {
  int nodeId;

  ClassMemberType type;

  int isStatic;

  struct VarDeclNode* varDeclNode;
  struct FuncDeclNode* funcDeclNode;
  struct ConstructorDeclNode* constructorDeclNode;
  
  struct ClassMemberNode* next;
} ClassMemberNode;


SuperConstructorNode* createSuperConstructor(char* constructorName, ArgNode* arguments);


ConstructorDeclNode* createConstructorDecl(char* id, char* constructorName, ParamNode* parameters, SuperConstructorNode* superConstructor, StmtNode* body);


ClassDeclNode* createClassDecl(ClassModifier modifier, char* id, char* parentId, ClassMemberNode* classMembers);


ClassMemberNode* createFieldMember(int isStatic, VarDeclNode* varDeclNode);
ClassMemberNode* createMethodMember(ClassMemberType type, int isStatic, FuncDeclNode* funcDeclNode);
ClassMemberNode* createConstructorMember(ConstructorDeclNode* constructorDeclNode);

ClassMemberNode* addClassMemberToList(ClassMemberNode* list, ClassMemberNode* newMember);