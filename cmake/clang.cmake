# look for Clang C compiler
find_program(
    CLANG_C clang
    REQUIRED
)
# look for Clang C++ compiler
find_program(
    CLANG_CXX clang++
    REQUIRED
)

# use Clang compiler for C and C++ files
set(CMAKE_C_COMPILER "${CLANG_C}")
set(CMAKE_CXX_COMPILER "${CLANG_CXX}")

set(CLANG_ARGS "-m64 -D__ptr32=")
set(CMAKE_C_FLAGS "${CLANG_ARGS}")
set(CMAKE_CXX_FLAGS "${CLANG_ARGS}")
