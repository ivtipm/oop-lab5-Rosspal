#include "startmenu.h"
#include "ui_startmenu.h"

startMenu::startMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::startMenu)
{
    dir = QDir::currentPath();
    QString a;
    ui->setupUi(this);
    agi = 1;
    str = 1;
    intel = 1;
    statPoint = 10;
    pers = 0;
    k = 0;
    a = dir + "/image/portrait/portrait0.jpg";
    ui->portrait->setPixmap(a);

    text.push_back("Вы обычный бродяга который берётся за любую работу\n"
                   "всё что у вас есть это 500 золотых монет выруче-\n"
                   "ных за продажу семейного кольца");
    text.push_back("Вы представитель древнего рода эльфов, которого\n"
                   "изгнали из дома за изучение запретной магии\n"
                   "у вас повышенное количество манны и ваш любимый\n"
                   "посох 'адепта'");
    text.push_back("Вы орк с пустошей Акама, ещё ребёнком вас продали\n"
                   "в рабство и разъеденили с семьёй. Но вам повезло\n"
                   "вас купила очень добрая госпожа, которая воспиты-\n"
                   "вала вас как своего сына\n"
                   "ваша приёмная мать подарила вам снаряжение своего\n"
                   "покойного сына на ваше совершенолетие");
    text.push_back("Вы гном с гор Махакама, всю свою жизнь вы прораотали в\n"
                   "шахтах.Не в силах больше терпеть такую жизнь ушли на\n"
                   "вольные заработки\n"
                   "имеет повышенную силу,здоровье и свою счастливую кирку");
    text.push_back("Вы представительница 'храма теней' что сбежала от туда\n"
                   "устав от постоянного контроля и правил"
                   "тренировки в храме сделали ваши движения быстрымии точными\n"
                   "крит,шанс уворота и сила крита повышены, ваш любимый клинок\n"
                   "всегда с вами");
    ui->description->setText(text[0]);
    connect(Game,SIGNAL(rebirth()),this,SLOT(rebirth()));
}

startMenu::~startMenu()
{
    delete ui;
}

void startMenu::rebirth()
{
    this->show();
    Game->close();
}

void startMenu::on_pushButton_clicked()
{
    if((ui->textEdit->toPlainText() != "")&&(statPoint == 0)){
    Game->show();
    Game->createPers(ui->textEdit->toPlainText(),str,agi,intel,pers);
    Game->refreshBag();
    Game->refresh();
    this->close();
    }

}

void startMenu::on_spinBoxStr_valueChanged(int arg)
{
    if((arg > str)&&(statPoint != 0)){
        str = arg;
        statPoint -= 1;
    }
    if(arg < str){
        str = arg;
        statPoint += 1;
    }
    ui->spinBoxStr->setValue(str);
    ui->labelStatPoint->setNum(statPoint);
}

void startMenu::on_spinBoxAgi_valueChanged(int arg1)
{
    if((arg1 > agi)&&(statPoint != 0)){
        agi = arg1;
        statPoint -= 1;
    }
    if(arg1 < agi){
        agi = arg1;
        statPoint += 1;
    }
    ui->spinBoxAgi->setValue(agi);
    ui->labelStatPoint->setNum(statPoint);
}

void startMenu::on_spinBoxInt_valueChanged(int arg1)
{
    if((arg1 > intel)&&(statPoint != 0)){
        intel = arg1;
        statPoint -= 1;
    }
    if(arg1 < intel){
        intel = arg1;
        statPoint += 1;
    }
    ui->spinBoxInt->setValue(intel);
    ui->labelStatPoint->setNum(statPoint);
}

void startMenu::on_buttonRight_clicked()
{
    if((k + 1) == 5){
        k = 0;
    }else{
        k++;
    }
    pers = k;
    ui->portrait->setPixmap(dir + "/image/portrait/portrait" + QString::number(k) + ".jpg");
    ui->description->setText(text[k]);
}

void startMenu::on_buttonLeft_clicked()
{
    if((k - 1) == -1){
        k = 4;
    }else{
        k--;
    }
    pers = k;
    ui->portrait->setPixmap(dir + "/image/portrait/portrait" + QString::number(k) + ".jpg");
    ui->description->setText(text[k]);
}
