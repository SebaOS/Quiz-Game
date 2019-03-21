#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPixmap>
#include <QMessageBox>
#include <fstream>
#include <QTimer>
#include <QProgressBar>


class Pytanie;

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //USTAWIENIA DOMYŚLNE
    QPixmap logo(":/MojePliki/logoquiz.png");
    ui->label_pic->setScaledContents(true);
    ui->label_pic->setPixmap(logo);
    style=0;
    ui->pushButton_back->setIcon(QIcon(":/MojePliki/back.png"));
    numer_pytania=0;


}

MainWindow::~MainWindow()
{
    delete ui;
}


                                                //***FUNKCJE***//

void MainWindow::ustaw_motyw(QPixmap p)
{
    ui->label_pic->setScaledContents(true);
    ui->label_pic->setPixmap(p);

}

void MainWindow::ustaw_styl(int s){style=s;}

void MainWindow::ustaw_pole()
{
    if(style==0)
    {
        ui->polepytanie->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.136364, x2:1, y2:0.602273, stop:0.0207254 rgba(255, 180, 0, 255), stop:1 rgba(187, 22, 77, 255));"
                                   "color: white;" "font: 15pt;" "font-weight: bold;" "border-radius: 10px;");
    }
    else
    {
        ui->polepytanie->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.767, stop:0 rgba(153, 255, 255, 255), stop:1 rgba(153, 255, 131, 255));"
                                     "color: rgb(51, 51, 51);" "font: 15pt;" "font-weight: bold;" "border-radius: 10px;");
    }
}

void MainWindow::wczytaj_pytania()
{

    ifstream plik;
    plik.open( "/Users/sebastianoskiewicz/Desktop/Quiz/pytania.txt");
    if( !plik.good() )
    {
        QMessageBox msgBox;
              msgBox.setWindowTitle("Uwaga!");
              msgBox.setIcon(QMessageBox::Critical);
              msgBox.setText("Nie udało wczytać się pytań");
              msgBox.setStandardButtons(QMessageBox::Cancel);
              msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }
    else
    {

        wczytanie=true;
        while(!plik.eof())
        {
            string linie[6];
            int i=0;
            while(getline(plik, linia))
            {
                linie[i++]=linia;
                if(i==6)
                    break;
            }
            if(i==6)
                pytania.push_back(Pytanie(linie[0].c_str(),linie[1].c_str(),linie[2].c_str(),linie[3].c_str(),linie[4].c_str(),linie[5].c_str()));
        }
        zadaj_pytania();
    }
    plik.close();
}

void MainWindow::zadaj_pytania()
{
    ui->polepytanie->setText(pytania[numer_pytania].pytanie);
    ui->pushButton->setText(pytania[numer_pytania].a);
    ui->pushButton_2->setText(pytania[numer_pytania].b);
    ui->pushButton_3->setText(pytania[numer_pytania].c);
    ui->pushButton_4->setText(pytania[numer_pytania].d);
}

void MainWindow::zmien_styl_cieply(QPushButton *p)
{
    p->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.136364, x2:1, y2:0.602273, stop:0.0207254 rgba(255, 180, 0, 255), stop:1 rgba(187, 22, 77, 255));"
                     "color: white;"
                     "border-radius: 10px;");
}

void MainWindow::zmien_styl_zimny(QPushButton *p)
{
    p->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.767, stop:0 rgba(153, 255, 255, 255), stop:1 rgba(153, 255, 131, 255));"
                                      "color: rgb(51, 51, 51);"
                                      "border-radius: 10px;");
}

void MainWindow::wroc_styl(QPushButton *w)
{
    w->setStyleSheet("border-radius: 10px;" "color: white;"
                     "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(52, 52, 52, 255), stop:1 rgba(85, 85, 85, 255));");
    w->setDisabled(false);
}

void MainWindow::czas_start()
{
    t.setTimerType(Qt::PreciseTimer);
    connect(&t,SIGNAL(timeout()),this,SLOT(progres()));
    t.start(4);

}

void MainWindow::progres()
{
    int progress=ui->progressBar->value();
    progress++;
    ui->progressBar->setValue(progress);
    ui->progressBar->repaint();
}

void MainWindow::przejscie()
{  
    if(numer_pytania+1<pytania.size()){
    numer_pytania=numer_pytania+1;
    zadaj_pytania();
    wroc_styl(ui->pushButton);
    wroc_styl(ui->pushButton_2);
    wroc_styl(ui->pushButton_3);
    wroc_styl(ui->pushButton_4);
    ui->progressBar->setValue(0);
    t.start();

    }
    else
    koniec_gry();
}

void MainWindow::przejdz_dalej()
{
    p.singleShot(1000,this,SLOT(przejscie()));
}

void MainWindow::koniec_gry()
{

przyciski_odp(false);
ui->label_smile->setVisible(true);
ui->polepytanie->setText(QString("Uzyskałeś/aś: %1 pkt na %2 możliwych").arg(punkty).arg(pytania.size()));
if(pytania.size()/2<=punkty)
{
    QPixmap smile_h(":/MojePliki/happy.png");

    ui->label_smile->setScaledContents(true);
    ui->label_smile->setPixmap(smile_h);
}
else
{
    QPixmap smile_s(":/MojePliki/sad.png");
    ui->label_smile->setScaledContents(true);
    ui->label_smile->setPixmap(smile_s);
}
}

void MainWindow::przyciski_odp(int in)
{
    ui->pushButton->setVisible(in);
    ui->pushButton_2->setVisible(in);
    ui->pushButton_3->setVisible(in);
    ui->pushButton_4->setVisible(in);
    ui->progressBar->setVisible(in);
}


                                                //***ELEMENTY UI***//

void MainWindow::on_pushButton_clicked()
{
    if(style==0)
        zmien_styl_cieply(ui->pushButton);
    else
        zmien_styl_zimny(ui->pushButton);

    if(QString(pytania[numer_pytania].a)==QString(pytania[numer_pytania].odpowiedz))
    {
        ui->polepytanie->setText("Poprawna odpowiedź");
        punkty=punkty+1;
    }
    else
    {
        ui->polepytanie->setText("Niepoprawna odpowiedź");
    }        
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    t.stop();
    przejdz_dalej();

}

void MainWindow::on_pushButton_2_clicked()
{
    if(style==0)
        zmien_styl_cieply(ui->pushButton_2);
    else
        zmien_styl_zimny(ui->pushButton_2);

    if(QString(pytania[numer_pytania].b)==QString(pytania[numer_pytania].odpowiedz))
    {
        ui->polepytanie->setText("Poprawna odpowiedź");
        punkty=punkty+1;
    }
    else
    {
        ui->polepytanie->setText("Niepoprawna odpowiedź");
    }
    ui->pushButton->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    t.stop();
    przejdz_dalej();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(style==0)
        zmien_styl_cieply(ui->pushButton_3);
    else
        zmien_styl_zimny(ui->pushButton_3);

    if(QString(pytania[numer_pytania].c)==QString(pytania[numer_pytania].odpowiedz))
    {
        ui->polepytanie->setText("Poprawna odpowiedź");
        punkty=punkty+1;
    }
    else
    {
        ui->polepytanie->setText("Niepoprawna odpowiedź");
    }
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    t.stop();
    przejdz_dalej();
}

void MainWindow::on_pushButton_4_clicked()
{

    if(style==0)
        zmien_styl_cieply(ui->pushButton_4);
    else
        zmien_styl_zimny(ui->pushButton_4);

    if(QString(pytania[numer_pytania].d)==QString(pytania[numer_pytania].odpowiedz))
    {
        ui->polepytanie->setText("Poprawna odpowiedź");
        punkty=punkty+1;
    }
    else
    {
        ui->polepytanie->setText("Niepoprawna odpowiedź");
    }
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    t.stop();
    przejdz_dalej();

}

void MainWindow::on_pushButton_back_clicked()
{
    emit showStart();
    hide();
    wroc_styl(ui->pushButton);
    wroc_styl(ui->pushButton_2);
    wroc_styl(ui->pushButton_3);
    wroc_styl(ui->pushButton_4);
    ui->progressBar->setValue(0);
    numer_pytania=0;
    punkty=0;
    t.stop();
    przyciski_odp(true);
    ui->label_smile->setVisible(false);


}

void MainWindow::on_progressBar_valueChanged(int value)
{
    if(value==800)
    {
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->polepytanie->setText("KONIEC CZASU");
    t.stop();
    }
}


