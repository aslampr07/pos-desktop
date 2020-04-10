import QtQuick 2.0
import QtQuick.Controls 2.5

Button {

    property alias source: navImage.source
    property bool isActive: false

    onIsActiveChanged: {
        if(isActive){
            navBackground.opacity = 0.3
            navIndicator.visible = true
        }
        else {
            navBackground.opacity = 0
            navIndicator.visible = false
        }
    }

    background: Rectangle {
        id: navBackground
        color: "#ffffff"
        opacity: 0
    }
    padding: 30
    Image {
        id: navImage
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle {
        id: navIndicator
        width: 5
        visible: false
        color: "#ffffff"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
}
