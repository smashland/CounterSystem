//                                        演习结果
import QtQuick 2.12
import Qt.labs.qmlmodels 1.0
import Qt.labs.platform 1.1
import QtQuick.Controls 1.4 as QC114
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.15
import "../Common"
import "../Manage/Plugins"

Item {
    id: exerciseResults
    width: 1184 *dpx
    height: 860 *dpy

    property string defaltFolderUrl: "file:///D:/InstallSoftWare/CounterSystem/Data/Szy/"
    property string loactionStr:"{"+$app.sAveLon+","+$app.sAveLat+"}"

    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_27.png"
    }

    PopupTitle {
        name: "演习结果"
        icon:"\ue654"
        x: 65*dpx
        y: 64*dpy
    }

    CloseButton {
        anchors.right: exerciseResults.right
        anchors.rightMargin: 70 *dpx
        anchors.top: exerciseResults.top
        anchors.topMargin: 70 *dpy
        onClicked:
        {
            exerciseResults.visible = false
            $app.allData.clearInfo();
        }
    }

    Column {
        y: 117*dpy
        x: 80*dpx
        spacing: 13*dpy

        ExerciseItem {
            id:sceName
            width: 300*dpx
            title:"演习名称:"
            name:sceManager.currentSceName
        }

        Row {
            id:xuxian1
            width:1024*dpx
            height: 1*dpy
            spacing: 4*dpx
            clip: true
            Repeater {
                anchors.fill: parent
                model:128
                delegate:Rectangle {
                    width: 4*dpx
                    height: 1*dpy
                    color:"white"
                }
            }
        }

        Row {
            spacing: 200*dpx
            ExerciseItem {
                width: 300*dpx
                title:"演习开始时间:"
                name: manoeuvre.startTime
            }
            ExerciseItem {
                width: 300*dpx
                title:"演习结束时间:"
                name:manoeuvre.endTime
            }
        }
        Row {
            id:xuxian2
            width:1024*dpx
            height: 1*dpy
            spacing: 4*dpx
            clip: true
            Repeater {
                anchors.fill: parent
                model:128
                delegate:Rectangle {
                    width: 4*dpx
                    height: 1*dpy
                    color:"white"
                }
            }
        }
        Row {
            spacing: 200*dpx
            ExerciseItem {
                id:earthName
                width: 300*dpx
                title:"地图名称:"
                name:earthManager.currentName
            }
            ExerciseItem {
                id:earthLoction
                width: 300*dpx
                title:"位置:"
                name:loactionStr
            }
        }
    }

    QC114.TableView
    {
        id:resultTable
        y: 256*dpy
        x: 80 *dpx
        width: 1024 *dpx
        height: 142*dpy
        //        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        style:TableViewStyle
        {
            id:tstyle;
            backgroundColor:"#4671a6"; //"#4671a6" : "#2D5689"

            //设置表头的样式
            headerDelegate :Rectangle{
                implicitWidth: 100
                implicitHeight: 40
                color: "#4671a6"
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: styleData.value
                    color: "white"
                    font.pixelSize: 20*dpy
                    font.bold: true
                }
            }

            // 设置行
            rowDelegate:Rectangle
            {
                height:50*dpy;
                color:styleData.alternate ? "#4671a6":"#2D5689"
            }

            // 设置单元格
            itemDelegate: Text
            {
                text:styleData.value;
                font.pointSize:18;
                color:"#ffffff"
                verticalAlignment:Text.AlignVCenter;
                horizontalAlignment:Text.AlignHCenter;
            }
        }
        QC114.TableViewColumn
        {
            role: "belong"
            title: qsTr("属方")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "all"
            title: qsTr("总人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "hurt"
            title: qsTr("受伤人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "dealth"
            title: qsTr("死亡人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "score"
            title: qsTr("得分情况")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        model: $app.allData.listResult;
    }

    Row {
        spacing: 24 *dpx
        y: 410 *dpy
        x: 80 *dpx
        Repeater {
            model: $app.allData.allResult
            Rectangle {
                width :500*dpx
                height: 320*dpy
                color: Qt.rgba(74/255,120/255,177/255,0.3)

//                Text
//                {
//                    id: sahngwangqingkuang
//                    x: 40 *dpx
//                    y: 20 *dpy
//                    text:qsTr(modelData.belong+"伤亡情况")
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignHCenter
//                    font.pixelSize: 20*dpx
//                    color: "#ffffff"
//                    font.family: "Microsoft YaHei"
//                }
                ComboBoxItem{
                    id: chartImg
                    x: 40 *dpx
                    y: 20 *dpy
                    width: 206*dpx
                    height: 21*dpy
                    listheight: 130
                    listelementheight: 30
                    items: [
                        {target:modelData.belong+"伤亡情况"},
                        {target:"弹药损耗情况"}
                    ]
                    currentText: modelData.belong+"伤亡情况"
                    onCurrentIndexChanged: {
                        var type = chartImg.currentIndex;
                        if(type === 0){
                            chartImg.currentText = modelData.belong+"伤亡情况"
                            redChart.visible = true
                            glow.visible = true
                            circle.visible = true
                            lineChart.visible = false
                        }else if(type === 1) {
                            chartImg.currentText = "弹药损耗情况"
                            redChart.visible = false
                            glow.visible = false
                            circle.visible = false
                            lineChart.visible = true
                        }
                    }
                }

                RedChart {
                    id: redChart
                    width :500*dpx
                    height: 320*dpy
                    //                     title: modelData.belong
                    hurtData:modelData.hurt
                    deathData:modelData.dealth
                    okData:modelData.ok
                }
                LineChart {
                    id: lineChart
                    y: 35*dpy
                    width: 500*dpx
                    height: 290*dpy
                    visible: false
                    belongColor:modelData.belong
                    allBulltes: 1000//modelData.allBullets
                }

                Rectangle {
                    id: circle
                    width: 125*dpy
                    height: 125*dpy
                    border.color: "skyblue"
                    color: "transparent"
                    radius: width/2
                    antialiasing: true
                    anchors.centerIn: parent
                }

                Glow {
                    id: glow
                    anchors.fill: circle
                    radius:9
                    samples: 13
                    color: "#dddddd"
                    source: circle
                    spread: 0.5
                    opacity: 0.8
                    NumberAnimation on opacity {
                        id:an1
                        to:0.8
                        duration: 2000
                        running: true
                        onStopped: {
                            an2.start()
                        }
                    }
                    NumberAnimation on opacity {
                        id:an2
                        to:0.2
                        duration: 2000
                        onStopped: {
                            an1.start()
                        }
                    }
                }

            }
        }
    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 375.5*dpx
        PopupButton {
            id: save
            width: 150*dpx
            background: Rectangle {
                color: "#265aef"
                Text {
                    id: popupText
                    height: 36 *dpy
                    width: 150*dpx
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "保存演习数据"
                    font.pixelSize: 16*dpx
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                }
            }

            //            nameButton: "保存演习数据"
            onClicked: {              
                openFile.open()
            }

        }
        FileDialog
        {
            id:openFile
            folder:defaltFolderUrl
            fileMode:FileDialog.SaveFile
            title: qsTr("保存演习数据")
            nameFilters: [qsTr("演习数据(*.szy)")]
            options: FileDialog.DontConfirmOverwrite
            onAccepted:
            {
                $app.allData.saveData(currentFile);
                $app.saveNoticText(currentFile);

            }
        }
        PopupButton {
            //            id: print
            width: 150*dpx
            background: Rectangle {
                color: "#265aef"
                Text {
                    height: 36 *dpy
                    width: 150*dpx
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "打印演习报告"
                    font.pixelSize: 16*dpx
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                }
            }

            //            nameButton: "打印演习报告"
            onClicked:
            {
                printWPS.open();
            }

        }
        FileDialog
        {
            id:printWPS
            folder:$app.appPath
            fileMode:FileDialog.SaveFile
            title: qsTr("保存演习报告")
            nameFilters: [qsTr("演习报告(*.docx)")]
            onAccepted:
            {
                $app.allData.getSceVsLoc(sceName.name,earthLoction.name);
                $app.allData.createReport(currentFile);
            }
        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked:
            {
                exerciseResults.visible = false
                $app.allData.clearInfo();
            }
        }
    }
}
