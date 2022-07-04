import QtQuick 2.12
import "Common"
import "Login"
import "Exercise"
import "Manage"


Rectangle
{
    id: index
    anchors.fill: parent
    color: "black"


    Information {
        x: 80 *dpx
        y: 80 *dpy
    }
    NavImage {
        anchors.top: parent.top
        anchors.topMargin: 30 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 30 *dpx
    }

    RedInformation {
        anchors.right: parent.right
        anchors.rightMargin: 80*dpx
        anchors.top: parent.top
        anchors.topMargin: 80*dpy
    }
    BlueInformation {
        anchors.right: parent.right
        anchors.rightMargin: 80*dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120*dpy
    }
    Manoeuvre {
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

    Soldier {
        id: soldier
        visible: false
        x: (index.width-soldier.width) / 2
        y: (index.height-soldier.height) / 2
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
        visible: false
        x: (index.width-setloader.width) / 2
        y: (index.height-setloader.height) / 2
    }
    HelpLoader {
        id: helploader
        visible: false
        x: (index.width-helploader.width) / 2
        y: (index.height-helploader.height) / 2
    }
    ScenarioLoader {
        id: scenarioLoader
        visible: false
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

    ScenarioRevise {
        id: scenarioRevise
        visible: false
        x: (index.width-scenarioRevise.width) / 2
        y: (index.height-scenarioRevise.height) / 2
    }

    PlaybackLoader {
        id: playbackLoader
        visible: false
        x: (index.width-playbackLoader.width) / 2
        y: (index.height-playbackLoader.height) / 2
    }
    PlaybackRefresh {
        id: playbackRefresh
        visible: false
        x: (index.width-playbackRefresh.width) / 2
        y: (index.height-playbackRefresh.height) / 2
    }
    ScenarioRemove {
        id: scenarioRemove
        visible: false
        x: (index.width-scenarioRemove.width) / 2
        y: (index.height-scenarioRemove.height) / 2
    }

//        Progressbar {
//            id: progressbar
//            visible: true
//        }
    //    CloseBar {
    //        id: closebar
    //        visible: true
    //    }
    CloseBarFull{
        id: closebarFull
        visible: false
    }
    Kill {
        id: kill
        visible: false
        y: 65 *dpy
        x: 395 *dpx
    }
    KillExpand {
        id: killExpand
        visible: true
        y: 65 *dpy
        x: 395 *dpx
    }



}
