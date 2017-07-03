#include "readtext.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
using namespace std;
ReadText::ReadText(const  QString &filename)
{
    QFile f(filename);
    if(f.size()==0)
        return;
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    int i=0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();        
        QStringList list;

        list=lineStr.split(" ");
        //start.point
        lineStr=list.at(2);
        INFO *node=new INFO;
        node->start.setX(QString(lineStr.split(":").at(1)).toInt());
        node->start.setY(QString(list.at(3)).toInt());
        //end.point
        node->end.setX(QString(list.at(4)).toInt());
        node->end.setY(QString(list.at(5)).toInt());
        //文件名
        node->filename=QDir(filename).absolutePath();
        //类型
        node->type=list.at(1);
        //得分
        lineStr=list.at(6);
        node->score=lineStr.split(":").at(1);
        info.insert(i,*node);
        i++;
    }

}

void ReadText::Set(const  QString &filename)
{
    QFile f(filename);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    int i=0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list;
        list=lineStr.split(" ");
        //start.point
        lineStr=list.at(2);
        INFO *node=new INFO;
        node->start.setX(QString(lineStr.split(":").at(1)).toInt());
        node->start.setY(QString(list.at(3)).toInt());
        //end.point
        node->end.setX(QString(list.at(4)).toInt());
        node->end.setY(QString(list.at(5)).toInt());
        //文件名
        node->filename=QDir(filename).absolutePath();
        //类型
        node->type=list.at(1);
        //得分
        lineStr=list.at(6);
        node->score=lineStr.split(":").at(1);
        info.insert(i,*node);
        i++;
    }
}
QList<INFO> ReadText::GetInfo() const
{
    return info;
}
