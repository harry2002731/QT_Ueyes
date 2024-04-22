cmake_minimum_required(VERSION 3.14)

project(DataTableViewer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets sql Charts)

add_library(DataTableViewer SHARED
  DataTableViewer_global.h
  datatableviewer.cpp
  datatableviewer.h
  DataTableViewer.ui
  SqlInterface.h
)

target_link_libraries(DataTableViewer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql Qt6::Charts)

target_compile_definitions(DataTableViewer PRIVATE DATATABLEVIEWER_LIBRARY)
