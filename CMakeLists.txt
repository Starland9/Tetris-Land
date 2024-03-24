cmake_minimum_required(VERSION 3.16)
project(Tetris VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(Tetris main.c) 


target_include_directories(
  Tetris
  PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/Headers
)


# Specify the path to the MinGW SDL2 libraries
target_link_libraries(
  Tetris
  PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/SDL2
)


# Specify the path to the MinGW SDL2 libraries
# target_link_libraries(Tetris "-lmingw32 -lSDL2main -lSDL2")


include_directories(Tetris "src/")



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
