cmake_minimum_required(VERSION 3.16)

project(assetel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Concurrent QuickControls2)

qt_standard_project_setup()

qt_add_executable(appassetel
    main.cpp
    resources.qrc
    #qml/Main.qml
)

qt_add_qml_module(appassetel
    URI assetel
    VERSION 1.0
    QML_FILES qml/Main.qml qml/NodeExample.qml qml/TreeView.qml qml/TreeViewItem.qml
    RESOURCES resources.qrc
    SOURCES models/treemodel.h models/treemodel.cpp models/treeitem.h models/treeitem.cpp models/treemanipulator.h models/treemanipulator.cpp
)

# NodeLink to save and load project.
add_subdirectory(NodeLink)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appassetel PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appexample
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)

target_link_libraries(appassetel
    PRIVATE Qt6::Quick Qt6::QuickControls2
    NodeLink
    NodeLinkplugin
)

include(GNUInstallDirs)

install(TARGETS NodeLink
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


install(TARGETS appassetel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

