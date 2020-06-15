#ifndef STARTMENU_H
#define STARTMENU_H

#include <QFrame>
#include <QDir>
#include "maintab.h"

namespace Ui {
class startMenu;
}

class startMenu : public QFrame
{
    Q_OBJECT

public:
    explicit startMenu(QWidget *parent = nullptr);
    ~startMenu();

private slots:
    void rebirth();

    void on_pushButton_clicked();

    void on_spinBoxStr_valueChanged(int arg);

    void on_spinBoxAgi_valueChanged(int arg1);

    void on_spinBoxInt_valueChanged(int arg1);

    void on_buttonRight_clicked();

    void on_buttonLeft_clicked();

private:
    QString dir;
    Ui::startMenu *ui;
    mainTab *Game = new mainTab;
    int statPoint;
    int str;
    int agi;
    int intel;
    int pers;
    QString name;
    std::vector<QString> text;
    int k;
};

#endif // STARTMENU_H
