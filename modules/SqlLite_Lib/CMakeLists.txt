cmake_minimum_required(VERSION 3.14)

project(SqlLite_Lib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)
add_library(SqlLite_Lib SHARED
  SqlLite_Lib_global.h
  SqlLite_Lib.cpp
  SqlLite_Lib.h
)
target_link_libraries(SqlLite_Lib PUBLIC Qt6::Sql)

target_link_libraries(SqlLite_Lib PUBLIC Qt${QT_VERSION_MAJOR}::Core
                        Qt${QT_VERSION_MAJOR}::Sql)


target_compile_definitions(SqlLite_Lib PUBLIC SQLLITE_LIB_LIBRARY)
