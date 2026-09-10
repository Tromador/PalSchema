include(FetchContent)

set(UE4SS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RE-UE4SS")
set(UE4SS_SDK_BUILD_DIR "${UE4SS_SOURCE_DIR}/build-sdk")
set(
    UE4SS_RUNTIME_LIBRARY
    "/home/steam/PalServer/Pal/Binaries/Linux/libUE4SS.so"
)

if(NOT EXISTS "${UE4SS_RUNTIME_LIBRARY}")
    message(FATAL_ERROR
        "Installed UE4SS runtime not found: ${UE4SS_RUNTIME_LIBRARY}"
    )
endif()

# UE4SS public DynamicOutput headers use fmt templates.
# Use the exact fmt source populated by the pinned NullPrism configure.
add_subdirectory(
    "${UE4SS_SDK_BUILD_DIR}/_deps/fmt-src"
    "${CMAKE_CURRENT_BINARY_DIR}/ue4ss-fmt"
)

set(UE4SS_INCLUDE_DIRS
    "${UE4SS_SOURCE_DIR}/UE4SS/include"
    "${UE4SS_SOURCE_DIR}/UE4SS/generated_include"

    "${UE4SS_SOURCE_DIR}/deps/first/File/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Helpers/include"
    "${UE4SS_SOURCE_DIR}/deps/first/String/include"
    "${UE4SS_SOURCE_DIR}/deps/first/DynamicOutput/include"

    "${UE4SS_SOURCE_DIR}/deps/first/Unreal/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Unreal/generated_include"
    "${UE4SS_SOURCE_DIR}/deps/first/Unreal/include/Unreal"
    "${UE4SS_SOURCE_DIR}/deps/first/Unreal/include/Unreal/Core"

    "${UE4SS_SOURCE_DIR}/deps/first/SinglePassSigScanner/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Constructs/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Function/include"
    "${UE4SS_SOURCE_DIR}/deps/first/ASMHelper/include"
    "${UE4SS_SOURCE_DIR}/deps/first/LuaMadeSimple/include"
    "${UE4SS_SOURCE_DIR}/deps/first/LuaRaw/include"
    "${UE4SS_SOURCE_DIR}/deps/first/IniParser/include"
    "${UE4SS_SOURCE_DIR}/deps/first/ParserBase/include"
    "${UE4SS_SOURCE_DIR}/deps/first/JSON/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Input/include"
    "${UE4SS_SOURCE_DIR}/deps/first/MProgram/include"
    "${UE4SS_SOURCE_DIR}/deps/first/ScopedTimer/include"
    "${UE4SS_SOURCE_DIR}/deps/first/Profiler/include"

    "${UE4SS_SDK_BUILD_DIR}/_deps/fmt-src/include"
)

set(UE4SS_COMPILE_DEFINITIONS
    DISABLE_PROFILER
    HAS_INPUT
    IS_SUPERLUMINAL=0
    IS_TRACY=0

    LINUX
    PLATFORM_LINUX
    PLATFORM_UNIX
    OVERRIDE_PLATFORM_HEADER_NAME=Linux
    UBT_COMPILED_PLATFORM=Linux

    UE_BUILD_SHIPPING
    UE_GAME

    RC_ASM_HELPER_BUILD_STATIC
    RC_DYNAMIC_OUTPUT_BUILD_STATIC
    RC_FILE_BUILD_STATIC
    RC_FUNCTION_TIMER_BUILD_STATIC
    RC_INI_PARSER_BUILD_STATIC
    RC_INPUT_BUILD_STATIC
    RC_JSON_BUILD_STATIC
    RC_JSON_PARSER_BUILD_STATIC
    RC_LUA_MADE_SIMPLE_BUILD_STATIC
    RC_LUA_RAW_BUILD_STATIC
    RC_LUA_WRAPPER_GENERATOR_BUILD_STATIC
    RC_PARSER_BASE_BUILD_STATIC
    RC_SINGLE_PASS_SIG_SCANNER_BUILD_STATIC
    RC_SINGLE_PASS_SIG_SCANNER_STATIC
    RC_STRING_BUILD_STATIC
    RC_UNREAL_BUILD_STATIC

    ZYCORE_STATIC_BUILD
    ZYDIS_STATIC_BUILD
    ASMTK_STATIC
    ASMJIT_STATIC

    UE4SS_LIB_BETA_STARTED=1
    UE4SS_LIB_IS_BETA=1
    UE4SS_LIB_VERSION_MAJOR=3
    UE4SS_LIB_VERSION_MINOR=0
    UE4SS_LIB_VERSION_HOTFIX=1
    UE4SS_LIB_VERSION_PRERELEASE=0
    UE4SS_LIB_VERSION_BETA=0

    "UE4SS_LIB_BUILD_GITSHA=\"a5b3c4c5\""
    "UE4SS_CONFIGURATION=\"Game__Shipping__Linux\""

    printf_s=printf
    wprintf_s=wprintf
)

set(UE4SS_COMPILE_OPTIONS
    -fms-extensions
    -fvisibility=hidden
    -fvisibility-inlines-hidden
)

set(UE4SS_LINK_OPTIONS
    -static-libstdc++
    -static-libgcc
    -Wl,--no-as-needed
    -Wl,-z,defs
    -Wl,--exclude-libs,ALL
    "-Wl,-rpath,$ORIGIN/../../.."
)

add_library(UE4SSUnreal STATIC IMPORTED GLOBAL)

set_target_properties(UE4SSUnreal PROPERTIES
    IMPORTED_LOCATION "${UE4SS_SDK_BUILD_DIR}/Game__Shipping__Linux/lib/libUnreal.a"
)

add_library(UE4SS SHARED IMPORTED GLOBAL)

set_target_properties(UE4SS PROPERTIES
    IMPORTED_LOCATION "${UE4SS_RUNTIME_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${UE4SS_INCLUDE_DIRS}"
    INTERFACE_COMPILE_DEFINITIONS "${UE4SS_COMPILE_DEFINITIONS}"
    INTERFACE_COMPILE_OPTIONS "${UE4SS_COMPILE_OPTIONS}"
    INTERFACE_LINK_LIBRARIES "UE4SSUnreal;fmt::fmt;dl;pthread"
    INTERFACE_LINK_OPTIONS "${UE4SS_LINK_OPTIONS}"
)

add_subdirectory("json")
add_subdirectory("safetyhook")
add_subdirectory("glaze")
add_subdirectory("efsw")