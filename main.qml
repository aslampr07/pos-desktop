import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import com.kadbyte.signup 1.0
import com.kadbyte.navigation 1.0

Window {
    id: window
    visible: true
    width: 1366
    height: 768
    title: qsTr("KadByte")

    Connections{
        target: Navigation
        onTokenLoaded: {
            if(isTokenAvailable){
                rootLoader.source = "MainPage.qml"
            }
            else{
                rootLoader.source = "Authentication.qml"
            }
        }
    }

    Connections{
        target: rootLoader.item
        onAuthenticationSuccess: {
            rootLoader.source = "MainPage.qml"
        }
    }

    Loader{
        id: rootLoader
        anchors.fill: parent
        Component.onCompleted: {
            Navigation.checkToken()
        }
    }
}
