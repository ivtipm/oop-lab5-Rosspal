#include "person.h"

void Person::setName(QString value)
{
    name = value;
}

void Person::addMoney(int a)
{
    money += a;
}

void Person::setMoney(int _money)
{
    money = _money;
}

int Person::getMoney()
{
    return money;
}

QPixmap Person::getModel()
{
    return model;
}

QString Person::getName()
{
    return name;
}
