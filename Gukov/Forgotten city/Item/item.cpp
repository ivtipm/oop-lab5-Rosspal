#include "item.h"

int Item::getStatus() const
{
    return status;
}

void Item::setStatus(int value)
{
    status = value;
}

void Item::addDurability(int a)
{
    if((durability + a) >= 100){
        durability = 100;
    }else{
        if((durability + a) <= 0){
            durability = 0;
        }else{
            durability += a;
        }
    }
}

void Item::addQuantity(int a)
{
    quantity += a;
}

ushort Item::getLevel() const
{
    return level;
}

void Item::setLevel(const ushort &value)
{
    level = value;
}

Item::Item(int _cost, int _value, int _type, int _durability, int _quantity)
{
    cost = _cost;
    value = _value;
    type = _type;
    durability = _durability;
    quantity = _quantity;

}

void Item::setCost(int _cost)
{
    cost = _cost;
}

int Item::getCost()
{
    return cost;
}

Spells* Item::getEff()
{
    return effect;
}

void Item::setValue(double _value)
{
    value = _value;
}

void Item::setType(int _type)
{
    type = _type;
}

int Item::getType()
{
    return type;
}

void Item::setDurability(int _durability)
{
    durability = _durability;
}

double Item::getValue()
{
    return value;
}

double Item::getDurability()
{
    return durability;
}

void Item::setName(QString _name)
{
    name = _name;
}

QString Item::getName()
{
    return name;
}

void Item::create(int c,int t ,int v, int d, int q, QString n,Spells* e,ushort l)
{
    cost = c;
    type = t;
    value = v;
    durability = d;
    quantity = q;
    name = n;
    effect = e;
    level = l;
}

void Item::setQuantity(int _quantity)
{
    quantity = _quantity;
}

int Item::getQuantity()
{
    return quantity;
}
