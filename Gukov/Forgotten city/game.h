#ifndef GAME_H
#define GAME_H
#include <vector>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include <cmath>
#include "character/player.h"
#include "character/allspell.h"
#include "EnemyHero.h"
#include "Item/item.h"
#include "secondaryfunctions.h"
#include "lootgeneration.h"


const int maxLevel = 5;
const int maxRoom = 12;
const int minRoom = 4;
const int costHospital = 150;
const int costTemple = 150;
const int costRepairs = 40;
const QString nullName = "пусто";

class Game: public QObject
{
    Q_OBJECT
private:
    std::vector<int> level;
    std::vector<int> cityLevel;
    std::vector<std::vector<int>> costCity;//стоимость улучшений города
    QVector<int> dunge;
    std::vector<bool> treeVisible;//видимые способности на дереве
    std::vector<QString> monsters; //временно не используется
    bool salesMode = false;
    bool warehouseMode = false;
    int roomNumber ;
    int checkRoom ;
    QString roomImage;
    int dungeLevel;
    int costHos = costHospital;
    int costTemp = costTemple;
    int moneyBank;
    LootGeneration loot;

public:
    Game();
    Game(bool a);

    BagItem store;

    EnemyHero NPC;
    Player hero;



    void initHero(int s,int i, int a); // инициализация героя
    void initGame();
    void initNPC(int level);
    void addBaseItem(); //initEquip
    void createPers(QString _name,int _str,int _agi,int _int,int pers);

    int fight(int n); // 0- вне боя 1-бой 2- победа 3-поражение
    void win();// победа в бою
    void lose();//поражение
    void usePoision(int j);
    bool escape();
    int enemyStrike();

    void genMonster();
    Spells *addSpellMonster(int n,int l);

    void characterLeveling(int a); // метод ответсвенный за дерево прокачки персонажа...

    void spellUp(int k);//прокачка способностей
    void deleteSpell(int i); // удаление способности
    void addSpell(Spells* sp);// добавить spell

    void changeOfItem(int i, int j);
    void changeOfPoision(int j);
    void sellItem(int i, int j);
    int takeOffSubject(int a);
    void changeWarehouse(int i, int j);

    void storeRefresh();  //магазин
    int storeBuy();

    void createDunge();//создание комнат подземелья
    void createRoom();
    int getRoom();
    void nextRoom();
    QString getRoomImage() const;
    void setRoomImage(const QString &value);
    int getCheckRoom() const;


    bool getSalesMode() const;
    void setSalesMode(bool value);

    int cityUpdate(int k);
    int getCityLevel(int i);

    int hospital();
    int temple();
    int repairs(int row, int column);

    int getCostHos() const;
    void setCostHos(int value);

    void refresh();

    int getCostTemp() const;
    void setCostTemp(int value);

    int getMoneyBank() const;
    void setMoneyBank(int value);

    bool getTreeVisible(int i);

    int getCostCity(int k);

    bool getWarehouseMode() const;
    void setWarehouseMode(bool value);

signals:

    void textOut(QString);
    void refreshCell(int,int);
    void refreshBelt(int,int);
    void rebirth();
};

#endif // GAME_H
