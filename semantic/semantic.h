// потом нормально заинклюдить
#include "std_ds.h"


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
    JvmConstant int64(int64_t value);
    JvmConstant double64(double value);
    JvmConstant str(uint16_t strConstNum);
    JvmConstant classConst(uint16_t classNameConstNum);
    JvmConstant nt(uint16_t nameConstNum, uint16_t descriptorConstNum);
    JvmConstant fref(uint16_t classConstNum, uint16_t ntConstNum);
    JvmConstant mref(uint16_t classConstNum, uint16_t ntConstNum);


typedef struct ConstantsTable {
    JvmConstant* values = NULL;
    
} ConstantsTable;

    uint16_t add_CT(JvmConstant* constant);
    uint16_t addUtf8_CT(char* str);
    uint16_t addClass_CT(char* className);
    uint16_t addStr_CT(char* strConstant);
    uint16_t addFref_CT(char* className, char* name, char* descriptor);
    uint16_t addMref_CT(char* className, char* name, char* descriptor);