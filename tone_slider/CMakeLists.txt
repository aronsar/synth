cmake_minimum_required(VERSION 3.5)

project(tone_slider VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        toneslider.cpp
        toneslider.h
        toneslider.ui
	sineloop.cpp
	sineloop.h
)

# Handle stk includes and macros
include_directories("../stk/include")
file(GLOB STK_SOURCES ../stk/src/*.cpp)
file(GLOB STK_DRIVERS ../stk/src/include/*)

link_libraries(winmm ole32 wsock32)
add_definitions(-D__WINDOWS_MM__)

link_libraries(dsound)
add_definitions(-D__WINDOWS_DS__)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tone_slider
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
	${STK_SOURCES}
	${STK_DRIVERS}
    )
endif()

target_link_libraries(tone_slider PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(tone_slider PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS tone_slider
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tone_slider)
endif()
