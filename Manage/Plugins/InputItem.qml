import QtQuick 2.12
import QtQuick.Controls 2.15

TextInput {
    id: textInput
    property alias name: textInput.text

    x: 10 *dpx
//    text:scenarioNewInfo.sceName
    width: 420*dpx
    height: 40 *dpy
    font.pixelSize: 17*dpx
    color: "#ffffff"
    clip: true
    font.family: "Microsoft YaHei"
    verticalAlignment: Text.AlignVCenter
//    onEditingFinished: {
//        scenarioNewInfo.setSceName(nameItemContent.text)
//    }

}
