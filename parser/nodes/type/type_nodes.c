#include "expr_nodes.h"

TypeNode* createIdType(char* value) {
    TypeNode* result = calloc(1, sizeof(TypeNode));

    result->type = IdType;
    result->id = value;

    return result;
}


TypeNode* createArrayType(TypeNode* innerType) {
    TypeNode* result = calloc(1, sizeof(TypeNode));

    result->type = ListType;
    result->innerType = innerType;

    return result;
}