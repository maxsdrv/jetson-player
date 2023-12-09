import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import network_manager 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("JetPlayer")

    property string ipAddr: {"http://localhost:5001"}

    // Button {
    //     id: fetchDataBtn
    //     text: "Play"
    //     anchors.centerIn: parent
    //     onClicked: {
    //         networkManager.sendRequest(ipAddr)
    //     }
    // }

    Network {
        id: networkManager
        url: ipAddr

        onResponseChanged: {
            console.log("Response ...")
        }
    }

    Label {
        id: responseLabel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: networkManager.response
        //text: "Server response:"
    }
}
