#include "EnemyHero.h"

void EnemyHero::create(int s, int a, int i, int hp, int mp, int arm, int att)
{
    stats.setStr(s);
    stats.setAgi(a);
    stats.setInt(i);
    stats.setBaseHP(hp);
    stats.setBaseMP(mp);
    stats.setArmor(arm);
    stats.setAttack(att);
    stats.setHP(stats.getMaxHP());
}

void EnemyHero::createNPC(int l)
{
    switch (random(1,6)) {
    case 1:
        model.load(":/new/monstes/image/enemyNPC/orc.png");
        name = "Орк";
        spell = new baseAttackNPC;
        setParam(0.9,0.9,0.9,0.9,0.9,0.9,0.9);
        setExtraOptions(0,0.1,0);
        setIncrease(1,1,1);
        setResistance(1,1,1);
        break;

    case 2:
        model.load(":/new/monstes/image/enemyNPC/Bear.png");
        name = "Медведь";
        spell = new baseAttackNPC;
        setParam(0.9,0.9,0.9,1,1,1,1);
        setExtraOptions(0,1,0);
        setIncrease(1,1,1);
        setResistance(1.3,1,0.9);
        break;

    case 3:
        model.load(":/new/monstes/image/enemyNPC/Enemy.png");
        name = "Жуткое создание";
        spell = new baseAttackNPC;
        setParam(1,1,1,0.9,0.5,0.8,1);
        setExtraOptions(0,1,0);
        setIncrease(1,1,1);
        setResistance(1,1,1);
        break;

    case 4:
        model.load(":/new/monstes/image/enemyNPC/Wolf.png");
        name = "Волк";
        spell = new baseAttackNPC;
        setParam(1,1,1,1,1,1,1);
        setExtraOptions(12,1.3,18);
        setIncrease(1,1,1);
        setResistance(1.4,1.1,0.9);
        break;

    case 5:
        model.load(":/new/monstes/image/enemyNPC/zombi.png");
        name = "Воставший мертвец";
        spell = new baseAttackNPC;
        setParam(1,1,1,1,1,0.1,1.2);
        setExtraOptions(0,1,0);
        setIncrease(1,1,1);
        setResistance(1.5,1,0.5);
        break;

    case 6:
        model.load(":/new/monstes/image/enemyNPC/vampire.jpg");
        name = "Вампир";
        spell = new vampirism;
        setParam(1,1,1,1.2,0.5,0.1,1.6);
        setExtraOptions(8,1.2,16);
        setIncrease(1,1,1);
        setResistance(1.7,0.9,0.9);
        break;
    }

    exp = random(l * 10 + 10,30 + l * 10  );

    create(round(random((l * 2) - 1 ,l * 3 + 1) * s),
           round(random((l * 2) - 1 ,l * 3 + 1) * a),
           round(random((l * 2) - 1 ,l * 3 + 1) * i),
           round(random(11 * l - 6,12 * l + 8) * hp),
           round(random(11 * l - 8,20 * l + 10) * mp),
           round(random(l * 2 - 1,l * 2 + 1) * arm),
           round(random(l * 2 - 1,l * 2 + 2))* att);
    stats.setLevel(l);
}

void EnemyHero::createBoss(int l)
{
    switch (random(1,4)) {
    case 1:
        model.load(":/new/boss/image/boss/Herald of hell.jpg");
        name = "Глашатай ада";
        spell = new fireAttack;
        spell->level = random(2,5);
        setParam(1.1,1,1,1.1,1,1,1.1);
        setExtraOptions(1,1,1);
        setIncrease(2,1,1);
        setResistance(-1,2,0.9);
        break;

    case 2:
        model.load(":/new/boss/image/boss//Monkey king.jpg");
        name = "Monkey king";
        spell = new attackSwordNPC;
        spell->level = random(2,5);
        setParam(1,1,1,0.5,1,1.1,1);
        setExtraOptions(1,1,1);
        setIncrease(1,1,1);
        setResistance(1.3,1,0.6);
        break;

    case 3:
        model.load(":/new/boss/image/boss/Pangolin.jpg");
        name = "Pangolin";
        spell = new poisonAttack;
        spell->level = random(2,5);
        setParam(1.1,1,1,1,1,1.1,1.1);
        setExtraOptions(0,1,1);
        setIncrease(1,1,2);
        setResistance(0.7,1.6,0);
        break;

    case 4:
        model.load(":/new/boss/image/boss/Skull collector.jpg");
        name = "Skull collector";
        spell = new attackDaggerNPC;
        spell->level = random(2,5);
        setParam(0.9,1,1,0.8,0.5,0.7,1);
        setExtraOptions(25,1.4,30);
        setIncrease(1,1,1);
        setResistance(0.8,0.8,1);
        break;
    }

    exp = random(l * 20 + 10,30 + l * 20  );

    create(round(random((l * 3) + 2 - 4 ,l * 4 + 1) * s),
           round(random((l * 3) + 2 - 4 ,l * 4 + 1) * a),
           round(random((l * 3) + 2 - 4 ,l * 4 + 1) * i),
           round(random(9 * l - 10,16 * l + 5) * hp),
           round(random(9 * l - 10,20 * l + 5) * mp),
           round(random(l * 2 - 1,l * 3 + 1) * arm),
           round(random(l * 2 - 1,l * 3 + 1))* att);
    stats.setLevel(l);
}

int EnemyHero::getExp()
{
    return exp;
}

void EnemyHero::setParam(double _s, double _a, double _i, double _hp, double _mp, double _arm, double _att)
{
    s = _s;
    a = _a;
    i = _i;
    hp = _hp;
    mp = _mp;
    arm = _arm;
    att = _att;
}

void EnemyHero::setExtraOptions(int _e,double _c,int _ch)
{
    stats.setEvasion(_e);
    stats.setCrit(_c);
    stats.setCritChance(_ch);
}

void EnemyHero::setResistance(double f, double c, double p)
{
    stats.setFireResistance(f);
    stats.setColdResistance(c);
    stats.setPoisonResistance(p);

}

void EnemyHero::setIncrease(double f, double c, double p)
{
    stats.setFireIncrease(f);
    stats.setColdIncrease(c);
    stats.setPoisonIncrease(p);
}

void EnemyHero::createMonster(QString _name, Spells* _spell,MainStats _stats)
{
    model.load(":/new/EnemyNPC/image/enemyNPC/" + _name + ".png");
    name = _name;
    spell = _spell;
    stats = _stats;
    exp = random(stats.getLevel() * 20 + 10,30 + stats.getLevel() * 20  );
}
