cmake_minimum_required(VERSION 3.5)

project(BT-Monitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets SvgWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets SvgWidgets REQUIRED)
find_package(cppzmq)

include_directories(${PROJECT_SOURCE_DIR}/icons/)
include_directories(${PROJECT_SOURCE_DIR}/inc/)

set(PROJECT_SOURCES
        #Main
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/mainwindow.cpp"
        "${PROJECT_SOURCE_DIR}/inc/mainwindow.h"
        "${PROJECT_SOURCE_DIR}/src/mainwindow.ui"
        #ZMQPuller
        "${PROJECT_SOURCE_DIR}/src/zmqpuller.cpp"
        "${PROJECT_SOURCE_DIR}/inc/zmqpuller.h"
        #BTModel
        "${PROJECT_SOURCE_DIR}/src/bt_nodemodel.cpp"
        "${PROJECT_SOURCE_DIR}/inc/bt_nodemodel.h"
        "${PROJECT_SOURCE_DIR}/src/bt_connectionmodel.cpp"
        "${PROJECT_SOURCE_DIR}/inc/bt_connectionmodel.h"
        "${PROJECT_SOURCE_DIR}/src/bt_model.cpp"
        "${PROJECT_SOURCE_DIR}/inc/bt_model.h"
        "${PROJECT_SOURCE_DIR}/icons/icons.qrc"
        #Graph
        "${PROJECT_SOURCE_DIR}/src/graph_model.cpp"
        "${PROJECT_SOURCE_DIR}/inc/graph_model.h"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BT-Monitor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BT-Monitor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BT-Monitor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BT-Monitor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BT-Monitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cppzmq Qt6::SvgWidgets)

set_target_properties(BT-Monitor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BT-Monitor)
endif()
