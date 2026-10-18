#include <stdio.h>
#include <stdlib.h>

typedef enum TypeNodeType {
    IdTType, ListTType,
} TypeNodeType;


typedef struct TypeNode {
    TypeNodeType type;

    char* id;
    struct TypeNode* innerType;
} TypeNode;


TypeNode* createIdType(char* value);
TypeNode* createArrayType(TypeNode* innerType);