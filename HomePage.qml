import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.14

import com.kadbyte.item 1.0
import com.kadbyte.invoice 1.0
import com.kadbyte.expense 1.0

Rectangle {

    FontLoader {
        id: robotoCondensed
        source: "fonts/RobotoCondensed-Regular.ttf"
    }
    FontLoader {
        id: robotoCondensedBold
        source: "fonts/RobotoCondensed-Bold.ttf"
    }

    Invoice {
        id: invoice
        onInvoiceItemChange: {
            totalAmountText.text = "₹" + total
        }
        onInvoiceTabChanged: {
            invoiceTab.model = list
        }
    }

    Item {
        id: item

        onItemListFetched: {
            itemGridList.model = product
            gridLoading.running = false
        }
    }

    color: "#F2F8FF"
    TextField {
        id: itemSearchInput
        width: 300
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 50
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
        id: addExpenseButton
        text: "New Expense"
        leftPadding: 40
        rightPadding: 10
        anchors.top: itemSearchInput.top
        anchors.bottom: itemSearchInput.bottom
        anchors.right: invoiceLayout.left
        anchors.rightMargin: 50
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
            addExpensePopup.open()
        }
    }

    Expense{
        id: expense
        onExpenseCreated: {
            addExpensePopup.close()
        }
    }

    Popup {
        id: addExpensePopup
        modal: true
        width: 350
        x: (parent.width / 2) - (width / 2)
        y: (parent.height / 2) - (implicitHeight / 2)
        background: Rectangle {
            border.width: 0
            radius: 3
        }


        closePolicy: Popup.NoAutoClose
        contentItem: ColumnLayout {

            Image {
                source: "/img/close.png"
                Layout.alignment: Qt.AlignRight
                MouseArea {
                    anchors.fill: parent
                    onClicked: addExpensePopup.close()
                }
            }

            Text {
                text: qsTr("New Expense")
                font.pointSize: 14
                Layout.alignment: Qt.AlignHCenter
                Layout.bottomMargin: 20
            }

            EditText {
                id: expenseTitle
                placeholderText: qsTr("Item")
                Layout.fillWidth: true
                font.pointSize: 12
                anchors.topMargin: 40
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                padding: 15
                Layout.bottomMargin: 20
            }
            EditText {
                id: expenseAmount
                placeholderText: qsTr("Amount")
                Layout.fillWidth: true
                font.pointSize: 12
                anchors.topMargin: 40
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                padding: 15
                validator: DoubleValidator {
                    bottom: 0
                    top: 10000
                    decimals: 2
                }
                Layout.bottomMargin: 20
            }

            Button {
                id: saveExpenseButton
                text: "Save"
                topPadding: 12
                bottomPadding: 12
                background: Rectangle {
                    radius: 5
                    color: "#3949AB"
                }
                Layout.fillWidth: true
                contentItem: Text {
                    text: parent.text
                    font.pointSize: 13
                    font.family: robotoCondensed.name
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
                onClicked: {
                    expense.createInvoice(expenseTitle.text, expenseAmount.text)
                }
            }
        }
    }

    GridView {
        id: itemGridList
        anchors.top: itemSearchInput.bottom
        anchors.left: parent.left
        anchors.right: invoiceLayout.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 50
        anchors.topMargin: 20
        clip: true

        boundsBehavior: Flickable.StopAtBounds

        cellHeight: 150
        cellWidth: 150

        Component.onCompleted: {
            item.loadItemList()
        }

        delegate: Rectangle {
            color: "#E67E22"
            width: 130
            height: 130
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    priceView.visible = true
                }
                onExited: {
                    priceView.visible = false
                }

                onClicked: {
                    invoice.addItemToInvoice(modelData.code,
                                             modelData.itemName,
                                             modelData.price)
                }
            }

            Rectangle {
                id: priceView
                visible: false
                color: "#ecf0f1"
                height: 30
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    text: "₹ " + modelData.price
                    font.pointSize: 13
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: robotoCondensedBold.name
                }
            }

            Rectangle {
                color: "white"
                height: 30
                clip: true
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    text: modelData.itemName
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: robotoCondensedBold.name
                }
            }
        }
    }

    BusyIndicator {
        id: gridLoading
        running: true
        anchors.right: invoiceLayout.left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        id: invoiceLayout
        color: "white"
        width: 400
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        ListView {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: totalAmountText.top

            model: invoice.model
            clip: true

            header: Rectangle {
                height: 40
                width: parent.width

                Text {
                    text: "Name"
                    color: "#888888"
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: "Quantity"
                    color: "#888888"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: "Price"
                    color: "#888888"
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            add: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: 400
                    easing.type: Easing.OutCirc
                }
            }
            remove: Transition {
                NumberAnimation {
                    property: "opacity"
                    from: 1.0
                    to: 0
                    duration: 200
                }
            }
            displaced: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: 400
                    easing.type: Easing.OutBounce
                }
            }

            delegate: Rectangle {
                width: parent.width
                height: 60
                Text {
                    anchors.left: parent.left
                    anchors.right: addRemoveItemLayout.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 10
                    text: name
                    font.pointSize: 11
                    font.family: robotoCondensed.name
                    elide: Text.ElideRight
                }

                RowLayout {
                    id: addRemoveItemLayout
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    Image {
                        source: quantity == 1 ? "/img/delete.png" : "/img/removeitem.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                invoice.removeItemFromInvoice(code)
                            }
                        }
                    }
                    Text {
                        text: quantity + "x"
                    }
                    Image {
                        source: "/img/additem.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                invoice.addItemToInvoice(code, name,
                                                         price / quantity)
                            }
                        }
                    }
                }
                Text {
                    anchors.right: parent.right
                    anchors.left: addRemoveItemLayout.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 10
                    text: "₹" + price
                    font.family: robotoCondensed.name
                    font.pointSize: 11
                    horizontalAlignment: Text.AlignRight
                }

                Rectangle {
                    width: parent.width - 50
                    height: 1
                    color: "#CCCCCC"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Text {
            text: "Total"
            anchors.bottom: confirmButton.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            color: "#888888"
            font.family: robotoCondensed.name
            font.pointSize: 20
        }

        Text {
            id: totalAmountText
            text: "₹0"
            anchors.bottom: confirmButton.top
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            font.bold: true
            font.family: robotoCondensed.name
            font.pointSize: 24
        }

        Button {
            id: confirmButton
            text: "CONFIRM"
            topPadding: 12
            bottomPadding: 12
            anchors.bottom: tabSection.top
            anchors.right: parent.right
            anchors.left: parent.left
            background: Rectangle {
                color: "#3949AB"
            }
            contentItem: Text {
                text: parent.text
                font.pointSize: 13
                font.family: robotoCondensed.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }
            onClicked: {
                invoice.createInvoice()
            }
        }
        Row{
            id: tabSection
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 50
            Repeater{
                id: invoiceTab
                anchors.fill: parent
                model: invoice.tabmodel
                Button{
                    width: 50
                    height: parent.height
                    text: index + 1
                    onClicked: invoice.tabItemClicked(index)
                    background:   Rectangle{
                        color: model.display ? "#B4B4B4": "white"
                    }
                }
            }
        }
    }
}








