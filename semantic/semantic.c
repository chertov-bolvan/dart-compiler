#include "semantic.h"


// ЭТАПЫ

int octavia_stage1(SemanticProgram* semantic) {

    int success = 1;

    for (TopLevelDeclNode* node = semantic->program->topLevelDeclNode; 
        node != NULL; 
        node = node->next) {
        
        if (node->type == TopLevelFuncDeclType) {
            FuncDeclNode* funcDecl = node->funcDeclNode;
            
            SemanticFunc* semanticFunc = calloc(1, sizeof(SemanticFunc));


            // ПОТОМ: Прописать ли овнера как класс Main?
            semanticFunc->name = funcDecl->id;
            semanticFunc->type = SemanticFunction;
            semanticFunc->func = funcDecl;

            if(!mapInsert(&semantic->functions, funcDecl->id, semanticFunc)) {
                fprintf(stderr, "Error: Function '%s' is already defined.\n", funcDecl->id);

                free(semanticFunc);
                success = 0;
            }

        }
        else if (node->type == TopLevelVarDeclType) {

        }
        else if (node->type == TopLevelClassDeclType) {

        }
    }


    return success;
}

void octavia_stock(SemanticProgram* semantic) { //semantic_free
    for (size_t i = 0; i < mapSize(&semantic->functions); i++) {
        SemanticFunc* func = mapValueAt(&semantic->functions, i);
        free(func);
    }

    mapFree(&semantic->functions);
}



// ---- Реализация функций для ConstantsTable ----

uint16_t add_CT(ConstantsTable* table, JvmConstant* constant) {
    uint16_t index = 0;
    for (;i < arrlen(table->values); i++) {
        if (equalsJC(table->value[i], constant))
            break;
    }

    if (i == arrlen(table->values))
        arrput(table->values, constant);

    return i+1;
}

uint16_t addUtf8_CT(char* str) {
    return add_CT(utf8(str));
}

uint16_t addClass_CT(char* className) {
    uint16_t classConstNum = add_CT(utf8(className));
    return add_CT(classConst(classConstNum));
}

uint16_t addStr_CT(char* strConstant) {
    uint16_t strConstNum = add_CT(utf8(strConstant));
    return add_CT(str(strConstNum));
}

uint16_t addNt_CT(char* name, char* descriptor) {
    uint16_t nameConstNum = addUtf8_CT(name);
    uint16_t descriptorConstNum = addUtf8_CT(descriptor);
    return add_CT(nt(nameConstNum, descriptorConstNum));
}

uint16_t addFref_CT(char* className, char* name, char* descriptor) {
    uint16_t classConstNum = addClass_CT(className);
    uint16_t ntConstNum = addNt_CT(char* name, char* descriptor);
    return add_CT(fref(classConstNum, ntConstNum));
}

uint16_t addMref_CT(char* className, char* name, char* descriptor) {
    uint16_t classConstNum = addClass_CT(className);
    uint16_t ntConstNum = addNt_CT(char* name, char* descriptor);
    return add_CT(mref(classConstNum, ntConstNum));
}


// ---- Реализация функций для JvmConstant ----

JvmConstant utf8(char* str) {
    JvmConstant result = {0};
    result.type = UTF8;
    result.utf8Value = strdup(str);

    return result;
}

JvmConstant int32(int32_t value) {
    JvmConstant result = {0};
    result.type = INT;
    result.intValue = value;

    return result;
}

JvmConstant int64(int64_t value) {
    JvmConstant result = {0};
    result.type = LONG;
    result.longValue = value;

    return result;
}

JvmConstant double64(double value) {
    JvmConstant result = {0};
    result.type = DOUBLE;
    result.longValue = value;

    return result;
}

JvmConstant str(uint16_t strConstNum) {
    JvmConstant result = {0};
    result.type = STR;
    result.constNum1 = strConstNum;

    return result;
}

JvmConstant classConst(uint16_t classNameConstNum) {
    JvmConstant result = {0};
    result.type = CLASS;
    result.constNum1 = classNameConstNum;

    return result;
}

JvmConstant nt(uint16_t nameConstNum, uint16_t descriptorConstNum) {
    JvmConstant result = {0};
    result.type = NT;
    result.constNum1 = nameConstNum;
    result.constNum2 = descriptorConstNum;

    return result;
}

JvmConstant fref(uint16_t classConstNum, uint16_t ntConstNum) {
    JvmConstant result = {0};
    result.type = FREF;
    result.constNum1 = classConstNum;
    result.constNum2 = ntConstNum;
    return result;
}

JvmConstant mref(uint16_t classConstNum, uint16_t ntConstNum) {
    JvmConstant result = {0};
    result.type = MREF;
    result.constNum1 = classConstNum;
    result.constNum2 = ntConstNum;

    return result;
}

int equalsJC(JvmConstant constant1, JvmConstant constant2) {
    return (constant1.type == constant2.type &&
    (constant1.utf8Value == constant2.utf8Value ||
    constant1.utf8Value != NULL && constant2.utf8Value != NULL &&
    strcmp(constant1.utf8Value, constant2.utf8Value) == 0) &&
    constant1.intValue == constant2.intValue &&
    constant1.longValue == constant2.longValue &&
    constant1.doubleValue == constant2.doubleValue &&
    constant1.constNum1 == constant2.constNum1 &&
    constant1.constNum2 == constant2.constNum2);
}