cmake_minimum_required(VERSION 3.14)

project(Hikvision_Lib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(Hikvision_Lib SHARED
  Hikvision_Lib_global.h
  Hikvision_Lib.cpp
  Hikvision_Lib.h
  MvCamera.cpp
  MvCamera.h
)
target_link_libraries(Hikvision_Lib PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt6::Gui)
target_include_directories(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/linux/x86/include/")
target_link_libraries(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/linux/x86/lib/64/libMvCameraControl.so")

# # target_link_libraries(Hikvision_Lib PRIVATE "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/aarch/lib/aarch64/libMvCameraControl.so")
# # target_include_directories(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/aarch/include/")
if (UNIX AND NOT APPLE)
    target_link_libraries(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/linux/x86/lib/64/libMvCameraControl.so")
    target_include_directories(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/linux/x86/include")
elseif(WIN32)
    target_link_libraries(Hikvision_Lib PRIVATE "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/win/win64/MvCameraControl.lib")
    target_include_directories(Hikvision_Lib PUBLIC "${CMAKE_SOURCE_DIR}/../3rdparty/Camera/MVCamera/win/includes")
endif()
