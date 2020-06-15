#ifndef BAGITEM_H
#define BAGITEM_H
#include <vector>
#include "Item/item.h"
#include "allspell.h"

class BagItem//инвентарь
{
private:
    int line;
    int column;
    std::vector<std::vector<Item>> bag; //вектор item для инвентаря
    std::vector<std::vector<int>> check;
    int modifiedI;
    int modifiedJ;
public:
    BagItem(int i, int j);
    BagItem() = default;
    int getLine();
    int getColumn();
    void setColumn(int col);
    void setLine(int _line);
    int getModifiedI();// последние изменения по i
    int getModifiedJ();// последние изменения по j
    void setModifiedIJ(int i,int j);//установить адресс последнего изменения
    void setCheck(int i,int j, int a);
    void deleteItem(int i,int j);

    void setCell(int i, int j, Item a);
    Item getCell(int i,int j);

    void bagCreate(int a,int b);
    void addItem(Item a);

    int vacancySearch();
};

#endif // BAGITEM_H
