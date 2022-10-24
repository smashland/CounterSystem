import QtQuick 2.14
import QtQuick.Controls 2.14
import QtCharts 2.14
import QtQuick.Layouts 1.14

ChartView
{
    property var hurtData
    property var deathData
    property var okData
    property var flagData
    width: 310*dpy
    height: 310*dpy
    anchors.fill: parent
    legend.visible: false
    antialiasing: true
    animationOptions: ChartView.AllAnimations
    backgroundColor: "transparent"

    /// 伤亡情况
    PieSeries
    {
        id: pieSeries1
//        visible: okData && hurtData && deathData > 0 ? true : false
        PieSlice { label: qsTr("良好 "/*+value*/);labelVisible:value?true:false; value:okData ;labelColor:"#7EC8E4";color: "#7EC8E4"; borderColor: "#7EC8E4"}
        PieSlice { label: qsTr("受伤 "/*+value*/);labelVisible:value?true:false; value:hurtData ;labelColor:"#00A1F8" ;color: "#00A1F8";borderColor: "#00A1F8"}
        PieSlice { label: qsTr("死亡 "/*+value*/);labelVisible:value?true:false; value:deathData ;labelColor:"#2E85A8";color: "#2E85A8";borderColor: "#2E85A8"}
    }
}

