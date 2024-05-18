cmake_minimum_required(VERSION 3.14)

project(Python_Lib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
message("Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message("Python3_LIBRARIES: ${Python3_LIBRARIES}")
message("Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")

add_library(Python_Lib SHARED
  Python_Lib_global.h
  pythonlib.cpp
  pythonlib.h
)
target_link_libraries(Python_Lib PUBLIC Qt${QT_VERSION_MAJOR}::Core ${Python3_LIBRARIES})

target_include_directories(Python_Lib PUBLIC ${Python3_INCLUDE_DIRS})

target_compile_definitions(Python_Lib PUBLIC PYTHON_LIB_LIBRARY)
