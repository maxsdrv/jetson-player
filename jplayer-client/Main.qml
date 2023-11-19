import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import network_manager 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("JetPlayer")

    Button {
        id: fetchDataBtn
        text: "Play"
        anchors.centerIn: parent
        onClicked: {
            netManager.sendRequest("http://192.168.1.194:8080")
        }
    }

    Label {
        id: responseLabel
        anchors.top: fetchDataBtn.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: netManager.response
    }

    Network {
        id: netManager

    }
}
