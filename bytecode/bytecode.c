#include "bytecode.h"






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