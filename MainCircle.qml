import QtQuick 2.14

// ？
Canvas
{
    signal rightClick()
    signal leftClick()

    id: canvas
    antialiasing: true
    property real centerWidth: width / 2.0
    property real centerHeight: height / 2.0
    property real rLineWidth: Math.min(canvas.width, canvas.height)*0.095
    property real radius: Math.min(canvas.width, canvas.height)*0.4
    property var nodes:[]
    property real startAngle: -0.5*Math.PI
    property real endAngle: 1.5*Math.PI
    property real circlAngle: endAngle-startAngle
    property real fontSize: 30
    onPaint:
    {
        var ctx = getContext("2d");
        ctx.save();

        ctx.font = "bold "+ fontSize + "px sans-serif"
        ctx.textAlign = "center"
        ctx.textBaseline="middle"
        ctx.clearRect(0, 0, canvas.width, canvas.height);


        ctx.lineWidth = rLineWidth;
        for(var index =0; index < nodes.length; ++index)
        {

            var tmpRadius = radius-index*rLineWidth*1.8;
            var node = nodes[index];

            /// 绘制底图
            ctx.beginPath();
            ctx.strokeStyle = $app.settings.type2BackColor(node.type);
            ctx.arc(centerWidth,
                    centerHeight,
                    tmpRadius,
                    startAngle,
                    endAngle);
            ctx.stroke();


            if(0 !== node.liveRatio)
            {
                /// 绘制活着的 第一个原点
                ctx.beginPath();
                ctx.fillStyle = $app.settings.type2Color(node.type);
                ctx.arc(centerWidth + tmpRadius*Math.cos(startAngle),
                        centerHeight+ tmpRadius*Math.sin(startAngle),
                        0.5*rLineWidth,0,circlAngle);
                ctx.fill();


                /// 绘制区域
                ctx.beginPath();
                ctx.strokeStyle = $app.settings.type2Color(node.type);
                ctx.arc(centerWidth,
                        centerHeight,
                        tmpRadius,
                        startAngle,
                        node.liveRatio*circlAngle+startAngle);
                ctx.stroke();

                /// 绘制最后一个点
                ctx.beginPath();
                ctx.arc(centerWidth + tmpRadius*Math.cos(node.liveRatio*circlAngle+startAngle),
                        centerHeight+ tmpRadius*Math.sin(node.liveRatio*circlAngle+startAngle),
                        rLineWidth*0.5,0,circlAngle);
                ctx.fill();
            }


            if(0 !== node.hurtRatio)
            {
                /// 绘制受伤的 第一个原点
                ctx.beginPath();
                ctx.fillStyle = "#FFFFFF00";
                ctx.arc(centerWidth + tmpRadius*Math.cos((node.liveRatio-node.hurtRatio)*circlAngle+startAngle),
                        centerHeight+ tmpRadius*Math.sin((node.liveRatio-node.hurtRatio)*circlAngle+startAngle),
                        0.5*rLineWidth,0,circlAngle);
                ctx.fill();


                /// 绘制区域
                ctx.beginPath();
                ctx.strokeStyle = "#FFFFFF00";
                ctx.arc(centerWidth,
                        centerHeight,
                        tmpRadius,
                        (node.liveRatio-node.hurtRatio)*circlAngle+startAngle,
                        node.liveRatio*circlAngle+startAngle);
                ctx.stroke();

                /// 绘制最后一个点
                ctx.beginPath();

                ctx.arc(centerWidth + tmpRadius*Math.cos(node.liveRatio*circlAngle+startAngle),
                        centerHeight+ tmpRadius*Math.sin(node.liveRatio*circlAngle+startAngle),
                        rLineWidth*0.5,0,circlAngle);
                ctx.fill();
            }

        }

        /// 设置字体填充颜色
        ctx.fillStyle="#ffffffff"

        ctx.beginPath();
        ctx.fillText($app.allData.allLiveNumber,centerWidth,centerHeight)
        ctx.stroke();

        ctx.restore();

    }

    MouseArea
    {
        id:mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton |Qt.MidButton
        onClicked:
        {
            switch(mouse.button)
            {
            case Qt.RightButton:
                rightClick();
                break;
            case Qt.LeftButton:
                leftClick();
                mouse.accepted=true;
                break;
            }
        }

        onDoubleClicked:
        {
        }
    }
    Component.onCompleted:
    {
        var node = {type:"蓝方",liveRatio:1,hurtRatio:0}
        nodes.push(node);
        node = {type:"红方",liveRatio:1,hurtRatio:0}
        nodes.push(node);
        canvas.requestPaint();
    }

    Connections
    {
        target: $app.allData
        function onUpdateGroup(groupStatus)
        {
            for(var index=0;index<nodes.length;++index)
            {
                if(groupStatus.type === nodes[index].type)
                {
                    if(groupStatus.liveRatio === nodes[index].liveRatio
                            && groupStatus.hurtRatio === nodes[index].hurtRatio)
                    {
                        break;
                    }

                    nodes[index].liveRatio = groupStatus.liveRatio;
                    nodes[index].hurtRatio = groupStatus.hurtRatio;
                    canvas.requestPaint();
                    break;
                }
            }
        }
    }

    Connections
    {
        target: $app.settings
        function onStartStatusChanged(bIsStart)
        {
            if(bIsStart)
            {
                for(var index=0;index<nodes.length;++index)
                {
                    nodes[index].liveRatio = 1.;
                    nodes[index].hurtRatio = 0.;
                    canvas.requestPaint();
                }
            }
        }
    }
}
