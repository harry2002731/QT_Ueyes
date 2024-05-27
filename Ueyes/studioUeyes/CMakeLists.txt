cmake_minimum_required(VERSION 3.5)
project(studio_ueyes VERSION 0.0.1) 


set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../3rdparty/OpenCV-MinGW-Build/x64/mingw/lib")
find_package(OpenCV  REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Sql Gui Widgets Quick QuickWidgets Xml QuickControls2)

if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    find_package(Qt6 COMPONENTS AxContainer REQUIRED)
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB studio_SRCS "*.cpp")
file(GLOB studio_HEADERS "*.h")
file(GLOB studio_QRC "*.qrc")
file(GLOB studio_UI "*.ui")

list(REMOVE_ITEM studio_SRCS  "")
list(REMOVE_ITEM studio_HEADERS  "")
list(REMOVE_ITEM studio_QRC  "")
list(REMOVE_ITEM studio_UI  "")


add_executable(${PROJECT_NAME} WIN32 ${studio_HEADERS} ${studio_SRCS}  ${studio_QRC} ${studio_UI})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../coreUeyes/coreDock"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/../coreUeyes/plugins"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/../coreUeyes/services"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/../guiUeyes"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/../pluginUeyes"
                                                     "${OpenCV_INCLUDE_DIRS}"
                                                    )
target_link_libraries(${PROJECT_NAME} PUBLIC   ${OpenCV_LIBS}
                                                       Qt6::Core
                                                       Qt6::Gui
                                                       Qt6::Widgets
                                                       Qt6::Quick
                                                       Qt6::QuickWidgets
                                                       Qt6::Sql
                                                       Qt6::Quick
                                                       Qt6::Xml
                                                       Qt6::QuickControls2
                                                    )

#MESSAGE(STATUS "Project: ${PROJECT_NAME}")
#MESSAGE(STATUS "OpenCV library status:")
#MESSAGE(STATUS "version: ${OpenCV_VERSION}")
#MESSAGE(STATUS "libraries: ${OpenCV_LIBS}")
#MESSAGE(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
#qt_import_plugins(${PROJECT_NAME} INCLUDE SqlLite_Lib) #可能这个只能加载官方的插件

target_link_libraries(${PROJECT_NAME} PRIVATE core_ueyes)
target_link_libraries(${PROJECT_NAME} PRIVATE gui_ueyes)
target_link_libraries(${PROJECT_NAME} PRIVATE WidgetLib)
target_link_libraries(${PROJECT_NAME} PRIVATE BaseFunc_Lib)
target_link_libraries(${PROJECT_NAME} PRIVATE SqlLite_Lib)
target_link_libraries(${PROJECT_NAME} PRIVATE LoginView)
target_link_libraries(${PROJECT_NAME} PRIVATE DataTableViewer)

if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::AxContainer)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 0.0.1
    EXPORT_NAME "Qt ueyes docking system demo"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin"
)
#if(BUILD_STATIC)
#    target_compile_definitions(${PROJECT_NAME} PRIVATE ADS_STATIC)
#endif()

