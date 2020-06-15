#include "player.h"

int Player::getPers() const
{
    return pers;
}

void Player::setPers(int value)
{
    pers = value;
}

Player::Player()
{
    spellPlayer.push_back(new backstab);
    spellPlayer.push_back(new achillesHeel);
    spellPlayer.push_back(new cutWallet);
    spellPlayer.push_back(new lifeSteal);
    spellPlayer.push_back(new blockOfStone);
    spellPlayer.push_back(new fireball);            //способности возможные для изучения
    spellPlayer.push_back(new blockOfIce);
    spellPlayer.push_back(new unityOfMagic);
    spellPlayer.push_back(new strongBeat);
    spellPlayer.push_back(new furiousBlow);
    spellPlayer.push_back(new toRam);
    spellPlayer.push_back(new berserkerRage);

    Item c;
    bag.bagCreate(9,5);
    c.create(0,0,0,0,0,"пусто",new stub,0);

    for (int i = 0; i < bag.getLine(); i++){
        for (int j = 0; j < bag.getColumn(); j++){
            bag.setCell(i,j,c);
        }
    }
    belt.bagCreate(1,6);
    for (int i = 0; i < belt.getLine(); i++){
        for (int j = 0; j < belt.getColumn(); j++){
            belt.setCell(i,j,c);
        }
    }
    belt.setColumn(1);

    c.setName("close");
    warehouse.bagCreate(2,5);
    for (int i = 0; i < warehouse.getLine(); i++){
        for (int j = 0; j < warehouse.getColumn(); j++){
            warehouse.setCell(i,j,c);
        }
    }
}

void Player::setStatPoint(int sp)
{
    statPoint = sp;
}

void Player::setSpellPoint(int sp)
{
    spellPoint = sp;
}

int Player::getStatPoint()
{
    return statPoint;
}

int Player::getSpellPoint()
{
    return spellPoint;
}

void Player::maxExp()
{
    expMax = 100 + stats.getLevel() * 100 * coefficient;
}

void Player::addExp(int e)
{
    exp += e;
    if (exp >= expMax){
        if ((exp - expMax) > 0){
            exp = exp - expMax;
        }
        else {
            exp = 0;
        }
        stats.setLevel(stats.getLevel() + 1);
        maxExp();
        statPoint += statPointUp;
        spellPoint += spellPointUp;
    }
}

int Player::getExp()
{
    return exp;
}

int Player::getExpMax()
{
    return expMax;
}

void Player::setExp(int e)
{
    exp = e;
}

void Player::addMoney(int a)
{
    money += a;
}

void Player::addSpellPoint(int a)
{
    spellPoint += a;
}

void Player::addStatsPoint(int a)
{
    statPoint += a;
}
