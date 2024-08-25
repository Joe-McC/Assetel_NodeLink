cmake_minimum_required(VERSION 3.16)

#The Library name
project(Assetel VERSION 1.0.0 LANGUAGES CXX)

# ##################################################################################################
# Project Settings
# ##################################################################################################


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list (APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#message(${QML_IMPORT_PATH})
#Turns on default settings for development of Assetel
set(DEVELOPER_DEFAULTS ON)

option(BUILD_TESTING "Build tests" ${DEVELOPER_DEFAULTS})
option(BUILD_EXAMPLES "Build Examples" ${DEVELOPER_DEFAULTS})
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)

# ##################################################################################################
# Dependencies
# ##################################################################################################
# Find the Qt libraries

# NodeLink to save and load project.
add_subdirectory(NodeLink)

find_package(Qt6
  COMPONENTS
   Quick Concurrent
)

if (NOT Qt6_FOUND)
  find_package(Qt5 QUIET
    COMPONENTS
    Quick
  )
endif()


if (NOT (Qt6_FOUND OR Qt5_FOUND))
  message(FATAL_ERRROR "Qt libraries were not found.")
endif()


if (Qt6_FOUND)
  set(Qt Qt)
else()
  set(Qt Qt5)
endif()


# ##################################################################################################
# Project Files
# ##################################################################################################
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)

set(PROJECT_SOURCES
        main.cpp
        resources/main.qml
        resources/NodeExample.qml
        resources/qml.qrc
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
qt_add_executable(gui
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#   if(ANDROID)
#        add_library(gui SHARED
#            ${PROJECT_SOURCES}
#        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(gui
#          ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

target_link_libraries(gui
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  #Qt${QT_VERSION_MAJOR}::QuickControls2
  #Qt${QT_VERSION_MAJOR}::Xml
  #Qt${QT_VERSION_MAJOR}::Widgets
  #misc
  NodeLink)

set_target_properties(gui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(gui)
    qt_finalize_executable(gui)
endif()

qt_add_qml_module(gui
    URI "ui"
    VERSION 1.0

   QML_FILES
    resources/main.qml
    resources/NodeExample.qml

   SOURCES

)

#qt_add_qml_module(gui
#    URI gui
#    VERSION 1.0
#    QML_FILES resources/main.qml
#    SOURCES misc/treemodel.h misc/treemodel.cpp misc/treeitem.h misc/treeitem.cpp misc/treemanipulator.h misc/treemanipulator.cpp
#)


