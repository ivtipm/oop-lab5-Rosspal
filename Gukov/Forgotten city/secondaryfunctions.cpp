#include "secondaryfunctions.h"

int random(int low, int high)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() + rand());
    return (qrand() % ((high + 1) - low) + low);
}

int chance(double a)
{
    if (a >= random(1,100)){
        return 1;
    }
    return 0;
}

double percent(int a, double b)
{
    return ((b/100) * a);
}

int percentNumNum(double a, double b)
{
    double onePercent = a / 100;
    return round(b / onePercent);
}
