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

    ColumnLayout
    {

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

        }

        Component.onCompleted:
        {
            selecetShowType.currentIndex = 0;
        }
    }
}
