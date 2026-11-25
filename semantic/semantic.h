#pragma once

// потом нормально заинклюдить
#include "string.h"
#include "../map/map.h"
#include "../parser/nodes/global/global_nodes.h"


typedef enum SemanticFuncType {
    SemanticFunction, SemanticMethod, SemanticGetter, SemanticSetter, SemanticConstructor
} SemanticFuncType;


typedef struct SemanticType {

} SemanticType;


typedef struct SemanticProgram {
    struct ProgramNode* program;

    Map classes;
    Map functions;
    Map globalVars;
} SemanticProgram;


typedef struct SemanticClass {
    struct ClassDeclNode* classDecl;
    struct SemanticClass* parent;

    Map fields;
    Map methods;
    Map getters;
    Map setters;

    Map namedConstructors;
    struct SemanticFunc* unnamedConstructor;

} SemanticClass;


typedef struct SemanticVar {
    struct VarDeclaratorNode* varDecl;
    struct TypeNode* declType;

    VarDeclModifier modifier;

    struct SemanticClass* owner;
    int isStatic;

    struct SemanticType* type;    
} SemanticVar;


typedef struct SemanticFunc {
    const char* name;
    SemanticFuncType type;

    struct SemanticClass* owner;
    int isStatic;

    struct SemanticType* returnType;

    struct FuncDeclNode* func;
    struct ConstructorDeclNode* constructor;
} SemanticFunc;


typedef struct ConstantsTable {
    JvmConstant* values = NULL;

} ConstantsTable;

    uint16_t add_CT(ConstantsTable* table, JvmConstant* constant);
    uint16_t addUtf8_CT(char* str);
    uint16_t addClass_CT(char* className);
    uint16_t addStr_CT(char* strConstant);
    uint16_t addNt_CT(char* name, char* descriptor);
    uint16_t addFref_CT(char* className, char* name, char* descriptor);
    uint16_t addMref_CT(char* className, char* name, char* descriptor);


typedef enum JvmConstantType {
    UTF8 = 1,
    INT = 3,
    LONG = 5,
    DOUBLE = 6,
    CLASS = 7,
    STR = 8,
    FREF = 9,
    MREF = 10,
    NT = 12
} JvmConstantType;


typedef struct JvmConstant {
    JvmConstantType type;

    char* utf8Value;
    int32_t intValue = 0;
    int64_t longValue = 0;
    double doubleValue = 0;
    uint16_t constNum1 = 0;
    uint16_t constNum2 = 0;

} JvmConstant;

JvmConstant utf8(char* str);
JvmConstant int32(int32_t value);
JvmConstant int64(int64_t value);
JvmConstant double64(double value);
JvmConstant str(uint16_t strConstNum);
JvmConstant classConst(uint16_t classNameConstNum);
JvmConstant nt(uint16_t nameConstNum, uint16_tdescriptorConstNum);
JvmConstant fref(uint16_t classConstNum, uint16_t ntConstNum);
JvmConstant mref(uint16_t classConstNum, uint16_t ntConstNum);

int equalsJC(JvmConstant constant1, JvmConstant constant2);


// Здесь могла быть реклама вашего автосервиса
int octavia_stage1(SemanticProgram* semantic);
void octavia_stock(SemanticProgram* semantic);

