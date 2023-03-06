import QtQuick 2.12
import QtQuick.Controls 2.3
import "Setting" as Settings
import "Common"
import "Login"
import "Exercise"
import "Exercise/Plugins"
import "Manage"
import "Status"
import "RePlay"
import MyItem 1.0


Rectangle
{
    property var modifySceInfo: null
    property var newEarthInfo: null
    id: index
    anchors.fill: parent
    color: "transparent"

    GroupDropArea
    {
        id:unGroup
        type:""
        source: "qrc:/Image/Grey_bg_all.png"
        height: 880 *dpy
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 80*dpx
        anchors.topMargin: 80*dpy
        visible: !$app.settings.bIsStart&&!$app.settings.bIsReplay
    }

    GroupDropArea
    {
        id:blue
        type:"蓝方"
        source: "qrc:/Image/Blue_bg_all.png"
        anchors.right: parent.right;
        anchors.top: parent.top
        anchors.rightMargin: 80*dpx
        anchors.topMargin: 80*dpy
    }

    GroupDropArea
    {
        id:red
        type:"红方"
        source: "qrc:/Image/Red_bg_all.png"
        anchors.right: ($app.settings.bIsStart || $app.settings.bIsReplay) ? undefined : parent.right
        anchors.top: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.top : blue.bottom
        anchors.left: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.left : undefined

        anchors.leftMargin: 80*dpx
        anchors.rightMargin: 80*dpx
        anchors.topMargin: 80*dpy
    }

    Menu
    {
        id: contextMenu
        property int userID
        width: 100*dpx
        height: 210*dpy//240*dpy

        MenuBackground
        {
            name: "充弹"
            onTriggered:
            {
                if(!$app.settings.bIsReplay)
                {
                    chongdan.nID=contextMenu.userID;
                    chongdan.open();
                }
            }
        }
        //        MenuItem { text: "配枪" ;onTriggered: { peiqiang.nID = contextMenu.userID;peiqiang.open();}}
        MenuBackground { name: "闭锁" ;onTriggered:if(!$app.settings.bIsReplay){$app.settings.setBiSuo(contextMenu.userID)}}
        MenuBackground { name: "解锁" ;onTriggered:if(!$app.settings.bIsReplay){$app.settings.setJiesuoSuo(contextMenu.userID)}}
        MenuBackground { name: "解除旁白";onTriggered:if(!$app.settings.bIsReplay){$app.settings.setJieChu(contextMenu.userID)} }
        MenuBackground { name: "判死";onTriggered:if(!$app.settings.bIsReplay){$app.settings.setPanSi(contextMenu.userID)}}
        MenuBackground { name: "复活" ;onTriggered:{if(!$app.settings.bIsReplay){$app.settings.setFuHuo(contextMenu.userID)}}}
        //        MenuBackground { name: "关机" }
        //        MenuItem { text: "同步时间";onTriggered:{sycntime.nID = contextMenu.userID;sycntime.open();}}
        MenuBackground { name: "定位";onTriggered:{$app.allData.dingWei(contextMenu.userID)}}
    }

    Menu
    {
        id: contextMenu2
        property int userID
        width: 100*dpx
        height: 150*dpy//240*dpy

        MenuBackground
        {
            name: "充弹"
            onTriggered:
            {
                if(!$app.settings.bIsReplay)
                {
                    chongdan.nID=contextMenu.userID;
                    chongdan.open();
                }
            }
        }
        MenuBackground { name: "闭锁" ;onTriggered:if(!$app.settings.bIsReplay){$app.settings.setBiSuo(contextMenu.userID)}}
        MenuBackground { name: "解锁" ;onTriggered:if(!$app.settings.bIsReplay){$app.settings.setJiesuoSuo(contextMenu.userID)}}
        MenuBackground { name: "判死";onTriggered:if(!$app.settings.bIsReplay){$app.settings.setPanSi(contextMenu.userID)}}
        MenuBackground { name: "复活" ;onTriggered:{if(!$app.settings.bIsReplay){$app.settings.setFuHuo(contextMenu.userID)}}}
    }
    /// 充弹窗口
    Settings.ChongDan
    {
        anchors.centerIn: parent
        id:chongdan
        width: 600*dpx
        height: 470*dpy
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

    PlaybackLoader {
        id: playbackLoader
        visible: footerBar.btnPlayback.checked
        x: (index.width-playbackLoader.width) / 2
        y: (index.height-playbackLoader.height) / 2
    }

    ScePopup {
        id: scePopup2
        visible: false
        anchors.centerIn: parent
        text: "方案名称为空或重复，请重新添加方案！"
    }
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
    ContrlRePlay
    {
        id:ctrReplay
        anchors.top: index.top
        //        anchors.left: index.left
        //        anchors.leftMargin: (index.width-ctrReplay.width)/2
        visible: false
    }

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
    EarthManager{
        id:earthManager
    }
    NoticManger{
        id:noticManger
    }

    RemoveDialog {
        id: removeDialog_quit
        visible: false
        title:"退出"
        content1: "此操作将退出程序，"
        content2: "确认要退出吗？"
        onYesPutDown: {
            $app.exitApp();
            Qt.quit()
        }
    }



}
