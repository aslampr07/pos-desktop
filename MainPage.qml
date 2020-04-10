import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    Rectangle {
        id: navigationBar
        color: "#3949AB"
        width: 64
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        ButtonGroup{
            buttons: buttonColumn.children
            onClicked: {
                //For setting up the acive button, and disable inactive button.
                for(let i = 0; i < buttonColumn.children.length; i++){
                    if(button === buttonColumn.children[i]){
                        button.isActive = true
                        workSpace.currentIndex = i + 1
                    }
                    else{
                        buttonColumn.children[i].isActive = false
                    }
                }
            }
        }

        ColumnLayout {
            id: buttonColumn
            spacing: 0
            NavButton{
                id: homeButton
                source: "/img/img/home.png"
            }
            NavButton{
                id: statButton
                source: "/img/img/stats.png"
            }
            NavButton{
                id: itemButton
                source: "/img/img/items.png"
            }
        }

    }

    StackLayout{
        id: workSpace
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navigationBar.right

        /*To be removed*/
        currentIndex: 3

        Rectangle{
            color: "white"

        }
        Rectangle{
            color: "green"

        }
        Rectangle{
            color: "cyan"
        }
        Rectangle{
            id: itemsPage
            color: "#F2F8FF"

            Drawer{
                id: newItemLayout
                width: 400
                height: parent.height
                edge: Qt.RightEdge
                interactive: false
                closePolicy: Popup.NoAutoClose

                Rectangle {
                    anchors.fill: parent
                    Rectangle {
                        id: itemTitleLayout
                        color: "#e1e4f3"
                        height: 200
                        anchors.left: parent.left
                        anchors.right: parent.right

                        Button{
                            anchors.top: addItemTitle.top
                            anchors.bottom: addItemTitle.bottom
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            onClicked: {
                                newItemLayout.close()
                            }
                            background: Image {
                                source: "/img/img/back.png"
                            }
                        }

                        Text {
                            id: addItemTitle
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            text: qsTr("New Item")
                            font.pointSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    TextField {
                        id: itemNameInput
                        placeholderText: qsTr("Name")
                        font.pointSize: 12
                        anchors.top: itemTitleLayout.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 30
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                        background: Rectangle {
                            border.color: "#3949AB"
                            border.width: 2
                            radius: 5
                        }
                    }
                    TextField {
                        id: itemPriceInput
                        placeholderText: qsTr("Price")
                        font.pointSize: 12
                        anchors.top: itemNameInput.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 30
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                        background: Rectangle {
                            border.color: "#3949AB"
                            border.width: 2
                            radius: 5
                        }
                    }
                    TextField {
                        id: itemAliasInput
                        placeholderText: qsTr("Alias")
                        font.pointSize: 12
                        anchors.top: itemPriceInput.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 30
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                        background: Rectangle {
                            border.color: "#3949AB"
                            border.width: 2
                            radius: 5
                        }
                    }
                    Button {
                        id: saveButton
                        text: "Save"
                        anchors.right: itemAliasInput.horizontalCenter
                        anchors.left: itemAliasInput.left
                        anchors.top: itemAliasInput.bottom
                        anchors.topMargin: 30
                        anchors.rightMargin: 10
                        topPadding: 12
                        bottomPadding: 12
                        background: Rectangle {
                            color: "#3949AB"
                        }
                        contentItem: Text {
                            text: parent.text
                            font.pointSize: 11
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }
                    }
                    Button {
                        id: saveNewButton
                        text: "Save + New"
                        anchors.right: itemAliasInput.right
                        anchors.left: itemAliasInput.horizontalCenter
                        anchors.top: itemAliasInput.bottom
                        anchors.topMargin: 30
                        anchors.leftMargin: 10
                        topPadding: 12
                        bottomPadding: 12
                        background: Rectangle {
                            border.color: "#3949AB"
                            border.width: 2
                        }
                        contentItem: Text {
                            text: parent.text
                            font.pointSize: 11
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#3949AB"
                        }
                    }
                }

            }

            TextField {
                id: itemSearchInput
                width: 300
                placeholderText: qsTr("Search name, alias")
                anchors.left: itemList.left
                anchors.top: parent.top
                anchors.topMargin: 20
                font.pointSize: 10
                padding: 15
                leftPadding: 40
                background: Rectangle {
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 5
                    Image {
                        id: name
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        source: "img/img/seach.png"
                    }
                }
            }
            Button {
                id: addItemButton
                text: "Add Item"
                anchors.right: itemList.right
                anchors.top: itemSearchInput.top
                anchors.bottom: itemSearchInput.bottom
                leftPadding: 40
                rightPadding: 10
                background: Rectangle {
                    color: "#3949AB"
                    radius: 5

                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        source: "img/img/add.png"
                    }
                }
                contentItem: Text {
                    text: parent.text
                    font.pointSize: 11
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
                onClicked: {
                    newItemLayout.open()
                }
            }

            Rectangle {
                id: itemList
                color: "white"
                width: 1000
                height: 600
                anchors.verticalCenter: parent.verticalCenter
                anchors.topMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}















