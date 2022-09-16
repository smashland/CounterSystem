import QtQuick 2.0

Image
{
    id:wuqiIcon
    property var bConnected:true
    property alias wuqiImage: wuqiIcon.source
    width: 25*dpy
    height: 25*dpy
    visible: bConnected
}
