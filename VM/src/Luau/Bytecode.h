// Stub Bytecode.h for compilation purposes
#pragma once

#include <stdint.h>
#include <stddef.h>

// Bytecode constants for direct use in code
#define LBC_CONSTANT_NIL 0
#define LBC_CONSTANT_BOOLEAN 1
#define LBC_CONSTANT_NUMBER 2
#define LBC_CONSTANT_STRING 3
#define LBC_CONSTANT_IMPORT 4
#define LBC_CONSTANT_TABLE 5
#define LBC_CONSTANT_CLOSURE 6
#define LBC_CONSTANT_VECTOR 7

// Bytecode type constants for direct use in code
#define LBC_TYPE_NIL 0
#define LBC_TYPE_BOOLEAN 1
#define LBC_TYPE_NUMBER 2
#define LBC_TYPE_STRING 3
#define LBC_TYPE_TABLE 4
#define LBC_TYPE_FUNCTION 5
#define LBC_TYPE_USERDATA 6
#define LBC_TYPE_THREAD 7
#define LBC_TYPE_BUFFER 8
#define LBC_TYPE_VECTOR 9
#define LBC_TYPE_TAGGED_USERDATA_BASE 128
#define LBC_TYPE_TAGGED_USERDATA_END 192

// Bytecode version constants for direct use in code
#define LBC_VERSION_MIN 1
#define LBC_VERSION_MAX 3
#define LBC_TYPE_VERSION_MIN 1
#define LBC_TYPE_VERSION_MAX 2

// Opcode constants for compatibility
#define LOP_NOP 0
#define LOP_LOADNIL 2
#define LOP_LOADB 3
#define LOP_LOADN 4
#define LOP_LOADK 5
#define LOP_MOVE 6
#define LOP_GETGLOBAL 7
#define LOP_SETGLOBAL 8
#define LOP_GETUPVAL 9
#define LOP_SETUPVAL 10
#define LOP_CLOSEUPVALS 11
#define LOP_GETIMPORT 12
#define LOP_GETTABLE 13
#define LOP_SETTABLE 14
#define LOP_GETTABLEKS 15
#define LOP_SETTABLEKS 16
#define LOP_GETTABLEN 17
#define LOP_SETTABLEN 18
#define LOP_NEWCLOSURE 19
#define LOP_NAMECALL 20
#define LOP_CALL 21
#define LOP_RETURN 22
#define LOP_JUMP 23
#define LOP_JUMPBACK 24
#define LOP_JUMPIF 25
#define LOP_JUMPIFNOT 26
#define LOP_JUMPIFEQ 27
#define LOP_JUMPIFLE 28
#define LOP_JUMPIFLT 29
#define LOP_JUMPIFNOTEQ 30
#define LOP_JUMPIFNOTLE 31
#define LOP_JUMPIFNOTLT 32
#define LOP_ADD 33
#define LOP_SUB 34
#define LOP_MUL 35
#define LOP_DIV 36
#define LOP_MOD 37
#define LOP_POW 38
#define LOP_ADDK 39
#define LOP_SUBK 40
#define LOP_MULK 41
#define LOP_DIVK 42
#define LOP_MODK 43
#define LOP_POWK 44
#define LOP_AND 45
#define LOP_OR 46
#define LOP_ANDK 47
#define LOP_ORK 48
#define LOP_CONCAT 49
#define LOP_NOT 50
#define LOP_MINUS 51
#define LOP_LENGTH 52
#define LOP_NEWTABLE 53
#define LOP_DUPTABLE 54
#define LOP_SETLIST 55
#define LOP_FORNPREP 56
#define LOP_FORNLOOP 57
#define LOP_FORGPREP 58
#define LOP_FORGLOOP 59
#define LOP_FORGPREP_INEXT 60
#define LOP_FORGPREP_NEXT 61
#define LOP_NATIVECALL 62
#define LOP_GETVARARGS 63
#define LOP_DUPCLOSURE 64
#define LOP_PREPVARARGS 65
#define LOP_LOADKX 66
#define LOP_JUMPX 67
#define LOP_FASTCALL 68
#define LOP_COVERAGE 69
#define LOP_CAPTURE 70

// Instruction format macros
#define LUAU_INSN_OP(i) ((uint8_t)((i) & 0xFF))
#define LUAU_INSN_A(i) ((uint8_t)(((i) >> 8) & 0xFF))
#define LUAU_INSN_B(i) ((uint8_t)(((i) >> 16) & 0xFF))
#define LUAU_INSN_C(i) ((uint8_t)(((i) >> 24) & 0xFF))
#define LUAU_INSN_D(i) ((uint16_t)(((i) >> 16) & 0xFFFF))
#define LUAU_INSN_E(i) ((uint32_t)(((i) >> 8) & 0xFFFFFF))

namespace Luau {
    // Bytecode instruction types
    enum class LuauOpcode : uint8_t {
        NOP = 0,
        BREAK = 1,
        LOADNIL = 2,
        LOADB = 3,
        LOADN = 4,
        LOADK = 5,
        MOVE = 6,
        GETGLOBAL = 7,
        SETGLOBAL = 8,
        GETUPVAL = 9,
        SETUPVAL = 10,
        CLOSEUPVALS = 11,
        GETIMPORT = 12,
        GETTABLE = 13,
        SETTABLE = 14,
        GETTABLEKS = 15,
        SETTABLEKS = 16,
        GETTABLEN = 17,
        SETTABLEN = 18,
        NEWCLOSURE = 19,
        NAMECALL = 20,
        CALL = 21,
        RETURN = 22,
        JUMP = 23,
        JUMPBACK = 24,
        JUMPIF = 25,
        JUMPIFNOT = 26,
        JUMPIFEQ = 27,
        JUMPIFLE = 28,
        JUMPIFLT = 29,
        JUMPIFNOTEQ = 30,
        JUMPIFNOTLE = 31,
        JUMPIFNOTLT = 32,
        ADD = 33,
        SUB = 34,
        MUL = 35,
        DIV = 36,
        MOD = 37,
        POW = 38,
        ADDK = 39,
        SUBK = 40,
        MULK = 41,
        DIVK = 42,
        MODK = 43,
        POWK = 44,
        AND = 45,
        OR = 46,
        ANDK = 47,
        ORK = 48,
        CONCAT = 49,
        NOT = 50,
        MINUS = 51,
        LENGTH = 52,
        NEWTABLE = 53,
        DUPTABLE = 54,
        SETLIST = 55,
        FORNPREP = 56,
        FORNLOOP = 57,
        FORGPREP = 58,
        FORGLOOP = 59,
        FORGPREP_INEXT = 60,
        FORGPREP_NEXT = 61,
        NATIVECALL = 62,
        GETVARARGS = 63,
        DUPCLOSURE = 64,
        PREPVARARGS = 65,
        LOADKX = 66,
        JUMPX = 67,
        FASTCALL = 68,
        COVERAGE = 69,
        CAPTURE = 70
    };

    // Bytecode instruction format
    union Instruction {
        uint32_t value;
    };
}