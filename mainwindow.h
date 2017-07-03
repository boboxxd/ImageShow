#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"
#include <QButtonGroup>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Read(QString name);
    void texteditshow(std::vector<INFO>);
public slots:
    void onopendirbtn();
    void onopenbtn();
    void onpriviousbtn();
    void onnextbtn();
    void oncreatexmlbtn();
    void onradioClicked(int);

signals:
    void sendtext(QString txt);
    void sendinfo(std::vector<INFO> info);

private:
    Ui::MainWindow *ui;
    int type;  //0:安全帽 1：危险车辆
    QString root;
    QString currentpath;
    //QStringList list;//路径下
    int count;//路径下的图片数
    int index=0;//图片序号
    std::vector<INFO> v_info;
    QButtonGroup buttongroup;
};

#endif // MAINWINDOW_H
