import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import "../Common"
import "../Exercise"

Popup
{
    id: personPopup
    width: 1002*dpx
    height: 680*dpy
    anchors.centerIn: parent
    modal: true

    property var outData
    property var rowNum;
    property var bConnected:true
    signal nameChanged(var personName)
    /// 背景半透明
    background:Rectangle
    {
        //        color:$app.settings.type2Color(outData.type)
        color:"transparent"
        //        opacity: 0.7
        Image {
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_27.png"
        }
    }

    PopupTitle {
        id: popuptitle
        name: qsTr("人员信息")
        icon: qsTr("\ue8b8")
        x: 60*dpx
        y: 40*dpy
    }


    Rectangle {
        x: 50 *dpx
        y: 106*dpy
        color: "transparent"
        width: 188*dpx
        height: 230*dpx
        Image {
            anchors.fill:parent
            source: "qrc:/Image/soldiers.png"
        }
    }
    Rectangle {
        width: 664 *dpx
        x: 278 *dpx
        y: 106 *dpy
        color: "transparent"

        Rectangle {
            id: column1
            color: "transparent"
            Text {
                id: shibbingxinxi
                width: shibbingxinxi.contentWidth
                height: shibbingxinxi.contentHeight
                text: qsTr("士兵信息")
                font.pixelSize: 18*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei"
            }
            Rectangle {
                id: line1
                y: shibbingxinxi.contentHeight
                width: 664 *dpx
                height: 2 *dpy
                color: "#3b6daa"
            }
            SoldierItem {
                id:shebeiName
                y: shibbingxinxi.contentHeight + line1.height + 20 *dpy
                text: "名       字:"
                name: outData.name
            }

            SoldierItem {
                id:shebeiId
                x: line1.width/2
                y: shibbingxinxi.contentHeight + line1.height + 20 *dpy
                text: "装备编号:"
                name: outData.id
            }
        }

        Rectangle {
            id: colum2
            y: shibbingxinxi.contentHeight + line1.height + 20 *dpy + 74 *dpy
            color: "transparent"
            Text {
                id: fushangxinxi
                width: fushangxinxi.contentWidth
                height: fushangxinxi.contentHeight
                text: qsTr("负伤信息")
                font.pixelSize: 18*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei"
            }
            Rectangle {
                id: line2
                y: fushangxinxi.contentHeight
                width: 664 *dpx
                height: 2 *dpy
                color: "#3b6daa"
            }
            SoldierItem {
                id:reliveName
                y: fushangxinxi.contentHeight + line2.height + 20 *dpy
                text: "复活次数:"
                name: outData.uRelive
            }
        }
        Rectangle {
            id: colum3
            y: (fushangxinxi.contentHeight + line2.height + 20 *dpy + 74 *dpy) * 2
            color: "transparent"
            Text {
                id: weizhixinxi
                width: weizhixinxi.contentWidth
                height: weizhixinxi.contentHeight
                text: qsTr("位置信息")
                font.pixelSize: 18*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei"
            }
            Rectangle {
                id: line3
                y: weizhixinxi.contentHeight
                width: 664 *dpx
                height: 2 *dpy
                color: "#3b6daa"
            }
            SoldierItem {
                id:lat
                y: weizhixinxi.contentHeight + line3.height + 20 *dpy
                text: "经       度:"
                name:outData.dLon
            }
            SoldierItem {
                id:lon
                x: line1.width/2
                y: weizhixinxi.contentHeight + line3.height + 20 *dpy
                text: "纬       度:"
                name: outData.dLat
            }
        }
        Rectangle {
            id: colum4
            y: (fushangxinxi.contentHeight + line2.height + 20 *dpy + 74 *dpy) * 3
            color: "transparent"
            Text {
                id: zhuangbei
                width: zhuangbei.contentWidth
                height: zhuangbei.contentHeight
                text: qsTr("装备连接状态")
                font.pixelSize: 18*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei"
            }
            Rectangle {
                id: line4
                y: zhuangbei.contentHeight
                width: 664 *dpx
                height: 2 *dpy
                color: "#3b6daa"
            }
            Item {
                y: zhuangbei.contentHeight + line3.height + 20 *dpy
                Rectangle {
                    color: "transparent"
                    Text {
                        id: toukui
                        width: toukui.contentWidth
                        height: 34 *dpy
                        text: "头盔连接:"
                        color: "#ffffff"
                        font.pixelSize: 17*dpx;
                        font.family: "Microsoft YaHei";
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                Rectangle {
                    x: toukui.contentWidth + 20 *dpx
                    width: 200*dpx
                    height: 34 *dpy
                    color: "#52749e"
                    border.color: "#3b6daa"
                    EquipConnStat
                    {
                        id: toukuizhuangtai
                        bConnected: outData.bTK
                        source: "qrc:/Image/wuqi/toukui.png"
                    }
                }
            }
        }

    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 413*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"
            onClicked: {
                personPopup.close()
                $app.allData.setUserName(outData.id,shebeiName.name);
                if(shebeiName.name ===""){
                    $app.allData.setUserName(outData.id,shebeiName.name);
                }
            }

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: {
                personPopup.close()
            }
        }
    }

    onClosed:
    {
        $app.allData.setUpdateAllInfo(false);
    }

    onOpened:
    {
        if($app.settings.bIsStart)
        {
            $app.allData.setUpdateAllInfo(true);
        }
    }

//    Connections {
//        target: $app.allData
//        function onMapPersonInfo(id,name,relive,dLon,dLat,bTk){
//            shebeiId.name = id;
//            shebeiName.name = name
//            reliveName.name = relive;
//            lat.name = dLat;
//            lon.name = dLon;
//            toukuizhuangtai.bConnected = bTk;
//            personPopup.visible=true;
//        }
//    }
}
