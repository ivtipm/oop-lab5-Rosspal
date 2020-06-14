#include "bagitem.h"

BagItem::BagItem(int i, int j)
{
    line = i;
    column = j;
    bag.resize(line);
    for (int a = 0; a < line; a++)
    {
        bag[a].resize(column);
    }
}

int BagItem::getLine()
{
    return line;
}

int BagItem::getColumn()
{
    return column;
}

void BagItem::setColumn(int col)
{
    column = col;
}

void BagItem::setLine(int _line)
{
    line = _line;
}

int BagItem::getModifiedI()
{
    return modifiedI;
}

int BagItem::getModifiedJ()
{
    return modifiedJ;
}

void BagItem::setModifiedIJ(int i, int j)
{
    modifiedI = i;
    modifiedJ = j;
}

void BagItem::setCheck(int i, int j, int a)
{
    check[i][j] = a;
}

void BagItem::deleteItem(int i, int j)
{
    Item a;
    a.create(0,0,0,0,0,"пусто",new stub,0);
    bag[i][j] = a;
    check[i][j] = 0;
    modifiedI = i;
    modifiedJ = j;
}

void BagItem::setCell(int i, int j, Item a)
{
    modifiedI = i;
    modifiedJ = j;
    bag[i][j] = a;
}

Item BagItem::getCell(int i, int j)
{
    return bag[i][j];
}

void BagItem::bagCreate(int a, int b)
{
    Item c;
    line = a;
    column = b;
    bag.resize(a);
    check.resize(a);
    for (int i = 0; i < a; i++)
    {
        bag[i].resize(b);
        check[i].resize(b);
    }
    for(int i = 0; i < a; i++){
        for(int j = 0; j < b; j++){
            check[i][j] = 0;
        }
    }
}

void BagItem::addItem(Item a)
{
    int k = 0;

    if(a.getType() >= 10){

        for(int i = 0; i < line; i++){
            for(int j = 0; j < column; j++){
                if((a.getName() == bag[i][j].getName())&&(a.getEff()->level == bag[i][j].getEff()->level)){
                    bag[i][j].addQuantity(a.getQuantity());
                    modifiedI = i;
                    modifiedJ = j;
                    k = 1;
                }
            }
        }
    }
    if(vacancySearch()){
    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; j++){
            if((check[i][j] == 0)&&(k == 0)){
                bag[i][j] = a;
                check[i][j] = 1;
                modifiedI = i;
                modifiedJ = j;
                k = 1;
            }
        }
    }
    }
}

int BagItem::vacancySearch()
{
    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; j++){
            if((check[i][j] == 0)&&(bag[i][j].getName() != "close")){
                return 1;
            }
        }
    }
    return 0;
}
