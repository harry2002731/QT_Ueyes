cmake_minimum_required(VERSION 3.14)

project(pluginmanager LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)


file(GLOB SOURCE_CPP "*.cpp" "*.qrc" "*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_CPP}
  )

target_link_libraries(pluginmanager PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(pluginmanager PRIVATE PLUGINMANAGER_LIBRARY)
