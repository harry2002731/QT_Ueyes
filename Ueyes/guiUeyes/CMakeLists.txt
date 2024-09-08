cmake_minimum_required(VERSION 3.5)
project(gui_ueyes VERSION 0.0.1) 


find_package(Qt6 REQUIRED COMPONENTS Core Sql Gui Widgets QuickWidgets Quick  Xml QuickControls2)

if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    find_package(Qt6 COMPONENTS AxContainer REQUIRED)
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB gui_SRCS "*.cpp")
file(GLOB gui_HEADERS "*.h")
file(GLOB gui_QRC "*.qrc")
file(GLOB gui_UI "*.ui")

list(REMOVE_ITEM gui_SRCS "")
list(REMOVE_ITEM gui_HEADERS "")
list(REMOVE_ITEM gui_QRC "")
list(REMOVE_ITEM gui_UI "")


add_library(${PROJECT_NAME} SHARED ${gui_SRCS} ${gui_SRCS} ${gui_HEADERS} ${gui_QRC} ${gui_UI}
    )

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../coreUeyes/")

if(WIN32 AND QT_VERSION_MAJOR LESS 6)
    target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::AxContainer)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC  Qt6::Core
                                            Qt6::Gui
                                            Qt6::Widgets
                                            Qt6::Quick
                                            Qt6::QuickWidgets
                                            Qt6::Sql
                                            Qt6::Quick
                                            Qt6::Xml
                                            Qt6::QuickControls2
                                                    )
target_link_libraries(${PROJECT_NAME} PRIVATE core_ueyes)
target_compile_definitions(${PROJECT_NAME} PUBLIC GUI_UEYES_LIBRARY)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 0.0.1
    # EXPORT_NAME "Qt ueyes docking system demo"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin"
)

#if(BUILD_STATIC)
#    target_compile_definitions(${PROJECT_NAME} PRIVATE ADS_STATIC)
#endif()

