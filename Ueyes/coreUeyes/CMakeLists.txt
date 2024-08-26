cmake_minimum_required(VERSION 3.5)

if(QT_VERSION_MAJOR STREQUAL "5")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
elseif(QT_VERSION_MAJOR STREQUAL "6")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)
endif()

project(core_ueyes LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

# set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../3rdparty/OpenCV-MinGW-Build/x64/mingw/lib")
find_package(OpenCV  REQUIRED)

# coreUeyes 构建
file(GLOB core_SRCS "coreDock/*.cpp")
file(GLOB core_HEADERS "coreDock/*.h")
file(GLOB core_QRCS "coreDock/*.qrc")
file(GLOB plugins_SRCS "plugins/*.cpp")
file(GLOB plugins_HEADERS "plugins/*.h")
file(GLOB services_SRCS "services/*.cpp")
file(GLOB services_HEADERS "services/*.h")

list(REMOVE_ITEM core_SRCS "")
list(REMOVE_ITEM core_HEADERS "")
list(REMOVE_ITEM plugins_SRCS "")
list(REMOVE_ITEM plugins_HEADERS "")
list(REMOVE_ITEM services_SRCS "")
list(REMOVE_ITEM services_HEADERS "")


#list(REMOVE_ITEM services_SRCS "*/services/BaseInterface.cpp")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if (UNIX AND NOT APPLE)
    file(GLOB core_SRCS "coreDock/linux/*.cpp" ${core_SRCS})
    file(GLOB core_HEADERS "coreDock/linux/*.h" ${core_HEADERS})
endif()

if(BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC ${core_SRCS} ${core_HEADERS} ${core_QRCS}
        ${plugins_SRCS} ${plugins_HEADERS}
        ${services_SRCS} ${services_HEADERS})
    target_compile_definitions( ${PROJECT_NAME} PUBLIC ADS_STATIC)

else()
    add_library(${PROJECT_NAME} SHARED ${core_SRCS} ${core_HEADERS} ${core_QRCS}
        ${plugins_SRCS} ${plugins_HEADERS}
        ${services_SRCS} ${services_HEADERS})
    target_compile_definitions( ${PROJECT_NAME} PRIVATE ADS_SHARED_EXPORT)
    #为PROJECT_NAME添加ADS_SHARED_EXPORT定义、PRIVATE仅对于目标内部是可见的，对于目标的所有用户和依赖项都是不可见的

endif()

# add_library(ads::${PROJECT_NAME} ALIAS ${PROJECT_NAME}) # 可能有问题

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core 
                                               Qt${QT_VERSION_MAJOR}::Gui 
                                               Qt${QT_VERSION_MAJOR}::Widgets
                                               ${OpenCV_LIBS})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/plugins
                                               ${CMAKE_CURRENT_SOURCE_DIR}/services
                                               ${CMAKE_CURRENT_SOURCE_DIR}/coreDock
                                               "${OpenCV_INCLUDE_DIRS}"
                                           )
if (UNIX AND NOT APPLE)
   include_directories(${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
endif()
if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PUBLIC xcb)
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 0.0.1
    COMPATIBILITY SameMajorVersion
)
install(FILES ${ads_HEADERS}
    DESTINATION include/${PROJECT_NAME}
    COMPONENT headers
)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/../gnu-lgpl-v2.1.md"
    DESTINATION license/ads
    COMPONENT license
)
install(TARGETS ${PROJECT_NAME}
    EXPORT adsTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include/${PROJECT_NAME}
)

install(EXPORT adsTargets
    FILE adsTargets.cmake
    NAMESPACE ads::
    DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES qtadvanceddockingConfig.cmake RENAME ${PROJECT_NAME}Config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CMAKE_INCLUDE_CURRENT_DIR ON0
    CXX_EXTENSIONS OFF
    VERSION 0.0.1
    # EXPORT_NAME "Qt ueyes docking system demoQt ueyes docking system demo"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ueyes_PlatformDir}/bin"
)
