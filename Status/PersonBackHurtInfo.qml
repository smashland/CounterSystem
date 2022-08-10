import QtQuick 2.0

Item
{
    property var type

//    Image
//    {
//        id: all;
//        source: "qrc:/Image/Person/"+type+"/back/back.png"
//        anchors.fill: parent;
//        fillMode: Image.PreserveAspectFit
//    }
    Rectangle {
        x: 50 *dpx
        y: 106*dpy
        color: "transparent"
        width: 188*dpx
        height: 230*dpx
        Image {
            id:all
            anchors.fill:parent
//            fillMode: Image.PreserveAspectFit
            source: "qrc:/Image/soldiers.png"
        }
    }

    /// 背部
    Image
    {
        id: center;
        source: "qrc:/Image/Person/"+type+"/back/center.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bCenter
    }

    /// 头部
    Image
    {
        id: head;
        source: "qrc:/Image/Person/"+type+"/back/head.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bHead
    }

    /// 左臂
    Image
    {
        id: left_arm;
        source: "qrc:/Image/Person/"+type+"/back/left_arm.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bLeftArm
    }

    /// 右臂
    Image
    {
        id: right_arm;
        source: "qrc:/Image/Person/"+type+"/back/right_arm.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bRightArm
    }

    /// 右腿
    Image
    {
        id: right_leg;
        source: "qrc:/Image/Person/"+type+"/back/right_leg.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bRightLeg
    }

    /// 左臂
    Image
    {
        id: left_leg;
        source: "qrc:/Image/Person/"+type+"/back/left_leg.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bLeftLeg
    }
}
