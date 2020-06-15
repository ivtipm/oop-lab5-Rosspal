#include <QApplication>
#include "maintab.h"
#include "startmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //mainTab w;
    startMenu w;

    w.show();
    return a.exec();
}
