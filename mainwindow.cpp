#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <QDebug>
#include <QFileDialog>
#include <vector>
#include "readtext.h"
#include "xmlcreator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentpath="/";

    buttongroup.addButton(ui->dangerousradio,0);
    buttongroup.addButton(ui->helmetradio,1);
    ui->dangerousradio->setChecked(true);
    type=0;
    buttongroup.setExclusive(true);

    connect(&buttongroup, SIGNAL(buttonClicked (int)), this, SLOT(onradioClicked(int)) );
    connect(this,SIGNAL(sendinfo(std::vector<INFO>)),ui->openGLWidget,SLOT(getinfo(std::vector<INFO>)));
}

void MainWindow::onradioClicked(int id)
{
    type=id;   
}

void MainWindow::Read(QString name)
{
    v_info.clear();
    static VehicleMap map_vehicle;
    map_vehicle.insert("1",truck_crane);
    map_vehicle.insert("2",excavator);
    map_vehicle.insert("3",cement_pump_truck);
    map_vehicle.insert("4",bulldozer);
    map_vehicle.insert("5",truck_crane_working_arm);
    map_vehicle.insert("6",tower_crane_arm);

    static HelmetMap  map_helmet;
    map_helmet.insert("1",humen);
    map_helmet.insert("2",red_waistcoat);
    map_helmet.insert("3",helmet_red);
    map_helmet.insert("4",helmet_blue);
    map_helmet.insert("5",helmet_yellow);
    map_helmet.insert("6",helmet_white);

    ReadText  TXT(name);
    //std::vector<INFO> v_info;
    for(int i=0;i<TXT.GetInfo().count();i++)
    {
        INFO node;
        node.filename=TXT.GetInfo().at(i).filename;

        if(type==0)
            node.type=myprint(map_vehicle,TXT.GetInfo().at(i).type);
        else
        {
            node.type=myprint(map_helmet,TXT.GetInfo().at(i).type);
        }

        node.start=TXT.GetInfo().at(i).start;
        node.end=TXT.GetInfo().at(i).end;
        node.score=TXT.GetInfo().at(i).score;
        v_info.push_back(node);
    }
    texteditshow(v_info);
    emit sendinfo(v_info);

}


void MainWindow::onopendirbtn()
{
    qDebug()<<"onopendirbtn()";

    ui->textEdit->clear();
    root=QFileDialog::getExistingDirectory(this,"选择路径",currentpath);
    if(!root.isEmpty())
    {
        currentpath=root;
        index=0;
        QDir dir(root);
        QStringList filter;
        filter<<"*.jpg"<<"*.JPG"<<"*.jpeg"<<"*.JPEG";
        dir.setNameFilters(filter);
        count=dir.entryList().count();

        if(QFile(root+"/"+dir.entryList().at(index)+".txt").exists())
        {
            Read(root+"/"+dir.entryList().at(index)+".txt");
        }else
        {
            ui->textEdit->setText("文件： "+root+"/"+dir.entryList().at(index)+".txt"+"不存在!");
        }
        emit sendtext(root+"/"+dir.entryList().at(index));
    }
}

void MainWindow::onopenbtn()
{

    qDebug()<<"onopenbtn()";
    ui->textEdit->clear();
    QString filename=QFileDialog::getOpenFileName(this,"请选择打开图片",currentpath,"*jpg *JPG *jpeg *JPEG");
    QFileInfo fileinfo(filename);
    QStringList filter;
    filter<<"*.jpg"<<"*.JPG"<<"*.jpeg"<<"*.JPEG";
    root=fileinfo.absoluteDir().absolutePath();
    currentpath=fileinfo.absoluteDir().absolutePath();

    if(!filename.isEmpty())
    {
        emit sendtext(filename);
        QString txtname=filename+".txt";
        if(QFile(txtname).exists())
        {
            Read(txtname);
        }else
        {
            ui->textEdit->setText("文件： "+txtname+"不存在!");
        }
    }
}

void MainWindow::onpriviousbtn()
{  
    if(!root.isEmpty())
    {
    qDebug()<<"onpriviousbtn()";
    ui->textEdit->clear();
    QDir dir(root);
    QStringList filter;
    filter<<"*.jpg"<<"*.JPG"<<"*.jpeg"<<"*.JPEG";
    dir.setNameFilters(filter);
    count=dir.entryList().count();
    if(index>0)
    --index;
    Read(root+"/"+dir.entryList().at(index)+".txt");
    if(!QFile(root+"/"+dir.entryList().at(index)+".txt").exists())
    {
        ui->textEdit->setText("文件： "+root+"/"+dir.entryList().at(index)+".txt"+"不存在!");
    }
    emit sendtext(root+"/"+dir.entryList().at(index));
    }
}

void MainWindow::onnextbtn()
{
    if(!root.isEmpty())
    {
    qDebug()<<"onnextbtn()";
    ui->textEdit->clear();
    QDir dir(root);
    QStringList filter;
    filter<<"*.jpg"<<"*.JPG"<<"*.jpeg"<<"*.JPEG";
    dir.setNameFilters(filter);
    count=dir.entryList().count();
    if(index<count-1)
    ++index;
    Read(root+"/"+dir.entryList().at(index)+".txt");
    if(!QFile(root+"/"+dir.entryList().at(index)+".txt").exists())
    {
         ui->textEdit->setText("文件： "+root+"/"+dir.entryList().at(index)+".txt"+"不存在!");
    }
        emit sendtext(root+"/"+dir.entryList().at(index));
    }
}



void MainWindow::texteditshow(std::vector<INFO> info)
{
    for(int i=0;i<info.size();i++)
    {
        ui->textEdit->append("------文件名------");
        ui->textEdit->append(info.at(i).filename);
        ui->textEdit->append("\n");
        ui->textEdit->append("----("+QString::number(i,10)+")--报警类别------");
        ui->textEdit->append(info.at(i).type);
        ui->textEdit->append("\n");
        ui->textEdit->append("----("+QString::number(i,10)+")--相似得分------");
        ui->textEdit->append(info.at(i).score);
        ui->textEdit->append("\n");
    }
}



void MainWindow::oncreatexmlbtn()
{    
    qDebug()<<"oncreatexmlbtn()";
    XmlCreator temp;
    temp.set(v_info);
}


MainWindow::~MainWindow()
{
    delete ui;
}
