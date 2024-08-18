cmake_minimum_required(VERSION 3.14)

project(Basler_Lib LANGUAGES CXX)
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../3rdparty/OpenCV-MinGW-Build/x64/mingw/lib")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
find_package(OpenCV  REQUIRED)

add_library(Basler_Lib SHARED
  Basler_Lib_global.h
  Basler_Lib.cpp
  Basler_Lib.h

)

target_link_libraries(Basler_Lib PRIVATE Qt${QT_VERSION_MAJOR}::Core ${OpenCV_LIBS}
    Qt6::Gui Qt6::Widgets
)

target_include_directories(Basler_Lib PUBLIC "${OpenCV_INCLUDE_DIRS}")
target_compile_definitions(Basler_Lib PRIVATE BASLER_LIB_LIBRARY)
