#pragma once
#include <secondaryfunctions.h>

class MainStats
{
private:
    int maxHP;
    int maxMP;
    int HP;
    int MP;
    int strength;
    int agility;
    int intelect;
    int level = 1;
    double crit = 1.1;
    int critChance = 5;
    double evasion = 0;
    int escapeChance = 25;
    double critMagic = 1.1;
    int critMagicChance = 5;
    double fireResistance = 0.8;
    double fireIncrease = 1;
    double coldResistance = 0.8;
    double coldIncrease = 1;
    double poisonResistance = 0.8;
    double poisonIncrease = 1;
    int regenHP = 1;
    int regenMP = 1;
    int oratory = 0;
    double healPower = 1;
    double manaPower = 1;

    double baseHP;
    int baseMP;     //базовые значения нужны для умений повышающих тот или иной параметр
    double baseAttack;
    int baseArmor;

    double armor;//общая броня
    double attack;
public:
    MainStats();

    void addManaPower(double a);
    void addHealPower(double a);

    void addRegHP(int a);
    void addRegMP(int a);

    void regeneration();

    void zeroing();

    void setMaxHP(int a);
    int getMaxHP();

    void setMaxMP(int a);
    int getMaxMP();

    void setHP(int a);
    int getHP();

    void setMP(int a);
    int getMP();

    void setStr(int a);
    int getStr();

    void setAgi(int a);
    int getAgi();

    void setInt(int a);
    int getInt();

    void setLevel(int a);
    int getLevel();

    void setEvasion(double a);
    double getEvasion();

    void setCrit(double a);
    double getCrit();

    void setCritChance(double a);
    int getCritChance();

    void setBaseHP(int a);
    int getBaseHP();

    void setBaseMP(int a);
    int getBaseMP();

    void setBaseAttack(int a);
    int getBaseAttack();

    void setBaseArmor(int a);
    int getBaseArmor();

    void setAttack(int a);
    int getAttack();

    void setArmor(int a);
    int getArmor();

    void setEscapeChance(int a);
    int getEscapeChance();

    double getCritMagic() const;
    void setCritMagic(double value);

    int getCritMagicChance() const;
    void setCritMagicChance(int value);

    void setAll(int _maxHP,int _maxMP,int _HP,int _MP,int _strength,int _agility,int _intelect,int _level);

    void refresh();

    void addInt(int a);
    void addStr(int a);
    void addAgi(int a);
    void addHP(int a);
    void addMP(int a);
    void addLevel(int a);
    void addCrit(double a);
    void addCritChance(int a);
    void addEvasion(int a);
    void addBaseHP(int a);
    void addBaseMP(int a);
    void addBaseAttack(int a);
    void addBaseArmor(int a);
    void addEscapeChance(int a);
    void addOratory(int a);

    double getFireResistance() const;
    void setFireResistance(double value);
    double getFireIncrease() const;
    void setFireIncrease(double value);
    double getColdResistance() const;
    void setColdResistance(double value);
    double getColdIncrease() const;
    void setColdIncrease(double value);
    double getPoisonResistance() const;
    void setPoisonResistance(double value);
    double getPoisonIncrease() const;
    void setPoisonIncrease(double value);
    int getOratory() const;
    void setOratory(int value);

    void addFireResistance(double value);
    void addColdResistance(double value);
    void addPoisonResistance(double value);

    void addFireIncrease(double value);
    void addColdIncrease(double value);
    void addPoisonIncrease(double value);

    int getRegenHP() const;
    void setRegenHP(int value);
    int getRegenMP() const;
    void setRegenMP(int value);
    double getHealPower() const;
    void setHealPower(double value);
    double getManaPower() const;
    void setManaPower(double value);
};

