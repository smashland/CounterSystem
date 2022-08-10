import QtQuick 2.0

Item
{
    property var type
    Image
    {
        id: all;
        source: "qrc:/Image/Person/"+type+"/font/font.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
    }

    /// 腹部
    Image
    {
        id: abdome;
        source: "qrc:/Image/Person/"+type+"/font/abdomen.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bAbdomen
    }

    /// 胸部
    Image
    {
        id: breast;
        source: "qrc:/Image/Person/"+type+"/font/breast.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bBreast
    }

    /// 头部
    Image
    {
        id: head;
        source: "qrc:/Image/Person/"+type+"/font/head.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bHead
    }

    /// 左臂
    Image
    {
        id: left_arm;
        source: "qrc:/Image/Person/"+type+"/font/left_arm.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bLeftArm
    }

    /// 右臂
    Image
    {
        id: right_arm;
        source: "qrc:/Image/Person/"+type+"/font/right_arm.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bRightArm
    }

    /// 右腿
    Image
    {
        id: right_leg;
        source: "qrc:/Image/Person/"+type+"/font/right_leg.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bRightLeg
    }

    /// 左臂
    Image
    {
        id: left_leg;
        source: "qrc:/Image/Person/"+type+"/font/left_leg.png"
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit
        visible: outData.bLeftLeg
    }
}
