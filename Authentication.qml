import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import com.kadbyte.signup 1.0

Rectangle{
    id: loginSection
    color: "#314C31"

    signal authenticationSuccess()

    Rectangle {
        id: startSection
        width: 1000
        height: leafImage.sourceSize.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: leafImage
            source: "/img/bg.png"
        }

        ColumnLayout {
            anchors.right: leafImage.right
            anchors.left: leafImage.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 50
            anchors.rightMargin: 50

            Text {
                text: qsTr("Manage")
                font.pointSize: 18
                color: "white"
            }

            Text {
                text: qsTr("With KadByte manage your business from everywhere at anytime")
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                color: "white"
            }

            Button {
                text: qsTr("Sign Up")
                Layout.fillHeight: false
                visible: true
                Layout.fillWidth: true
                Layout.topMargin: 20
                background: Rectangle {
                    color: "#2ECC71"
                    radius: 5
                }
                contentItem: Text {
                    text: parent.text
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
                topPadding: 15
                bottomPadding: 15
                onClicked: {
                    text = signUpStack.currentIndex == 0 ? qsTr("Sign Up") : qsTr("Sign In")
                    signUpStack.currentIndex = signUpStack.currentIndex == 0 ? 1 : 0
                }
            }
        }

        StackLayout {
            id: signUpStack
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: leafImage.right

            Rectangle {
                id: signInSection
                color: "#F8F8F8"

                SignUp {
                    id: signup
                    onUserNameError: console.log(error)
                    onPasswordError: console.log(error)
                    onSuccess: authenticationSuccess()
                }

                ColumnLayout {

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    width: 300

                    Text {
                        id: welcomeLabel
                        text: qsTr("Welcome Back")
                        font.pointSize: 20
                        Layout.bottomMargin: 25
                        color: "#2ECC71"
                        Layout.alignment: Qt.AlignHCenter
                    }
                    TextField {
                        id: userNameInput
                        placeholderText: qsTr("Username")
                        font.pointSize: 12
                        Layout.fillWidth: true
                        padding: 15
                        background: Rectangle {
                            border.color: "#2ECC71"
                            border.width: 2
                            radius: 5
                        }
                    }
                    TextField {
                        id: passwordInput
                        placeholderText: qsTr("Password")
                        font.pointSize: 12
                        width: 300
                        Layout.fillWidth: true
                        Layout.topMargin: 20
                        padding: 15
                        echoMode: "Password"
                        onAccepted: {
                            console.log("Enter pressed");
                            signup.username = userNameInput.text
                            signup.password = passwordInput.text
                            signup.signup()
                        }
                        background: Rectangle {
                            border.color: "#2ECC71"
                            border.width: 2
                            radius: 5
                        }
                    }

                    CheckBox {
                        text: qsTr("Remember me")
                        onToggled: signup.isRemeberEnabled = checked
                    }

                    Button {
                        anchors.topMargin: 10
                        leftPadding: 20
                        rightPadding: 20
                        text: qsTr("Log In")
                        visible: true
                        background: Rectangle {
                            color: "#2ECC71"
                            radius: 5
                        }
                        contentItem: Text {
                            text: parent.text
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }
                        onClicked: {
                            signup.username = userNameInput.text
                            signup.password = passwordInput.text
                            signup.signup()
                        }
                    }
                }
            }

            Rectangle {
                id: signUpSection
                color: "grey"
            }
        }
    }
}
