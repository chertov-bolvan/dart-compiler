#pragma once

// Потом нормально подключить
#include <stdio.h>
#include "semantic.h"
#include "std_ds.h"


// запись в файл строки в utf8
void constUtf8(FILE* file, char* str);
// запись в файл 4-байтного числа
void constInt(FILE* file, int value);
// запись в файл 8-байтного числа
void constLong(FILE* file, uint64_t value);
// запись в файл 8-байтного дробного числа
void constDouble(FILE* file, double value);
// запись в файл ссылку на класс
void constClass(FILE* file, uint16_t classNameConstNum);
// запись в файл ссылку на строку
void constStr(FILE* file, uint16_t strConstNum);
// запись в файл ссылку на имя и декриптор
void constNt(FILE* file, uint16_t nameConstNum, uint16_t typeConstNum);
// запись в файл ссылку на поле класса через ссылки на класс и nt
void constFref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum);
// запись в файл ссылку на метод класса через ссылки на класс и nt
void constMref(FILE* file, uint16_t classConstNum, uint16_t ntConstNum);



// загружает небольшую целочисленную константу i на стек
void iconst_J(Bytes* bytes, int8_t value);

// Команда bipush загружает на стек однобайтовую целую константу, sipush — двухбатовую
void bipush_J(Bytes* bytes, int8_t value);
void sipush_J(Bytes* bytes, int16_t value);

// загружают на стек целую или дробную константу из таблицы констант класса
void ldc_J(Bytes* bytes, int8_t constNum);
void ldc_w_J(Bytes* bytes, int16_t constNum);

//  загружают на стек целое число (iload) или ссылку (aload) из локальной переменной.
void iload_J(Bytes* bytes, int8_t localVarIndex);
void aload_J(Bytes* bytes, int8_t localVarIndex);

//  сохраняют целое число(istore) или ссылку (astore) с вершины стека в локальную переменную.
void istore_J(Bytes* bytes, int8_t localVarIndex);
void astore_J(Bytes* bytes, int8_t localVarIndex);


// снимает с вершины стека содержащееся там значение. Значение может быть любым кроме long и double.
void pop_J(Bytes* bytes);
// дублирует значение, лежащее на вершине стека. Значение может быть любым кроме long и double.
void dup_J(Bytes* bytes);
// дублирует одно(для long и double) или два(для всего кроме long и double) значения, лежащие на вершине стека
void dup2_J(Bytes* bytes);


// выполняет сложение двух целых чисел, лежащих на вершине стека(с их удалением оттуда) и помещает сумму на вершину стека
void iadd_J(Bytes* bytes);
// выполняет умножение двух целых чисел
void imul_J(Bytes* bytes);
// выполняет вычитание одного числа из другого
void isub_J(Bytes* bytes);
//  выполняет деление одного числа на другое
void idiv_J(Bytes* bytes);


// условный переход если сравнение целых чисел дает истину
void if_icmpeq_J(Bytes* bytes, int16_t shift); // Значение1=Значение2
void if_icmpne_J(Bytes* bytes, int16_t shift); // Значение1≠Значение2
void if_icmplt_J(Bytes* bytes, int16_t shift); // Значение2 < Значение1
void if_icmple_J(Bytes* bytes, int16_t shift); // Значение2 ≤ Значение1
void if_icmpgt_J(Bytes* bytes, int16_t shift); // Значение2 > Значение1
void if_icmpge_J(Bytes* bytes, int16_t shift); // Значение2 ≥ Значение1

// перейти, если сравнение целого числа с нулем дает истину
void ifeq_J(Bytes* bytes, int16_t shift); // Значение = 0
void ifne_J(Bytes* bytes, int16_t shift); // Значение ≠ 0
void iflt_J(Bytes* bytes, int16_t shift); // Значение < 0
void ifle_J(Bytes* bytes, int16_t shift); // Значение ≤ 0
void ifgt_J(Bytes* bytes, int16_t shift); // Значение > 0
void ifge_J(Bytes* bytes, int16_t shift); // Значение ≥ 0

// перейти, если сравнение ссылок верно
void if_acmpeq_J(Bytes* bytes, int16_t shift); // Ссылка1 = Ссылка2
void if_acmpne_J(Bytes* bytes, int16_t shift); // Ссылка1 ≠ Ссылка2

// осуществляет безусловный переход на указанное смещение от текущей команды
void goto_J(Bytes* bytes, int16_t shift);


// тут может быть работа с массивом или ваша реклама

//


// создает объект заданного типа в области динамически выделяемой памяти и помещает ссылку на него на вершину стека
void new_J(Bytes* bytes, int16_t classConstNum);
// получает значение поля объекта
void getfield_J(Bytes* bytes, int16_t constFrefNum);
// устанавливает значение поля объекта
void putfield_J(Bytes* bytes, int16_t constFrefNum);
// проверяет, является ли ссылка на объект экземпляром заданного класса
void instanceof_J(Bytes* bytes, int16_t classConstNum);
// проверяет, является ли ссылка на объект экземпляром заданного класса, если ссылка null, то выбрасывается исключение
void checkcast_J(Bytes* bytes, int16_t classConstNum);


// вызывает метод экземпляра класса
void invokevirtual_J(Bytes* bytes, int16_t constMrefNum);
// вызывает специальный метод экземпляра класса: для вызовов конструкторов
void invokespecial_J(Bytes* bytes, int16_t constMrefNum);
// вызывает статический метод класса
void invokestatic_J(Bytes* bytes, int16_t constMrefNum);

// завершает выполнение текущего метода с возвращением целого числа (ireturn), либо ссылки на объект (areturn)
void ireturn_J(Bytes* bytes);
void areturn_J(Bytes* bytes);
// завершает выполнение текущего метода
void return_J(Bytes* bytes);


// записывает в файл 1 байт
void appendByte_BC(FILE* file, uint8_t value);
// записывает в файл 2 байта
void appendTwoByte_BC(FILE* file, uint16_t value);
// записывает в файл 4 байта
void appendFourByte_BC(FILE* file, uint32_t value);
// записывает в файл 8 байт
void appendEightByte_BC(FILE* file, uint64_t value);


typedef struct Bytes {
    uint8_t* values = NULL;
} Bytes;

// возращает текущее кол-во байт в буфере
int size_B(Bytes bytes);
// добавляет 1 байт в буфер
void appendByte_B(Bytes* bytes, uint8_t value);
// добавляет 2 байта в буфер
void appendTwoByte_B(Bytes* bytes, uint16_t value);
// добавляет 4 байта в буфер
void appendFourByte_B(Bytes* bytes, uint32_t value);
// добавляет 8 байт в буфер
void appendEightByte_B(Bytes* bytes, uint64_t value);
// добавляет в конец все байты из bytes в this
void append_B(Bytes* this, Bytes* bytes);
// записывает в файл все байты из буфера
void write_B(Bytes bytes, FILE* file);