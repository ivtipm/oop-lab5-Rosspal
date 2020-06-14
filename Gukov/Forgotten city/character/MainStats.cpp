#include "MainStats.h"

double MainStats::getCritMagic() const
{
    return critMagic;
}

void MainStats::setCritMagic(double value)
{
    critMagic = value;
}

int MainStats::getCritMagicChance() const
{
    return critMagicChance;
}

void MainStats::setCritMagicChance(int value)
{
    critMagicChance = value;
}

double MainStats::getFireResistance() const
{
    return fireResistance;
}

void MainStats::setFireResistance(double value)
{
    fireResistance = value;
}

double MainStats::getFireIncrease() const
{
    return fireIncrease;
}

void MainStats::setFireIncrease(double value)
{
    fireIncrease = value;
}

double MainStats::getColdResistance() const
{
    return coldResistance;
}

void MainStats::setColdResistance(double value)
{
    coldResistance = value;
}

double MainStats::getColdIncrease() const
{
    return coldIncrease;
}

void MainStats::setColdIncrease(double value)
{
    coldIncrease = value;
}

double MainStats::getPoisonResistance() const
{
    return poisonResistance;
}

void MainStats::setPoisonResistance(double value)
{
    poisonResistance = value;
}

double MainStats::getPoisonIncrease() const
{
    return poisonIncrease;
}

void MainStats::setPoisonIncrease(double value)
{
    poisonIncrease = value;
}

int MainStats::getOratory() const
{
    return oratory;
}

void MainStats::setOratory(int value)
{
    oratory = value;
}

void MainStats::addFireResistance(double value)
{
    fireResistance += value;
}

void MainStats::addColdResistance(double value)
{
    coldResistance += value;
}

void MainStats::addPoisonResistance(double value)
{
    poisonResistance += value;
}

void MainStats::addFireIncrease(double value)
{
    fireIncrease += value;
}

void MainStats::addColdIncrease(double value)
{
    coldIncrease += value;
}

void MainStats::addPoisonIncrease(double value)
{
    poisonIncrease += value;
}

int MainStats::getRegenHP() const
{
    return regenHP;
}

void MainStats::setRegenHP(int value)
{
    regenHP = value;
}

int MainStats::getRegenMP() const
{
    return regenMP;
}

void MainStats::setRegenMP(int value)
{
    regenMP = value;
}

double MainStats::getHealPower() const
{
    return healPower;
}

void MainStats::setHealPower(double value)
{
    healPower = value;
}

double MainStats::getManaPower() const
{
    return manaPower;
}

void MainStats::setManaPower(double value)
{
    manaPower = value;
}

MainStats::MainStats()
{
    maxHP = 3;
    maxMP = 3;
    HP = 3;
    MP = 3;
    strength = 1;
    agility = 1;
    intelect = 1;
    level = 1;
}

void MainStats::addManaPower(double a)
{
    manaPower += a;
}

void MainStats::addHealPower(double a)
{
    healPower += a;
}

void MainStats::addRegHP(int a)
{
    regenHP += a;
}

void MainStats::addRegMP(int a)
{
    regenMP += a;
}

void MainStats::regeneration()
{
    addHP(regenHP);
    addMP(regenMP);
}

void MainStats::zeroing()
{
    strength = 1;
    agility = 1;
    intelect = 1;
    level = 1;
    crit = 1.1;
    critChance = 5;
    evasion = 0;
    escapeChance = 25;
    critMagic = 1.1;
    critMagicChance = 5;
    fireResistance = 0.8;
    fireIncrease = 1;
    coldResistance = 0.8;
    coldIncrease = 1;
    poisonResistance = 0.8;
    poisonIncrease = 1;
    regenHP = 1;
    regenMP = 1;
    oratory = 0;
    healPower = 1;
    manaPower = 1;

    baseHP = 0;
    baseMP = 0;
    baseAttack = 0;
    baseArmor = 0;

    armor = 0;
    attack = 0;
}

void MainStats::setMaxHP(int a)
{
    maxHP = a;
}

int MainStats::getMaxHP()
{
    return maxHP;
}

void MainStats::setMaxMP(int a)
{
    maxMP = a;
}

int MainStats::getMaxMP()
{
    return maxMP;
}

void MainStats::setHP(int a)
{
    HP = a;
}

int MainStats::getHP()
{
    return HP;
}

void MainStats::setMP(int a)
{
    MP = a;
}

int MainStats::getMP()
{
    return MP;
}

void MainStats::setStr(int a)
{
    strength = a;
    refresh();
}

int MainStats::getStr()
{
    return strength;
}

void MainStats::setAgi(int a)
{
    agility = a;
    refresh();
}

int MainStats::getAgi()
{
    return agility;
}

void MainStats::setInt(int a)
{
    intelect = a;
    refresh();
}

int MainStats::getInt()
{
    return intelect;
}

void MainStats::setLevel(int a)
{
    level = a;
}

int MainStats::getLevel()
{
    return level;
}

void MainStats::setEvasion(double a)
{
    evasion = a;
}

double MainStats::getEvasion()
{
    return evasion;
}

void MainStats::setCrit(double a)
{
    crit = a;
}

double MainStats::getCrit()
{
    return crit;
}

void MainStats::setCritChance(double a)
{
    critChance = a;
}

int MainStats::getCritChance()
{
    return critChance;
}

void MainStats::setBaseHP(int a)
{
    baseHP = a;
    refresh();
}

int MainStats::getBaseHP()
{
    return baseHP;
}

void MainStats::setBaseMP(int a)
{
    baseMP = a;
}

int MainStats::getBaseMP()
{
    return baseMP;
}

void MainStats::setBaseAttack(int a)
{
    baseAttack = a;
}

int MainStats::getBaseAttack()
{
    return baseAttack;
}

void MainStats::setBaseArmor(int a)
{
    baseArmor = a;
}

int MainStats::getBaseArmor()
{
    return baseArmor;
}

void MainStats::setAttack(int a)
{
    attack = a;
}

int MainStats::getAttack()
{
    return attack;
}

void MainStats::setArmor(int a)
{
    armor = a;
}

int MainStats::getArmor()
{
    return  armor;
}

void MainStats::setEscapeChance(int a)
{
    escapeChance = a;
}

int MainStats::getEscapeChance()
{
    return  escapeChance;
}

void MainStats::setAll(int _maxHP, int _maxMP, int _HP, int _MP, int _strength, int _agility, int _intelect, int _level)
{
    maxHP = _maxHP;
    maxMP = _maxMP;
    HP = _HP;
    MP = _MP;
    strength = _strength;
    agility = _agility;
    intelect = _intelect;
    level = _level;
}

void MainStats::refresh()
{
    int a = percentNumNum(maxHP,HP);
    maxHP = strength * 7.5 + baseHP;
    HP = percent(a,maxHP);
    maxMP = intelect * 4 + baseMP;
    MP = maxMP;
    armor = agility/4 + baseArmor;
}

void MainStats::addInt(int a)
{
    intelect += a;
    refresh();
}

void MainStats::addStr(int a)
{
    strength += a;
    refresh();
}

void MainStats::addAgi(int a)
{
    agility += a;
    refresh();
}

void MainStats::addHP(int a)
{
    if((HP + a) > maxHP){
        HP = maxHP;
    }
    else{
        if((HP + a) < 0){
            HP = 0;
        }else{
            HP += a;
        }
    }
}

void MainStats::addMP(int a)
{
    if((MP + a) > maxMP){
        MP = maxMP;
    }
    else{
        if((MP + a) < 0){
            MP = 0;
        }else{
            MP += a;
        }
    }
}

void MainStats::addLevel(int a)
{
    level += a;
}

void MainStats::addCrit(double a)
{
    crit += a;
}

void MainStats::addCritChance(int a)
{
    critChance += a;
}

void MainStats::addEvasion(int a)
{
    evasion += a;
}

void MainStats::addBaseHP(int a)
{
    baseHP += a;
    refresh();
}

void MainStats::addBaseMP(int a)
{
    baseMP += a;
    refresh();
}

void MainStats::addBaseAttack(int a)
{
    baseAttack += a;
}

void MainStats::addBaseArmor(int a)
{
    baseArmor += a;
}

void MainStats::addEscapeChance(int a)
{
    escapeChance += a;
}

void MainStats::addOratory(int a)
{
    oratory += a;
}
