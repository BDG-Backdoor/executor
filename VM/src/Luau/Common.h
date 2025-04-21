// Luau/Common.h - Common definitions for Luau VM
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>  // for malloc and free

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#define LUAU_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#define LUAU_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define LUAU_PLATFORM_IOS 1
#else
#define LUAU_PLATFORM_OSX 1
#endif
#elif defined(__linux__)
#define LUAU_PLATFORM_LINUX 1
#elif defined(__ANDROID__)
#define LUAU_PLATFORM_ANDROID 1
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
#define LUAU_ARCH_X64 1
#elif defined(__i386__) || defined(_M_IX86)
#define LUAU_ARCH_X86 1
#elif defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64)
#define LUAU_ARCH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#define LUAU_ARCH_ARM 1
#endif

// Compiler detection and specific attributes
#if defined(_MSC_VER)
#define LUAU_COMPILER_MSVC 1
#define LUAU_NOINLINE __declspec(noinline)
#define LUAU_FORCEINLINE __forceinline
#define LUAU_NORETURN __declspec(noreturn)
#define LUAU_LIKELY(x) (x)
#define LUAU_UNLIKELY(x) (x)
#elif defined(__GNUC__) || defined(__clang__)
#if defined(__clang__)
#define LUAU_COMPILER_CLANG 1
#else
#define LUAU_COMPILER_GCC 1
#endif
#define LUAU_NOINLINE __attribute__((noinline))
#define LUAU_FORCEINLINE inline __attribute__((always_inline))
#define LUAU_NORETURN __attribute__((noreturn))
#define LUAU_LIKELY(x) __builtin_expect((x), 1)
#define LUAU_UNLIKELY(x) __builtin_expect((x), 0)
#else
#define LUAU_NOINLINE
#define LUAU_FORCEINLINE inline
#define LUAU_NORETURN
#define LUAU_LIKELY(x) (x)
#define LUAU_UNLIKELY(x) (x)
#endif

// Fast flag system for feature flags and configuration
#ifdef LUAU_FASTFLAG_SUPPORT
// Production implementation would connect to a real feature flag system
#define LUAU_FASTFLAGVARIABLE(name) namespace FFlag { extern bool name; }
#define LUAU_FASTFLAG(name) FFlag::name
#else
// Simple implementation for development and testing
#define LUAU_FASTFLAGVARIABLE(name) namespace FFlag { bool name = true; }
#define LUAU_FASTFLAG(name) FFlag::name
#endif

// Define some fast flags used by the VM
LUAU_FASTFLAGVARIABLE(LuauFastintSupport)
LUAU_FASTFLAGVARIABLE(LuauVectorLib)
LUAU_FASTFLAGVARIABLE(LuauBufferLib)
LUAU_FASTFLAGVARIABLE(LuauRecursionLimit)
LUAU_FASTFLAGVARIABLE(LuauTailCallOptimization)
LUAU_FASTFLAGVARIABLE(LuauStringFormatFixC)

// Dynamic fast flag system
#define LUAU_DYNAMIC_FASTFLAGVARIABLE(name, value) namespace DFFlag { bool name = value; }

// Fallthrough attribute
#define LUAU_FALLTHROUGH ((void)0)

// Luau VM capture types
#define LCT_VAL 0    // Captures value
#define LCT_REF 1    // Captures reference
#define LCT_UPVAL 2  // Captures upvalue

namespace Luau {
    // Common types
    typedef int32_t int32;
    typedef uint32_t uint32;
    typedef int64_t int64;
    typedef uint64_t uint64;
    
    // Assertion macros with different behaviors in debug/release
#ifdef NDEBUG
    #define LUAU_ASSERT(x) ((void)0)
    #define LUAU_UNREACHABLE() ((void)0)
#else
    #define LUAU_ASSERT(x) assert(x)
    #define LUAU_UNREACHABLE() assert(false)
#endif

    // Memory allocation functions
    inline void* luau_malloc(size_t size) {
        return malloc(size);
    }
    
    inline void luau_free(void* ptr) {
        free(ptr);
    }
    
    // Alignment helpers
    template<typename T>
    inline T align(T value, size_t alignment) {
        return T((size_t(value) + alignment - 1) & ~(alignment - 1));
    }
    
    // Utility functions
    inline uint32 log2ceil(uint32 value) {
        if (value == 0)
            return 0;
            
        uint32 result = 0;
        uint32 v = value - 1;
        
        while (v >>= 1)
            result++;
            
        return result + 1;
    }
    
    // Endian conversion helpers
    inline uint16_t byteswap16(uint16_t value) {
        return (value >> 8) | (value << 8);
    }
    
    inline uint32_t byteswap32(uint32_t value) {
        return (value >> 24) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | (value << 24);
    }
    
    // Determine if the system is little endian
    inline bool isLittleEndian() {
        static const union { uint32_t i; char c[4]; } u = { 0x01020304 };
        return u.c[0] == 4;
    }
}