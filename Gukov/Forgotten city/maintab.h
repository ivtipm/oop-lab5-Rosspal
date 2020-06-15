#ifndef MAINTAB_H
#define MAINTAB_H

#include <QTabWidget>
#include <QKeyEvent>
#include <QMenu>
#include <QContextMenuEvent>
#include <windows.h>
#include <QMessageBox>
#include <QDir>

#include "game.h"
#include "character/allspell.h"
#include "dungeon.h"

namespace Ui {
class mainTab;
}

class mainTab : public QTabWidget
{
    Q_OBJECT 
public:
    explicit mainTab(QWidget *parent = nullptr);
    ~mainTab();
    void refresh(); // обновление всего на экране
    void refreshBag();
    void createPers(QString _name, int _str, int _agi, int _int, int pers);
    QString itemToolTip(Item a);

signals:
    void refreshBagCell(int,int);

    void refreshBeltCell(int,int);

    void rebirth();



private slots:
    void refreshCellBelt(int i,int j);

    void rebirthMediator();

    //void unLock();

    void takeOffSubject(int i,int j);

    void returnToTheCity();

    void refreshBag(int i,int j);

    void leveling(); // вызов нужных действий от нажатия на дерево прокачки

    void on_addStr_clicked();

    void on_addAgi_clicked();

    void on_addInt_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_buttonRefresh_clicked();

    void on_ButtonBuy_clicked();

    void on_tableStore_cellClicked(int row, int column);

    void on_sellRadioButton_clicked(bool checked);

    void on_healButton_clicked();

    void on_hospitalButton_clicked();

    void on_manaButton_clicked();

    void on_templeButton_clicked();

    void on_libraryButton_clicked();

    void on_warehouseButton_clicked();

    void on_bankButton_clicked();

    void on_arenaButton_clicked();

    void on_herbalistButton_clicked();

    void on_forgeButton_clicked();

    void on_storeButton_clicked();

    void on_bankBox_valueChanged(int arg);

    void on_forge_cellClicked(int row, int column);

    void on_ButtonRepairs_clicked();

    void on_belt_cellClicked(int row, int column);

    void on_warehouseRadioButton_clicked(bool checked);

    void on_warehouse_cellClicked(int row, int column);

    void on_buttOut_clicked();

private:
    QString dir;
    int i,j;
    std::vector<QPushButton*> treeSpell;
    Ui::mainTab *ui;
    Game g;
    dungeon *dunge = new dungeon;

};

#endif // MAINTAB_H
