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
            source: "qrc:/Image/Popup_bg_20.png"
        }
    }

    PopupTitle {
        id: popuptitle
        x: 50 *dpx;
        y: 50 *dpy
        name: qsTr("人员信息")
        icon: qsTr("\ue8b8")
    }
    TransverseLine {
        x: 50 *dpx
        y: popuptitle.height + 50 *dpy
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
                    Rectangle {
                        id: soldierItem
                        y: shibbingxinxi.contentHeight + line1.height + 20 *dpy
                        Rectangle {
                            color: "transparent"
                            Text {
                                id: soldierItemText
                                width: soldierItemText.contentWidth
                                height: 34 *dpy
                                color: "#ffffff"
                                text: "名       字:"
                                font.pixelSize: 17*dpx;
                                font.family: "Microsoft YaHei";
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Rectangle {
                            x: soldierItemText.contentWidth + 20 *dpx
                            width: 200*dpx
                            height: 34 *dpy
                            color: "#1d4f88"
                            border.color: "#3b6daa"
                            TextInput {
                                id: soldierItemContent
                                x: 10 *dpx
                                width: 190*dpx
                                height: 34 *dpy
                                font.pixelSize: 17*dpx
                                color: "#ffffff"
                                clip: true
                                font.family: "Microsoft YaHei"
                                verticalAlignment: Text.AlignVCenter
                                text:outData.name
                                onEditingFinished:
                                {
                                    $app.allData.setUserName(outData.id,text);
                                }
                            }
                        }
                    }

                    SoldierItem {
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
                        y: weizhixinxi.contentHeight + line3.height + 20 *dpy
                        text: "经       度:"
                        name:outData.dLon
                    }
                    SoldierItem {
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
                            Text {
                                width: toukui.contentWidth
                                height: 34 *dpy
                                x: 10 *dpx
                                text: "是"
                                color: "#ffffff"
                                font.pixelSize: 17*dpx;
                                font.family: "Microsoft YaHei";
                                verticalAlignment: Text.AlignVCenter
                                visible: bConnected
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

                }

            }
            PopupButton {
                background: Rectangle {
                    color: "#1d4f88"
                }
                nameButton: "取消"
                onClicked: {
                    personPopup.visible = false
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

}
