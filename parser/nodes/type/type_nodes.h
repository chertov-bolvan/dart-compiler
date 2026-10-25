#include <stdio.h>
#include <stdlib.h>
#include "global_id.c"

typedef enum TypeNodeType {
    IdTType, ListTType, VoidTType,
} TypeNodeType;


typedef struct TypeNode {
    int nodeId;
    TypeNodeType type;

    char* id;
    struct TypeNode* innerType;
} TypeNode;


TypeNode* createIdType(char* value);
TypeNode* createArrayType(TypeNode* innerType);
TypeNode* createVoidType();