import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import network_manager 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("JetPlayer")

    property string ipAddr: {"http://192.168.1.194:5005"}

    /*Button {
        id: fetchDataBtn
        text: "Play"
        anchors.centerIn: parent
        onClicked: {
            netManager.sendRequest(ipAddr)
        }
    }*/

    Network {
        id: networkManager

    }


    Label {
        id: responseLabel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        //text: netManager.response
        text: "Server response:"
    }
}
