cmake_minimum_required(VERSION 3.5)

project(instrument_mixer VERSION 0.1 LANGUAGES CXX)

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
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
	instrumentcontroller.cpp
	instrumentcontroller.h
	instrumentcontroller.ui
	spectrogram.cpp
	spectrogram.h
	spectrogram.ui
)

# Handle stk includes and macros
include_directories("../thirdparty/stk/include")
file(GLOB STK_SOURCES ../thirdparty/stk/src/*.cpp)
file(GLOB STK_DRIVERS ../thirdparty/stk/src/include/*)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    link_libraries(Threads::Threads)

link_libraries(winmm ole32 wsock32)
add_definitions(-D__WINDOWS_MM__)

link_libraries(dsound)
add_definitions(-D__WINDOWS_DS__)

#add_definitions(-D_STK_DEBUG_)

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(NOT IS_BIG_ENDIAN)
  add_definitions(-D__LITTLE_ENDIAN__)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(instrument_mixer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
	${STK_SOURCES}
	${STK_DRIVERS}
    )
endif()

target_link_libraries(instrument_mixer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(instrument_mixer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS instrument_mixer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(instrument_mixer)
endif()
