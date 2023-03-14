import QtQuick 2.14
import QtQuick.Controls 2.14
import QtCharts 2.14
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.15

import QtQuick 2.0
import QtCharts 2.3

ChartView {

    property string belongColor
    property int  allBulltes
    property var  hitRate
    property int  bulltes
    //    anchors.fill: parent
    legend.alignment: Qt.AlignBottom	//上图：目前产量 目标产量的位置，这里指下方
    antialiasing: true					//反锯齿
    backgroundColor: "transparent"
    legend.visible: false

    Connections{
        function onHitRate(hitRate,bulltes)
        {
            console.log("onHitRate"+" "+hitRate+" "+bulltes)
            for(var i=0;i<11;i++)
            {
                if(i===hitRate*10)
                {
                    console.log("onHitRate"+" "+i)
                    barSetId.remove(i,4)
//                    barSetId.valuesAdded(i,bulltes)
                }
                barSetId.valuesAdded(i,0)
            }
        }
        target: exerciseResults
    }


    //    legend.alignment:Qt.AlignTop

    //不同的坐标轴需要用不一样的Axis
    BarCategoryAxis {
        id: axisx
        color: "#ffffff"
        labelsFont.pointSize: 13*dpy
        labelsColor: "#ffffff"
        gridVisible: false
        labelsFont.family: "Microsoft YaHei"
        categories: [
            "0","0.1", "0.2","0.3", "0.4","0.5", "0.6","0.7", "0.8","0.9", "1"
        ]
    }
    ValueAxis {
        id: axisy
        min: 0
        max: allBulltes
        tickCount: 6				//上图只是演示这个的功能，并非一般这么写，y轴方向7个指示点
        labelsColor: "#ffffff"
        labelsFont.pointSize: 13*dpy
        //        labelsFont.bold: true
        //        labelFormat: "%d"
        labelsFont.family: "Microsoft YaHei"
        gridVisible: false
    }


    BarSeries {
        id: barSeries
        axisX: axisx
        axisY: axisy
        labelsPosition: AbstractBarSeries.LabelsInsideEnd		//指条形图里面的数字值的位置
        labelsVisible: true										//指条形图里面的数字值是否显示，默认不显示
        //        BarSet {
        //            color: "#00a0fa"
        //            values: [ 0,40,0,0,0,0 ]
        //        }
        BarSet {
            id:barSetId
            color:if(belongColor==="红方")
                  {
                      barSetId.color="#eb5959"
                  }
                  else if(belongColor==="蓝方")
                  {
                      barSetId.color="#00a0fa"
                  }
            values:[0,0,0,0,0,0,0,0,0,0,0] /*$app.allData.hitRateResult // *//*[0,0,0,0,3,0]*/
        }

    }
}
