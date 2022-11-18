import QtQuick 2.14
import QtQuick.Controls 2.14
import QtCharts 2.14
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.15

ChartView {
    id:pie
    property var hurtData
    property var deathData
    property var okData
    property var flagData

    property int zongshu: okData+hurtData+deathData
    property string percentageOk: okData/zongshu *100 + "%"
    property string percentageHurt: hurtData/zongshu *100 + "%"
    property string percentageDeath: deathData/zongshu *100 + "%"
    width: 310*dpy
    height: 310*dpy
    anchors.fill: parent
    legend.visible: false
    animationOptions: ChartView.AllAnimations
    backgroundColor: "transparent"
    legend.alignment:Qt.AlignTop
    antialiasing:false
    PieSeries {
        holeSize:0.58
        PieSlice {
            id: lianghao
            label: qsTr("良好 "/*+value*/ + percentageOk);
            labelVisible:value?true:false;
            value:okData;
            labelColor:"#ffffff";
            color: "#4169E1";
            borderColor: "#4169E1";
            labelArmLengthFactor: 0.35;
        }
        PieSlice {
            label: qsTr("受伤 "/*+value*/ + percentageHurt);
            labelVisible:value?true:false;
            value:hurtData;
            labelColor:"#ffffff";
            color: "#00A1F8";
            borderColor: "#00A1F8";
            labelArmLengthFactor: 0.35;
        }
        PieSlice {
            label: qsTr("死亡 "/*+value*/ + percentageDeath);
            labelVisible:value?true:false;
            value:deathData;
            labelColor:"#ffffff";
            color: "#2E85A8";
            borderColor: "#2E85A8";
            labelArmLengthFactor: 0.35;
        }
    }

}

