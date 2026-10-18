#include <stdio.h>
#include <stdlib.h>

typedef enum TypeNodeType {
    IdType, ListType,
} TypeNodeType;


typedef struct TypeNode {
    TypeNodeType type;

    char* id;
    TypeNode* innerType;
} TypeNode;


TypeNode* createIdType(char* value);
TypeNode* createArrayType(TypeNode* innerType);