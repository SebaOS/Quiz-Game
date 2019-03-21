#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
* \class
*/
///Klasa okna z pytaniami reprezentująca jego zmienne oraz funkcje

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QTimer>
#include "pytanie.h"
#include <QVector>
using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ///QPixmap p;
    int style;
    ///Zmienne wczytywania i zadawania pytań
    string linia;
    QVector <Pytanie> pytania;
    int numer_pytania;
    ///Zmienna punktów
    int punkty=0;
    ///Pokazywanie przycisków odpowiedzi
    int in;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ///Funkcja ustawiająca kolor logo
    void ustaw_motyw(QPixmap p);
    ///Funkcja ustawiająca wybrany przez użytkownika styl/motyw
    void ustaw_styl(int s);
    ///Funkcja ustawiająca tło pytań
    void ustaw_pole();
    ///Funkcja zadająca wczytane pytania do okienek
    void zadaj_pytania();
    ///Funkcja wczytająca pytania
    void wczytaj_pytania();
    ///Funkcja rozpoczynająca zliczanie
    void czas_start();
    ///Funkcja przejścia do następnego pytania
    void przejdz_dalej();
    ///Funkcja kończąca gre
    void koniec_gry();
    ///Chowa/pokazuje przyciski odpowiedzi
    void przyciski_odp(int in);
    ///Zmienna informująca o wczytaniu pliku do programu
    int wczytanie=false;

    QTimer t;


signals:
    void showStart(); ///Sygnal powrotu do głównego okna

private slots:
    ///Zmienia motyw aplikacji na ciepły
    void zmien_styl_cieply(QPushButton *p);
    ///Zmienia motyw aplikacji na zimny
    void zmien_styl_zimny(QPushButton *p);
    ///Przywraca PushButtonom użyteczność
    void wroc_styl(QPushButton *s);
    ///Przycisk odpowiedzi pierwszej
    void on_pushButton_clicked();
    ///Przycisk odpowiedzi drugiej
    void on_pushButton_2_clicked();
    ///Przycisk odpowiedzi trzeciej
    void on_pushButton_3_clicked();
    ///Przycisk odpowiedzi czwartej
    void on_pushButton_4_clicked();
    ///Przycisk powrotu do okna głównego
    void on_pushButton_back_clicked();
    ///Odlicza czas timera
    void progres();
    ///Odlicza czas przejscia
    void przejscie();
    ///Progressbar pokazujący upływający czas
    void on_progressBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    ///Objekt timer t do odliczania czasu na odpowiedź

    ///Objekt timer p do odliczania czasu przejścia do następnego pytania
    QTimer p;




};

#endif // MAINWINDOW_H
