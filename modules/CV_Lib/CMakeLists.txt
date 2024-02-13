cmake_minimum_required(VERSION 3.5)

project(CVLib LANGUAGES CXX)

find_package(OpenCV REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)


#set(ads_demo_SRCS
#    OpencvFunc_global.h
#    OpencvFunc.cpp
#    OpencvFunc.h
#    main.cpp
#    form.ui
#)
#add_executable(OpencvFunc WIN32 ${ads_demo_SRCS})

add_library(CVLib SHARED
        OpencvFunc_globals.h
        OpencvFunc.cpp
        utils/ImageProcess.cpp
        OpencvFunc.h
        main.cpp
        form.ui
        BasicModule.h BasicModule.cpp
        utils/ImageRead.cpp)


#用以包含CV_Lib需要的头文件
target_include_directories(CVLib PRIVATE "${Opencv_INCLUDE_DIR}")


target_link_libraries(CVLib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                    ${OpenCV_LIBS})

target_compile_definitions(CVLib PRIVATE OpencvFunc_LIBRARY)



set_target_properties(CVLib PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CMAKE_INCLUDE_CURRENT_DIR ON
    CXX_EXTENSIONS OFF
    VERSION 0.0.1
    EXPORT_NAME "Qt Advanced Docking System Demo"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/bin"
)
