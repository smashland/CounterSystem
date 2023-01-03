import QtQuick 2.0
import QtQuick.Controls 2.3
import "../Common"

Dialog{
    id: dialog
    property int nID: 0
    modal: true
    background:Rectangle {
        color: "transparent"
        Image {
            anchors.fill: parent
            source: "qrc:/Image/wuqi/08-bg.png"
        }
    }
    PopupTitle {
        name: ("给"+nID+'号充弹')
        icon: "\ue795"
        x: 54 *dpx
        y: 44*dpy
    }

    onAccepted:
    {
        var allNum=[8];
        for(var i=0; i<allInfo.count;++i)
        {
            allNum[i] = allInfo.itemAt(i).children[1].text;
        }
        $app.settings.chongDan(nID,allNum);
    }

    Column {
        id:allInfo
        spacing: 16
        anchors.centerIn: parent
        SoldierItem2 {
            title: "手      枪："
//            danwei: "支"
        }
        SoldierItem2 {
            title: "步      枪："
//            danwei: "支"
        }
        SoldierItem2 {
            title: "机      枪："
//            danwei: "支"
        }
        SoldierItem2 {
            title: "狙击步枪："
//            danwei: "支"
        }
        SoldierItem2 {
            title: "手      雷："
//            danwei: "个"
        }
    }
    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40 *dpy
        x: 204.5*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"
            onClicked: {
                var allNum=[8];
                for(var i=0; i<allInfo.count;++i)
                {
                    allNum[i] = allInfo.itemAt(i).children[1].text;
                }
                $app.settings.chongDan(nID,allNum);
                dialog.close()
            }

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: {
                dialog.close()
            }
        }
    }


}









/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
