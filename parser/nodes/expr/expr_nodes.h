#include <stdio.h>
#include <stdlib.h>
#include "type_nodes.h"
#include "global_id.c"

typedef enum ExprNodeType {
    IntType, BoolType, DoubleType, StringType, 
    IdType, NullType, SuperType, ThisType, ListLiteralType,

    IncPostfixType, DecPostfixType, 
    AccessFieldType, ThisFuncType,
    SuperFuncType, FuncType, MethodType, 
    AccessArrElementType, 
    IncPrefixType, DecPrefixType,
    UminusType, NotType, MulType,
    DivType, ModType, IntDivType, AddType, 
    MinusType, LessType, GreaterType, 
    LEqType, GEqType, IsType, AsType, NIsType,
    EqEqType, NEqType, LogAndType, LogOrType,
    TernaryOperatorType, AddAssignType, 
    SubAssignType, MulAssignType, DivAssignType,
    ModAssignType, IntDivAssignType, EqType,
    ThisAccessFieldType, ThisMethodType,
    SuperAccessFieldType, SuperMethodType,
    NewClassType,
} ExprNodeType;

typedef struct ExprNode {
    ExprNodeType type;

    int nodeId;
    int intValue;
    double doubleValue;
    int boolValue;
    char* strValue;
    char* id;
    
    struct TypeNode* typeNode;
    struct ExprNode* args;
    struct ExprNode* left;
    struct ExprNode* center;
    struct ExprNode* right;

    int insideParens;

    struct ExprNode* next;
} ExprNode;


ExprNode* createIntExpr(int value);
ExprNode* createBoolExpr(int value);
ExprNode* createDoubleExpr(double value);
ExprNode* createStringExpr(char* value);
ExprNode* createIDExpr(char* value);
ExprNode* createExpr(ExprNodeType type);
ExprNode* createListLiteralExpr(ExprNode* expr);
ExprNode* createOperationTypeExpr(ExprNodeType type, ExprNode* left, TypeNode* typeNode);
ExprNode* createBinExpr(ExprNodeType type, ExprNode* left, ExprNode* right);
ExprNode* createPrefixUnExpr(ExprNodeType type, ExprNode* expr);
ExprNode* createPostfixUnExpr(ExprNodeType type, ExprNode* expr);
ExprNode* createAccessFieldExpr(ExprNode* expr, char* fieldId);
ExprNode* createMethodCallExpr(ExprNode* expr, char* methodId, ExprNode* arguments);
ExprNode* createFuncCallExpr(char* funcId, ExprNode* arguments);
ExprNode* createTernaryOperatorExpr(ExprNode* left, ExprNode* center, ExprNode* right);
ExprNode* createAccessArrElementExpr(ExprNode* left, ExprNode* right);
ExprNode* createThisFuncExpr(ExprNode* right);
ExprNode* createSuperFuncExpr(ExprNode* right);
ExprNode* createNewClass(char* classId, ExprNode* arguments);
ExprNode* addExprToListExpr(ExprNode* list, ExprNode* elem);