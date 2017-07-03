#include "showwidget.h"
#include<QDebug>
#include <vector>
ShowWidget::ShowWidget(QWidget *parent):QOpenGLWidget(parent)
{

}

void  ShowWidget::setimage(QString name)
{
    image.load(name);
    update();
}

void ShowWidget::getinfo(std::vector<INFO> info)
{

    ob.erase(ob.begin(),ob.end());


    for(int i=0;i<info.size();i++)
    {
        Drawobject node;
        node.type=info.at(i).type;
        if(info.at(i).start.x()<info.at(i).end.x())
        {
        node.start=info.at(i).start;
        node.end=info.at(i).end;
        }else
        {
            node.start=info.at(i).end;
            node.end=info.at(i).start;
        }
        ob.push_back(node);
    }

    update();
}

//void ShowWidget::resizeEvent(QResizeEvent *event)
//{
//    rect.setHeight(this->height());
//    rect.setWidth(this->width());
//    update();

//}


void ShowWidget::paintEvent(QPaintEvent *event)
{
    QOpenGLWidget::paintEvent(event);
    if(!image.isNull())
    {
        qDebug()<<"paintEvent:"<<ob.size();

        if(ob.size()!=0)
        {
            painter.begin(&image);
            painter.setPen(QPen(Qt::red));
            for(int i=0;i<ob.size();i++)
        {
            painter.drawText(ob.at(i).start,"("+QString::number(i,10)+")"+ob.at(i).type);
            painter.drawRect(QRect(ob.at(i).start,ob.at(i).end));
        }
            painter.end();
        }
    painter.begin(this);
    QRect rect(0,0,image.width()/1.1,image.height()/1.1);  //创建绘图区域
    qDebug()<<rect.width()<<":"<<rect.height();
    painter.drawImage(rect,image);
    //painter.drawImage(0,0,image);
    painter.end();
    }   
}
