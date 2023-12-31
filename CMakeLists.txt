cmake_minimum_required(VERSION 3.5)

project(taskmanager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

include_directories(src/lib)
include_directories(src/lib/header)
include_directories(src/lib/ui)
include_directories(src/lib/model)
include_directories(src/lib/model/header)

set(PROJECT_SOURCES
        main.cpp
        src/lib/loginpage.cpp
        src/lib/header/loginpage.h
        src/lib/ui/loginpage.ui
        src/lib/mainwindow.cpp
        src/lib/header/mainwindow.h
        src/lib/ui/mainwindow.ui
        src/lib/model/header/serverconnection.h
        src/lib/model/serverconnection.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(taskmanager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(taskmanager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(taskmanager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(taskmanager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(taskmanager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS taskmanager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(taskmanager)
endif()
