#ifndef PYTANIE_H
#define PYTANIE_H
#include <QString>


/*!
* \class
*/
///Klasa reprezentująca pytania oraz ich zmienne
class Pytanie
{
public:
    ///Zmienna przechowująca treść pytania
    QString pytanie;
    ///Zmienna przechowująca odpowiedz pierwsza
    QString a;
    ///Zmienna przechowująca odpowiedz drugą
    QString b;
    ///Zmienna przechowująca odpowiedz trzecią
    QString c;
    ///Zmienna przechowująca odpowiedz czwartą
    QString d;
    ///Zmienna przechowująca odpowiedz prawidłową
    QString odpowiedz;

    Pytanie(QString x1,QString x2,QString x3,QString x4,QString x5,QString x6):pytanie(x1),a(x2),b(x3),c(x4),d(x5),odpowiedz(x6){}
    Pytanie(){}
};
#endif // PYTANIE_H
