#include "bytecode.h"



void iconst_J(Bytes* bytes, int8_t value) {
    if (value < -1 || value > 5)
        throw "The number must be between -1 and 5";

    appendByte_B(bytes->values, value+3);
}


void bipush_J(Bytes* bytes, int8_t value) {
    appendByte_B(bytes->values, 0x10);
    appendByte_B(bytes->values, value);
}

void sipush_J(Bytes* bytes, int16_t value) {
    appendByte_B(bytes->values, 0x11);
    appendTwoByte_B(bytes->values, value);
}


void ldc_J(Bytes* bytes, int8_t constNum) {
    appendByte_B(bytes->values, 0x12);
    appendByte_B(bytes->values, constNum);
}

void ldc_w_J(Bytes* bytes, int16_t constNum) {
    appendByte_B(bytes->values, 0x13);
    appendTwoByte_B(bytes->values, constNum);
}


void iload_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes->values, 0x15);
    appendByte_B(bytes->values, localVarIndex);
}

void aload_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes->values, 0x19);
    appendByte_B(bytes->values, localVarIndex);
}


void istore_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes->values, 0x36);
    appendByte_B(bytes->values, localVarIndex);
}

void astore_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes->values, 0x3A);
    appendByte_B(bytes->values, localVarIndex);
}


void pop_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x57);
}

void dup_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x59);
}

void dup2_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x5C);
}



void iadd_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x60);
}

void imul_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x68);
}

void isub_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x64);
}

void idiv_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0x6C);
}



void if_icmpeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9F);
    appendTwoByte_B(bytes->values, shift);
}

void if_icmpne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA0);
    appendTwoByte_B(bytes->values, shift);
}

void if_icmplt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA1);
    appendTwoByte_B(bytes->values, shift);
}

void if_icmple_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA4);
    appendTwoByte_B(bytes->values, shift);
}

void if_icmpgt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA3);
    appendTwoByte_B(bytes->values, shift);
}

void if_icmpge_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA2);
    appendTwoByte_B(bytes->values, shift);
}


void ifeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x99);
    appendTwoByte_B(bytes->values, shift);
}

void ifne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9A);
    appendTwoByte_B(bytes->values, shift);
}

void iflt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9B);
    appendTwoByte_B(bytes->values, shift);
}

void ifle_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9E);
    appendTwoByte_B(bytes->values, shift);
}

void ifgt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9D);
    appendTwoByte_B(bytes->values, shift);
}

void ifge_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0x9C);
    appendTwoByte_B(bytes->values, shift);
}


void if_acmpeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA5);
    appendTwoByte_B(bytes->values, shift);
}

void if_acmpne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA6);
    appendTwoByte_B(bytes->values, shift);
}


void goto_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes->values, 0xA7);
    appendTwoByte_B(bytes->values, shift);
}


// тут может быть работа с массивом

//

void new_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes->values, 0xBB);
    appendTwoByte_B(bytes->values, classConstNum);
}

void getfield_J(Bytes* bytes, int16_t constFrefNum) {
    appendByte_B(bytes->values, 0xB4);
    appendTwoByte_B(bytes->values, constFrefNum);
}

void putfield_J(Bytes* bytes, int16_t constFrefNum) {
    appendByte_B(bytes->values, 0xB5);
    appendTwoByte_B(bytes->values, constFrefNum);
}

void instanceof_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes->values, 0xC1);
    appendTwoByte_B(bytes->values, classConstNum);
}

void checkcast_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes->values, 0xC0);
    appendTwoByte_B(bytes->values, classConstNum);
}


void invokevirtual_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes->values, 0xB6);
    appendTwoByte_B(bytes->values, constMrefNum);
}

void invokespecial_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes->values, 0xB7);
    appendTwoByte_B(bytes->values, constMrefNum);
}

void invokestatic_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes->values, 0xB8);
    appendTwoByte_B(bytes->values, constMrefNum);
}

void ireturn_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0xAC);
}
void areturn_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0xB0);
}

void return_J(Bytes* bytes) {
    appendByte_B(bytes->values, 0xB1);
}


void appendByte_BC(FILE* file, uint8_t value) {
    fprintf(file, "%c", value);
}

void appendTwoByte_BC(FILE* file, uint16_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);

    fprintf(file, "%c%c", value2, value1);
}

void appendFourByte_BC(FILE* file, uint32_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);
    uint8_t value3 = (value >> 16);
    uint8_t value4 = (value >> 24);

    fprintf(file, "%c%c%c%c", value4, value3, value2, value1);
}





int size_B(Bytes bytes){
    return arrlen(bytes->values);
}

void appendByte_B(Bytes* bytes, uint8_t value){
    arrput(bytes->values, value);
}

void appendTwoByte_B(Bytes* bytes, uint16_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);

    appendByte_B(bytes, value2);
    appendByte_B(bytes, value1);
}

void appendFourByte_B(Bytes* bytes, uint32_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);
    uint8_t value3 = (value >> 16);
    uint8_t value4 = (value >> 24)

    appendByte_B(bytes, value4);
    appendByte_B(bytes, value3);
    appendByte_B(bytes, value2);
    appendByte_B(bytes, value1);
}

void append_B(Bytes* this, Bytes* bytes) {
    for (int i = 0; i < arrlen(bytes->values); i++) {
        arrput(this->values, bytes->values);
    }
}

void write_B(Bytes bytes, FILE* file) {
    for (int i = 0; i < arrlen(bytes->values); i++) {
        fprintf(file, "%c", bytes->values[i]);
    }
}
