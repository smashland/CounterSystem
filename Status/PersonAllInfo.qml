import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import "../Common"
import "../Exercise"

Popup
{
    width: 1002*dpx
    height: 680*dpy
    anchors.centerIn: parent
    modal: true

    property var outData
    property var rowNum;
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
                    SoldierItem {
                        id: mingzi
                        y: shibbingxinxi.contentHeight + line1.height + 20 *dpy
                        text: "名       字:"
//                            name: outData.name
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
                        name: "1"
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
                        text: "精       度:"
                        name: "0.00"
                    }
                    SoldierItem {
                        x: line1.width/2
                        y: weizhixinxi.contentHeight + line3.height + 20 *dpy
                        text: "纬       度:"
                        name: "0"
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
                        }
                    }
                    Item {
                        x: line1.width/2
                        y: zhuangbei.contentHeight + line3.height + 20 *dpy
                        Rectangle {
                            color: "transparent"
                            Text {
                                id: beixin
                                width: beixin.contentWidth
                                height: 34 *dpy
                                text: "背心连接:"
                                color: "#ffffff"
                                font.pixelSize: 17*dpx;
                                font.family: "Microsoft YaHei";
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Rectangle {
                            x: beixin.contentWidth + 20 *dpx
                            width: 200*dpx
                            height: 34 *dpy
                            color: "#52749e"
                            border.color: "#3b6daa"
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

            }
            PopupButton {
                background: Rectangle {
                    color: "#1d4f88"
                }
                nameButton: "取消"
            }
        }






//    ColumnLayout
//    {
//        spacing: 0
//        anchors.fill: parent
//        GridLayout
//        {
//            id: grid
//            Layout.fillHeight: false
//            Layout.fillWidth: false
//            rows: rowNum;
//            columns: 3

//            /// 人员模块信息
//            PersonFlipable
//            {
//                Layout.preferredHeight: 411
//                Layout.preferredWidth: 193
//                Layout.rowSpan: rowNum
//                Layout.columnSpan: 1
//            }

//            /// 显示设备信息
//            PersonInfoLabel
//            {
//                id: equipmentID
//                text: qsTr("设备ID:")+outData.id
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 150
//                Layout.columnSpan: 2
//                Layout.rowSpan: 1
//            }

//            /// 设备显示信息
//            PersonInfoLabel
//            {
//                id: nameLabel
//                text: qsTr("姓  名:")

//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 100
//                Layout.column: 1
//                Layout.row: 1
//            }

//            /// 输入信息
//            TextInput
//            {
//                id: textInput
//                text: outData.name
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 100
//                Layout.column: 2
//                Layout.row: 1

//                font:equipmentID.font
//                color:equipmentID.color
//                verticalAlignment: equipmentID.verticalAlignment
//                horizontalAlignment: equipmentID.horizontalAlignment
//                maximumLength:4

//                onEditingFinished:
//                {
//                    $app.allData.setUserName(outData.id,text);
//                }
//            }

//            /// 归属方
//            PersonInfoLabel
//            {
//                id: nameLabel1
//                text: qsTr("归属方:")+outData.type
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 150
//                Layout.columnSpan: 2
//                Layout.rowSpan: 1
//            }

//            /// 站立姿态
//            PersonInfoLabel
//            {
//                id: attitudeLabel
//                text: qsTr("姿  态:") + (outData.bStand ? qsTr("站立") : qsTr("卧倒"))
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 150
//                Layout.columnSpan: 2
//                Layout.rowSpan: 1
//            }

//            /// 手枪子弹数
//            PersonInfoLabel
//            {
//                id: numPistol
//                visible: outData.bPistol
//                text: qsTr("手枪子弹数:") + outData.nPistol
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 150
//                Layout.columnSpan: 2
//                Layout.rowSpan: 1
//            }

//            /// 步枪子弹数
//            PersonInfoLabel
//            {
//                id: numRifle
//                visible: outData.bRifle
//                text: qsTr("步枪子弹数:") + outData.nRifle
//                Layout.preferredHeight: 27
//                Layout.preferredWidth: 170
//                Layout.columnSpan: 2
//                Layout.rowSpan: 1
//            }
//        }

//        /// 状态信息
//        GroupBox
//        {
//            label: PersonInfoLabel
//            {
//                text: qsTr("状态信息")
//            }

//            id: groupBox
//            x: 247
//            y: 170
//            width: 228
//            height: 235

//            Layout.fillWidth: true
//            Layout.fillHeight: true
//            ScrollView
//            {
//                anchors.fill: parent
//                clip: true
//                ColumnLayout
//                {
//                    id:uuuu
//                    anchors.fill: parent
//                    ListView
//                    {
//                        height: 200
//                        id:showHurtInfo
//                        model: outData.listHit
//                        delegate: PersonInfoLabel
//                        {
//                            text: modelData
//                        }
//                    }
//                }
//            }
//        }
//    }

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
