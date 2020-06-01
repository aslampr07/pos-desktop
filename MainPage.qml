import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import com.kadbyte.item 1.0

Rectangle {
    Rectangle {
        id: navigationBar
        color: "#3949AB"
        width: 64
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        ButtonGroup {
            buttons: buttonColumn.children
            onClicked: {
                //For setting up the acive button, and disable inactive button.
                for (var i = 0; i < buttonColumn.children.length; i++) {
                    if (button === buttonColumn.children[i]) {
                        button.isActive = true
                        workSpace.currentIndex = i + 1
                    } else {
                        buttonColumn.children[i].isActive = false
                    }
                }
            }
        }

        ColumnLayout {
            id: buttonColumn
            spacing: 0
            NavButton {
                id: homeButton
                source: "/img/home.png"
            }
            NavButton {
                id: statButton
                source: "/img/stats.png"
            }
            NavButton {
                id: itemButton
                source: "/img/items.png"
            }
        }
    }

    StackLayout {
        id: workSpace
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navigationBar.right

        currentIndex: 0

        Rectangle {
            color: "green"
        }

        HomePage { }

        StatPage{}
        Rectangle {
            id: itemsPage
            color: "#F2F8FF"
            Component.onCompleted: {
                item.loadItemList()
            }

            Item {
                id: item
                onItemInsertSuccess: {
                    itemNameInput.text = ""
                    itemAliasInput.text = ""
                    itemPriceInput.text = ""
                    item.loadItemList()
                    if (!isSaveNew) {
                        newItemLayout.close()
                    }
                }
                onNameInputError: {
                    itemNameInput.error = error
                }
                onAliasInputError: {
                    itemAliasInput.error = error
                }
                onPriceInputError: {
                    itemPriceInput.error = error
                }
                onItemListFetched: {
                    itemList.model = product
                }
            }

            Drawer {
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

                        Button {
                            anchors.top: addItemTitle.top
                            anchors.bottom: addItemTitle.bottom
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            onClicked: {
                                newItemLayout.close()
                            }
                            background: Image {
                                source: "/img/back.png"
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

                    EditText {
                        id: itemNameInput
                        placeholderText: qsTr("Name")
                        anchors.top: itemTitleLayout.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 40
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                        font.pointSize: 12
                    }

                    EditText {
                        id: itemPriceInput
                        placeholderText: qsTr("Price")
                        font.pointSize: 12
                        anchors.top: itemNameInput.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 40
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                        validator: DoubleValidator {
                            bottom: 0
                            top: 10000
                            decimals: 2
                        }
                    }

                    EditText {
                        id: itemAliasInput
                        placeholderText: qsTr("Alias")
                        font.pointSize: 12
                        anchors.top: itemPriceInput.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 40
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        padding: 15
                    }

                    Button {
                        id: saveButton
                        text: "Save"
                        anchors.right: itemAliasInput.horizontalCenter
                        anchors.left: itemAliasInput.left
                        anchors.top: itemAliasInput.bottom
                        anchors.topMargin: 40
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
                        onClicked: {
                            itemNameInput.error = ""
                            itemAliasInput.error = ""
                            itemPriceInput.error = ""
                            item.createItem(itemNameInput.text,
                                            itemAliasInput.text,
                                            itemPriceInput.text, false)
                        }
                    }
                    Button {
                        id: saveNewButton
                        text: "Save + New"
                        anchors.right: itemAliasInput.right
                        anchors.left: itemAliasInput.horizontalCenter
                        anchors.top: itemAliasInput.bottom
                        anchors.topMargin: 40
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
                        onClicked: {
                            itemNameInput.error = ""
                            itemAliasInput.error = ""
                            itemPriceInput.error = ""
                            item.createItem(itemNameInput.text,
                                            itemAliasInput.text,
                                            itemPriceInput.text, true)
                        }
                    }
                }
            }

            TextField {
                id: itemSearchInput
                width: 300
                anchors.topMargin: 50
                anchors.top: parent.top
                anchors.left: itemList.left
                placeholderText: qsTr("Search name, alias")
                font.pointSize: 10
                padding: 15
                leftPadding: 40
                background: Rectangle {
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 3
                    Image {
                        id: name
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        source: "/img/seach.png"
                    }
                }
            }
            Button {
                id: addItemButton
                text: "Add Item"
                leftPadding: 40
                rightPadding: 10
                anchors.top: itemSearchInput.top
                anchors.bottom: itemSearchInput.bottom
                anchors.right: itemList.right
                background: Rectangle {
                    color: "#3949AB"
                    radius: 3

                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        source: "/img/add.png"
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

            ListView {
                id: itemList
                width: 1000
                anchors.topMargin: 60
                anchors.top: itemSearchInput.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 60
                clip: true
                ScrollBar.vertical : ScrollBar{

                }
                spacing: 10
                delegate: Rectangle {
                    width: parent.width
                    height: 40
                    RowLayout {
                        width: parent.width

                        Text {
                            text: modelData.slNumber
                        }
                        Text {
                            text: modelData.code
                        }
                        Text {
                            text: modelData.itemName
                            horizontalAlignment: Text.Center
                            Layout.fillWidth: true
                        }
                        Text {
                            text: modelData.price
                            horizontalAlignment: Text.AlignRight
                        }
                        Text {
                            text: modelData.createdAt
                        }
                    }
                }
            }
        }
    }
}
