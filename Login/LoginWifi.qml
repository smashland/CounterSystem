import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import MyItem 1.0
import "../Manage/Plugins"
import "../Common"
import "Plugins"

Column {
    signal toConnect()
    id: columnTextField
    spacing: 50*dpy
    Row
    {
        id: row
        spacing: 15*dpx

        TextFieldItem
        {
            id:outInput
            width: 220*dpx
            height: 50 *dpy
            background: Rectangle {
                color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                border.color: "#00baff"
            }
            text: $app.settings.getSip()
            font.bold: false
            placeholderText: qsTr("请输入IP地址")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        TextFieldItem {
            id:portInput
            width: 120*dpx
            height: 50 *dpy
            placeholderText: qsTr("端口号")
            background: Rectangle {
                color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                border.color: "#00baff"
            }
            font.bold: false
            validator: IntValidator{bottom: 0;top:65535;}
            text: $app.settings.getPort()
        }
    }

    LoginButton {
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                $app.settings.setWifiInfo(outInput.text,portInput.text);
                $app.startConnect();
                $licCheck.saveLicense(lrText.text);
                $licCheck.checkLicense()
            }
        }
    }
}

