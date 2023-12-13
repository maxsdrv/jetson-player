import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtMultimedia

import network_manager 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("JetPlayer")

    property string ipAddr: {"http://localhost:5001"}

    MediaPlayer {
        id: mediaPlayer
        source: "rtp://localhost:5000"
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            mediaPlayer.play()
        }
    }

    Control {
        Button {
            text: mediaPlayer.playbackState == MediaPlayer.PlayingState ? "Pause" : "Play"
            onClicked: {
                if (mediaPlayer.playbackState == MediaPlayer.PlayingState) {
                    mediaPlayer.pause();
                } else {
                    networkManager.play()
                    console.log("FFmpeg server run.")
                    mediaPlayer.play();
                    console.log("Media Player play.")
                }
            }
        }
    }

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
