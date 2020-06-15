#ifndef DUNGEON_H
#define DUNGEON_H

#include <QTabWidget>
#include <QKeyEvent>
#include <QMenu>
#include <QContextMenuEvent>
#include <windows.h>
#include <QMessageBox>
#include <QVector>
#include <QPoint>
#include <QBitmap>
#include <QDir>

#include "game.h"
#include "character/allspell.h"

namespace Ui {
class dungeon;
}

class dungeon : public QTabWidget
{
    Q_OBJECT

public:
    explicit dungeon(QWidget *parent = nullptr);
    ~dungeon();
    void initDungeon(Game *_game);
    void refresh(); // обновление всего на экране
    void refreshBag();
    QString itemToolTip(Item a);
    void refreshRoom(int a);
    void SetEnemyVisible(bool a);
    void refreshBelt();


signals:
    void changeScreen();

    void refreshBagCell(int,int);

private slots:
    void refreshCellBelt(int i,int j);

    void cellRefresh();

    void takeOffSubject(int i,int j);

    void refreshBag(int i,int j);

    void on_tableWidget_cellClicked(int row, int column);

    void outTextLog(QString s);

    void keyPressEvent(QKeyEvent *key); // Обработка нажатий

    void on_tableSpell_cellClicked(int row, int column);

    void on_ButtonSearch_clicked();

    void on_goHome_clicked();

    void on_belt_cellClicked(int row, int column);

    void on_belt_2_cellClicked(int row, int column);

    void on_escape_clicked();

private:
    QString dir;
    Ui::dungeon *ui;
    Game *g = new Game(false);
};

#endif // DUNGEON_H
