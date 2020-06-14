#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <cmath>
#include "Item/item.h"

class Equipment // экипированные предметы
{
private:
    Item hand;
    Item helmet;
    Item footwear;
    Item pants;
    Item torso;
    Item belt;
    Item oneRing;
    Item twoRing;
    Item gloves;

public:
    Equipment();
    void takeOff(Item a); // снять предмет

    void setHand(Item a);
    void setHelmet(Item a);
    void setFootwear(Item a);
    void setPants(Item a);       // добавить предмет
    void setBelt(Item a);
    void setOneRing(Item a);
    void setTwoRing(Item a);
    void setGloves(Item a);
    void setTorso(Item a);

    Item getTorso();
    Item getHand();
    Item getHelmet();
    Item getFootwear();  // вывод предмета
    Item getPants();
    Item getBelt();
    Item getOneRing();
    Item getTwoRing();
    Item getGloves();

    void addDurabilityHand(int a);
    void addDurabilityHelmet(int a);
    void addDurabilityFootwear(int a);
    void addDurabilityPants(int a);
    void addDurabilityTorso(int a);
    void addDurabilityOneRing(int a);
    void addDurabilityTwoRing(int a);
    void addDurabilityGloves(int a);

    double getGeneralAttack();//конечный урон,защита
    double getGeneralArmor();

};

#endif // EQUIPMENT_H
