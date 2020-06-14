#ifndef LOOTGENERATION_H
#define LOOTGENERATION_H

#include <vector>
#include <QFile>
#include <QTextStream>
#include "Item/item.h"
#include "secondaryfunctions.h"
#include "character/allspell.h"

const int minLevel = 5;
const int strengthDifference = 7;

struct chanceAndNumber{
    int chance;
    int number;
};

class LootGeneration
{
private:

    std::vector<chanceAndNumber> chanceItem;
    std::vector<QString> itemList;
    int max;
    int oldlevel = 0;

    int createBoundaries(int level);
    Item itemGeneration(int a);
    Spells* addSpellItem(int n, int l);
public:
    LootGeneration();
    Item generation(int level,int attempt);
};

#endif // LOOTGENERATION_H
