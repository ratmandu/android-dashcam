import QtQuick 2.0
import QtQuick.Controls 1.1
import QtMultimedia 5.0
import ConnectorClass 1.0

Rectangle {
  color: "black"
  width: parent.width
  height: parent.height

  ConnectorClass {
    id: connector
    objectName: "connectorObject"
  }

  Timer {
    id: imgTimer
    interval: 1000 / 30
    running: true
    repeat: true
    onTriggered: {
      frontImage.source = ""
      frontImage.source = "image://Cameras/front"
      rearImage.source = ""
      rearImage.source = "image://Cameras/rear"
    }
  }


  Flow {
    id: flow1
    anchors.fill: parent
    anchors.margins: 10
    spacing: 10

      Image {
        id: frontImage
        height: parent.height - 30
        width: (parent.width/2) - 15
        fillMode: Image.PreserveAspectFit
        cache: false
        source: "image://Cameras/front"
      }

      Image {
        id: rearImage
        height: parent.height - 30
        width: (parent.width/2) - 15
        fillMode: Image.PreserveAspectFit
        cache: false
        source: "image://Cameras/rear"
      }


  }

  Row {
    width: parent.width
    height: 30
    spacing: parent.width / 2

    Button {
      text: " Connect Front "
//      onClicked: connector.findAndConnectFrontServer()
      onClicked: connector.connectFrontServer("192.168.43.3")
    }

    Button {
      text: " Connect Rear "
//      onClicked: connector.findAndConnectRearServer()
      onClicked: connector.connectRearServer("192.168.43.2")
    }
  }

}

