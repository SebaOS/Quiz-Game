#include "start.h"
#include "ui_start.h"
#include <QPixmap>
#include "mainwindow.h"
#include <QWidget>
#include <QMessageBox>

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/MojePliki/logoquiz.png"));
    //wstawienie głównego loga
    QPixmap pic(":/MojePliki/logoquiz.png");
    ui->startlogo->setScaledContents(true);
    ui->startlogo->setPixmap(pic);
    connect(&mainwindow,SIGNAL(showStart()),this,SLOT(show()));
    opcje(true,false);

}

Start::~Start()
{
    delete ui;
}

void Start::opcje(int a, int b)
{
    ui->pushButton_3->setVisible(a);
    ui->pushButton_tool->setVisible(a);
    ui->pushButton->setVisible(b);
    ui->pushButton_2->setVisible(b);
    ui->label_color->setVisible(b);
    ui->label_music->setVisible(b);
    ui->label_sound->setVisible(b);
    ui->pushButton_4->setVisible(b);

}

void Start::on_pushButton_clicked()
{
    QPixmap logo(":/MojePliki/logoquiz.png");  //Przycisk Hot
    ui->startlogo->setScaledContents(true);
    ui->startlogo->setPixmap(logo);
    mainwindow.ustaw_motyw(logo);
    mainwindow.ustaw_styl(0);
    mainwindow.ustaw_pole();
}

void Start::on_pushButton_2_clicked()
{
    QPixmap logo(":/MojePliki/logoquiz_2.png");
    ui->startlogo->setScaledContents(true);
    ui->startlogo->setPixmap(logo);
    mainwindow.ustaw_motyw(logo);
    mainwindow.ustaw_styl(1);
    mainwindow.ustaw_pole();
}

void Start::on_pushButton_3_clicked()
{
    if(mainwindow.wczytanie==false)
    {
    mainwindow.wczytaj_pytania();
    mainwindow.czas_start();
    if(mainwindow.wczytanie==true)
    {
        mainwindow.show();
        this->hide();
    }
    }
    else
    {
        mainwindow.zadaj_pytania();
        mainwindow.show();
        this->hide();
        mainwindow.t.start();
    }

}




void Start::on_pushButton_tool_clicked()
{
    opcje(false,true);
}

void Start::on_pushButton_4_clicked()
{
    opcje(true,false);
}
