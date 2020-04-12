import QtQuick 2.0
import QtQuick.Controls 2.5

TextField {
    property string error: ""

    onErrorChanged: {
        if(error != ""){
            inputError.visible = true
            inputError.text = error
            inputBackground.border.color = "red"
        }
        else {
            inputError.visible = false
            inputBackground.border.color = "#3949AB"
            inputError.text = "error"
        }
    }
    background: Rectangle {
        id: inputBackground
        border.color: "#3949AB"
        border.width: 2
        radius: 5
        Text {
            id: inputError
            visible: false
            color: "red"
            anchors.top: parent.bottom
            anchors.topMargin: 2
            anchors.left: parent.left
        }
    }
}
