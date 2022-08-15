import QtQuick 2.0
import QtQuick.Controls 2.14
import QtCharts 2.14
import QtQuick.Layouts 1.14

GroupBox
{
    property var hurtData
    property var deathData
    property var okData

    Layout.preferredWidth:380
    Layout.preferredHeight:360

//    ColumnLayout
//    {
//        ComboBox
//        {
//            id:selecetShowType
//            model: [qsTr("伤亡情况"), qsTr("弹药消耗情况"), qsTr("折线图")]
//        }

        ChartView
        {
            id:showSelecetType
            theme: ChartView.ChartThemeBlueIcy
            Layout.preferredWidth:360
            Layout.preferredHeight:280
            antialiasing: true

            /// 伤亡情况
            PieSeries
            {
                id: pieSeries1
                visible: selecetShowType.currentIndex === 0 ? true : false
                PieSlice { label: qsTr("受伤"); value: hurtData ;labelVisible: true}
                PieSlice { label: qsTr("死亡"); value: deathData ;labelVisible: true}
                PieSlice { label: qsTr("完好"); value: okData ;labelVisible: true}
            }

            /// 弹药消耗情况
//            BarSeries
//            {
//                id: mySeries
//                visible:selecetShowType.currentIndex === 1 ? true : false
//                axisX: ValueAxis{}
//                axisY: ValueAxis{}
//                BarSet { label: qsTr("弹药消耗"); values: [200, 500] }
//                BarSet { label: qsTr("命中率"); values: [0.9,0.1] }

//                onVisibleChanged:
//                {
//                    axisX.visible = mySeries.visible
//                    axisY.visible = mySeries.visible
//                }
//            }

//            /// 子弹数
//            LineSeries
//            {
//                id:line
//                name: qsTr("子弹数")
//                visible:selecetShowType.currentIndex === 2 ? true : false

//                axisY: ValueAxis{}
//                axisX: ValueAxis{}
//                XYPoint { x: 0; y: 0 }
//                XYPoint { x: 1.1; y: 2.1 }
//                XYPoint { x: 1.9; y: 3.3 }
//                XYPoint { x: 2.1; y: 2.1 }
//                XYPoint { x: 2.9; y: 4.9 }
//                XYPoint { x: 3.4; y: 3.0 }
//                XYPoint { x: 4.1; y: 3.3 }
//                onVisibleChanged:
//                {
//                    axisX.visible = line.visible
//                    axisY.visible = line.visible
//                }
//            }
//        }

        Component.onCompleted:
        {
            selecetShowType.currentIndex = 0;
        }
    }
}

