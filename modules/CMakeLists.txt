cmake_minimum_required(VERSION 3.5)
project(cv_libs LANGUAGES CXX VERSION 0.0.1)
#add_subdirectory(CV_Lib) # 图像处理功能包
add_subdirectory(Widget_Lib) # 窗体功能包
add_subdirectory(BaseFunc_Lib) #基础功能包（读取动态库等）
add_subdirectory(SqlLite_Lib) # 数据库功能包
