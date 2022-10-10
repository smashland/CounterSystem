import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

ListView {
    id: listView
    x: 90 *dpx
    width: 985*dpx
    height: 335 *dpy
    header: headerView
    clip: true
    focus: true
    ScrollBar.vertical: ScrollBar {
        id: scrollBar
    }
    Component {
        id: headerView
        Item {
            width: parent.width
            height: 40 *dpy
            Rectangle {
                anchors.fill: parent
                color: "#2D5689"
            }
            Row {
                spacing: 56 *dpx
                x: 25 *dpx
                height: 40 *dpy
                TextListItem {
                    text: "设备编号"
                    widthTitle: 70 *dpx
                    heightTitle: 40 *dpy
                }
                TextListItem {
                    text: "人员姓名"
                    widthTitle: 80 *dpx
                    heightTitle: 40 *dpy
                }
                TextListItem {
                    text: "人员职务"
                    widthTitle: 110 *dpx
                    heightTitle: 40 *dpy
                }
                TextListItem {
                    text: "红蓝方"
                    widthTitle: 80 *dpx
                    heightTitle: 40 *dpy
                }
                TextListItem {
                    text: "是否是人质"
                    widthTitle: 138 *dpx
                    heightTitle: 40 *dpy
                }
                TextListItem {
                    text: "操作"
                    widthTitle: 180 *dpx
                    heightTitle: 40 *dpy
                }
            }
        }
    }
}
