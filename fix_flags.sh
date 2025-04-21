#!/bin/bash

# Clean up object files
rm -f ./VM/src/*.o

# Create a backup directory
mkdir -p ./VM/src/backup

# Backup original files
cp ./VM/src/*.cpp ./VM/src/backup/

# Create a Common.h file with the flags defined as extern
cat > ./VM/src/Luau/Common.h << 'EOF'
// Common.h - Common definitions for Luau VM
#pragma once

#include <stddef.h>
#include <stdint.h>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#define LUAU_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#define LUAU_PLATFORM_APPLE 1
#elif defined(__linux__)
#define LUAU_PLATFORM_LINUX 1
#elif defined(__ANDROID__)
#define LUAU_PLATFORM_ANDROID 1
#else
#define LUAU_PLATFORM_UNKNOWN 1
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
#define LUAU_ARCH_X64 1
#elif defined(__i386__) || defined(_M_IX86)
#define LUAU_ARCH_X86 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#define LUAU_ARCH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#define LUAU_ARCH_ARM 1
#else
#define LUAU_ARCH_UNKNOWN 1
#endif

// Compiler detection
#if defined(_MSC_VER)
#define LUAU_COMPILER_MSVC 1
#elif defined(__clang__)
#define LUAU_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define LUAU_COMPILER_GCC 1
#else
#define LUAU_COMPILER_UNKNOWN 1
#endif

// Attributes
#if defined(LUAU_COMPILER_MSVC)
#define LUAU_FORCEINLINE __forceinline
#define LUAU_NOINLINE __declspec(noinline)
#define LUAU_NORETURN __declspec(noreturn)
#define LUAU_LIKELY(x) (x)
#define LUAU_UNLIKELY(x) (x)
#elif defined(LUAU_COMPILER_CLANG) || defined(LUAU_COMPILER_GCC)
#define LUAU_FORCEINLINE inline __attribute__((always_inline))
#define LUAU_NOINLINE __attribute__((noinline))
#define LUAU_NORETURN __attribute__((noreturn))
#define LUAU_LIKELY(x) __builtin_expect(!!(x), 1)
#define LUAU_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define LUAU_FORCEINLINE inline
#define LUAU_NOINLINE
#define LUAU_NORETURN
#define LUAU_LIKELY(x) (x)
#define LUAU_UNLIKELY(x) (x)
#endif

// Memory utilities
#define LUAU_ASSERT(cond) ((void)0)
#define LUAU_UNREACHABLE() ((void)0)
#define LUAU_UNREACHABLE_FALLTHROUGH ((void)0)

// Constant types
#define LCT_NIL 0
#define LCT_BOOLEAN 1
#define LCT_NUMBER 2
#define LCT_STRING 3
#define LCT_VECTOR 4
#define LCT_TABLE 5
#define LCT_FUNCTION 6
#define LCT_USERDATA 7
#define LCT_THREAD 8
#define LCT_VAL 9
#define LCT_REF 10
#define LCT_UPVAL 11

// Feature flags
namespace FFlag
{
    extern bool LuauFastintSupport;
    extern bool LuauVectorLib;
    extern bool LuauBufferLib;
    extern bool LuauRecursionLimit;
    extern bool LuauTailCallOptimization;
    extern bool LuauStringFormatFixC;
}
EOF

# Create a Flags.cpp file with the flags defined
cat > ./VM/src/Luau/Flags.cpp << 'EOF'
#include "Luau/Common.h"

namespace FFlag
{
    bool LuauFastintSupport = true;
    bool LuauVectorLib = true;
    bool LuauBufferLib = true;
    bool LuauRecursionLimit = true;
    bool LuauTailCallOptimization = true;
    bool LuauStringFormatFixC = true;
}
EOF

# Find all cpp files in VM/src
for file in ./VM/src/*.cpp; do
    # Skip our flags file
    if [[ "$file" == "./VM/src/Luau/Flags.cpp" ]]; then
        continue
    fi
    
    # Remove any existing FFlag definitions
    sed -i '/namespace FFlag/,/}/d' "$file"
    sed -i '/bool FFlag::LuauFastintSupport/d' "$file"
    sed -i '/bool FFlag::LuauVectorLib/d' "$file"
    sed -i '/bool FFlag::LuauBufferLib/d' "$file"
    sed -i '/bool FFlag::LuauRecursionLimit/d' "$file"
    sed -i '/bool FFlag::LuauTailCallOptimization/d' "$file"
    sed -i '/bool FFlag::LuauStringFormatFixC/d' "$file"
    
    # Add include for our common header at the top of the file
    sed -i '1i #include "Luau/Common.h"' "$file"
done

echo "Fixed flag definitions in VM source files"