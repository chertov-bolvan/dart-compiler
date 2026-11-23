#pragma once

// Потом нормально подключить
#include <stdio.h>
#include "semantic.h"
#include "std_ds.h"



typedef struct Bytes {
    uint8_t values = NULL;
} Bytes;

int size_B(Bytes bytes);
void appendByte_B(Bytes* bytes, uint8_t value);
void appendTwoByte_B(Bytes* bytes, uint16_t value);
void appendFourByte_B(Bytes* bytes, uint32_t value);
void append(Bytes* this, Bytes* bytes);
void write(Bytes bytes, FILE* file);