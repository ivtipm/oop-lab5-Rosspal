#ifndef ALLSPELL_H
#define ALLSPELL_H
#include <QPixmap>
#include <QDateTime>

#include "character/person.h"
#include "EnemyHero.h"
#include "secondaryfunctions.h"

const double koef = 0.2;
const double koefDagger = 0.1;
const double koefSword = 0.15;
const int koefMana = 15;
const int koefHealth = 15;
const double koefCrit = 0.1;
const int koefCritChance = 5;
const int koefEvasion = 5;
const double koefRes = 0.05;
const double koefInc = 0.05;


class EnemyHero;
class Person;

class Spells
{
public:
    QString text = "";
    int level = 1;
    int closed = 1;
    int used = 0;
    int coolDown = 0;
    int manaCost = 0;
    std::vector<int> valueLevel;
    std::vector<int> manaCostLevel;
    Spells() = default;
    virtual void effect(EnemyHero &NPC,Person &hero) = 0;
    virtual int CD() = 0;
    virtual QString name() = 0;
    virtual QString description() = 0;
};

class  stub:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;

};

class  baseAttack:public Spells
{
public:
    int used = 1;
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  attackSword:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  attackDagger:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  luckyHit:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  heal:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  manaRecovery:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  mana:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  health:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  Crit:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  evasion:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  critChance:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  ColdInc:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  ColdRes:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  poisInc:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  poisRes:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  fireRes:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  ArmorUp:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  oneShot:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;

};

class  backstab:public Spells // 1 разбойник
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  achillesHeel:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  cutWallet:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  lifeSteal:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  fireball:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{10,14,18,22,26};
    std::vector<int> manaCostLevel{15,20,25,32,38};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  fireballStaff:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{6,10,14,18,22};
    std::vector<int> manaCostLevel{12,15,18,22,25};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  blockOfIce:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{7,11,15,19,23};
    std::vector<int> manaCostLevel{11,16,20,25,30};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  IceStaff:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{4,8,12,16,20};
    std::vector<int> manaCostLevel{6,10,14,18,20};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  unityOfMagic:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{20,25,30,35,40};
    std::vector<int> manaCostLevel{40,50,60,70,80};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  blockOfStone:public Spells
{
public:
    QString description() override;
    std::vector<int> valueLevel{3,7,11,15,19};
    std::vector<int> manaCostLevel{7,11,14,16,20};
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  strongBeat:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  furiousBlow:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  toRam:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  berserkerRage:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  baseAttackUp:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  baseAttackNPC:public Spells //NPC
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  vampirism:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  attackSwordNPC:public attackSword
{
public:
    void effect(EnemyHero &NPC,Person &hero) override ;
};

class  attackDaggerNPC:public attackDagger
{
public:
    void effect(EnemyHero &NPC,Person &hero) override ;
};

class  fireAttack:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};

class  poisonAttack:public Spells
{
public:
    QString description() override;
    QString name() override;
    void effect(EnemyHero &NPC,Person &hero) override ;
    int CD() override;
};
#endif // ALLSPELL_H
