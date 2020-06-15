#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "character/person.h"
#include "character/bagitem.h"
#include "character/allspell.h"

const int spellPointUp = 2; // очки способностей за 1 уровень
const int statPointUp = 3; //очки статов за 1 уровень
const double coefficient = 1.25; //коэфф увеличения количества опыта нужного для каждого нового уровня

class Player : public Person
{
private:
    int spellPoint; //очки способностей
    int statPoint; //очки характеристик
    int expMax; //максимальное количество опыта до нового уровня
    int exp; //текущий опыт
    int pers;


public:
    Player();
    BagItem bag; // рюкзак
    BagItem belt; //пояс с зельями
    BagItem warehouse; //склад
    std::vector<Spells*> spell;
    std::vector<int> spellNumb{0,0,0,0,0,0,0,0}; //нужно для отслеживания того какая ячейка занята способностью
    std::vector<Spells*> spellPlayer;
    void setStatPoint(int sp);
    void setSpellPoint(int sp);
    int getStatPoint();
    int getSpellPoint();
    void maxExp(); //высчитывает максимум опыта
    void addExp(int e); //добавить опыть
    int getExp();
    int getExpMax();
    void setExp(int e);
    void addMoney(int a);

    void addSpellPoint(int a);
    void addStatsPoint(int a);
    int getPers() const;
    void setPers(int value);
};

#endif // PLAYER_H
