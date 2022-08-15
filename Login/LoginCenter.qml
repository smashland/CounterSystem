import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import MyItem 1.0
import "../Common"

Item
{
    id: loginCenter
    anchors.fill: parent
    signal nextFrame(var licInfo)

    // 收到机器码信息
    function recive(str)
    {
        needLic.updateString(str);
        element.text = str;
    }

    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Login_bg.jpg"
    }
    NavImage {
        anchors.top: parent.top
        anchors.topMargin: 30 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 30 *dpx
    }

    Login {
        id: loginRect
        x: (mainWindow.width-loginRect.width)/2
        y: (mainWindow.height-loginRect.height)/2
    }
    Rectangle
        {
            id: rectangle
            width: 319*dpx
            height: 181*dpy
            color:  '#00000000'
            x: (mainWindow.width-rectangle.width)/2
            y: 760 *dpy
            Component.onCompleted:
            {
                rectangle.forceActiveFocus();
            }

            /// 显示二维码
            Rect
            {
                id:needLic
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.height/2
                height: parent.height/2
                visible: true
            }

            /// 显示二维码对应的文字
            Text
            {
                id: element
                enabled: false
                anchors.top: needLic.bottom
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
            }

            RowLayout
            {
                id: rowLayout
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: element.bottom
                anchors.topMargin: 5
                Text
                {
                    id: element1
                    text: "扫一扫 获取授权码"
                    color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
                    enabled: false
                }
            }
        }
    Connect {
        id: connect
        y: 950 *dpy
    }
}
