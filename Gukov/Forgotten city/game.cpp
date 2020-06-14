#include "game.h"

Game::Game()
{
    initGame();
}

Game::Game(bool a)
{

}

void Game::initHero(int s, int i, int a)
{
    hero.stats.setAgi(a);
    hero.stats.setStr(s);
    hero.stats.setInt(i);
    hero.stats.setEvasion(0);
    hero.stats.setCrit(1);
    hero.stats.setCritChance(0);
    hero.stats.setLevel(1);
    hero.setStatPoint(0);
    hero.setSpellPoint(0);
    hero.setExp(0);
    hero.maxExp();
    hero.stats.setBaseAttack(0);
    hero.stats.setBaseArmor(0);
    hero.stats.refresh();

    for (int i = 0; i < 8; i++){
        hero.spell.push_back(new stub);
        hero.spell[i]->coolDown = -1;
    }

    hero.spell[0] = new baseAttack;
    addBaseItem();

    for (int i = 0; i < 37; i++){
        level.push_back(0);
    }

    store.bagCreate(2,5);


    hero.setName("wanderer");
}

void Game::initGame()
{
    for(int i = 0;i < 9; i++){
        cityLevel.push_back(0);
    }

    for(int i = 0;i < 36; i++){
        treeVisible.push_back(false);
    }
    treeVisible[0] = true;
    treeVisible[12] = true;
    treeVisible[24] = true;

    initHero(1,1,1);

    QFile file(":/new/base item/lists/monsters" + QString::number(hero.stats.getLevel()) + ".txt");
    QTextStream in(&file);
    file.open(QIODevice::ReadOnly);
    QString line;
    in.setCodec("utf-8");

    QStringList list;
    file.setFileName(":/new/base item/lists/costCity.txt");
    std::vector<int> a;
    file.open(QIODevice::ReadOnly);
    costCity.resize(9);

    int j = 0;
    while (!in.atEnd()) {
        line = in.readLine();
        list = line.split(";");
        for(int i = 0; i < 10; i++){
            costCity[j].push_back(list[i].toInt());
        }
        j++;
    }
    costCity[0][0] = 50;
    file.close();

    storeRefresh();
    for(int i = 0;i < maxRoom + 1; i++){
        dunge.push_back(0);
    }


}

bool Game::getWarehouseMode() const
{
    return warehouseMode;
}

void Game::setWarehouseMode(bool value)
{
    warehouseMode = value;
}

bool Game::getSalesMode() const
{
    return salesMode;
}

void Game::setSalesMode(bool value)
{
    salesMode = value;
}

int Game::cityUpdate(int k)
{
    if((cityLevel[k] < 10)&&(cityLevel[8] < 5)){
        if(hero.getMoney() < costCity[k][cityLevel[k]]){
            return 1;
        }
        hero.addMoney(-costCity[k][cityLevel[k]]);
        cityLevel[k] += 1;
        refresh();
        bool l = true;
        Item c;
        c.create(0,0,0,0,0,nullName,new stub,0);
        switch (k) {
        case 1:
            hero.addSpellPoint(2);
            break;
        case 2:
            for(int i = 0; i < hero.warehouse.getLine();i++){
                for(int j = 0; j < hero.warehouse.getColumn();j++){
                    if((hero.warehouse.getCell(i,j).getName() == "close")&&(l)){
                        hero.warehouse.setCell(i,j,c);
                        l = false;
                    }
                }
            }
            break;
        case 4:
            hero.addStatsPoint(3);
            break;
        }
        if(k == 8){
            if(cityLevel[k] >= 6){
                return 3;
            }
        }
        if(cityLevel[k] >= 10){
            return 3;
        }
        return 0;
    }
    return 2;
}

int Game::getCityLevel(int i)
{
    return cityLevel[i];
}

int Game::hospital()
{
    if(hero.getMoney() < -costHos){
        return 1;
    }
    if(hero.stats.getHP() == hero.stats.getMaxHP()){
        return 2;
    }
    hero.stats.addHP(hero.stats.getMaxHP());
    hero.addMoney(-costHos);
    return 0;
}

int Game::temple()
{
    if(hero.getMoney() < costTemple){
        return 1;
    }
    if(hero.stats.getMP() == hero.stats.getMaxMP()){
        return 2;
    }
    hero.stats.addMP(hero.stats.getMaxMP());
    hero.addMoney(-costTemp);
    return 0;
}

int Game::repairs(int row, int column)
{
    Item c;
    if(hero.getMoney() < costRepairs){
        return 1;
    }

    switch (row) {
    case 0:
        switch (row + column) {
        case 0:
            if(hero.equip.getHand().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityHand(getCityLevel(7) * 5);
            break;
        case 1:
            if(hero.equip.getPants().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityPants(getCityLevel(7) * 5);
            break;
        case 2:
            if(hero.equip.getTorso().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityTorso(getCityLevel(7) * 5);
            break;
        case 3:
            if(hero.equip.getGloves().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityGloves(getCityLevel(7) * 5);
            break;
        }
        break;
    case 1:
        switch (row + column) {
        case 1:
            if(hero.equip.getHelmet().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityHelmet(getCityLevel(7) * 5);
            break;
        case 2:
            if(hero.equip.getOneRing().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityOneRing(getCityLevel(7) * 5);
            break;
        case 3:
            if(hero.equip.getTwoRing().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityTwoRing(getCityLevel(7) * 5);
            break;
        case 4:
            if(hero.equip.getFootwear().getDurability() == 100){
                return 2;
            }
            hero.equip.addDurabilityFootwear(getCityLevel(7) * 5);
            break;
        }
        break;
    }
    std::cout << hero.equip.getTorso().getDurability();
    return 0;
}

int Game::getCostHos() const
{
    return costHos;
}

void Game::setCostHos(int value)
{
    costHos = value;
}

void Game::refresh()
{
    costHos = round(costHospital * (1 - 0.1 * cityLevel[0]));
    costTemp = round(costTemple * (1 - 0.1 * cityLevel[5]));
}

int Game::getCostTemp() const
{
    return costTemp;
}

void Game::setCostTemp(int value)
{
    costTemp = value;
}

int Game::getMoneyBank() const
{
    return moneyBank;
}

void Game::setMoneyBank(int value)
{
    moneyBank = value;
}

bool Game::getTreeVisible(int a)
{
    return treeVisible[a];
}

int Game::getCostCity(int k)
{
    return costCity[k][cityLevel[k]];
}

void Game::createDunge()
{
    int n = random(minRoom,maxRoom);
    for(int i = 1; i < n; i++){
        if(chance(55)){//бой
            dunge[i] = 1;
        }else{
            if(chance(15)){//сокровище
                dunge[i] = 2;
            }else{
                if(chance(12)){//ловушка
                    dunge[i] = 3;
                }else
                    if(chance(20)){
                        dunge[i] = 4;//хорошее событие
                    }else
                        dunge[i] = 5;//нейтральное событие,пустая комната
            }
        }
    }
    dunge[n] = 9;
    dunge[n+1] = 10;
    roomNumber = 0;
    dungeLevel = hero.stats.getLevel();
}

void Game::createRoom()
{
    int n;
    double value;
    Item a;
    switch (dunge[roomNumber]) {
    case 0:
        n = random(0,3);
        switch (n) {
        case 0:
            emit textOut("вы вошли в старинный склеп, что же вас ждёт дальше?");
            roomImage = "crypt";
            break;
        case 1:
            emit textOut("вы вошли в подземелье, что же вас ждёт дальше?");
            roomImage = "dungeon";
            break;
        case 2:
            emit textOut("вы вышли на погост, что же вас ждёт дальше?");
            roomImage = "churchyard";
            break;
        case 3:
            emit textOut("вы вошли в старинный замок, что же вас ждёт дальше?");
            roomImage = "dungeon";
            break;
        }
        emit textOut("\n");
        checkRoom = 1;
        break;
    case 1:
        NPC.createNPC(hero.stats.getLevel());
        //genMonster();
        checkRoom = 0;
        emit textOut("на вас напал " + NPC.getName());
        emit textOut("\n");
        break;

    case 2:
        if(chance(15)){
            a = loot.generation(hero.stats.getLevel(),5);
            emit textOut("посреди комнаты лежит труп вашего предшественика,внимательно оглядевшись вы нашли " + a.getName());
            hero.bag.addItem(a);
        }else{
            if(chance(45)){
                a = loot.generation(hero.stats.getLevel(),3);
                emit textOut("посреди комнаты лежит труп вашего предшественика,внимательно оглядевшись вы нашли " + a.getName());
                hero.bag.addItem(a);
            }else{
                if(chance(80)){
                    a = loot.generation(hero.stats.getLevel(),1);
                    emit textOut("посреди комнаты лежит труп вашего предшественика,внимательно оглядевшись вы нашли " + a.getName());
                    hero.bag.addItem(a);
                }else{
                    emit textOut("посреди комнаты лежит труп вашего предшественика, внимательно оглядевшись вы заметили надпись рядом с телом 'ОПАСНОСТЬ', решив не рисковать вы уходите как можно быстрее ");
                }
            }
        }
        emit textOut("\n");
        roomImage = "hero’s corpse";
        checkRoom = 1;
        break;

    case 3:
        if(chance(hero.stats.getEvasion())){
            emit textOut("благодаря своей ловкости вы смогли увернуться от ловушки");
        }else{
            value = round(20 * (double)(hero.stats.getMaxHP()/100));
            emit textOut("вы попали в ловушку! получено " + QString::number(value) + " урона");
            hero.stats.addHP(-value);
        }
        roomImage = "trap";
        emit textOut("\n");
        checkRoom = 1;
        break;
    case 4:
        n = random(0,2);
        switch (n) {
        case 0:
            emit textOut("вы нашли целебный источник, испив из него вы полность востанавливаете свои силы");
            hero.stats.addHP(hero.stats.getMaxHP());
            hero.stats.addMP(hero.stats.getMaxMP());
            roomImage = "healing spring";
            break;
        case 1:
            emit textOut("вы нашли горсть окровавленых монет");
            value = random(5,50);
            emit textOut("полученно " + QString::number(value) + " монет");
            roomImage = "money";
            break;
        case 2:
            emit textOut("вы нашли костёр на котором кто-то готовил обед, не найдя ни кого рядом вы решаете его съесть");
            value = round(35 * hero.stats.getMaxHP()/100);
            hero.stats.addHP(value);
            emit textOut("вы востановили " + QString::number(value) + " здоровья");
            roomImage = "campfire";
            break;
        }
        emit textOut("\n");
        checkRoom = 1;
        break;
    case 5:
        emit textOut("кажется здесь нет ничего интересного");
        emit textOut("\n");
        roomImage = "empty room";
        checkRoom = 1;
        break;
    case 9:
        emit textOut("вы встретили монстра охраняющего сокровища этих проклятых мест");
        NPC.createBoss(hero.stats.getLevel());
        checkRoom = 0;
        emit textOut("на вас напал " + NPC.getName());
        emit textOut("\n");

        break;
    case 10:
        roomImage = "treasure";
        emit textOut("вы нашли сокровищницу!");
        checkRoom = 0;
        int k = random(10* hero.stats.getLevel(),18 * hero.stats.getLevel());
        hero.addMoney(k);
        emit textOut("найдено " + QString::number(k) + " золота");

        k = random(10* hero.stats.getLevel(),30 * hero.stats.getLevel());
        hero.addExp(k);
        emit textOut("полученно " + QString::number(k) + " опыта");
        if(chance(20)){
            a = loot.generation(hero.stats.getLevel(),5);
            hero.bag.addItem(a);
            emit textOut("вы нашли " + a.getName() + ".");
            emit refreshCell(hero.bag.getModifiedI(),hero.bag.getModifiedJ());
        }else{
            if(chance(45)){
                a = loot.generation(hero.stats.getLevel(),3);
                hero.bag.addItem(a);
                emit textOut("вы нашли " + a.getName() + ".");
                emit refreshCell(hero.bag.getModifiedI(),hero.bag.getModifiedJ());
            }else{
                if(chance(90)){
                    a = loot.generation(hero.stats.getLevel(),1);
                    hero.bag.addItem(a);
                    emit textOut("вы нашли " + a.getName() + ".");
                    emit refreshCell(hero.bag.getModifiedI(),hero.bag.getModifiedJ());
                }
            }
        }
        break;
    }
}

int Game::getRoom()
{
    return dunge[roomNumber];
}

void Game::nextRoom()
{
    roomNumber += 1;
    hero.stats.regeneration();
}

QString Game::getRoomImage() const
{
    return roomImage;
}

void Game::setRoomImage(const QString &value)
{
    roomImage = value;
}

int Game::getCheckRoom() const
{
    return checkRoom;
}

void Game::initNPC(int level)
{
    NPC.createNPC(level);
}

int Game::fight(int n) // 0- вне боя 1-бой 2- победа 3-поражение
{
    if(NPC.stats.getHP() <= 0){
        return 0;
    }

    if(chance(NPC.stats.getEvasion())){
        emit textOut("противник оказался проворнее и ушёл от вашей атаки");
    }else{
        hero.spell[n]->effect(NPC,hero); //hero attack
        emit textOut(hero.spell[n]->text);
        if (NPC.stats.getHP() <= 0){
            win();
            return 2;
        }
    }

    if(chance(hero.stats.getEvasion())){
        emit textOut("вы оказались проворнее и ушли от атаки противника");
    }else{
        NPC.spell->effect(NPC,hero); //NPC attack
        emit textOut(NPC.spell->text);
        if(hero.stats.getHP() <= 0){
            lose();
            return 3;
        }
    }
    emit textOut("\n");
    hero.stats.regeneration();
    return 1;
}

void Game::addSpell(Spells* sp)
{
    int k = 0;

    for (int i = 1; i < 8; i++){
        if ((hero.spellNumb[i] == 0)&&(k == 0)){
            hero.spell[i] = sp;
            hero.spellNumb[i] = 1;
            k = 1;
        }
    }
}

void Game::win()
{
    int gold  = hero.stats.getLevel() * 5;
    emit textOut("вы победили");
    emit textOut("вы получили " + QString::number(NPC.getExp()) + " опыта");
    emit textOut("вы получили " + QString::number(gold) + " золота");
    hero.addMoney(gold);
    Item a = loot.generation(hero.stats.getLevel(),1);
    if(chance(20)){
        hero.bag.addItem(a);
        emit textOut("вам выпал " + a.getName() + ".");
    }
    hero.addExp(NPC.getExp());
    checkRoom = 1;
    emit textOut("\n");
}

void Game::lose()
{
    emit textOut("вы проиграли");
    emit rebirth();
}

void Game::usePoision(int j)
{
    Item a;
    a = hero.belt.getCell(0,j);
    a.getEff()->effect(NPC,hero);
    a.addQuantity(-1);
    if(a.getQuantity() == 0){
        a.create(0,0,0,0,0,"",new stub,0);
        hero.belt.setCell(0,j,a);
        hero.belt.setCheck(0,j,0);
    }else{
    hero.belt.setCell(0,j,a);
    }
}

bool Game::escape()
{
    if(chance(hero.stats.getEscapeChance())){
        return true;
    }
    return false;
}

int Game::enemyStrike()
{
    if(chance(hero.stats.getEvasion())){
        emit textOut("вы оказались проворнее и ушли от атаки противника");
    }else{
        NPC.spell->effect(NPC,hero); //NPC attack
        emit textOut(NPC.spell->text);
        if(hero.stats.getHP() <= 0){
            lose();
            return 1;
        }
    }
    emit textOut("\n");
    return 0;
}

void Game::genMonster()
{
    MainStats stats;
    QString value;
    QString name;
    int k,k2;
    double d;
    int n = random(0,monsters.size() - 1);
    name = monsters[n].mid(0,30);
    name = name.trimmed();

    value = monsters[n].mid(31,2);
    k = value.toInt();
    stats.setStr(k);

    value = monsters[n].mid(34,2);
    k = value.toInt();
    stats.setAgi(k);

    value = monsters[n].mid(37,2);
    k = value.toInt();
    stats.setInt(k);

    value = monsters[n].mid(40,2);
    k = value.toInt();
    stats.setLevel(k);

    value = monsters[n].mid(43,4);
    d = value.toDouble();
    stats.setCrit(d);

    value = monsters[n].mid(48,2);
    k = value.toInt();
    stats.setCritChance(k);

    value = monsters[n].mid(51,2);
    k = value.toInt();
    stats.setEvasion(k);//

    value = monsters[n].mid(54,4);
    d = value.toDouble();
    stats.setCritMagic(d);

    value = monsters[n].mid(113,2);
    k = value.toInt();
    stats.setCritMagicChance(k);

    value = monsters[n].mid(59,4);
    d = value.toDouble();
    stats.setFireResistance(d);

    value = monsters[n].mid(64,4);
    d = value.toDouble();
    stats.setFireIncrease(d);

    value = monsters[n].mid(69,4);
    d = value.toDouble();
    stats.setColdResistance(d);

    value = monsters[n].mid(74,4);
    d = value.toDouble();
    stats.setColdIncrease(d);

    value = monsters[n].mid(79,4);
    d = value.toDouble();
    stats.setPoisonResistance(d);

    value = monsters[n].mid(84,4);
    d = value.toDouble();
    stats.setPoisonIncrease(d);

    value = monsters[n].mid(89,4);
    k = value.toInt();
    stats.setBaseHP(k);

    value = monsters[n].mid(94,4);
    k = value.toInt();
    stats.setBaseMP(k);

    value = monsters[n].mid(99,4);
    k = value.toInt();
    stats.setArmor(k);

    value = monsters[n].mid(103,4);
    k = value.toInt();
    stats.setAttack(k);

    value = monsters[n].mid(107,2);
    k = value.toInt();
    value = monsters[n].mid(1010,2);
    k2 = value.toInt();

    NPC.createMonster(name,addSpellMonster(k,k2),stats);
}

Spells *Game::addSpellMonster(int n, int l)
{
    Spells *a;
    switch (n) {
    case 0:
        a = new baseAttackNPC;
        break;
    case 1:
        a = new attackSwordNPC;
        break;
    case 2:
        a = new attackDaggerNPC;
        break;
    case 3:
        a = new vampirism;
        break;
    case 4:
        a = new fireAttack;
        break;
    case 5:
        a = new poisonAttack;
        break;
    }
    a->level = l;
    a->closed = 0;
    return a;
}

void Game::characterLeveling(int a)
{
    switch (a) {
    case 1:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(0);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[1] = true;
                    treeVisible[2] = true;
                }
            }
        }
        break;
    case 2:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseAttack(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[3] = true;
                }
            }
        }
        break;
    case 3:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addEscapeChance(5);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[3] = true;
                }
            }
        }
        break;
    case 4:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(1);
                level[a] += 1;
                if(level[a] == 1){
                    treeVisible[4] = true;
                }
            }
        }
        break;
    case 5:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addCrit(0.15);
                hero.stats.addCritChance(3);
                hero.stats.addEvasion(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[5] = true;
                    treeVisible[6] = true;
                }
            }
        }
        break;
    case 6:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addCrit(0.10);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[7] = true;
                }
            }
        }
        break;
    case 7:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addEvasion(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[8] = true;
                }
            }
        }
        break;
    case 8:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addCritChance(3);
                level[a] += 1;
                if(level[a] == 3){
                    treeVisible[9] = true;
                }
            }
        }
        break;
    case 9:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addPoisonIncrease(0.1);
                hero.stats.addPoisonResistance(0.1);
                level[a] += 1;
                if(level[a] == 3){
                    treeVisible[10] = true;
                }
            }
        }
        break;
    case 10:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(2);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[11] = true;
                }
            }
        }
        break;
    case 11:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[11] = true;
                }
            }
        }
        break;
    case 12:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addCrit(0.50);
                level[a] += 1;
            }
        }
        break;
    case 13:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(4);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[13] = true;
                    treeVisible[14] = true;
                }
            }
        }
        break;
    case 14:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseMP(15);
                level[a] += 1;
                if((level[a] + level[a + 1]) >= 3){
                    treeVisible[15] = true;
                }
            }
        }
        break;
    case 15:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addRegMP(3);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 3){
                    treeVisible[15] = true;
                }
            }
        }
        break;
    case 16:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addHealPower(0.15);
                hero.stats.addManaPower(0.15);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[16] = true;
                    treeVisible[17] = true;
                }
            }
        }
        break;
    case 17:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(5);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[18] = true;
                }
            }
        }
        break;
    case 18:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(6);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[19] = true;
                }
            }
        }
        break;
    case 19:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addFireIncrease(0.1);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[20] = true;
                }
            }
        }
        break;
    case 20:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addColdIncrease(0.1);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[21] = true;
                }
            }
        }
        break;
    case 21:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addFireResistance(0.1);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 2){
                    treeVisible[22] = true;
                }
            }
        }
        break;
    case 22:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addColdResistance(0.1);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 2){
                    treeVisible[22] = true;
                }
            }
        }
        break;
    case 23:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addColdResistance(0.05);
                hero.stats.addFireResistance(0.05);
                hero.stats.addColdIncrease(0.05);
                hero.stats.addFireIncrease(0.05);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[23] = true;
                }
            }
        }
        break;
    case 24:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(7);
                level[a] += 1;
            }
        }
        break;
    case 25:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(8);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[25] = true;
                    treeVisible[26] = true;
                }
            }
        }
        break;
    case 26:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseArmor(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[27] = true;
                }
            }
        }
        break;
    case 27:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addRegHP(3);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[28] = true;
                }
            }
        }
        break;
    case 28:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addFireResistance(0.04);
                hero.stats.addColdResistance(0.04);
                level[a] += 1;
                if((level[a] + level[a + 1]) >= 3){
                    treeVisible[29] = true;
                }
            }
        }
        break;
    case 29:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseHP(10);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 3){
                    treeVisible[29] = true;
                }
            }
        }
        break;
    case 30:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(9);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[30] = true;
                    treeVisible[31] = true;
                }
            }
        }
        break;
    case 31:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addStr(4);
                level[a] += 1;
                if((level[a] + level[a + 1]) >= 3){
                    treeVisible[32] = true;
                }
            }
        }
        break;
    case 32:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addAgi(4);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 3){
                    treeVisible[32] = true;
                }
            }
        }
        break;
    case 33:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(10);
                level[a] += 1;
                if(level[a] == 2){
                    treeVisible[33] = true;
                    treeVisible[34] = true;
                }
            }
        }
        break;
    case 34:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseArmor(6);
                hero.stats.addRegHP(2);
                level[a] += 1;
                if((level[a] + level[a + 1]) >= 3){
                    treeVisible[35] = true;
                }
            }
        }
        break;
    case 35:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                hero.stats.addBaseHP(20);
                hero.stats.addRegHP(5);
                level[a] += 1;
                if((level[a] + level[a - 1]) >= 3){
                    treeVisible[35] = true;
                }
            }
        }
        break;
    case 36:
        if (level[a] < maxLevel){
            if (hero.getSpellPoint() > 0){
                hero.addSpellPoint(-1);
                spellUp(11);
                level[a] += 1;
            }
        }
        break;
    }
}

void Game::addBaseItem()
{
    Item a;
    a.create(0,0,0,0,0,"",new stub,0);
    hero.equip.setBelt(a);
    hero.equip.setTorso(a);
    hero.equip.setPants(a);
    hero.equip.setGloves(a);
    hero.equip.setHelmet(a);
    hero.equip.setOneRing(a);
    hero.equip.setTwoRing(a);
    hero.equip.setFootwear(a);
    hero.equip.setHand(a);
}

void Game::spellUp(int k)
{
    if(hero.spellPlayer[k]->closed == 1){
        hero.spellPlayer[k]->closed = 0;
        hero.spellPlayer[k]->used = 1;
        addSpell(hero.spellPlayer[k]);
    }   else {
        hero.spellPlayer[k]->level += 1;
        if (hero.spellPlayer[k]->used == 0){
            addSpell(hero.spellPlayer[k]);
        }
    }
}

void Game::deleteSpell(int i)
{
    hero.spellNumb[i] = 0;
    hero.spell[i] = new stub;
}

void Game::changeOfItem(int i, int j)
{
    if(salesMode){
        sellItem(i,j);
    }else{
         Item a,b;
         b.create(0,0,0,0,0,nullName,new stub,0);
         a = hero.bag.getCell(i,j);
        if(warehouseMode){
            if(hero.warehouse.vacancySearch()){
            hero.warehouse.addItem(a);
            hero.bag.setModifiedIJ(i,j);
            hero.bag.setCell(i,j,b);
            hero.bag.setCheck(i,j,0);
            }
        }
        else{
                    switch (a.getType()) {
                    case 1:
                        if(hero.equip.getHand().getName() == ""){
                            hero.equip.setHand(a);
                            hero.spell[0] = a.getEff();
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 2:

                        break;
                    case 3:
                        if(hero.equip.getHelmet().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getHelmet()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setHelmet(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 4:
                        if(hero.equip.getTorso().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getTorso()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setTorso(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 5:
                        if(hero.equip.getPants().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getPants()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setPants(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 6:
                        if(hero.equip.getFootwear().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getFootwear()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setFootwear(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 7:
                        if(hero.equip.getGloves().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getGloves()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setGloves(a);
                            hero.belt.setColumn(a.getValue());
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 8:
                        if(hero.equip.getOneRing().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getOneRing()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setOneRing(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 9:
                        if(hero.equip.getTwoRing().getName() == ""){
                            hero.bag.setCell(i,j,hero.equip.getTwoRing()) ;
                            if(a.effect->closed){
                                a.effect->used = 0;
                                a.effect->effect(NPC,hero);
                            }
                            hero.equip.setTwoRing(a);
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    case 10:
                        if(hero.belt.vacancySearch()){
                            hero.belt.addItem(a);
                            emit refreshBelt(hero.belt.getModifiedI(),hero.belt.getModifiedJ());
                            hero.bag.setModifiedIJ(i,j);
                            hero.bag.setCell(i,j,b);
                            hero.bag.setCheck(i,j,0);
                        }
                        break;
                    }

        }
    }

}

void Game::changeOfPoision(int j)
{
    if(hero.belt.getCell(0,j).getQuantity() != 0){
        if(hero.bag.vacancySearch()){
            Item b;
            b.create(0,0,0,0,0,"пусто",new stub,0);
            hero.bag.addItem(hero.belt.getCell(0,j));
            hero.belt.setCell(0,j,b);
            hero.belt.setCheck(0,j,0);
            emit refreshBelt(hero.belt.getModifiedI(),hero.belt.getModifiedJ());
        }
    }
}

void Game::sellItem(int i, int j)
{
    hero.addMoney(percent(30 + hero.stats.getOratory(),hero.bag.getCell(i,j).getCost()));
    hero.bag.deleteItem(i,j);
}

void Game::storeRefresh()
{
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            store.setCell(i,j,loot.generation(hero.stats.getLevel(),cityLevel[8] + 1));
        }
    }

    if(cityLevel[6] != 0){
        Item c;
        int level;

        level = random(1,cityLevel[6]);
        c.create(level * 40,10,0,100,1,"healing potion",new heal,0);
        c.getEff()->level = level;
        store.setCell(random(0,1),random(0,4),c);

        level = random(1,cityLevel[6]);
        c.create(level * 40,10,0,100,1,"mana potion",new manaRecovery,0);
        c.getEff()->level = level;
        store.setCell(random(0,1),random(0,4),c);
    }
}

int Game::storeBuy()
{
    if(!hero.bag.vacancySearch()){
        return 1;
    }

    if(hero.getMoney() < store.getCell(store.getModifiedI(),store.getModifiedJ()).getCost()){
        return 2;
    }
    hero.addMoney(-(store.getCell(store.getModifiedI(),store.getModifiedJ()).getCost()));
    hero.bag.addItem(store.getCell(store.getModifiedI(),store.getModifiedJ()));
    return 0;
}

void Game::createPers(QString _name, int _str, int _agi, int _int, int pers)
{
    Item a;
    hero.stats.zeroing();
    hero.setExp(0);

    hero.setStatPoint(0);
    hero.setSpellPoint(0);

    hero.setName(_name);
    hero.stats.setStr(_str);
    hero.stats.setAgi(_agi);
    hero.stats.setInt(_int);
    hero.setPers(pers);
    hero.stats.addHP(hero.stats.getMaxHP());

    hero.addSpellPoint(cityLevel[1]);
    hero.addStatsPoint(cityLevel[4] * 4);

    for(int i = 0; i < hero.spellPlayer.size(); i++){
        hero.spellPlayer[i]->used = 0;
        hero.spellPlayer[i]->closed = 1;
        hero.spellPlayer[i]->level = 1;
        hero.spellPlayer[i]->coolDown = 0;
    }


    for (int i = 1; i < 8; i++){
        hero.spellNumb[i] = 0;
        hero.spell[i] = new stub;
        hero.spell[i]->coolDown = -1;
    }
    hero.spell[0] = new baseAttack;
    addBaseItem();

    for (int i = 0; i < 37; i++){
        level[i] = 0;
        treeVisible[i] = false;
    }

    a.create(0,0,0,0,0,nullName,new stub,0);
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 5; j++){
            hero.bag.setCell(i,j,a);
        }
    }

    switch (pers) {
    case 0:
        hero.setMoney(500);
        hero.addStatsPoint(4);
        break;
    case 1:
        hero.setMoney(150);
        hero.stats.addBaseMP(+30);
        hero.stats.addInt(4);

        a.create(100,1,1,100,1,"Посох",new fireballStaff,1);
        a.effect->level = 1;
        hero.bag.addItem(a);
        changeOfItem(0,0);
        break;
    case 2:
        hero.setMoney(100);
        a.create(105,4,8,100,1,"Броня",new critChance,1);
        a.effect->level = 2;
        hero.bag.addItem(a);
        hero.addStatsPoint(4);
        changeOfItem(0,0);
        a.create(55,6,3,100,1,"Ботинки",new health,1);
        a.effect->level = 1;
        hero.bag.addItem(a);
        changeOfItem(0,0);
        break;
    case 3:
        hero.setMoney(150);
        hero.stats.addBaseHP(20);
        hero.stats.addStr(4);
        a.create(100,1,6,100,1,"Счастливая кирка",new luckyHit,1);
        a.effect->level = 2;
        hero.bag.addItem(a);
        changeOfItem(0,0);
        break;
    case 4:
        hero.setMoney(150);
        hero.stats.addCrit(0.20);
        hero.stats.addCritChance(10);
        hero.stats.addEvasion(10);
        a.create(95,1,7,100,1,"Кинжал убийцы",new attackDagger,2);
        a.effect->level = 2;
        hero.bag.addItem(a);
        changeOfItem(0,0);
        break;
    }
}

int Game::takeOffSubject(int a)
{
    if(!hero.bag.vacancySearch()){
        return 1;
    }

    Item c;
    c.create(0,0,0,0,0,"",new stub,0);

    switch (a) {
    case 1:
        if(hero.equip.getHand().getName() == ""){
            return 2;
        }
        hero.bag.addItem(hero.equip.getHand());
        hero.spell[0] = new baseAttack;
        hero.equip.setHand(c);
        break;
    case 2:

        break;
    case 3:
        if(hero.equip.getHelmet().getName() == ""){
            return 2;
        }
        hero.equip.getHelmet().effect->used = 1;
        hero.equip.getHelmet().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getHelmet());
        hero.equip.setHelmet(c);
        break;
    case 4:
        if(hero.equip.getTorso().getName() == ""){
            return 2;
        }
        hero.equip.getTorso().effect->used = 1;
        hero.equip.getTorso().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getTorso());
        hero.equip.setTorso(c);
        break;
    case 5:
        if(hero.equip.getPants().getName() == ""){
            return 2;
        }
        hero.equip.getPants().effect->used = 1;
        hero.equip.getPants().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getPants());
        hero.equip.setPants(c);
        break;
    case 6:
        if(hero.equip.getFootwear().getName() == ""){
            return 2;
        }
        hero.equip.getFootwear().effect->used = 1;
        hero.equip.getFootwear().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getFootwear());
        hero.equip.setFootwear(c);
        break;
    case 7:
        if(hero.equip.getGloves().getName() == ""){
            return 2;
        }
        for(int i = 0; i < hero.belt.getColumn(); i++){
            if(hero.belt.getCell(0,i).getType() != 0){
                hero.bag.addItem(hero.belt.getCell(0,i));
                hero.belt.setCell(0,i,c);
                hero.belt.setCheck(0,i,0);
                emit refreshBelt(0,i);
                emit refreshCell(hero.bag.getModifiedI(),hero.bag.getModifiedJ());
            }
        }

        hero.equip.getGloves().effect->used = 1;
        hero.equip.getGloves().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getGloves());
        hero.equip.setGloves(c);
        hero.belt.setColumn(1);
        break;
    case 8:
        if(hero.equip.getOneRing().getName() == ""){
            return 2;
        }
        hero.equip.getOneRing().effect->used = 1;
        hero.equip.getOneRing().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getOneRing());
        hero.equip.setOneRing(c);
        break;
    case 9:
        if(hero.equip.getTwoRing().getName() == ""){
            return 2;
        }
        hero.equip.getTwoRing().effect->used = 1;
        hero.equip.getTwoRing().effect->effect(NPC,hero);
        hero.bag.addItem(hero.equip.getTwoRing());
        hero.equip.setTwoRing(c);
        break;
    }
    return 0;

}

void Game::changeWarehouse(int i, int j)
{
            if(hero.bag.vacancySearch()){
                Item b;
                b.create(0,0,0,0,0,"пусто",new stub,0);
                hero.bag.addItem(hero.warehouse.getCell(i,j));
                hero.warehouse.setCell(0,j,b);
                hero.warehouse.setCheck(0,j,0);
            }
}
