cmake_minimum_required(VERSION 3.14)

project(SqlLite_Lib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql Widgets)

find_package(Python REQUIRED COMPONENTS Interpreter Development)
message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")

add_library(SqlLite_Lib SHARED
  SqlLite_Lib_global.h
  sqlLitelib.cpp
  sqlLitelib.h
  SqlInterface.h
  BaseInterface.h

)
target_link_libraries(SqlLite_Lib PUBLIC Qt${QT_VERSION_MAJOR}::Core
                        Qt${QT_VERSION_MAJOR}::Sql
                     Qt${QT_VERSION_MAJOR}::Widgets
                 ${Python_LIBRARIES}
             )

target_include_directories(SqlLite_Lib PRIVATE ${Python_INCLUDE_DIRS})

target_compile_definitions(SqlLite_Lib PUBLIC SQLLITE_LIB_LIBRARY)
