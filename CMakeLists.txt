cmake_minimum_required(VERSION 4.0)
project(dd_chess VERSION 0.0)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
  dd_chess 
  src/main.c
  src/board/board.c
)

target_compile_options(
  dd_chess PRIVATE 
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Werror>
  $<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)


