add_library(misc STATIC
    utilities.cpp
    abstractasseteltem.h
    mydocument.h mydocument.cpp
    xmlelement.h xmlelement.cpp
    xmlconnector.h xmlconnector.cpp
    xmlnode.h xmlnode.cpp
    customtype.h customtype.cpp
    parentsmodel.h parentsmodel.cpp
    xmlprocessor.h xmlprocessor.cpp
    nodelistmodel.h nodelistmodel.cpp
    connectorlistmodel.h connectorlistmodel.cpp
)
target_link_libraries(misc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2 Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml)
target_include_directories(misc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

