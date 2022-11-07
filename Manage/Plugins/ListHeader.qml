import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

Component {
    id: headerView
    Item {
        width: parent.width
        height: 30 *dpy
        Rectangle {
            anchors.fill: parent
            color: "#2D5689"
        }
        TextListItem {
            text: "序号"
            width: 100 *dpx
            height: 30 *dpy
        }
        TextListItem {
            x: 170 *dpx
            text: "方案名称"
            width: 200 *dpx
            height: 30 *dpy
        }
        TextListItem {
            x: 572 *dpx
            text: "操作"
            width: 370 *dpx
            height: 30 *dpy
        }
    }
}
