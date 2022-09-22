import QtQuick 2.12
import QtQuick.Controls 2.3
import "Setting" as Settings
import "Common"
import "Login"
import "Exercise"
import "Manage"
import "Status"
import "RePlay" as MyRePlay
import MyItem 1.0


Rectangle
{
    id: index
    anchors.fill: parent
    color: "transparent"

    GroupDropArea
    {
        id:unGroup
        type:""
//        Image {
//            anchors.fill: parent
            source: "qrc:/Image/Grey_bg_all.png"
//        }
        height: 880 *dpy
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 80
        anchors.topMargin: 80
        visible: !$app.settings.bIsStart&&!$app.settings.bIsReplay
    }

    GroupDropArea
    {
        id:blue
        type:"蓝方"
//        Image {
//            anchors.fill: parent
            source: "qrc:/Image/Blue_bg_all.png"
//        }

        anchors.right: parent.right;
        anchors.top: parent.top
        anchors.rightMargin: 80
        anchors.topMargin: 80
    }

    GroupDropArea
    {
        id:red
        type:"红方"
//        Image {
//            anchors.fill: parent
            source: "qrc:/Image/Red_bg_all.png"
//        }

        anchors.right: ($app.settings.bIsStart || $app.settings.bIsReplay) ? undefined : parent.right
        anchors.top: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.top : blue.bottom
        anchors.left: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.left : undefined

        anchors.leftMargin: 80
        anchors.rightMargin: 80
        anchors.topMargin: 80
    }

    Menu
    {
        id: contextMenu
        property int userID
        width: 100*dpx
        height: 240*dpy
        MenuBackground
        {
            name: "充弹"
            onTriggered:
            {
                chongdan.nID=contextMenu.userID;
                chongdan.open();
            }
        }
//        MenuItem { text: "配枪" ;onTriggered: { peiqiang.nID = contextMenu.userID;peiqiang.open();}}
        MenuBackground { name: "闭锁" ;onTriggered:$app.settings.setBiSuo(contextMenu.userID)}
        MenuBackground { name: "解锁" ;onTriggered:$app.settings.setJiesuoSuo(contextMenu.userID)}
        MenuBackground { name: "解除旁白";onTriggered:$app.settings.setJieChu(contextMenu.userID) }
        MenuBackground { name: "判死";onTriggered:$app.settings.setPanSi(contextMenu.userID)}
        MenuBackground { name: "复活" ;onTriggered:{$app.settings.setFuHuo(contextMenu.userID)}}
        MenuBackground { name: "关机" }
//        MenuItem { text: "同步时间";onTriggered:{sycntime.nID = contextMenu.userID;sycntime.open();}}
        MenuBackground { name: "定位";onTriggered:{$app.allData.dingWei(contextMenu.userID)}}
    }

    /// 充弹窗口
    Settings.ChongDan
    {
        anchors.centerIn: parent
        id:chongdan
        width: 600
        height: 500
    }

    Dialog
    {
        id:peiqiang
        anchors.centerIn: parent
        property var nID: 0
        title: "给"+nID+'号配枪'
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        TextField
        {
            id:qianghao
            maximumLength:4
            placeholderText:'枪号'
            validator: IntValidator
            {
                bottom:1
                top:9999
            }
        }
        onAccepted:
        {
            $app.settings.peiQiang(nID,qianghao.text);
        }
    }

    Dialog
    {
        id:sycntime
        property var nID: 0
        title: "给"+nID+"同步时间";
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        TextField
        {
            id:setTime
            maximumLength:4
            placeholderText:'时间(s):'
            validator: IntValidator
            {
                bottom:1
                top:60
            }
        }
        onAccepted:
        {
            $app.settings.sycTime(nID,setTime.text);
        }
    }

    /// 用户的详细信息
    PersonAllInfo
    {
        id:allInfo
        visible: false
    }

    Manoeuvre {
        id:manoeuvre
        x: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: true
    }
    FooterBar {
        id: footerBar
        x: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false
    }

    KillSituation {
        id: killSituation
        visible: false
        x: (index.width-killSituation.width) / 2
        y: (index.height-killSituation.height) / 2
    }
    ExerciseResults {
        id: exerciseResults
        visible: false
        x: (index.width-exerciseResults.width) / 2
        y: (index.height-exerciseResults.height) / 2
    }
    SetLoader {
        id: setloader
        visible: footerBar.btnSet.checked
        x: (index.width-setloader.width) / 2
        y: (index.height-setloader.height) / 2
    }
    HelpLoader {
        id: helploader
        visible: footerBar.btnHelp.checked
        x: (index.width-helploader.width) / 2
        y: (index.height-helploader.height) / 2
    }
    ScenarioLoader {
        id: scenarioLoader
        visible: footerBar.btnScenario.checked
        x: (index.width-scenarioLoader.width) / 2
        y: (index.height-scenarioLoader.height) / 2
    }
    ScenarioNew {
        id: scenarioNew
        visible: false
        x: (index.width-scenarioNew.width) / 2
        y: (index.height-scenarioNew.height) / 2
    }
    ScenarioPopup {
        id: scenariopop
        visible: false
        x: (index.width-scenariopop.width) / 2
        y: (index.height-scenariopop.height) / 2
    }
    PlaybackLoader {
        id: playbackLoader
        visible: footerBar.btnPlayback.checked
        x: (index.width-playbackLoader.width) / 2
        y: (index.height-playbackLoader.height) / 2
    }

    PlaybackRefresh {
        id: playbackRefresh
        visible: false
        x: (index.width-playbackRefresh.width) / 2
        y: (index.height-playbackRefresh.height) / 2
    }
//    ScenarioRemove {
//        id: scenarioRemove
//        visible: false
//        x: (index.width-scenarioRemove.width) / 2
//        y: (index.height-scenarioRemove.height) / 2
//    }

//        Progressbar {
//            id: progressbar
//            visible: true
//        }
        CloseBar {
            id: closebar
            visible: true
        }
    CloseBarFull{
        id: closebarFull
        visible: false
    }
    Kill {
        id: kill
        visible: false
        y: killExpand.y
        x: killExpand.x
        Drag.active: dragAreakill.drag.active
        Drag.hotSpot.x: 10
        Drag.hotSpot.y: 10
        MouseArea {
            id: dragAreakill
            anchors.fill: parent
            drag.target: parent
            propagateComposedEvents: true
        }
    }
    KillExpand {
        id: killExpand
        visible: false
        y: 65 *dpy
        x: 395 *dpx
        Drag.active: dragAreakillExpand.drag.active
        Drag.hotSpot.x: 10
        Drag.hotSpot.y: 10

        MouseArea {
            id: dragAreakillExpand
            anchors.fill: parent
            drag.target: parent
            propagateComposedEvents: true
        }
    }
    MyRePlay.ContrlRePlay
    {
        id:ctrReplay
        anchors.top: index.top
//        anchors.left: index.left
//        anchors.leftMargin: (index.width-ctrReplay.width)/2
        visible: false
    }
//    GroupInfoDisplay {
//        id: groupInfoDisplay

//        Drag.active: dragAreagroupInfoDisplay.drag.active
//        Drag.hotSpot.x: 10
//        Drag.hotSpot.y: 10

//        MouseArea {
//            id: dragAreagroupInfoDisplay
//            anchors.fill: parent
//            drag.target: parent
//            propagateComposedEvents: true
//        }
//    }

    ResizeItem {
        id: resizeItem
        enableSize: 8
        anchors.fill: parent
        focus: true
        visible: false
    }
    PersonAdd {
        id: personAdd
        anchors.centerIn: parent
        visible: false
    }
    SceManager{
        id:sceManager
    }
    ScePersonInfo{
        id:scePersonInfo
    }
    RemoveDialog {
        id: removeDialog_quit
        visible: false
        content1: "此操作将退出程序，"
        content2: "确认要退出吗？"
        onYesPutDown: {
            $app.exitApp();
            Qt.quit()
        }
    }



}
