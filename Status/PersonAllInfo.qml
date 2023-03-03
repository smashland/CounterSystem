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
            y: shibbingxinxi.contentHeight + line1.height + 74 *dpy+ 20 *dpy
            color: "transparent"
            Text {
                id: fushangxinxi
                width: fushangxinxi.contentWidth
                height: fushangxinxi.contentHeight
                text: qsTr("装备信息")
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
                id:shouqiang
                y: fushangxinxi.contentHeight + line2.height + 20 *dpy
                text: outData.nRifle > 0 ? "步枪子弹数:" : "子弹数:"
                name:outData.nRifle + "/"+outData.nRifleSum
            }


            SoldierItem {
                id:buqiang
                x: line2.width/2
                y: fushangxinxi.contentHeight + line2.height + 20 *dpy
                text: outData.nPistol > 0 ? "手枪子弹数:" : "子弹数:"
                name: outData.nPistol +   "/" +  outData.nPistolSum
            }

            SoldierItem {
                id:juji
                x: line2.width/2
                y: fushangxinxi.contentHeight + line2.height + 74 *dpy
                text: outData.nSniperSum > 0 ?"狙击子弹数:" : "子弹数:"
                name: outData.nSniperSum/*outData.nSniper*/ +   "/" +  outData.nSniperSum
            }

        }
        Rectangle {
            id: colum3
            y: (fushangxinxi.contentHeight + line2.height + 74 *dpy+ 20 *dpy) * 2
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
            y: (fushangxinxi.contentHeight + line2.height + 74 *dpy+ 20 *dpy) * 3
            color: "transparent"
            Text {
                id: zhuangbei
                width: zhuangbei.contentWidth
                height: zhuangbei.contentHeight
                text: qsTr("状态信息")
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
            SoldierItem {
                id:mingzhong
                y: zhuangbei.contentHeight + line3.height + 20 *dpy
                text: "命       中:"
                name:outData.nHitCount
            }
            SoldierItem {
                id:beimingzhong
                x: line1.width/2
                y: zhuangbei.contentHeight + line3.height + 20 *dpy
                text: "被  命  中:"
                name: outData.nHurtCount
            }
        }

    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40 *dpy
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
