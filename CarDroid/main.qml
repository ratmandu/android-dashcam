import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
  id: mainWindow
  visible: true
  width: 1280
  height: 800
  color: "black";
  title: qsTr("CarDroid")

  CameraView {
    anchors.left: parent.left
  }

}
