import QtQuick 2.0
import QtQuick.Controls 2.15


Rectangle {
    id:comboBox
    property alias currentIndex: listviewer.currentIndex  //把currentInedx提出来，方便外部调用
    property alias currentText: currentext.text
    property string currentName: ""       //初始状态下，comboBox显示的内容，看需求自定义
    property int listheight: 100          //listview的长度和listelement的长度
    property int listelementheight: 30
    property var items: [                //listview的代理项目
//        { target: "" }
    ]
    width: 180*dpx;
    height: 25*dpy;
    z: 999
    smooth:true;
    color: "transparent"

    Rectangle {
        id:chosenItem
        color: "#1d4f88"
        border.color: "#3b6daa"
        border.width: 1
        width:parent.width;
        height:34 *dpy;
        smooth:true;

        Text {
            id:currentext
            color:"#ffffff"
            text: comboBox.currentName
            smooth:true
            x: 10 *dpx
            width: 180*dpx
            height: 34 *dpy
            font.pixelSize: 17*dpx
            clip: true
            font.family: "Microsoft YaHei"
            verticalAlignment: Text.AlignVCenter
        }

        //下拉按钮
        Button{
            width: height
            height: parent.height
            anchors.right: parent.right
            background: Rectangle{
                color: "transparent"
            }
            Text {
                id: icon
                text: qsTr("⊽")
                color: "#ffffff"
                anchors.centerIn: parent
                font.pixelSize: 24*dpx
                anchors.right: parent.right
                font.family: "Microsoft YaHei"
                font.bold: true
            }
        }

        MouseArea {
            width: comboBox.width / 18 * 40
            height: comboBox.height / 3
            anchors.bottomMargin: 0
            anchors.fill: parent;
            onClicked: {
                comboBox.state = comboBox.state==="dropDown"?"":"dropDown"  //控制下拉和回收
            }
        }
    }

    Rectangle{
        id:dropDown
        width:comboBox.width;
        height:0;
        clip:true;
        //        radius:4;
        anchors.top: chosenItem.bottom;
        anchors.margins: comboBox.height / 9
        color: "transparent"

        ListView{
            id:listviewer
            height: 210*dpy;
            model: comboBox.items
            currentIndex: 0;
            delegate: Rectangle{
                id: listbg
                width: comboBox.width
                height: comboBox.listelementheight;
//                color: ListView.isCurrentItem ? "black" : "#20252c"  //设置当前选择项高亮
                color:"#ffffff"
                Text {
                    text: modelData.target
                    font.pixelSize: 16*dpx
                    anchors.fill: parent
                    color: "black";
                    elide: Text.ElideRight
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onEntered: {
                        listbg.color="#1d4f88"
                    }
                    onExited: {
                        listbg.color="#ffffff"
                    }

                    onClicked: {
                        comboBox.state = ""
                        currentext.text = modelData.target;
                        listviewer.currentIndex = index;
                    }
                }
            }
        }
        ScrollBar.vertical: ScrollBar {
            id: scrollBar
        }
    }

    //设置下拉动画
    //状态列表
    states: State {
        name: "dropDown";
        PropertyChanges { target: dropDown; height:listviewer.height}
    }
    //转换列表
    transitions: Transition {
        NumberAnimation { target: dropDown; properties: "height"; easing.type: Easing.OutExpo; duration: 1000 }
    }

    onCurrentIndexChanged: {
        listviewer.currentIndex = comboBox.currentIndex
    }
}
