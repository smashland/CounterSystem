import QtQuick 2.0
import QtQuick.Controls 2.3

Dialog{
    id: dialog
    property int nID: 0
    title: "给"+nID+'号充弹'
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel


    onAccepted:
    {
        var allNum=[8];
        for(var i=0; i<allInfo.count;++i)
        {
            allNum[i] = allInfo.itemAt(i).children[1].text;
        }

        $app.settings.chongDan(nID,allNum);
    }

    Column
    {
        width: 161
        height: 320
        Repeater
        {
            id:allInfo
            model: 5
            Row
            {
                Label
                {
                    text: index
                }

                TextField
                {
                    id:zdshu
                    maximumLength:4
                    placeholderText:'子弹数量'
                    validator: IntValidator
                    {
                        bottom:1
                        top:9999
                    }
                }
            }
        }
    }

}









/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
