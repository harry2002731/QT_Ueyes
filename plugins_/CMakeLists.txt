cmake_minimum_required(VERSION 3.5)
project(cv_libs LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)

add_subdirectory(pluginmanager)# 窗体功能包

