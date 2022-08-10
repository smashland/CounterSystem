import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import SceneGraphRendering 1.0
import Qt.labs.platform 1.1
//import "Status" as MyStatus
//import "Result" as MyResult
//import "RePlay" as MyRePlay

Item
{
    id:rootItem
    anchors.fill: parent
    property var objSetting;

    /// 显示地图
    QuickOSGViewer
    {
        type: QuickOSGViewer.Item_3DMAP
        frameRate:60
        id: renderer
        anchors.fill: parent
        focus: true
        Keys.enabled: true;
        Keys.onEscapePressed:
        {
            $app.exitApp();
        }

        MouseArea
        {
            anchors.fill: renderer
            onPressed:
            {
                renderer.forceActiveFocus();
                mouse.accepted = false;
            }
            propagateComposedEvents: true
        }
    }

    function closeSettings()
    {
        if(null !== objSetting)
        {
            objSetting.destroy();
            renderer.forceActiveFocus();
        }
    }

    Component.onCompleted:
    {
        $app.setOsgItem(renderer);
        var cpShowSetting= Qt.createComponent("qrc:/Index.qml")
        objSetting = cpShowSetting.createObject(rootItem,{focus:true});
        if(null === objSetting)
        {
            console.log(cpShowSetting.errorString())
        }
    }


    /// 演习开始后的状态
//    MainCircle
//    {
//        id:showStatus
//        x:test.x
//        y:test.y
//        width:test.width
//        height:test.height
//        visible: false
//        onRightClick:
//        {
//            confirm.exitShowLabel="是否结束演习";
//            confirm.open();
//        }

//        onLeftClick:
//        {
//            showTest()
//        }
//    }

//    Connections
//    {
//        target: $app.settings
//        function onReplayStatusChanged(bReplay)
//        {
//            if(bReplay)
//            {
//                test.visible=false;
//            }
//            else
//            {
//                test.visible=true;
//            }
//        }
//    }
//    ConfirmPopUp
//    {
//        id:confirm;
//        onYesPutDown:
//        {
//            if(confirm.exitShowLabel==="是否保存演习数据")
//            {
//                openFile.open()
//            }
//            else
//            {

//                if($app.settings.bIsStart)
//                {
//                    showTest()
//                }

//                changeStatus()
//            }
//        }

//        onClosed:
//        {
//            if(confirm.exitShowLabel==="是否保存演习数据")
//            {
//                showResult.open()
//            }
//        }
//    }

//    /// 图标按钮
//    MainWindow
//    {
//        id:test
//        onRightClick:
//        {
//            confirm.exitShowLabel="是否开始演习";
//            confirm.open();
//        }
//        onLeftClick:
//        {
//            if($app.settings.bIsStart)
//            {
//                showMainCircl()
//            }
//        }

//        onStartReplay:
//        {
//            replayFile.open();
//        }
//    }


//    /// 导出结果界面
//    MyResult.Result
//    {
//        id:showResult
//    }

//    /// 命中提示
//    MyStatus.BoardNotice
//    {
//    }

//    /// 回放进度条
//    MyRePlay.ContrlRePlay
//    {
//        id:ctrReplay
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 50
//        visible: false
//        x:($appWindow.width-200)/2
//    }

//    FileDialog
//    {
//        id:replayFile
//        folder:$app.appPath
//        fileMode:FileDialog.OpenFile
//        title: qsTr("打开演习数据")
//        nameFilters: [qsTr("演习数据(*.szy)")]
//        onAccepted:
//        {
//            ctrReplay.nTimes = $app.allData.openReplayFile(currentFile);
//            ctrReplay.visible = true;
//            $app.settings.startReplay()
//            showStatus.visible=false
//        }
//    }

//    FileDialog
//    {
//        id:openFile
//        folder:$app.appPath
//        fileMode:FileDialog.SaveFile
//        title: qsTr("保存演习数据")
//        nameFilters: [qsTr("演习数据(*.szy)")]
//        onAccepted:
//        {
//            $app.allData.saveData(currentFile);
//        }
//    }



//    function showMainCircl()
//    {
//        fadeOut.target=test;
//        fadeIn.target=showStatus
//        fadeOut.start()
//        fadeIn.start()
//        if(null !== objSetting)
//        {
//            objSetting.visible = false
//        }
//    }

//    function showTest()
//    {
//        fadeOut.target=showStatus;
//        fadeIn.target=test
//        fadeOut.start()
//        fadeIn.start()
//        if(null !== objSetting)
//        {
//            objSetting.visible = true
//        }
//    }

//    /// 更改状态
//    function changeStatus()
//    {
//        if($app.settings.bIsStart)
//        {
//            /// 演习结束
//            $app.settings.setStop();
//            $app.allData.calResult();
//            confirm.exitShowLabel="是否保存演习数据"
//            confirm.open()
//        }
//        else
//        {
//            /// 演习开始清空状态
//            showMainCircl()
//            $app.allData.clearInfo();
//            $app.settings.setStart();
//        }
//    }

//    PropertyAnimation
//    {
//        id: fadeOut
//        target: test
//        duration: 300
//        property: "opacity"
//        from: 1.0
//        to: 0.0

//        onStopped:
//        {
//            target.visible = false
//        }
//    }

//    PropertyAnimation
//    {
//        id: fadeIn
//        target: showStatus
//        duration: 300
//        property: "opacity"
//        from: 0.0
//        to: 1.0
//        onStarted:
//        {
//            target.visible = true
//        }
//    }

}
