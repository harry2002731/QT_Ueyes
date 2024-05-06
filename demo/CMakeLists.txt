cmake_minimum_required(VERSION 3.5)
project(ads_demo VERSION 0.0.1) 

set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs/OpenCV-MinGW-Build/x64/mingw/lib")

find_package(OpenCV  REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS
            Core
            Sql
            Gui
            Widgets
            Quick
            QuickWidgets
        Xml
     QuickControls2)


if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    find_package(Qt6 COMPONENTS AxContainer REQUIRED)
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
#    SqlInterface.h
    qml.qrc
)
add_executable(AdvancedDockingSystemDemo WIN32 ${ads_demo_SRCS}
    welcomewindow.ui
)
target_include_directories(AdvancedDockingSystemDemo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src"
                                                            "${CMAKE_CURRENT_SOURCE_DIR}/../modules"
                                                            "${OpenCV_INCLUDE_DIRS}")
target_link_libraries(AdvancedDockingSystemDemo PUBLIC Qt6::Core
                                                       Qt6::Gui
                                                       Qt6::Widgets
                                                       Qt6::Quick
                                                       Qt6::QuickWidgets
                                                       Qt6::Sql
                                                       ${OpenCV_LIBS}
                                                       Qt6::Quick
                                                       Qt6::Xml
                                                       Qt6::QuickControls2
                                                    )

#MESSAGE(STATUS "Project: ${PROJECT_NAME}")
#MESSAGE(STATUS "OpenCV library status:")
#MESSAGE(STATUS "version: ${OpenCV_VERSION}")
#MESSAGE(STATUS "libraries: ${OpenCV_LIBS}")
#MESSAGE(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
#qt_import_plugins(AdvancedDockingSystemDemo INCLUDE SqlLite_Lib) #可能这个只能加载官方的插件


if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    target_link_libraries(AdvancedDockingSystemDemo PUBLIC Qt6::AxContainer)
endif()
target_link_libraries(AdvancedDockingSystemDemo PRIVATE qt6advanceddocking)
target_link_libraries(AdvancedDockingSystemDemo PRIVATE WidgetLib)
target_link_libraries(AdvancedDockingSystemDemo PRIVATE BaseFunc_Lib)
target_link_libraries(AdvancedDockingSystemDemo PRIVATE SqlLite_Lib)
target_link_libraries(AdvancedDockingSystemDemo PRIVATE LoginView)
target_link_libraries(AdvancedDockingSystemDemo PRIVATE DataTableViewer)

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

