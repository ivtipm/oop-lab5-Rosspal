#ifndef ENEMYHERO_H
#define ENEMYHERO_H

#include "character/person.h"
#include "secondaryfunctions.h"
#include "character/allspell.h"
#include <cmath>

class EnemyHero : public Person
{
private:
    int exp;
    double s,a,i,hp,mp,arm,att; //коэффициенты характеристик

public:
    Spells* spell;
    void create(int s, int a, int i,int hp, int mp ,int arm, int att);
    void createNPC(int l);
    void createBoss(int l);
    int getExp();
    void setParam(double _s, double _a, double _i, double _hp, double _mp, double _arm, double _att);
    void setExtraOptions(int _e,double _c,int _ch);
    void setResistance(double f,double c,double p);
    void setIncrease(double f,double c,double p);
    void createMonster(QString name, Spells* spell,MainStats stats); //не используется
};

#endif // ENEMYHERO_H
