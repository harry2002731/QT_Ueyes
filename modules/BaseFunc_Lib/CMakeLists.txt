cmake_minimum_required(VERSION 3.14)

project(BaseFunc_Lib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Python3 REQUIRED COMPONENTS Interpreter)


add_library(BaseFunc_Lib SHARED
  BaseFunc_Lib_global.h
  BaseFunc_Lib.cpp
  BaseFunc_Lib.h
  ReadMe.md
)
target_link_libraries(BaseFunc_Lib PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(BaseFunc_Lib PRIVATE BASEFUNC_LIB_LIBRARY)
