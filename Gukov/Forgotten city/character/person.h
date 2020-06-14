#ifndef PERSON_H
#define PERSON_H
#include <QPixmap>
#include <QString>
#include "character/MainStats.h"
#include "character/equipment.h"

class Person
{
protected:
    QPixmap model;
    QString name;
    int money = 0;

public:
    Equipment equip; //экипированные вещи
    MainStats stats; //характеристики
    void setMoney(int _money);
    int getMoney();

    QPixmap getModel();
    QString getName();
    void setName(QString value);
    void addMoney(int a);
};

#endif // PERSON_H
