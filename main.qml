import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id: window
    visible: true
    width: 1366
    height: 768
    title: qsTr("Kadbyte")
    color: "#314C31"
    visibility: "Maximized"

    Rectangle {
        id: rectangle
        width: 1000
        height: leafImage.sourceSize.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Image {
            id: leafImage
            source: "bg.png"
        }

        /*Text {
            text: qsTr("Manage")
            color: "white"
        }*/

        Button{
            text: qsTr("Sign Up")
            anchors.verticalCenter: parent.verticalCenter
            visible: true
            background: Rectangle {
                color: "#2ECC71"
                radius: 5
            }
            topPadding: 10
            bottomPadding: 10
            onClicked: console.log("Button is clicked")
            anchors.left: leafImage.left
            anchors.right: leafImage.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
        }
    }

}
