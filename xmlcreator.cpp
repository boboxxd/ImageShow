#include "xmlcreator.h"
#include<QtXml>
#include <QTime>

XmlCreator::XmlCreator()
{
    file=new QFile;
}

XmlCreator::~XmlCreator()
{

}

void XmlCreator::set(std::vector<INFO> info)
{
    QDomDocument doc;
   // QDate _date;
    QString name=QFileInfo(info.at(0).filename).canonicalFilePath();
    int index=name.lastIndexOf(".");
    name.truncate(index);

    QDomElement root=doc.createElement(QString("annotation"));
    doc.appendChild(root);
    QDomText text;
    QDomElement date=doc.createElement(QString("date"));
    text=doc.createTextNode(QDate::currentDate().toString ("yyyy.MM.dd ")+QTime::currentTime().toString("hh:mm:s"));
    date.appendChild(text);
    root.appendChild(date);

    QDomElement author=doc.createElement(QString("author"));
    text=doc.createTextNode("ImageShow");
    author.appendChild(text);
    root.appendChild(author);

    QDomElement folder=doc.createElement(QString("folder"));
    text=doc.createTextNode("unknow");
    folder.appendChild(text);
    root.appendChild(folder);

    QDomElement filename=doc.createElement(QString("filename"));
    text=doc.createTextNode(QFileInfo(info.at(0).filename).baseName());
    filename.appendChild(text);
    root.appendChild(filename);

    QDomElement path=doc.createElement(QString("path"));
    text=doc.createTextNode("unknow");
    path.appendChild(text);
    root.appendChild(path);



    QDomElement size=doc.createElement(QString("size"));
        QDomElement width=doc.createElement(QString("width"));
        text=doc.createTextNode(QString::number(QImage(name).width(),10));
        width.appendChild(text);
        size.appendChild(width);
        QDomElement height=doc.createElement(QString("height"));
        text=doc.createTextNode(QString::number(QImage(name).height(),10));
        height.appendChild(text);
        size.appendChild(height);
        QDomElement depth=doc.createElement(QString("depth"));
        text=doc.createTextNode(QString::number(3,10));
        depth.appendChild(text);
        size.appendChild(depth);
    root.appendChild(size);


//****************************************************************************************//

        for(int i=0;i<info.size();i++)
        {
            QDomElement object=doc.createElement(QString("object"));
                QDomElement name=doc.createElement(QString("name"));
                QDomElement bndbox=doc.createElement(QString("bndbox"));
                    QDomElement xmin=doc.createElement(QString("xmin"));
                    QDomElement ymin=doc.createElement(QString("ymin"));
                    QDomElement xmax=doc.createElement(QString("xmax"));
                    QDomElement ymax=doc.createElement(QString("ymax"));

            text=doc.createTextNode(info.at(i).type);
            name.appendChild(text);
            object.appendChild(name);

            text=doc.createTextNode(QString::number(info.at(i).start.x(),10));
            xmin.appendChild(text);
            bndbox.appendChild(xmin);

            text=doc.createTextNode(QString::number(info.at(i).start.y(),10));
            ymin.appendChild(text);
            bndbox.appendChild(ymin);

            text=doc.createTextNode(QString::number(info.at(i).end.x(),10));
            xmax.appendChild(text);
            bndbox.appendChild(xmax);
            text=doc.createTextNode(QString::number(info.at(i).end.y(),10));
            ymax.appendChild(text);
            bndbox.appendChild(ymax);
            object.appendChild(bndbox);
            root.appendChild(object);
        }
    //写入文件

       index=name.lastIndexOf(".");
       name.truncate(index);
       QFile file(name+".xml");
       if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) return ;
       QTextStream out(&file);
       doc.save(out,4);
       file.close();
}

