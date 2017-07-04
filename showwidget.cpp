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
 //#########################################################################
        qreal ratex=qreal(this->width())/qreal(image.width());
        qreal ratey=qreal(this->height())/qreal(image.height());
        qreal rate=qreal(image.width())/qreal(image.height());
        qDebug()<<ratex<<":"<<ratey;

        cv::Mat mat=QImage2cvMat(image);
        cv::Mat dst;
        cv::resize(mat, dst, cv::Size(qreal(image.width()*ratex), qreal(image.width()*ratey)/rate),cv::INTER_LINEAR);
        QImage temp=cvMat2QImage(dst);
        painter.begin(this);
        qDebug()<<this->width()<<"*"<<this->height();
        qDebug()<<temp.width()<<":"<<temp.height();
        painter.drawImage(0,0,temp);
        painter.end();
    }   
}
