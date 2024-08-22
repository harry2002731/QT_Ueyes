cmake_minimum_required(VERSION 3.14)

project(CameraViewer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
add_library(CameraViewer SHARED
  CameraViewer_global.h
  videobox.h
  CameraViewer.h
  videobox.cpp
  CameraViewer.cpp
  mainwindow.ui
  mWindow.h mWindow.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../Camera_Lib/")

target_link_libraries(CameraViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Basler_Lib)
target_link_libraries(${PROJECT_NAME} PRIVATE Hikvision_Lib)

target_compile_definitions(CameraViewer PRIVATE CAMERAVIEWER_LIBRARY)
