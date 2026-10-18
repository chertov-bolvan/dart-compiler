#include "expr_nodes.h"

ExprNode* createIntExpr(int value) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = IntType;
    result->intValue = value;

    return result;
}


ExprNode* createBoolExpr(int value) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = BoolType;
    result->boolValue = value;

    return result;
}


ExprNode* createDoubleExpr(double value) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = DoubleType;
    result->doubleValue = value;

    return result;
}


ExprNode* createStringExpr(char* value) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = StringType;
    result->strValue = value;

    return result;
}


ExprNode* createIDExpr(char* value) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = IdType;
    result->id = value;

    return result;
}


ExprNode* createExpr(ExprNodeType type) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = type;

    return result;
}


ExprNode* createOperationTypeExpr(ExprNodeType type, ExprNode* left, TypeNode* typeNode) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = type;
    result->left = left;
    result->typeNode = typeNode;

    return result;
}


ExprNode* createBinExpr(ExprNodeType type, ExprNode* left, ExprNode* right) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = type;
    result->left = left;
    result->right = right;

    return result;
}


ExprNode* createPrifixUnExpr(ExprNodeType type, ExprNode* expr) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = type;
    result->right = expr;

    return result;
}



ExprNode* createPostfixUnExpr(ExprNodeType type, ExprNode* expr) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = type;
    result->left = expr;

    return result;
}


ExprNode* createAccessFieldExpr(ExprNode* expr, char* fieldId) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = AccessFieldType;
    result->left = expr;
    result->id = fieldId;

    return result;
}


ExprNode* createMethodCallExpr(ExprNode* expr, char* methodId, ExprNode* arguments) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = MethodType;
    result->left = expr;
    result->id = methodId;
    result->args = arguments;

    return result;
}


ExprNode* createFuncCallExpr(char* funcId, ExprNode* arguments) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = FuncType;
    result->id = funcId;
    result->args = arguments;

    return result;
}


ExprNode* createTernaryOperatorExpr(ExprNode* left, ExprNode* center, ExprNode* right) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = TernaryOperatorType;
    result->left = left;
    result->center = center;
    result->right = right;

    return result;
}


ExprNode* createAccessArrElementExpr(ExprNode* left, ExprNode* right) {
    ExprNode* result = calloc(1, sizeof(ExprNode));

    result->type = AccessArrElementType;
    result->left = left;
    result->right = right;

    return result;
}


ExprNode* addExprToListExpr(ExprNode* list, ExprNode* elem) {
    ExprNode* result = list;

    while (list->next != NULL)
        list = list->next;
    list->next = elem;

    return result;
}
