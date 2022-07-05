import QtQuick 2.14

Canvas
{
    id:canvas
    width: 310
    height: 310
    onPaint:
    {
        function PieChart() {
            this.ctx = getContext("2d");
            var w = canvas.width;
            var h = canvas.height;
            this.ctx.clearRect(0, 0, w, h);
            //获取画布的中心
            this.x0 = this.ctx.canvas.width / 2 ;
            this.y0 = this.ctx.canvas.height / 2+30;
            //获取半径
            this.radius = 70;
            //标题伸出去的距离
            this.outLine = 25;

            this.ctx.font = " 17px sans-serif";

        }

        //初始化饼状图
        PieChart.prototype.init = function () {
            this.drawPie();
        }
        //添加饼图
        PieChart.prototype.drawPie = function () {
            //1、将数据转为弧度
            var angleList = this.drawAngle();
            var start = 0;//起始弧度
            angleList.forEach(function (item, i) {
                var end = item.angle + start;
                this.ctx.beginPath();
                this.ctx.moveTo(this.x0, this.y0);
                this.ctx.arc(this.x0, this.y0, this.radius, start, end);
                this.ctx.fillStyle = item.color;
                this.ctx.fill();

                //调用标的方法
                this.drawTitle(start, item, this.ctx.fillStyle);

                //调用画小矩形
                this.drawInfo(i,item.title,this.ctx.fillStyle);

                //记录上一个结束的弧度
                start = end;
            }.bind(this));
        }
        //添加标题
        PieChart.prototype.drawTitle = function (start, item, color) {
            //斜边的长度
            var edge = this.radius + this.outLine;
            //x轴方向的直角边
            var edgeX = edge * Math.cos(start + item.angle / 2);
            //y轴方向的直角边
            var edgeY = edge * Math.sin(start + item.angle / 2);
            //伸出去的横纵坐标
            var outX = this.x0 + edgeX;
            var outY = this.y0 + edgeY;
            this.ctx.beginPath();
            this.ctx.moveTo(this.x0, this.y0);
            this.ctx.lineTo(outX, outY);
            this.ctx.strokeStyle = color;
            this.ctx.stroke();

//            var baifenbi = Math.round(item.num/zongshu*100) +"%"
            //添加字体
//            var align = outX > this.x0 ? "left" : "right";
//            this.ctx.font = "13px 微软雅黑";
//            this.ctx.textAlign = align;
//            this.ctx.textBaseline = "bottom";
//            this.ctx.fillStyle = color;
//            this.ctx.fillText(item.title, outX, outY);

            //添加文字下面的线
            var textW = this.ctx.measureText(item.title + item.num).width;
            this.ctx.moveTo(outX, outY);
            outX = outX > this.x0 ? outX + textW : outX - textW;
            this.ctx.lineTo(outX, outY);
            this.ctx.stroke();

            //线下的文字
            var align1 = outX > this.x0 ? "left" : "right";
            this.ctx.font = "13px 微软雅黑";
            this.ctx.textAlign = align1;
            this.ctx.textBaseline = "top";
            this.ctx.fillStyle = color;
            outX = outX > this.x0 ? outX - textW/2 : outX + textW/2;
            this.ctx.fillText(item.title + "   " + item.num, outX, outY);
        }
        //添加说明
        PieChart.prototype.drawInfo = function (index,text,color) {
            this.ctx.beginPath();
            //画小矩形
            this.ctx.fillRect(this.spaceX,this.spaceY*index+this.smallH,this.smallW,this.smallH);
            //画文字
            this.ctx.font = "12px 微软雅黑";
            this.ctx.fillStyle = color;
            this.ctx.textAlign="left";
            this.ctx.fillText(text,this.spaceX*2+this.smallW,this.spaceY*index+this.smallH*2);
        }
        //添加转化弧度的方法
        PieChart.prototype.drawAngle = function () {
            //先获取数据的总和
            var total = 0;
            data.forEach(function (item, index) {
                total += item.num;
            });
            //获取每条数据的弧度
            data.forEach(function (item, index) {
                var angle = item.num / total * Math.PI * 2;
                item.angle = angle;
            });
            return data;
        }


        var data = [
                    {title: "良好", num: 2, color:"#7EC8E4"},
                    {title: "死亡", num: 3, color:"#2E85A8"},
                    {title: "受伤", num: 4, color:"#00A1F8"},
                ];

        var pieChart = new PieChart();
        pieChart.init();//初始化

    }
//    onVisibleChanged: {
//        if(visible)
//        {
//            requestPaint();
//        }
//    }
}
