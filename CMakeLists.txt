cmake_minimum_required(VERSION 3.5)

project(constellation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

set(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.h
        ${CMAKE_SOURCE_DIR}/src/mainwindow.ui
)

qt_add_executable(constellation
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${CMAKE_SOURCE_DIR}/src/binaryreader.h ${CMAKE_SOURCE_DIR}/src/binaryreader.cpp
    ${CMAKE_SOURCE_DIR}/src/constellationwidget.h ${CMAKE_SOURCE_DIR}/src/constellationwidget.cpp
    ${CMAKE_SOURCE_DIR}/src/constellationwindow.h ${CMAKE_SOURCE_DIR}/src/constellationwindow.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/iq_qam32.bin ${CMAKE_CURRENT_BINARY_DIR}/iq_qam32.bin COPYONLY)

target_link_libraries(constellation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(constellation PRIVATE Qt${QT_VERSION_MAJOR}::Core)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.constellation)
endif()
set_target_properties(constellation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS constellation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(constellation)
endif()
