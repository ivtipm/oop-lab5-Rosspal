#include "dungeon.h"
#include "ui_dungeon.h"

dungeon::dungeon(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::dungeon)
{
    dir = QDir::currentPath();
    ui->setupUi(this);

    connect(g,SIGNAL(textOut(QString)),this,SLOT(outTextLog(QString)));

    connect(ui->hand,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->helmet,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->torso,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->pants,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->footwear,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->gloves,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->ringOne,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(ui->ringTwo,SIGNAL(cellClicked(int,int)),this,SLOT(takeOffSubject(int,int)));
    connect(g,SIGNAL(refreshCell()),this,SLOT(cellRefresh()));
    connect(g,SIGNAL(refershBelt(int,int)),this,SLOT(refreshCellBelt(int,int)));

    for (int i = 0; i < g->hero.belt.getLine(); i++){
        for (int j = 0; j < g->hero.belt.getColumn(); j++){
            ui->belt->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
        }
    }
    for (int i = 0; i < g->hero.belt.getLine(); i++){
        for (int j = 0; j < g->hero.belt.getColumn(); j++){
            ui->belt_2->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
        }
    }
}

dungeon::~dungeon()
{
    delete ui;
}

void dungeon::refresh()
{
    QString a;
    ui->goHome->setVisible(false);

    ui->hpBar->setRange(0,g->hero.stats.getMaxHP());
    ui->mpBar->setRange(0,g->hero.stats.getMaxMP());
    ui->hpBar->setValue(g->hero.stats.getHP());
    ui->mpBar->setValue(g->hero.stats.getMP());
    ui->expBar->setRange(0,g->hero.getExpMax());
    ui->expBar->setValue(g->hero.getExp());

    a = dir + "/image/Item/" + g->hero.equip.getHand().getName() + ".png";
    ui->tableSpell->item(0,0)->setIcon(QIcon(a));                   //spell icon refresh
    ui->tableSpell->item(0,0)->setToolTip(g->hero.spell[0]->name() + "\n" + g->hero.spell[0]->description());

    for (int i = 1; i < 8 ; i++) {
        a = dir + "/image/spell/" + g->hero.spell[i]->name() + ".png";
        ui->tableSpell->item(0,i)->setIcon(QIcon(a));                   //spell icon refresh
        ui->tableSpell->item(0,i)->setToolTip(g->hero.spell[i]->name() + "\n" + g->hero.spell[i]->description());
    }

    for (int i = 1; i < 8 ; i++) {
        if(g->hero.spell[i]->coolDown > 0){
            ui->tableSpell->item(0,i)->setIcon(QIcon(dir + "/image/spell/" + g->hero.spell[i]->name() + QString::number(g->hero.spell[i]->coolDown) + ".png"));
        }
    }

    refreshRoom(g->getRoom());

    //сумка
    ui->tableWidget->item(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ())->setIcon(QIcon(dir + "/image/Item/" +
                                                                                              g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getName() +                                                                                     ".png"));
    a = itemToolTip(g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()));

    ui->tableWidget->item(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ())->setToolTip(a);

    emit refreshBagCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ());

    ui->belt->item(g->hero.belt.getModifiedJ(),g->hero.belt.getModifiedI())->setIcon(QIcon(dir + "/image/Item/" +
                                                                                              g->hero.belt.getCell(g->hero.belt.getModifiedI(),g->hero.belt.getModifiedJ()).getName() +
                                                                                              ".png"));

    ui->belt->item(g->hero.belt.getModifiedJ(),g->hero.belt.getModifiedI())->setToolTip(itemToolTip(g->hero.belt.getCell(g->hero.belt.getModifiedI(),g->hero.belt.getModifiedJ())));
    ui->belt->resize(60,g->hero.belt.getColumn() * 60);

    ui->belt_2->item(g->hero.belt.getModifiedJ(),g->hero.belt.getModifiedI())->setIcon(QIcon(dir + "/image/Item/" +
                                                                                              g->hero.belt.getCell(g->hero.belt.getModifiedI(),g->hero.belt.getModifiedJ()).getName() +
                                                                                              ".png"));

    ui->belt_2->item(g->hero.belt.getModifiedJ(),g->hero.belt.getModifiedI())->setToolTip(itemToolTip(g->hero.belt.getCell(g->hero.belt.getModifiedI(),g->hero.belt.getModifiedJ())));
    ui->belt_2->resize(60,g->hero.belt.getColumn() * 60);

    //снаряжение

    ui->handLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getHand().getName() + ".png");
    ui->hand->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getHand()));

    ui->helmetLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getHelmet().getName() + ".png");
    ui->helmet->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getHelmet()));

    ui->torsoLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getTorso().getName() + ".png");
    ui->torso->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getTorso()));

    ui->pantsLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getPants().getName() + ".png");
    ui->pants->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getPants()));

    ui->footwearLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getFootwear().getName() + ".png");
    ui->footwear->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getFootwear()));

    ui->glovesLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getGloves().getName() + ".png");
    ui->gloves->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getGloves()));

    ui->ringTwoLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getTwoRing().getName() + ".png");
    ui->ringTwo->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getTwoRing()));

    ui->ringOneLabel->setPixmap(dir + "/image/Item/" + g->hero.equip.getOneRing().getName() + ".png");
    ui->ringOne->item(0,0)->setToolTip(itemToolTip(g->hero.equip.getOneRing()));



}

QString dungeon::itemToolTip(Item a)
{
    return ( a.getName() +"\n"+
             "урон/броня-" + QString::number(a.getValue()) + "\n"+
             "качество-" + QString::number(a.getDurability()) + "%\n"+
             "количество-" + QString::number(a.getQuantity()) + "\n"+
             "цена-" + QString::number(a.getCost()) + "\n" +
             a.getEff()->name() + "\n" +
             a.getEff()->description());
}

void dungeon::refreshRoom(int a)
{
    switch (g->getRoom()) {
    case 0:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        break;

    case 1:
        SetEnemyVisible(true);
        ui->enemyHP->setRange(0,g->NPC.stats.getMaxHP());
        ui->enemyHP->setValue(g->NPC.stats.getHP()); // обновление NPC
        ui->enemyModel->setPixmap(g->NPC.getModel());
        ui->enemyName->setText(g->NPC.getName());
        ui->enemyArmor->setNum(g->NPC.stats.getArmor());
        ui->enemyAttack->setNum(g->NPC.stats.getAttack());
        break;

    case 2:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        break;

    case 3:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        break;

    case 4:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        break;

    case 5:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        break;
    case 9:
        SetEnemyVisible(true);
        ui->enemyHP->setRange(0,g->NPC.stats.getMaxHP());
        ui->enemyHP->setValue(g->NPC.stats.getHP()); // обновление NPC
        ui->enemyModel->setPixmap(g->NPC.getModel());
        ui->enemyName->setText(g->NPC.getName());
        ui->enemyArmor->setNum(g->NPC.stats.getArmor());
        ui->enemyAttack->setNum(g->NPC.stats.getAttack());
        break;
    case 10:
        SetEnemyVisible(false);
        ui->labelBackground->setPixmap(dir + "/image/background/" + g->getRoomImage() + ".jpg");
        ui->goHome->setVisible(true);
        break;
    }
}

void dungeon::SetEnemyVisible(bool a)
{
    ui->enemyHP->setVisible(a);
    ui->enemyName->setVisible(a);
    ui->enemyArmor->setVisible(a);
    ui->enemyAttack->setVisible(a);
    ui->enemyLabel->setVisible(a);
    ui->enemyLabel1->setVisible(a);
    ui->enemyModel->setVisible(a);
    ui->frame->setVisible(a);
}

void dungeon::refreshBelt()
{
    for (int i = 0; i < g->hero.belt.getLine(); i++){
        for (int j = 0; j < g->hero.belt.getColumn(); j++){
            ui->belt->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
        }
    }
    for (int i = 0; i < g->hero.belt.getLine(); i++){
        for (int j = 0; j < g->hero.belt.getColumn(); j++){
            ui->belt_2->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
        }
    }
}

void dungeon::refreshCellBelt(int i, int j)
{
    ui->belt->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
    ui->belt->item(j,i)->setToolTip(itemToolTip(g->hero.belt.getCell(i,j)) + g->hero.belt.getCell(i,j).getEff()->name());

    ui->belt_2->item(j,i)->setIcon(QIcon(dir + "/image/Item/" + g->hero.belt.getCell(i,j).getName() + ".png"));
    ui->belt_2->item(j,i)->setToolTip(itemToolTip(g->hero.belt.getCell(i,j)) + g->hero.belt.getCell(i,j).getEff()->name());
}

void dungeon::cellRefresh()
{
    QString a;
    ui->tableWidget->item(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ())->setIcon(QIcon("/image/Item/" +
                                                                                              g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getName() + ".png"));
    a = "урон/броня-" + QString::number(g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getValue()) + "\n"+
            "качество-" + QString::number(g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getDurability()) + "%\n"+
            "цена-" + QString::number(g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getCost());

    ui->tableWidget->item(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ())->setToolTip(a + g->hero.bag.getCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ()).getEff()->name());

    emit refreshBagCell(g->hero.bag.getModifiedI(),g->hero.bag.getModifiedJ());
}

void dungeon::takeOffSubject(int i,int j)
{
    QTableWidget *cell = (QTableWidget *)sender();

    switch (g->takeOffSubject(cell->item(0,0)->text().toInt())){
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

void dungeon::refreshBag(int i, int j)
{
    QString a;

    ui->tableWidget->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g->hero.bag.getCell(i,j).getName() +
                                              ".png"));
    a = "урон/броня-" + QString::number(g->hero.bag.getCell(i,j).getValue()) + "\n"+
            "качество-" + QString::number(g->hero.bag.getCell(i,j).getDurability()) + "%\n"+
            "цена-" + QString::number(g->hero.bag.getCell(i,j).getCost());

    ui->tableWidget->item(i,j)->setToolTip(a);
}

void dungeon::outTextLog(QString s)
{
    ui->textLog->append(s);
}

void dungeon::initDungeon(Game *_game)
{
    g = _game;
    connect(g,SIGNAL(textOut(QString)),this,SLOT(outTextLog(QString)));
    ui->goHome->setVisible(false);

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 5; j++){
            ui->tableWidget->item(i,j)->setIcon(QIcon(dir + "/image/Item/" + g->hero.bag.getCell(i,j).getName() + ".png"));
        }
    }
}

void dungeon::on_tableWidget_cellClicked(int row, int column)
{
    g->changeOfItem(row,column);
    refresh();
}

void dungeon::keyPressEvent(QKeyEvent *key)
{
    int keyCode; // Целочисленный код клавиши
    keyCode = key->key();
    switch (key->key())
    {
    case Qt::Key_1:
        on_tableSpell_cellClicked(0,0);
        break;
    case Qt::Key_2:
        on_tableSpell_cellClicked(0,1);
        break;
    case Qt::Key_3:
        on_tableSpell_cellClicked(0,2);
        break;
    case Qt::Key_4:
        on_tableSpell_cellClicked(0,3);
        break;
    case Qt::Key_5:
        on_tableSpell_cellClicked(0,4);
        break;
    case Qt::Key_6:
        on_tableSpell_cellClicked(0,5);
        break;
    case Qt::Key_7:
        on_tableSpell_cellClicked(0,6);
        break;
    case Qt::Key_8:
        on_tableSpell_cellClicked(0,7);
        break;
    }
}

void dungeon::on_tableSpell_cellClicked(int row, int column)
{
    if (g->hero.spell[column]->coolDown == 0){

        switch (g->fight(column)) {
        case 0:

            break;
        case 1:

            break;
        case 2:
            ui->enemyHP->setValue(0);
            break;
        case 3:
            ui->hpBar->setValue(0);
            break;
        }

        for(int i = 0; i < 8 ; i++){                //cd
            if ((g->hero.spell[i]->coolDown - 1) < 0){

            }else{
                if (i != column){
                    g->hero.spell[i]->coolDown -= 1;
                }
            }
        }
    }
    refresh();
}

void dungeon::on_ButtonSearch_clicked()
{
    if(g->getCheckRoom()){
    g->nextRoom();
    g->createRoom();
    refresh();
    }
}

void dungeon::on_goHome_clicked()
{
    changeScreen();
}

void dungeon::on_belt_cellClicked(int row, int column)
{
    g->changeOfPoision(row);
    refresh();
    g->fight(1);
}

void dungeon::on_belt_2_cellClicked(int row, int column)
{
    g->usePoision(row);
    refresh();
}

void dungeon::on_escape_clicked()
{
   if(g->escape()){
      changeScreen();
      QMessageBox::information(0, "успех!", "побег удался!");
   }
   else{
   QMessageBox::information(0, "неудача", "побег не удался");
   if(g->enemyStrike()){
       ui->hpBar->setValue(0);
   }
   refresh();
   }

}
