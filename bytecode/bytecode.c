#include "bytecode.h"


// запись в файл строки в utf8
void constUtf8(FILE* file, char* str) {
    int lenStr = strlen(str);
    appendByte_BC(file, UTF8);
    appendTwoByte_BC(file, lenStr);

    for (int i = 0; i < lenStr; i++) {
        appendByte_BC(file, str[i]);
    }
}

// запись в файл 4-байтного числа в utf8
void constInt(FILE* file, int value) {
    appendByte_BC(file, INT);
    appendFourByte_BC(file, value);
}

// запись в файл 8-байтного числа в utf8
void constLong(FILE* file, uint64_t value) {
    appendByte_BC(file, LONG);
    appendEightByte_BC(file, value);
}

// запись в файл 8-байтного дробного числа
void constDouble(FILE* file, double value) {
    appendByte_BC(file, DOUBLE);

    uint64_t bits = 0;
    memcpy(&bits, &value, sizeof(double));

    appendEightByte_BC(file, bits);
}

// запись в файл ссылку на класс
void constClass(FILE* file, uint16_t classNameConstNum) {
    appendByte_BC(file, CLASS);
    appendTwoByte_BC(file, classNameConstNum);
}

// запись в файл ссылку на строку
void constStr(FILE* file, uint16_t strConstNum) {
    appendByte_BC(file, STR);
    appendTwoByte_BC(file, strConstNum);
}

// запись в файл ссылку на имя и декриптор
void constNt(FILE* file, uint16_t nameConstNum, uint16_t typeConstNum) {
    appendByte_BC(file, NT);
    appendTwoByte_BC(file, nameConstNum);
    appendTwoByte_BC(file, typeConstNum);
}

// запись в файл ссылку на поле класса через ссылки на класс и nt
void constFref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum) {
    appendByte_BC(file, FREF);
    appendTwoByte_BC(file, classConstNum);
    appendTwoByte_BC(file, ntConstNum);
}

// запись в файл ссылку на метод класса через ссылки на класс и nt
void constMref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum) {
    appendByte_BC(file, MREF);
    appendTwoByte_BC(file, classConstNum);
    appendTwoByte_BC(file, ntConstNum);
}



void iconst_J(Bytes* bytes, int8_t value) {
    if (value < -1 || value > 5)
    //    throw "The number must be between -1 and 5";
        return;

    appendByte_B(bytes, value+3);
}


void bipush_J(Bytes* bytes, int8_t value) {
    appendByte_B(bytes, 0x10);
    appendByte_B(bytes, value);
}

void sipush_J(Bytes* bytes, int16_t value) {
    appendByte_B(bytes, 0x11);
    appendTwoByte_B(bytes, value);
}


void ldc_J(Bytes* bytes, int8_t constNum) {
    appendByte_B(bytes, 0x12);
    appendByte_B(bytes, constNum);
}

void ldc_w_J(Bytes* bytes, int16_t constNum) {
    appendByte_B(bytes, 0x13);
    appendTwoByte_B(bytes, constNum);
}


void iload_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes, 0x15);
    appendByte_B(bytes, localVarIndex);
}

void aload_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes, 0x19);
    appendByte_B(bytes, localVarIndex);
}


void istore_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes, 0x36);
    appendByte_B(bytes, localVarIndex);
}

void astore_J(Bytes* bytes, int8_t localVarIndex) {
    appendByte_B(bytes, 0x3A);
    appendByte_B(bytes, localVarIndex);
}


void pop_J(Bytes* bytes) {
    appendByte_B(bytes, 0x57);
}

void dup_J(Bytes* bytes) {
    appendByte_B(bytes, 0x59);
}

void dup2_J(Bytes* bytes) {
    appendByte_B(bytes, 0x5C);
}



void iadd_J(Bytes* bytes) {
    appendByte_B(bytes, 0x60);
}

void imul_J(Bytes* bytes) {
    appendByte_B(bytes, 0x68);
}

void isub_J(Bytes* bytes) {
    appendByte_B(bytes, 0x64);
}

void idiv_J(Bytes* bytes) {
    appendByte_B(bytes, 0x6C);
}



void if_icmpeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9F);
    appendTwoByte_B(bytes, shift);
}

void if_icmpne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA0);
    appendTwoByte_B(bytes, shift);
}

void if_icmplt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA1);
    appendTwoByte_B(bytes, shift);
}

void if_icmple_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA4);
    appendTwoByte_B(bytes, shift);
}

void if_icmpgt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA3);
    appendTwoByte_B(bytes, shift);
}

void if_icmpge_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA2);
    appendTwoByte_B(bytes, shift);
}


void ifeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x99);
    appendTwoByte_B(bytes, shift);
}

void ifne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9A);
    appendTwoByte_B(bytes, shift);
}

void iflt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9B);
    appendTwoByte_B(bytes, shift);
}

void ifle_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9E);
    appendTwoByte_B(bytes, shift);
}

void ifgt_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9D);
    appendTwoByte_B(bytes, shift);
}

void ifge_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0x9C);
    appendTwoByte_B(bytes, shift);
}


void if_acmpeq_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA5);
    appendTwoByte_B(bytes, shift);
}

void if_acmpne_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA6);
    appendTwoByte_B(bytes, shift);
}


void goto_J(Bytes* bytes, int16_t shift) {
    appendByte_B(bytes, 0xA7);
    appendTwoByte_B(bytes, shift);
}


// тут может быть работа с массивом

//

void new_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes, 0xBB);
    appendTwoByte_B(bytes, classConstNum);
}

void getfield_J(Bytes* bytes, int16_t constFrefNum) {
    appendByte_B(bytes, 0xB4);
    appendTwoByte_B(bytes, constFrefNum);
}

void putfield_J(Bytes* bytes, int16_t constFrefNum) {
    appendByte_B(bytes, 0xB5);
    appendTwoByte_B(bytes, constFrefNum);
}

void instanceof_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes, 0xC1);
    appendTwoByte_B(bytes, classConstNum);
}

void checkcast_J(Bytes* bytes, int16_t classConstNum) {
    appendByte_B(bytes, 0xC0);
    appendTwoByte_B(bytes, classConstNum);
}


void invokevirtual_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes, 0xB6);
    appendTwoByte_B(bytes, constMrefNum);
}

void invokespecial_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes, 0xB7);
    appendTwoByte_B(bytes, constMrefNum);
}

void invokestatic_J(Bytes* bytes, int16_t constMrefNum) {
    appendByte_B(bytes, 0xB8);
    appendTwoByte_B(bytes, constMrefNum);
}

void ireturn_J(Bytes* bytes) {
    appendByte_B(bytes, 0xAC);
}
void areturn_J(Bytes* bytes) {
    appendByte_B(bytes, 0xB0);
}

void return_J(Bytes* bytes) {
    appendByte_B(bytes, 0xB1);
}


// записывает в файл 1 байт
void appendByte_BC(FILE* file, uint8_t value) {
    fprintf(file, "%c", value);
}

// записывает в файл 2 байта
void appendTwoByte_BC(FILE* file, uint16_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);

    fprintf(file, "%c%c", value2, value1);
}

// записывает в файл 4 байта
void appendFourByte_BC(FILE* file, uint32_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);
    uint8_t value3 = (value >> 16);
    uint8_t value4 = (value >> 24);

    fprintf(file, "%c%c%c%c", value4, value3, value2, value1);
}

// записывает в файл 8 байт
void appendEightByte_BC(FILE* file, uint64_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);
    uint8_t value3 = (value >> 16);
    uint8_t value4 = (value >> 24);
    uint8_t value5 = (value >> 32);
    uint8_t value6 = (value >> 40);
    uint8_t value7 = (value >> 48);
    uint8_t value8 = (value >> 56);

    fprintf(file, "%c%c%c%c%c%c%c%c",
        value8, value7, value6, value5, value4, value3, value2, value1);
}




// возращает текущее кол-во байт в буфере
int size_B(Bytes bytes){
    return arrlen(bytes.values);
}

// добавляет 1 байт в буфер
void appendByte_B(Bytes* bytes, uint8_t value){
    arrput(bytes->values, value);
}

// добавляет 2 байта в буфер
void appendTwoByte_B(Bytes* bytes, uint16_t value) {
    uint8_t value1 = value;
    uint8_t value2 = (value >> 8);

    appendByte_B(bytes, value2);
    appendByte_B(bytes, value1);
}

// добавляет 4 байта в буфер
void appendFourByte_B(Bytes* bytes, uint32_t value) {
    for (int shift = 24; shift >= 0; shift-=8) 
        appendByte_B(bytes, (value >> shift));
}

// добавляет 8 байт в буфер
void appendEightByte_B(Bytes* bytes, uint64_t value) {
    for (int shift = 56; shift >= 0; shift-=8) 
        appendByte_B(bytes, (value >> shift));
}

// добавляет в конец все байты из bytes в this
void append_B(Bytes* this, Bytes* bytes) {
    for (int i = 0; i < arrlen(bytes->values); i++) {
        arrput(this->values, bytes->values[i]);
    }
}

// записывает в файл все байты из буфера
void write_B(Bytes bytes, FILE* file) {
    for (int i = 0; i < arrlen(bytes.values); i++) {
        fprintf(file, "%c", bytes.values[i]);
    }
}
