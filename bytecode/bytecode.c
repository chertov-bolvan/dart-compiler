#include "bytecode.h"



void iconst_J(Bytes* bytes, int8_t value) {

}


void bipush_J(Bytes* bytes, int8_t value) {

}

void sipush_J(Bytes* bytes, int16_t value) {

}


void ldc_J(Bytes* bytes, int8_t constNum) {

}

void ldc_w_J(Bytes* bytes, int16_t constNum) {

}


void iload_J(Bytes* bytes, int8_t localVarIndex) {

}

void aload_J(Bytes* bytes, int8_t localVarIndex) {

}


void istore_J(Bytes* bytes, int8_t localVarIndex) {

}

void astore_J(Bytes* bytes, int8_t localVarIndex) {

}


void pop_J(Bytes* bytes) {

}

void dup_J(Bytes* bytes) {

}

void dup2_J(Bytes* bytes) {
    \
}



void iadd_J(Bytes* bytes) {

}

void imul_J(Bytes* bytes) {

}

void isub_J(Bytes* bytes) {

}

void idiv_J(Bytes* bytes) {

}



void if_icmpeq_J(Bytes* bytes, int16_t shift) {

}

void if_icmpne_J(Bytes* bytes, int16_t shift) {

}

void if_icmplt_J(Bytes* bytes, int16_t shift) {

}

void if_icmple_J(Bytes* bytes, int16_t shift) {

}

void if_icmpgt_J(Bytes* bytes, int16_t shift) {

}

void if_icmpge_J(Bytes* bytes, int16_t shift) {

}


void ifeq_J(Bytes* bytes, int16_t shift) {

}

void ifne_J(Bytes* bytes, int16_t shift) {

}

void iflt_J(Bytes* bytes, int16_t shift) {

}

void ifle_J(Bytes* bytes, int16_t shift) {

}

void ifgt_J(Bytes* bytes, int16_t shift) {

}

void ifge_J(Bytes* bytes, int16_t shift) {

}


void if_acmpeq_J(Bytes* bytes, int16_t shift) {

}

void if_acmpne_J(Bytes* bytes, int16_t shift) {

}


void goto_J(Bytes* bytes, int16_t shift) {
    
}


// тут может быть работа с массивом

//

void new_J(Bytes* bytes, int16_t classConstNum) {

}

void getfield_J(Bytes* bytes, int16_t constFrefNum) {

}

void putfield_J(Bytes* bytes, int16_t constFrefNum) {

}

void instanceof_J(Bytes* bytes, int16_t classConstNum) {

}

void checkcast_J(Bytes* bytes, int16_t classConstNum) {

}


void invokevirtual_J(Bytes* bytes, int16_t constMrefNum) {

}

void invokespecial_J(Bytes* bytes, int16_t constMrefNum) {

}

void invokestatic_J(Bytes* bytes, int16_t constMrefNum) {

}

void ireturn_J(Bytes* bytes) {

}
void areturn_J(Bytes* bytes) {

}

void return_J(Bytes* bytes) {

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