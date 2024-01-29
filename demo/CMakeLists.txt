cmake_minimum_required(VERSION 3.5)
project(ads_demo VERSION 0.0.1) 

set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs/OpenCV-MinGW-Build/x64/mingw/lib")

find_package(OpenCV REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.5 COMPONENTS Core Gui Widgets Quick QuickWidgets REQUIRED)
if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AxContainer REQUIRED)
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ads_demo_SRCS
    main.cpp
    MainWindow.cpp
    mainwindow.ui
    StatusDialog.cpp
    StatusDialog.ui
    ImageViewer.cpp
    RenderWidget.cpp
    WelcomeWindow.h
    WelcomeWindow.cpp
    BasicWindow.h
    BasicWindow.cpp
    demo.qrc
)
add_executable(AdvancedDockingSystemDemo WIN32 ${ads_demo_SRCS})

target_include_directories(AdvancedDockingSystemDemo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_include_directories(AdvancedDockingSystemDemo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../libs/OpenCV-MinGW-Build/")

target_link_libraries(AdvancedDockingSystemDemo PUBLIC Qt${QT_VERSION_MAJOR}::Core 
                                                       Qt${QT_VERSION_MAJOR}::Gui 
                                                       Qt${QT_VERSION_MAJOR}::Widgets
                                                       Qt${QT_VERSION_MAJOR}::Quick
                                                       Qt${QT_VERSION_MAJOR}::QuickWidgets
                                                        ${OpenCV_LIBS})

MESSAGE(STATUS "Project: ${PROJECT_NAME}")
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    target_link_libraries(AdvancedDockingSystemDemo PUBLIC Qt${QT_VERSION_MAJOR}::AxContainer)
endif()
target_link_libraries(AdvancedDockingSystemDemo PRIVATE qt${QT_VERSION_MAJOR}advanceddocking)
set_target_properties(AdvancedDockingSystemDemo PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 0.0.1
    EXPORT_NAME "Qt Advanced Docking System Demo"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/bin"
)
#if(BUILD_STATIC)
#    target_compile_definitions(AdvancedDockingSystemDemo PRIVATE ADS_STATIC)
#endif()

