cmake_minimum_required(VERSION 3.5)

project(constellation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.h
        ${CMAKE_SOURCE_DIR}/src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(constellation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${CMAKE_SOURCE_DIR}/src/binaryreader.h ${CMAKE_SOURCE_DIR}/src/binaryreader.cpp
        ${CMAKE_SOURCE_DIR}/src/constellationwidget.h ${CMAKE_SOURCE_DIR}/src/constellationwidget.cpp
        ${CMAKE_SOURCE_DIR}/src/constellationwindow.h ${CMAKE_SOURCE_DIR}/src/constellationwindow.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET constellation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(constellation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(constellation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/iq_qam32.bin ${CMAKE_CURRENT_BINARY_DIR}/iq_qam32.bin COPYONLY)

target_link_libraries(constellation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(constellation PRIVATE Qt${QT_VERSION_MAJOR}::Xml)
# target_link_libraries(constellation PRIVATE ${QT_QTXML_LIBRARY})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
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
