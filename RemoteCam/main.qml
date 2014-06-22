import QtQuick 2.2
import QtQuick.Window 2.1
import QtMultimedia 5.0
import QtPositioning 5.2
import QtSensors 5.0
import ImageSource 1.0
import ImageServer 1.0
import SpaceChecker 1.0
import SensorLogger 1.0

Window {
  visible: true
  //    width: Window.width
  //    height: Window.height
  color: "black"

  Rectangle {
    color: "black"
    anchors.fill: parent

    SpaceChecker {
      id: spaceCheck
      onFreeSpace: freeSpaceText.text = "Free Space: " + freeSpace + "GB"
    }

    SensorLogger {
      id: sensorLog
    }

    ImageServer {
      id: imgSrv
    }

    ImageSource {
      id: imgSrc
      //      onNewFrame: imgSrv.newFrame(frame);
    }

    VideoOutput {
      id: viewFinder
      source: imgSrc
      anchors.fill: parent
      focus: visible
    }

    Rectangle {
      color: "black"
      anchors.bottom: parent.bottom
      anchors.left: parent.left
      width: parent.width
      height: 40
    }

    Text {
      id: freeSpaceText
      color: "white"
      anchors.bottom: parent.bottom
      anchors.right: parent.right
    }
  }
}
