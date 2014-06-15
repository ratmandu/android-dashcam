import QtQuick 2.2
import QtQuick.Window 2.1
import QtMultimedia 5.0
import QtPositioning 5.2
import QtSensors 5.0
import ImageSource 1.0
import ImageServer 1.0

Window {
    visible: true
    width: Window.width
    height: Window.height
    color: "black"


    ImageServer {
      id: imgSrv
    }

    ImageSource {
      id: imgSrc
      onNewFrame: imgSrv.newFrame(frame);
    }

    VideoOutput {
      id: viewFinder
      source: imgSrc
      visible: false
//      anchors.fill: parent
//      focus: visible
    }
}
