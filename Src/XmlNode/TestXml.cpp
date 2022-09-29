#include <QCoreApplication>
#include <QtXml> //也可以include <QDomDocument>
#include "TestXml.h"
#include <QApplication>

void TestXml::writeXml(QString xmlPath)
{
    xmlPath = QApplication::applicationDirPath() + "/Data/Earth/Geocentric.earth";
    QFile file(xmlPath); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return;
    QDomDocument doc;
//    QDomProcessingInstruction instruction; //添加xml说明
//    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
//    doc.appendChild(instruction);

//    QDomElement root=doc.createElement("bookstore"); //创建根元素
//    doc.appendChild(root); //添加根元素

    QDomElement bookElement=doc.createElement("tmsimage"); //一级子元素
    bookElement.setAttribute("category","CHILDREN"); //方式一：创建属性  其中键值对的值可以是各种类型

    QDomElement titleElement=doc.createElement("url"); //二级子元素
    titleElement.appendChild(doc.createTextNode("Harry Potter")); //为titleElement元素增加文本

    /*QDomElement yearElement=doc.createElement("year"); //二级子元素
    yearElement.appendChild(doc.createTextNode("2005")); //为yearElement元素增加文本*/

    bookElement.appendChild(titleElement); //增加子元素
//    bookElement.appendChild(yearElement);

//    root.appendChild(bookElement);

    QTextStream out_stream(&file); //输出到文件
    doc.save(out_stream,2); //缩进4格
    file.close();
}

