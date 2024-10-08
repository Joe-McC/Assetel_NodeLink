cmake_minimum_required(VERSION 3.16)

project(ColorPicker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

option(BUILD_TESTING "Build tests" ${DEVELOPER_DEFAULTS})
option(BUILD_EXAMPLES "Build Examples" ${DEVELOPER_DEFAULTS})
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)

qt_add_library(ColorPicker STATIC)

qt_add_qml_module(${PROJECT_NAME}
    URI ColorTools
    VERSION 1.0
    QML_FILES
        main.qml
        ColorTool.qml
        ColorHistory.qml
        ColorSampler.qml
        ColorPicker.qml
        RGBSlider.qml
        HSVSlider.qml
        ColorSlider.qml
        ColorPickerDialog.qml
    SOURCES
        colorwheel.h colorwheel.cpp
        colorsampler_p.h colorsampler_p.cpp
        colortool_p.h colortool_p.cpp
        colorpicker_p.h colorpicker_p.cpp
        colorslider_p.h colorslider_p.cpp
        colorhistorymodel.h colorhistorymodel.cpp
        colorpickerpreview.h colorpickerpreview.cpp
        textfielddoublevalidator.h textfielddoublevalidator.cpp
    RESOURCES
        assets/swap.svg
        assets/eyedropper.svg
        assets/alphaBackground.png
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
