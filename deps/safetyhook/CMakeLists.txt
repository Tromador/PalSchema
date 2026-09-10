set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_Declare(
    safetyhook
    GIT_REPOSITORY https://github.com/cursey/safetyhook.git
    GIT_TAG 8a975dee560c424329dcb0e151f3649fa4b19146
)

FetchContent_MakeAvailable(safetyhook)