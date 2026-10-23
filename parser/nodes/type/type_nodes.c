#include "type_nodes.h"

TypeNode* createIdType(char* value) {
    TypeNode* result = calloc(1, sizeof(TypeNode));

    result->nodeId = globalId++;

    result->type = IdTType;
    result->id = value;

    return result;
}


TypeNode* createArrayType(TypeNode* innerType) {
    TypeNode* result = calloc(1, sizeof(TypeNode));

    result->nodeId = globalId++;

    result->type = ListTType;
    result->innerType = innerType;

    return result;
}

TypeNode* createVoidType() {
    TypeNode* result = calloc(1, sizeof(TypeNode));

    result->nodeId = globalId++;

    result->type = VoidTType;
}