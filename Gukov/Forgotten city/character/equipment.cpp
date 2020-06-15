#include "equipment.h"

Equipment::Equipment()
{
    Item b(0,0,0,0,0);
    hand = b;
    helmet = b;
    footwear = b;
    pants = b;
    torso = b;
    belt = b;
    oneRing = b;
    twoRing = b;
    gloves = b;
}

void Equipment::takeOff(Item a)
{
    Item b(0,0,0,0,0);
    a = b;
}

void Equipment::setHand(Item a)
{
    hand = a;
}

void Equipment::setHelmet(Item a)
{
    helmet = a;
}

void Equipment::setFootwear(Item a)
{
    footwear = a;
}

void Equipment::setPants(Item a)
{
    pants = a;
}

void Equipment::setBelt(Item a)
{
    belt = a;
}

void Equipment::setOneRing(Item a)
{
    oneRing = a;
}

void Equipment::setTwoRing(Item a)
{
    twoRing = a;
}

void Equipment::setGloves(Item a)
{
    gloves = a;
}

void Equipment::setTorso(Item a)
{
    torso = a;
}

Item Equipment::getTorso()
{
    return torso;
}

Item Equipment::getHand()
{
    return hand;
}

Item Equipment::getHelmet()
{
    return helmet;
}

Item Equipment::getFootwear()
{
    return footwear;
}

Item Equipment::getPants()
{
    return pants;
}

Item Equipment::getBelt()
{
    return belt;
}

Item Equipment::getOneRing()
{
    return oneRing;
}

Item Equipment::getTwoRing()
{
    return twoRing;
}

Item Equipment::getGloves()
{
    return gloves;
}

void Equipment::addDurabilityHand(int a)
{
    hand.addDurability(a);
}

void Equipment::addDurabilityHelmet(int a)
{
    helmet.addDurability(a);
}

void Equipment::addDurabilityFootwear(int a)
{
    footwear.addDurability(a);
}

void Equipment::addDurabilityPants(int a)
{
    pants.addDurability(a);
}

void Equipment::addDurabilityTorso(int a)
{
    torso.addDurability(a);
}

void Equipment::addDurabilityOneRing(int a)
{
    oneRing.addDurability(a);
}

void Equipment::addDurabilityTwoRing(int a)
{
    twoRing.addDurability(a);
}

void Equipment::addDurabilityGloves(int a)
{
    gloves.addDurability(a);
}

double Equipment::getGeneralAttack()
{
    double damage;
    damage = hand.getValue() * hand.getDurability()/100;
    return round(damage);
}

double Equipment::getGeneralArmor()
{
    double d;
    d = (helmet.getValue() * (double)(helmet.getDurability()/100)) + (footwear.getValue() * (footwear.getDurability()/100)) + (pants.getValue() * (pants.getDurability()/100))
                         + (torso.getValue() * (torso.getDurability()/100));
    return round(d);
}
