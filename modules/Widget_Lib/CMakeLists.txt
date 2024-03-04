cmake_minimum_required(VERSION 3.14)

project(WidgetLib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_library(WidgetLib SHARED
  Widget_Lib_global.h  Widget_Lib.cpp  Widget_Lib.h
  FuncViewerWidget.h  FuncViewerWidget.cpp  FuncViewerWidget.ui
  FuncViewerPage.h  FuncViewerPage.cpp
  widget.qrc
  FuncViewerPage.ui
  VisualProcessWidget.h VisualProcessWidget.cpp
  Form.ui Form.h  Form.cpp
  BaseWidget.h BaseWidget.cpp
)

target_link_libraries(WidgetLib PRIVATE Qt${QT_VERSION_MAJOR}::Core  Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(WidgetLib PRIVATE WIDGET_LIB_LIBRARY)
