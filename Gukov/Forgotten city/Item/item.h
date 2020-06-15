#ifndef ITEM_H
#define ITEM_H
#include <QPixmap>
#include <QString>
#include <iostream>

class Spells;

class Item
{
private:

    int cost; // цена
    ushort value; // значение, будь то урон или защита
    ushort type; //тип предмета
    ushort status;//качество
    ushort durability; //прочность
    ushort quantity;// количество
    QString name;
    ushort level;

public:
    Item() = default;
    Item(int _cost,int _value,int _type,int _durability,int _quantity);

    Spells* effect; //способность предмета

    void setCost(int _cost);
    int getCost();

    Spells *getEff();

    void setQuantity(int _quantity);
    int getQuantity();

    void setValue(double _attack);
    double getValue();

    void setType(int _type);
    int getType();

    void setDurability(int _durability);
    double getDurability();

    void setName(QString _name);
    QString getName();

    void create(int c, int t , int v, int d, int q, QString n,Spells* e,ushort l);

    int getStatus() const;
    void setStatus(int value);

    void addDurability(int a);
    void addQuantity(int a);

    ushort getLevel() const;
    void setLevel(const ushort &value);
};

#endif // ITEM_H
