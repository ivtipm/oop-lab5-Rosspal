#include "maintab.h"
#include "ui_maintab.h"

mainTab::mainTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::mainTab)
{
    ui->setupUi(this);
    dir = QDir::currentPath();

    refresh();

    Game *h ;
    h = &g;
    dunge->initDungeon(h);
    dunge->refresh();

    for (int i = 0; i < g.hero.bag.getLine(); i++){
        for (int j = 0; j < g.hero.bag.getColumn(); j++){
            ui->tableWidget->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g.hero.bag.getCell(i,j).getName() + ".png"));
        }
    }

    for (int i = 0; i < g.store.getLine(); i++){
        for (int j = 0; j < g.store.getColumn(); j++){
            ui->tableStore->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g.store.getCell(i,j).getName() + ".png"));
        }
    }

    for (int i = 0; i < g.hero.belt.getLine(); i++){
        for (int j = 0; j < g.hero.belt.getColumn(); j++){
            ui->belt->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g.hero.belt.getCell(i,j).getName() + ".png"));
        }
    }

    for (int i = 0; i < g.hero.warehouse.getLine(); i++){
        for (int j = 0; j < g.hero.warehouse.getColumn(); j++){
            ui->warehouse->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g.hero.warehouse.getCell(i,j).getName() + ".png"));
        }
    }

    ui->forge->setVisible(false);
    ui->ButtonRepairs->setVisible(false);
    ui->warehouse->setVisible(false);
    ui->warehouseRadioButton->setVisible(false);

    treeSpell.push_back(ui->spellButt_1);
    treeSpell.push_back(ui->spellButt_2);
    treeSpell.push_back(ui->spellButt_3);
    treeSpell.push_back(ui->spellButt_4);
    treeSpell.push_back(ui->spellButt_5);
    treeSpell.push_back(ui->spellButt_6);
    treeSpell.push_back(ui->spellButt_7);
    treeSpell.push_back(ui->spellButt_8);
    treeSpell.push_back(ui->spellButt_9);
    treeSpell.push_back(ui->spellButt_10);
    treeSpell.push_back(ui->spellButt_11);
    treeSpell.push_back(ui->spellButt_12);
    treeSpell.push_back(ui->spellButt_13);
    treeSpell.push_back(ui->spellButt_14);
    treeSpell.push_back(ui->spellButt_15);
    treeSpell.push_back(ui->spellButt_16);
    treeSpell.push_back(ui->spellButt_17);
    treeSpell.push_back(ui->spellButt_18);
    treeSpell.push_back(ui->spellButt_19);
    treeSpell.push_back(ui->spellButt_20);
    treeSpell.push_back(ui->spellButt_21);
    treeSpell.push_back(ui->spellButt_22);
    treeSpell.push_back(ui->spellButt_23);
    treeSpell.push_back(ui->spellButt_24);
    treeSpell.push_back(ui->spellButt_25);
    treeSpell.push_back(ui->spellButt_26);
    treeSpell.push_back(ui->spellButt_27);
    treeSpell.push_back(ui->spellButt_28);
    treeSpell.push_back(ui->spellButt_29);
    treeSpell.push_back(ui->spellButt_30);
    treeSpell.push_back(ui->spellButt_31);
    treeSpell.push_back(ui->spellButt_32);
    treeSpell.push_back(ui->spellButt_33);
    treeSpell.push_back(ui->spellButt_34);
    treeSpell.push_back(ui->spellButt_35);
    treeSpell.push_back(ui->spellButt_36);

    for (int i = 0; i < 36; i++) {
        connect(treeSpell[i],SIGNAL(clicked()),this,SLOT(leveling()));
        treeSpell[i]->setVisible(false);
    }
    treeSpell[0]->setVisible(true);
    treeSpell[12]->setVisible(true);
    treeSpell[24]->setVisible(true);


    connect(ui->hand,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->helmet,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->torso,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->pants,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->footwear,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->gloves,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->ringOne,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->ringTwo,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));

    connect(&g,SIGNAL(rebirth()),this,SLOT(rebirthMediator()));
    connect(&g,SIGNAL(refreshCell(int,int)),this,SLOT(refreshBag(int,int)));
    connect(&g,SIGNAL(refreshCell(int,int)),this,SIGNAL(refreshBagCell(int,int)));
    //connect(&g,SIGNAL(refreshStat(int,int)),this,SIGNAL(refreshBagCell(int,int)));
    connect(&g,SIGNAL(refreshBelt(int,int)),this,SLOT(refreshCellBelt(int,int)));
    connect(&g,SIGNAL(refreshBelt(int,int)),dunge,SLOT(refreshCellBelt(int,int)));

    connect(dunge,SIGNAL(changeScreen()),this,SLOT(returnToTheCity()));
    connect(dunge,SIGNAL(refreshBagCell(int,int)),this,SLOT(refreshBag(int,int)));
    connect(this,SIGNAL(refreshBagCell(int,int)),dunge,SLOT(refreshBag(int,int)));

    ui->buttOut->setStyleSheet("QPushButton{background: transparent;color: rgb(255, 255, 255);}");


}

mainTab::~mainTab()
{
    delete ui;
}

void mainTab::refresh()
{
    QString a;
    ui->healButton->setToolTip(QString::number(g.getCostHos()) + " монет");
    ui->manaButton->setToolTip(QString::number(g.getCostTemp()) + " монет");

    ui->hpBar->setMaximum(g.hero.stats.getMaxHP());
    ui->hpBar->setValue(g.hero.stats.getHP());

    ui->mpBar->setMaximum(g.hero.stats.getMaxMP());
    ui->mpBar->setValue(g.hero.stats.getMP());

    ui->labCr->setNum(g.hero.stats.getCrit());
    ui->labEv->setNum(g.hero.stats.getEvasion());
    ui->labHP->setNum(g.hero.stats.getHP());
    ui->labMP->setNum(g.hero.stats.getMP());                        // обновление персонажа
    ui->LabOC->setNum(g.hero.getSpellPoint());
    ui->labOX->setNum(g.hero.getStatPoint());

    ui->labAgi->setNum(g.hero.stats.getAgi());
    ui->labInt->setNum(g.hero.stats.getInt());
    ui->labStr->setNum(g.hero.stats.getStr());

    ui->labCrCh->setNum(g.hero.stats.getCritChance());
    ui->labLevel->setNum(g.hero.stats.getLevel());

    ui->labMC->setNum(g.hero.stats.getCritMagic());
    ui->labMCChance->setNum(g.hero.stats.getCritMagicChance());

    ui->labResFire->setNum(g.hero.stats.getFireResistance());
    ui->labIncFire->setNum(g.hero.stats.getFireIncrease());
    ui->labResCold->setNum(g.hero.stats.getColdResistance());
    ui->labIncCold->setNum(g.hero.stats.getColdIncrease());
    ui->labResPois->setNum(g.hero.stats.getPoisonResistance());
    ui->labIncPois->setNum(g.hero.stats.getPoisonIncrease());

    ui->labArmor->setNum(g.hero.stats.getBaseArmor() + g.hero.equip.getGeneralArmor());
    ui->labArmorInv->setNum(g.hero.stats.getBaseArmor() + g.hero.equip.getGeneralArmor());
    ui->labSword->setNum(g.hero.stats.getBaseAttack() + g.hero.equip.getGeneralAttack());
    ui->labSwordInv->setNum(g.hero.stats.getBaseAttack() + g.hero.equip.getGeneralAttack());

    ui->labRegHpMp->setText(QString::number(g.hero.stats.getRegenHP()) + "/" + QString::number(g.hero.stats.getRegenMP()));

    //сумка
    ui->tableWidget->item(g.hero.bag.getModifiedI(),g.hero.bag.getModifiedJ())->setIcon(QIcon(dir + "/image/Item/" +
                                                                                              g.hero.bag.getCell(g.hero.bag.getModifiedI(),g.hero.bag.getModifiedJ()).getName() +
                                                                                              ".png"));

    ui->tableWidget->item(g.hero.bag.getModifiedI(),g.hero.bag.getModifiedJ())->setToolTip(itemToolTip(g.hero.bag.getCell(g.hero.bag.getModifiedI(),g.hero.bag.getModifiedJ())));
    emit refreshBagCell(g.hero.bag.getModifiedI(),g.hero.bag.getModifiedJ());

    ui->belt->item(g.hero.belt.getModifiedJ(),g.hero.belt.getModifiedI())->setIcon(QIcon(dir + "/image/Item/" +
                                                                                         g.hero.belt.getCell(g.hero.belt.getModifiedI(),g.hero.belt.getModifiedJ()).getName() +
                                                                                         ".png"));

    ui->belt->item(g.hero.belt.getModifiedJ(),g.hero.belt.getModifiedI())->setToolTip(itemToolTip(g.hero.belt.getCell(g.hero.belt.getModifiedI(),g.hero.belt.getModifiedJ())) + g.hero.belt.getCell(g.hero.belt.getModifiedI(),g.hero.belt.getModifiedJ()).getEff()->name());

    ui->belt->resize(60,g.hero.belt.getColumn() * 60);


    ui->warehouse->item(g.hero.warehouse.getModifiedI(),g.hero.warehouse.getModifiedJ())->setIcon(QIcon(dir + "/image/Item/" + g.hero.warehouse.getCell(g.hero.warehouse.getModifiedI(),g.hero.warehouse.getModifiedJ()).getName() + ".png"));
    ui->warehouse->item(g.hero.warehouse.getModifiedI(),g.hero.warehouse.getModifiedJ())->setToolTip(itemToolTip(g.hero.warehouse.getCell(g.hero.warehouse.getModifiedI(),g.hero.warehouse.getModifiedJ())) + g.hero.warehouse.getCell(g.hero.warehouse.getModifiedI(),g.hero.warehouse.getModifiedJ()).getEff()->name());


    //снаряжение

    ui->handLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getHand().getName() + ".png");
    ui->hand->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getHand()));
    ui->forge->item(0,0)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getHand().getName() + ".png"));

    ui->helmetLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getHelmet().getName() + ".png");
    ui->helmet->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getHelmet()));
    ui->forge->item(1,0)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getHelmet().getName() + ".png"));

    ui->torsoLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getTorso().getName() + ".png");
    ui->torso->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getTorso()));
    ui->forge->item(0,2)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getTorso().getName() + ".png"));

    ui->pantsLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getPants().getName() + ".png");
    ui->pants->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getPants()));
    ui->forge->item(0,1)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getPants().getName() + ".png"));

    ui->footwearLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getFootwear().getName() + ".png");
    ui->footwear->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getFootwear()));
    ui->forge->item(1,3)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getFootwear().getName() + ".png"));

    ui->glovesLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getGloves().getName() + ".png");
    ui->gloves->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getGloves()));
    ui->forge->item(0,3)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getGloves().getName() + ".png"));

    ui->ringTwoLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getTwoRing().getName() + ".png");
    ui->ringTwo->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getTwoRing()));
    ui->forge->item(1,2)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getTwoRing().getName() + ".png"));

    ui->ringOneLabel->setPixmap(dir + "/image/Item/" + g.hero.equip.getOneRing().getName() + ".png");
    ui->ringOne->item(0,0)->setToolTip(itemToolTip(g.hero.equip.getOneRing()));
    ui->forge->item(1,1)->setIcon(QIcon(dir + "/image/Item/" + g.hero.equip.getOneRing().getName() + ".png"));

    ui->gold->setNum(g.hero.getMoney());
    ui->myGold->setNum(g.hero.getMoney());

    ui->portrait->setPixmap(dir + "/image/portrait/portrait" + QString::number(g.hero.getPers()) + ".jpg");
    ui->portrait1->setPixmap(dir + "/image/portrait/portrait" + QString::number(g.hero.getPers()) + ".jpg");
    ui->name->setText(g.hero.getName());


    ui->hospitalButton->setText(QString::number(g.getCostCity(0)));
    ui->templeButton->setText(QString::number(g.getCostCity(5)));
    ui->libraryButton->setText(QString::number(g.getCostCity(1)));
    ui->warehouseButton->setText(QString::number(g.getCostCity(2)));
    ui->bankButton->setText(QString::number(g.getCostCity(3)));
    ui->arenaButton->setText(QString::number(g.getCostCity(4)));
    ui->herbalistButton->setText(QString::number(g.getCostCity(6)));
    ui->forgeButton->setText(QString::number(g.getCostCity(7)));
    ui->storeButton->setText(QString::number(g.getCostCity(8)));
}

void mainTab::refreshBag()
{
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 5; j++){
            ui->tableWidget->item(i,j)->setIcon(QIcon(dir + "/image/Item/" +g.hero.bag.getCell(i,j).getName() + ".png"));
            ui->tableWidget->item(i,j)->setToolTip(itemToolTip(g.hero.bag.getCell(i,j)) + g.hero.bag.getCell(i,j).getEff()->name());
            emit refreshBagCell(i,j);
        }
    }
}

void mainTab::takeOffSubject(int i,int j)
{
    QTableWidget *cell = (QTableWidget *)sender();

    switch (g.takeOffSubject(cell->item(0,0)->text().toInt())){
    case 1:
        QMessageBox::information(0, "ошибка", "недостаточно места");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "тут на вас ничего не надето");
        break;
    case 0:
        refresh();
        break;
    }
}

void mainTab::createPers(QString _name, int _str, int _agi, int _int, int pers)
{
    g.createPers(_name,_str,_agi,_int,pers);
    for (int i = 0; i < 36; i++) {
        treeSpell[i]->setVisible(false);
    }
    treeSpell[0]->setVisible(true);
    treeSpell[12]->setVisible(true);
    treeSpell[24]->setVisible(true);
    refresh();
}

QString mainTab::itemToolTip(Item a)
{
    return ( a.getName() +"\n"+
             "урон/броня-" + QString::number(a.getValue()) + "\n"+
             "качество-" + QString::number(a.getDurability()) + "%\n"+
             "количество-" + QString::number(a.getQuantity()) + "\n"+
             "цена-" + QString::number(a.getCost()) + "\n" +
             a.getEff()->name() + "\n" +
             a.getEff()->description());
}

void mainTab::refreshCellBelt(int i, int j)
{
    ui->belt->item(j,i)->setIcon(QIcon(":/new/item/image/Item/" + g.hero.belt.getCell(i,j).getName() + ".png"));
    ui->belt->item(j,i)->setToolTip(itemToolTip(g.hero.belt.getCell(i,j)));
}

void mainTab::rebirthMediator()
{
    dunge->close();
    emit rebirth();
}

void mainTab::returnToTheCity()
{
    dunge->close();
    this->setVisible(true);
    refresh();
}

void mainTab::refreshBag(int i, int j)
{
    QString a;

    ui->tableWidget->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g.hero.bag.getCell(i,j).getName() +
                                              ".png"));
    a = itemToolTip(g.hero.bag.getCell(i,j));

    ui->tableWidget->item(i,j)->setToolTip(a);
}

void mainTab::leveling()
{
    QPushButton *button = (QPushButton *)sender();
    g.characterLeveling(button->text().toInt());

    for (int i = 0; i < 36; i++) {
        if(g.getTreeVisible(i)){
            treeSpell[i]->setVisible(true);
        }
    }

    refresh();
}

void mainTab::on_addStr_clicked()
{
    if (g.hero.getStatPoint() > 0){
        g.hero.stats.addStr(1);
        g.hero.setStatPoint(g.hero.getStatPoint() - 1);
    }
    refresh();
}

void mainTab::on_addAgi_clicked()
{
    if (g.hero.getStatPoint() > 0){
        g.hero.stats.addAgi(1);
        g.hero.setStatPoint(g.hero.getStatPoint() - 1);
    }
    refresh();
}

void mainTab::on_addInt_clicked()
{
    if (g.hero.getStatPoint() > 0){
        g.hero.stats.addInt(1);
        g.hero.setStatPoint(g.hero.getStatPoint() - 1);
    }
    refresh();
}

void mainTab::on_tableWidget_cellClicked(int row, int column)
{
    g.changeOfItem(row,column);
    refresh();
}

void mainTab::on_buttonRefresh_clicked()
{
    g.storeRefresh();
    for (int i = 0; i < g.store.getLine(); i++){
        for (int j = 0; j < g.store.getColumn(); j++){
            ui->tableStore->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g.store.getCell(i,j).getName() + ".png"));
        }
    }
}

void mainTab::on_ButtonBuy_clicked()
{
    switch (g.storeBuy()) {
    case 1:
        QMessageBox::information(0, "ошибка покупки", "нет свободного места в инвентаре");
        break;
    case 2:
        QMessageBox::information(0, "ошибка покупки", "вам не хватает золота");
        break;
    case 0:
        QMessageBox::information(0, "покупка", "спасибо за покупку!");
        refresh();
        ui->tableStore->item(g.store.getModifiedI(),g.store.getModifiedJ())->setIcon(QIcon(dir + "/image/background/Sales.jpg"));
        break;

    }

}

void mainTab::on_tableStore_cellClicked(int row, int column)
{
    QString a;
    g.store.setModifiedIJ(row,column);
    ui->storeCost->setNum(g.store.getCell(row,column).getCost());
    ui->storeValue->setNum(g.store.getCell(row,column).getValue());
    ui->storeDurability->setNum(g.store.getCell(row,column).getDurability());
    ui->storeName->setText(g.store.getCell(row,column).getName());
    ui->product->setPixmap(dir + "/image/Item/" + g.store.getCell(row,column).getName() + ".png");
    ui->storeLab_4->setText(g.store.getCell(row,column).getEff()->name());
    switch (g.store.getCell(row,column).getStatus()) {
    case 1:
        a = dir + "/image/background/legendFrame.png";
        ui->auraProd->setPixmap(a);
        break;
    case 2:
        a = dir + "/image/background/mythical.jpg";
        ui->auraProd->setPixmap(a);
        break;
    case 3:
        a = dir + "/image/background/ordinary.jpg";
        ui->auraProd->setPixmap(a);
        break;
    }
}

void mainTab::on_sellRadioButton_clicked(bool checked)
{
    if(ui->warehouseRadioButton->isChecked()){
        ui->warehouseRadioButton->setChecked(false);
        g.setWarehouseMode(false);
    }
    g.setSalesMode(checked);
}

void mainTab::on_warehouseRadioButton_clicked(bool checked)
{
    if(ui->sellRadioButton->isChecked()){
        ui->sellRadioButton->setChecked(false);
        g.setSalesMode(false);
    }
    g.setWarehouseMode(checked);
}

void mainTab::on_healButton_clicked()
{
    switch (g.hospital()) {
    case 0:
        QMessageBox::information(0, "лечение", "ваше здоровье полностью восстановлено");
        refresh();
        break;
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "внимание", "не стоит отвлекать врачей от работы когда вы и так здоровы");
        break;
    }
}

void mainTab::on_hospitalButton_clicked()
{
    switch (g.cityUpdate(0)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->hospitalButton->setVisible(false);
        break;
    }
    refresh();
    ui->hospitalBar->setValue(g.getCityLevel(0));
    ui->healButton->setToolTip(QString::number(g.getCostHos()) + " монет");
}

void mainTab::on_manaButton_clicked()
{
    switch (g.temple()) {
    case 0:
        QMessageBox::information(0, "медитация", "ваша мана полностью восстановлено");
        refresh();
        break;
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "внимание", "не стоит отвлекать жриц от работы когда вы и так здоровы");
        break;
    case 3:
        ui->manaButton->setVisible(false);
        break;
    }
}

void mainTab::on_templeButton_clicked()
{
    switch (g.cityUpdate(5)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->templeButton->setVisible(false);
        break;
    }
    refresh();
    ui->templeBar->setValue(g.getCityLevel(5));
    ui->manaButton->setToolTip(QString::number(g.getCostTemp()) + " монет");

}

void mainTab::on_libraryButton_clicked()
{
    switch (g.cityUpdate(1)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->libraryButton->setVisible(false);
        break;
    }
    refresh();
    ui->libraryBar->setValue(g.getCityLevel(1));

}

void mainTab::on_warehouseButton_clicked()
{

    switch (g.cityUpdate(2)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 0:
        refresh();
        ui->warehouse->setVisible(true);
        ui->warehouseRadioButton->setVisible(true);
        ui->stockBar->setValue(g.getCityLevel(2));
        break;
    case 3:
        ui->warehouseButton->setVisible(false);
        break;
    }
}

void mainTab::on_bankButton_clicked()
{
    switch (g.cityUpdate(3)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->bankButton->setVisible(false);
        break;
    }
    refresh();
    ui->bankBar->setValue(g.getCityLevel(3));
    ui->bankBox->setMaximum(g.getCityLevel(3) * 200);
}

void mainTab::on_arenaButton_clicked()
{
    switch (g.cityUpdate(4)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->arenaButton->setVisible(false);
        break;
    }
    refresh();
    ui->arenaBar->setValue(g.getCityLevel(4));
}

void mainTab::on_herbalistButton_clicked()
{
    switch (g.cityUpdate(6)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->herbalistButton->setVisible(false);
        break;
    }
    refresh();
    ui->herbalistBar->setValue(g.getCityLevel(6));

}

void mainTab::on_forgeButton_clicked()
{
    switch (g.cityUpdate(7)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 0:
        ui->forge->setVisible(true);
        ui->ButtonRepairs->setVisible(true);
        ui->forgeClose->setVisible(false);
        refresh();
        ui->forgeBar->setValue(g.getCityLevel(7));
        break;
    case 3:
        ui->forgeButton->setVisible(false);
        break;
    }
}

void mainTab::on_storeButton_clicked()
{
    switch (g.cityUpdate(8)) {
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "ошибка", "максимальный уровень!");
        break;
    case 3:
        ui->storeButton->setVisible(false);
        break;
    }
    refresh();
    ui->storeBar->setValue(g.getCityLevel(8));

}

void mainTab::on_bankBox_valueChanged(int arg)
{
    int r = g.getMoneyBank() - arg;
    if((arg > g.getMoneyBank())&&(g.hero.getMoney() >= -r)){
        g.setMoneyBank(arg);
        g.hero.addMoney(r);
    }
    if(arg < g.getMoneyBank()){
        g.setMoneyBank(arg);
        g.hero.addMoney(r);
    }
    ui->bankBox->setValue(g.getMoneyBank());
    refresh();
}

void mainTab::on_forge_cellClicked(int row, int column)
{
    Item c;
    i = row;
    j = column;
    switch (row) {
    case 0:
        switch (row + column) {
        case 0:
            c = g.hero.equip.getHand();
            break;
        case 1:
            c = g.hero.equip.getPants();
            break;
        case 2:
            c = g.hero.equip.getTorso();
            break;
        case 3:
            c = g.hero.equip.getGloves();
            break;
        }
        break;
    case 1:
        switch (row + column) {
        case 1:
            c = g.hero.equip.getHelmet();
            break;
        case 2:
            c = g.hero.equip.getOneRing();
            break;
        case 3:
            c = g.hero.equip.getTwoRing();
            break;
        case 4:
            c = g.hero.equip.getFootwear();
            break;
        }
        break;
    }

    QString a;

    ui->storeCost->setNum(c.getCost());
    ui->storeValue->setNum(c.getValue());
    ui->storeDurability->setNum(c.getDurability());
    ui->storeName->setText(c.getName());
    ui->product->setPixmap(":/new/item/image/Item/" + c.getName() + ".png");
    ui->storeLab_4->setText(c.getEff()->name());
    switch (c.getStatus()) {
    case 1:
        a = dir + "/image/background/legendFrame.png";
        ui->auraProd->setPixmap(a);
        break;
    case 2:
        a = dir + "/image/background/mythical.jpg";
        ui->auraProd->setPixmap(a);
        break;
    case 3:
        a = dir + "/image/background/ordinary.jpg";
        ui->auraProd->setPixmap(a);
        break;
    }
}

void mainTab::on_ButtonRepairs_clicked()
{
    switch (g.repairs(i,j)) {
    case 0:
        QMessageBox::information(0, "ремонт", "вы починили предмет");
        refresh();
        break;
    case 1:
        QMessageBox::information(0, "ошибка", "у вас недостаточно денег");
        break;
    case 2:
        QMessageBox::information(0, "внимание", "не стоит отвлекать кузнеца от работы когда предмет и так цел");
        break;
    }
    emit on_forge_cellClicked(i,j);
}

void mainTab::on_belt_cellClicked(int row, int column)
{
    g.changeOfPoision(row);
    refresh();
}

void mainTab::on_warehouse_cellClicked(int row, int column)
{
    g.changeWarehouse(row,column);
    refresh();
}

void mainTab::on_buttOut_clicked()
{
    g.createDunge();
    g.createRoom();
    dunge->refresh();
    setVisible(false);
    dunge->show();
}
