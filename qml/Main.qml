import QtQuick
import QtQuickStream
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts

import NodeLink
import assetel

/*! ***********************************************************************************************
 * MainWindow of NodeLink assetel
 * ************************************************************************************************/

Window {
    id: window

    /* Property Declarations
     * ****************************************************************************************/

    //! will be overriden by load
    property Scene scene: Scene { }

    //! nodeRegistry: Use nodeRegistry in the main scene (we need one object)
    property NLNodeRegistry nodeRegistry:      NLNodeRegistry {
        _qsRepo: NLCore.defaultRepo

        imports: ["assetel","NodeLink"];
        defaultNode: 0
    }

    /* Object Properties
     * ****************************************************************************************/

    width: 1280
    height: 960
    visible: true
    title: qsTr("NodeLink assetel")
    color: "#1e1e1e"

    Material.theme: Material.Dark
    Material.accent: "#4890e2"


    Component.onCompleted: {
        // Prepare nodeRegistry
        var nodeType = 0;
        nodeRegistry.nodeTypes[nodeType]  = "NodeExample";
        nodeRegistry.nodeNames[nodeType]  = "NodeExample";
        nodeRegistry.nodeIcons[nodeType]  = "\ue4e2";
        nodeRegistry.nodeColors[nodeType] = "#444";

        nodeRegistry.nodeTypes[nodeType + 1]  = "Container";
        nodeRegistry.nodeNames[nodeType + 1]  = "Container";
        nodeRegistry.nodeIcons[nodeType + 1]  = "\uf247";
        nodeRegistry.nodeColors[nodeType + 1] = NLStyle.primaryColor;

        NLCore.defaultRepo = NLCore.createDefaultRepo(["QtQuickStream", "NodeLink", "assetel"])
        NLCore.defaultRepo.initRootObject("Scene");

        //Set registry to scene
        window.scene = Qt.binding(function() { return NLCore.defaultRepo.qsRootObject;});
        window.scene.nodeRegistry = Qt.binding(function() { return window.nodeRegistry});
    }

    /* Children
     * ****************************************************************************************/

    /*NLView {
        id: view
        scene: window.scene
        anchors.fill: parent
    }*/

    // MenuBar at the top
    MenuBar {
        id: menuBar
        z: 2  // Ensure the MenuBar is on top of other components
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50  // Set a fixed height for the MenuBar

        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...")
                onTriggered: loadDialog.visible = true }
            Action { text: qsTr("&Save")
                onTriggered: saveDialog.visible = true }
            Action { text: qsTr("Save &As...")
                onTriggered: saveDialog.visible = true }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("Cu&t") }
            Action { text: qsTr("&Copy") }
            Action { text: qsTr("&Paste") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
        }
    }

    // SplitView below the MenuBar
    SplitView {
        id: splitView
        anchors.top: menuBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 1  // Ensure the SplitView is below the MenuBar

        ColumnLayout {
            width: 300
            Layout.minimumWidth: 100
            Layout.maximumWidth: 500
            z: 1

            Text {
                id: titlelabel
                text: qsTr("Node Title:")
            }

            TreeView {
                id: treeView

                Layout.fillWidth: true
                Layout.fillHeight: true

                model: treeManipulator.sourceModel()
                selectionEnabled: true

                onCurrentIndexChanged: if(currentIndex) console.log("current index is (row=" + currentIndex.row + ", depth=" + model.depth(currentIndex) + ")")
                onCurrentDataChanged: if(currentData) console.log("current data is " + currentData)
                onCurrentItemChanged: if(currentItem) console.log("current item is " + currentItem)
            }
        }

        NLView {
            id: view
            scene: window.scene
            Layout.fillWidth: true
            Layout.fillHeight: true

            onNodeAdded: (nodeUuid) => {
                // Handle the nodeAdded signal here
                console.log("Node added:", nodeUuid);
                // Add any additional logic you need to handle the added node
                treeModel.handleNodeAdded(nodeUuid);
            }

        }
    }

    //Save
    FileDialog {
        id: saveDialog
        currentFile: "QtQuickStream.QQS.json"
        fileMode: FileDialog.SaveFile
        nameFilters: [ "QtQuickStream Files (*.QQS.json)" ]
        onAccepted: {
            NLCore.defaultRepo.saveToFile(saveDialog.currentFile);
        }
    }

    //! Load
    FileDialog {
        id: loadDialog
        currentFile: "QtQuickStream.QQS.json"
        fileMode: FileDialog.OpenFile
        nameFilters: [ "QtQuickStream Files (*.QQS.json)" ]
        onAccepted: {
            NLCore.defaultRepo.clearObjects();
            NLCore.defaultRepo.loadFromFile(loadDialog.currentFile);
//            window.scene = Qt.binding(function() { return NLCore.defaultRepo.qsRootObject;});
        }
    }

    //! Copy nodes shortcut
    Shortcut {
        sequence: "Ctrl+C"
        onActivated: {
            view.copyNodes();
        }
    }

    //! Paste nodes shortcut
    Shortcut {
        sequence: "Ctrl+V"
        onActivated: {
            view.pasteNodes()
        }
    }

    //! Select all nodes and links
    Shortcut {
        sequence: "Ctrl+A"
        onActivated: scene?.selectionModel.selectAll(scene.nodes, scene.links, scene.containers);
    }

    //! Clones all selected nodes
    Shortcut {
        sequence: "Ctrl+D"
        onActivated: {
            var copiedNodes = ({});
            var copiedContainers = ({});
            Object.keys(scene?.selectionModel.selectedModel ?? []).forEach(key => {
                if (Object.keys(scene.nodes).includes(key)){

                    var copiedNode = scene?.cloneNode(key);
                    copiedNodes[copiedNode._qsUuid] = copiedNode;
                }

                if (Object.keys(scene?.containers).includes(key)){
                    var copiedContainer = scene?.cloneContainer(key);
                    copiedContainers[copiedContainer._qsUuid] = copiedContainer;
                }
            });

            scene?.selectionModel.selectAll(copiedNodes, ({}), copiedContainers);
        }
    }
}
