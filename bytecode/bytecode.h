#pragma once

// Потом нормально подключить
#include <stdio.h>
#include "semantic.h"
#include "std_ds.h"



void constUtf8(FILE* file, char* str);
void constInt(FILE* file, int value);
void constLong(FILE* file, uint64_t value);
void constDouble(FILE* file, double value);
void constClass(FILE* file, uint16_t classNameConstNum);
void constStr(FILE* file, uint16_t strConstNum);
void constNt(FILE* file, uint16_t nameConstNum, uint16_t typeConstNum);
void constFref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum);
void constMref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum);




void iconst_J(Bytes* bytes, int8_t value);

void bipush_J(Bytes* bytes, int8_t value);
void sipush_J(Bytes* bytes, int16_t value);

void ldc_J(Bytes* bytes, int8_t constNum);
void ldc_w_J(Bytes* bytes, int16_t constNum);

void iload_J(Bytes* bytes, int8_t localVarIndex);
void aload_J(Bytes* bytes, int8_t localVarIndex);

void istore_J(Bytes* bytes, int8_t localVarIndex);
void astore_J(Bytes* bytes, int8_t localVarIndex);

void pop_J(Bytes* bytes);
void dup_J(Bytes* bytes);
void dup2_J(Bytes* bytes);


void iadd_J(Bytes* bytes);
void imul_J(Bytes* bytes);
void isub_J(Bytes* bytes);
void idiv_J(Bytes* bytes);


void if_icmpeq_J(Bytes* bytes, int16_t shift);
void if_icmpne_J(Bytes* bytes, int16_t shift);
void if_icmplt_J(Bytes* bytes, int16_t shift);
void if_icmple_J(Bytes* bytes, int16_t shift);
void if_icmpgt_J(Bytes* bytes, int16_t shift);
void if_icmpge_J(Bytes* bytes, int16_t shift);

void ifeq_J(Bytes* bytes, int16_t shift);
void ifne_J(Bytes* bytes, int16_t shift);
void iflt_J(Bytes* bytes, int16_t shift);
void ifle_J(Bytes* bytes, int16_t shift);
void ifgt_J(Bytes* bytes, int16_t shift);
void ifge_J(Bytes* bytes, int16_t shift);

void if_acmpeq_J(Bytes* bytes, int16_t shift);
void if_acmpne_J(Bytes* bytes, int16_t shift);

void goto_J(Bytes* bytes, int16_t shift);

// тут может быть работа с массивом

//

void new_J(Bytes* bytes, int16_t classConstNum);
void getfield_J(Bytes* bytes, int16_t constFrefNum);
void putfield_J(Bytes* bytes, int16_t constFrefNum);
void instanceof_J(Bytes* bytes, int16_t classConstNum);
void checkcast_J(Bytes* bytes, int16_t classConstNum);


void invokevirtual_J(Bytes* bytes, int16_t constMrefNum);
void invokespecial_J(Bytes* bytes, int16_t constMrefNum);
void invokestatic_J(Bytes* bytes, int16_t constMrefNum);

void ireturn_J(Bytes* bytes);
void areturn_J(Bytes* bytes);
void return_J(Bytes* bytes);


void appendByte_BC(FILE* file, uint8_t value);
void appendTwoByte_BC(FILE* file, uint16_t value);
void appendFourByte_BC(FILE* file, uint32_t value);
void appendEightByte_BC(FILE* file, uint64_t value);


typedef struct Bytes {
    uint8_t* values = NULL;
} Bytes;

int size_B(Bytes bytes);
void appendByte_B(Bytes* bytes, uint8_t value);
void appendTwoByte_B(Bytes* bytes, uint16_t value);
void appendFourByte_B(Bytes* bytes, uint32_t value);
void appendEightByte_B(Bytes* bytes, uint64_t value);
void append_B(Bytes* this, Bytes* bytes);
void write__B(Bytes bytes, FILE* file);