#include "lootgeneration.h"

LootGeneration::LootGeneration()
{
    QFile file(":/new/base item/lists/database item.txt");
    QTextStream in(&file);
    file.open(QIODevice::ReadOnly);
    QString line;
    in.setCodec("utf-8");


    while (!in.atEnd()) {
        line = in.readLine();
        itemList.push_back(line);
    }
    file.close();
}

int LootGeneration::createBoundaries(int level)
{
    QStringList list;
    int lowerBound = 0;
    int upperBound;
    chanceAndNumber temp;
    uint s = 0;
    for(int i = 0; i < itemList.size(); i++){
        list = itemList[i].split("|");
        if(level >= minLevel + 1){
            if(list[5].toUInt() == (level - minLevel - 1)){
                lowerBound = i + 1;
            }
        }
        if(list[5].toUInt() == level){
            upperBound = i;
        }
    }

    if(chanceItem.empty()){
        chanceItem.clear();
    }

    for(int i = lowerBound; i <= upperBound; i++){
        list = itemList[i].split("|");
        s += list[2].toUInt();
        temp.chance = s;
        temp.number = i;
        chanceItem.push_back(temp);
    }
    max = s;


}

Item LootGeneration::itemGeneration(int a)
{
    QStringList list;

    Item item;
    list = itemList[a].split("|");
    int levelSpell = 1;

    switch (list[9].toInt()){
        case 1:
        levelSpell = random(5,8);
        break;
    case 2:
        levelSpell = random(3,5);
        break;
    case 3:
        levelSpell = random(1,3);
        break;
    }

    item.create(list[7].toInt(),list[4].toInt(),list[3].toInt(),list[6].toInt(),1,list[1],addSpellItem(list[8].toInt(),levelSpell),list[5].toUInt());
    int x = random(-strengthDifference,strengthDifference);
    item.addDurability(x);
    item.setStatus(list[9].toInt());

    return item;
}

Spells *LootGeneration::addSpellItem(int n, int l)
{
    Spells *a = nullptr;
    switch (n) {
    case 0:
        a = new stub;
        a->level = l;
        a->closed = 0;
        break;
    case 1:
        a = new heal;
        a->level = l;
        a->closed = 0;
        break;
    case 2:
        a = new attackSword;
        a->level = l;
        a->closed = 0;
        break;
    case 3:
        a = new attackDagger;
        a->level = l;
        break;
    case 4:
        a = new mana;
        a->level = l;
        break;
    case 5:
        a = new health;
        a->level = l;
        break;
    case 6:
        a = new Crit;
        a->level = l;
        break;
    case 7:
        a = new evasion;
        a->level = l;
        break;
    case 8:
        a = new critChance;
        a->level = l;
        break;
    case 9:
        a = new ColdInc;
        a->level = l;
        break;
    case 10:
        a = new ColdRes;
        a->level = l;
        break;
    case 11:
        a = new fireballStaff;
        a->level = l;
        break;
    case 12:
        a = new luckyHit;
        a->level = l;
        break;
    case 13:
        a = new poisInc;
        a->level = l;
        break;
    case 14:
        a = new poisRes;
        a->level = l;
        break;
    case 15:
        a = new fireRes;
        a->level = l;
        break;
    case 16:
        a = new ArmorUp;
        a->level = l;
        break;
    case 17:
        a = new IceStaff;
        a->level = l;
        break;
    }
    return a;
}

Item LootGeneration::generation(int level,int attempt)
{
    Item a,temp;
    temp.create(0,2,0,0,0,"",new stub,0);
    a.create(0,2,0,0,0,"",new stub,0);

    for(int j = 0; j < attempt; j++){

        int x = random(0,max);

        if(oldlevel != level)
        {
            oldlevel = level;
            createBoundaries(level);
        }

        for(int i = 0; i < chanceItem.size(); i++){
            if((x < chanceItem[i].chance)){
                temp = itemGeneration(chanceItem[i].number);
                break;
            }
        }

        if(temp.getCost() > a.getCost()){
            a = temp;
        }
        else{
            if(temp.getCost() == a.getCost()){
                if(temp.getStatus() < a.getStatus()){
                    a = temp;
                }
            }
        }
    }

    return a;
}
