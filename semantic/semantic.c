#include "semantic.h"



// ---- Реализация функций для ConstantsTable ----

uint16_t add_CT(JvmConstant* constant) {

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
