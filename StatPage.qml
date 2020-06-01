import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.kadbyte.statistics 1.0

Rectangle {

    FontLoader {
        id: robotoCondensed
        source: "fonts/RobotoCondensed-Regular.ttf"
    }
    FontLoader {
        id: robotoCondensedBold
        source: "fonts/RobotoCondensed-Bold.ttf"
    }

    color: "cyan"
    Statistics{
        id: stats
        onStatisticsLoaded: {
            incomeLabel.text = "₹ " + income
            expenseLabel.text = "₹ " + expense
            netAmountLable.text = "₹ " + (income - expense)
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 400
        Calendar {
            id: mainCalender
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stats.loadStatistics(date)
         }

        Rectangle{
            id: divider
            anchors.verticalCenter: parent.verticalCenter
            anchors.topMargin: 70
            width: parent.width
            height: 1;
            color: "#D9D9D9"
        }
        Text {
            id: totalEarningTitle
            text: qsTr("Total Earnings")
            color: "#888888"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: divider.bottom
            font.family: robotoCondensed.name
            font.pointSize: 18
        }

        Image {
            id: profitImage
            anchors.top: totalEarningTitle.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.topMargin: 20
            source: "/img/profit.png"
        }
        Text {
            id: incomeText
            anchors.top: profitImage.top
            anchors.bottom: profitImage.bottom
            anchors.left: profitImage.right
            anchors.leftMargin: 10
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Incomes")
            font.family: robotoCondensed.name
            font.pointSize: 16
        }

        Text{
            id: incomeLabel
            anchors.top: profitImage.top
            anchors.bottom: profitImage.bottom
            anchors.right: parent.right
            anchors.rightMargin: 10
            verticalAlignment: Text.AlignVCenter
            font.family: robotoCondensed.name
            font.pointSize: 16
            color: "#22A98D"
        }
        Image {
            id: lossImage
            anchors.top: profitImage.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.topMargin: 20
            source: "/img/loss.png"
        }
        Text {
            id: expenseText
            anchors.top: lossImage.top
            anchors.bottom: lossImage.bottom
            anchors.left: lossImage.right
            anchors.leftMargin: 10
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Expenses")
            font.family: robotoCondensed.name
            font.pointSize: 16
        }
        Text{
            id: expenseLabel
            anchors.top: lossImage.top
            anchors.bottom: lossImage.bottom
            anchors.right: parent.right
            anchors.rightMargin: 10
            verticalAlignment: Text.AlignVCenter
            font.family: robotoCondensed.name
            font.pointSize: 16
            color: "#E06767"
        }
        Text{
            id: netAmountLable
            anchors.top: lossImage.bottom
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.topMargin: 30
            font.family: robotoCondensed.name
            font.pointSize: 32
        }
    }
}
