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
        source: "rtp://10.10.3.206:5000"
        videoOutput: videoOutput
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    Rectangle {
        width: parent.width
        height: 50
        color: "white"
        opacity: 2
        anchors.bottom: parent.bottom

        Row {
            spacing: 10
            anchors.centerIn: parent

            Button {
                icon.source: "qrc:/resource/play_02.png"
                onClicked: {
                    networkManager.play()
                }
            }

            Button {
                text: "Pause"
                onClicked: {

                }
            }

            Button {
                text: "Stop"
                onClicked: {

                }
            }
        }
    }

    // Control {
    //     Button {
    //         text: mediaPlayer.playbackState == MediaPlayer.PlayingState ? "Pause" : "Play"
    //         onClicked: {
    //             if (mediaPlayer.playbackState == MediaPlayer.PlayingState) {
    //                 mediaPlayer.pause();

    //             } else {
    //                  networkManager.play()
    //                  console.log("FFmpeg server run.")
    //             }
    //         }
    //     }
    // }

    Network {
        id: networkManager
        url: ipAddr

        onStreamSuccessfullyPlayed: {
            console.log("Gstreamer played")
            mediaPlayer.play();
        }
    }

    Label {
        id: responseLabel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: networkManager.response
    }
}
