cmake_minimum_required(VERSION 3.5)
project(cv_libs LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin)
#add_subdirectory(CV_Lib) # 图像处理功能包
add_subdirectory(Widget_Lib) # 窗体功能包
add_subdirectory(BaseFunc_Lib) #基础功能包（读取动态库等）
add_subdirectory(SqlLite_Lib) # 数据库功能包
add_subdirectory(Python_Lib) # python功能包
add_subdirectory(QXlsx/QXlsx)
