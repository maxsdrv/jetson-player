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
        opacity: 1
        anchors.bottom: parent.bottom

        Row {
            spacing: 10
            anchors.centerIn: parent

            Button {
                id: playButton
                width: 50
                height: 30
                scale: 1.0

                background: Rectangle {
                    color: "transparent"
                    radius: 10
                }

                contentItem: Image {
                    source: "qrc:/resource/play_01.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                MouseArea {
                    anchors.fill: parent

                    onPressed: {
                        playButton.scale = 0.9
                    }
                    onReleased: {
                        playButton.scale = 1.0
                    }

                    onClicked: {
                        networkManager.playRequested()
                    }
                }

                Behavior on scale {
                    NumberAnimation {
                        target: playButton
                        duration: 100
                    }
                }

            } // play button

            Button {
                text: "Pause"
                width: 50
                height: 30
                onClicked: {

                }
            } // pause button

            Button {
                text: "Stop"
                width: 50
                height: 30
                onClicked: {

                }
            } // stop button

        } // row

    } // control

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
