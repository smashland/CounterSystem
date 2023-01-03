import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml 2.12
import "../Manage/Plugins"
import "../Common"
//kunag
Item
{
    id:showNotice
    width: 770*dpx
    height: 380*dpy
    anchors.centerIn: parent

    MapHelpList{
        id: listView
        width: 710 *dpx
        height: 420 *dpy
        model:$app.noiceList
        spacing: 2
        x: 30*dpx
        delegate: DelegateRectangle {
            id: wrapper
            Rectangle {
                anchors.fill: parent
                color: "#4671a6"
            }
            TextListItem {
                id: fileName
                text: modelData.noiceText
                anchors.centerIn: parent
                color:modelData.colorNotic
                font.pixelSize: 22*dpx
            }
        }

    }




}
