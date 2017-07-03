#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H
#include <QOpenGLWidget>
#include "common.h"
#include <QPainter>
struct Drawobject
{
    QString type;
    QPoint start;
    QPoint end;
};

class ShowWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent);
    void paintEvent(QPaintEvent *event);
//    void resizeEvent(QResizeEvent *event);
public slots:
    void  setimage(QString name);
    void getinfo(std::vector<INFO> info);
private:
    QPainter painter;
    QImage image;
    QString imagename;
    int m_width;
    int m_height;
    QRect rect;
public:
    std::vector<Drawobject> ob;

};

#endif // SHOWWIDGET_H
