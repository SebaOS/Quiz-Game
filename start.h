#ifndef START_H
#define START_H

/*!
* \class
*/
///Klasa reprezentująca okno główne/menu oraz jego funkcje

#include <QWidget>
#include "mainwindow.h"


namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();

    void opcje(int a, int b);

signals:
    void rozpoczecie();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_tool_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Start *ui;
    MainWindow mainwindow;
};

#endif // START_H
