import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

ListView {
    id: listView
    focus: true
    clip: true
    ScrollBar.vertical: ScrollBar {
        id: scrollBar
    }
}
