#include "allspell.h"
#include <cmath>

int damage(EnemyHero &NPC,double d)
{
    double arm;
    arm = 50.0 * ((NPC.stats.getArmor() * 0.02)/(1.0 + (NPC.stats.getArmor() * 0.02)));
    arm = 1 - (arm / 100.0);
    NPC.stats.addHP(round(-(d * arm)));

    return (d * arm);
}

int damageNoArm(EnemyHero &NPC,double d)
{
    NPC.stats.addHP(round(-(d)));
    return round(d);
}

int damage(double d,Person &hero)
{
    double arm;
    arm = 50.0 * (((hero.equip.getGeneralArmor() + hero.stats.getBaseArmor()) * 0.02)/(1.0 + (hero.equip.getGeneralArmor() + hero.stats.getBaseArmor()) * 0.02));
    arm = 1 - (arm / 100.0);

    hero.stats.addHP(round(-(d * arm)));
    return (d * arm);
}
int damageNoArm(double d,Person &hero)
{
    hero.stats.addHP(round(-(d)));
    return (round(d));
}

int damageFire(EnemyHero &NPC,double d)
{
    d = d * NPC.stats.getFireResistance();
    NPC.stats.addHP(round(-(d)));
    return (round(d));
}

int damageCold(EnemyHero &NPC,double d)
{
    d = d * NPC.stats.getColdResistance();
    NPC.stats.addHP(round(-(d)));
    return (round(d));
}

int damagePoison(EnemyHero &NPC,double d)
{
    d = d * NPC.stats.getPoisonResistance();
    NPC.stats.addHP(round(-(d)));
    return (round(d));
}

/*****************************************************************************************************************************************************************************/

QString oneShot::description()
{
    return "One shot";
}

QString oneShot::name()
{
    return "One shot";
}

void oneShot::effect(EnemyHero &NPC, Person &hero)
{ 
    coolDown = CD();
    text = "вы нанесли " + QString::number(damage(NPC,9999)) + " единиц урона";
}

int oneShot::CD()
{
    return 0;
}

QString stub::description()
{
    return "";
}

QString stub::name()
{
    return "Stub";
}

void stub::effect(EnemyHero &NPC, Person &hero)
{
    //hero.stats.addHP(NPC.getAttack());
}

int stub::CD()
{
    return 7;
}

QString backstab::description()
{
    return "выждав момент вы наносите увеличенный урон в спину";
}

QString backstab::name()
{
    return "Удар в спину";
}

void backstab::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC, (hero.stats.getAgi() * (level * koef + 1) + hero.stats.getBaseAttack() + hero.equip.getGeneralAttack()) * hero.stats.getCrit() )) + " единиц урона";

    }else {
        text = "вы нанесли " + QString::number(damage(NPC, hero.stats.getAgi() * (level * koef + 1) + hero.stats.getBaseAttack() + hero.equip.getGeneralAttack() )) + " единиц урона";
    }
    coolDown = CD();
}

int backstab::CD()
{
    return 2;
}

QString baseAttack::description()
{
    return "обычный удар";
}

QString baseAttack::name()
{
    return "обычный удар";
}

void baseAttack::effect(EnemyHero &NPC, Person &hero)
{

    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,((hero.stats.getAgi() + hero.stats.getStr() + hero.stats.getInt()) / 4) * hero.stats.getCrit() )) + " единиц урона";

    }else {
        text = "вы нанесли " + QString::number(damage(NPC,(hero.stats.getAgi() + hero.stats.getStr() + hero.stats.getInt()) / 4 )) + " единиц урона";

    }
    coolDown = CD();
}

int baseAttack::CD()
{
    return 0;
}

QString achillesHeel::description()
{
    return "найдите слабое место противника и ударьте игнорируя броню";
}

QString achillesHeel::name()
{
    return "Ахилесова пята";
}

void achillesHeel::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damageNoArm(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * hero.stats.getCrit() )) + " единиц урона";

    }else {
        text = "вы нанесли " + QString::number(damageNoArm(NPC,hero.equip.getGeneralAttack() + hero.stats.getBaseAttack() )) + " единиц урона";

    }
    coolDown = CD();
}

int achillesHeel::CD()
{
    return 2;
}

QString cutWallet::description()
{
    return "NULL";
}

QString cutWallet::name()
{
    return "Cut wallet";
}

void cutWallet::effect(EnemyHero &NPC, Person &hero)
{
    int money = random(NPC.stats.getLevel() * 2,NPC.stats.getLevel() * 5);
    text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * hero.stats.getCrit() ))
            + " единиц урона \n украдено " + QString::number(money) + " монет";
    hero.addMoney(money);
    coolDown = CD();
}

int cutWallet::CD()
{
    return 2;
}

QString lifeSteal::description()
{
    return "ваша атака востановит вам часть жизни";
}

QString lifeSteal::name()
{
    return "Похищение жизни";
}

void lifeSteal::effect(EnemyHero &NPC, Person &hero)
{
    int d;
    if(chance(hero.stats.getCritChance())){
        d=damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * hero.stats.getCrit());
        text = "критический урон! вы нанесли " + QString::number(d) + " единиц урона \n вы востановили " + QString::number(d) + " единиц здоровья";

    }else {
        d=damage(NPC,hero.equip.getGeneralAttack() + hero.stats.getBaseAttack());
        text = "вы нанесли " + QString::number(d) + " единиц урона \n вы востановили " + QString::number(d) + " единиц здоровья";

    }
    hero.stats.addHP(d);
    coolDown = CD();
}

int lifeSteal::CD()
{
    return 3;
}

QString baseAttackUp::description()
{
    return "NULL";
}

QString baseAttackUp::name()
{
    return "Base attack";
}

void baseAttackUp::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(level)){
        damage(NPC,NPC.stats.getMaxHP() + 999999999);
    }else{
        if(chance(hero.stats.getCritChance())){
            damage(NPC,hero.equip.getGeneralAttack() + hero.stats.getBaseAttack() * hero.stats.getCrit());
        }else {
            damage(NPC,hero.equip.getGeneralAttack() + hero.stats.getBaseAttack());
        }
    }
    coolDown = CD();
}

int baseAttackUp::CD()
{
    return 0;
}

QString baseAttackNPC::description()
{
    return "NULL";
}

QString baseAttackNPC::name()
{
    return "baseAttackNPC";
}

void baseAttackNPC::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(NPC.stats.getCritChance())){
        text = NPC.getName() + " нанес вам критический урон! вы получили " + QString::number(damage(NPC.stats.getAttack() * NPC.stats.getCrit(),hero)) + " единиц урона";
    }else {
        text = NPC.getName() + " нанес вам " + QString::number(damage(NPC.stats.getAttack(),hero)) + " единиц урона";
    }
}

int baseAttackNPC::CD()
{
    return 0;
}

QString vampirism::description()
{
    return "NULL";
}

QString vampirism::name()
{
    return "Вампиризм";
}

void vampirism::effect(EnemyHero &NPC, Person &hero)
{
    int d;
    if(chance(NPC.stats.getCritChance())){
        d = damage(NPC.stats.getAttack() * NPC.stats.getCrit(),hero);
        text = NPC.getName() + " нанес вам критический урон! вы получили " + QString::number(d) + " единиц урона \n" + NPC.getName() + "востановил себе " + QString::number(d) + " единиц здоровья";
    }else {
        d = damage(NPC.stats.getAttack(),hero);
        text = NPC.getName() + " нанёс " + QString::number(d) + " единиц урона \n" + NPC.getName() + "востановил себе " + QString::number(d) + " единиц здоровья";
    }
    NPC.stats.addHP(d);
}

int vampirism::CD()
{
    return 0;
}

QString attackSword::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: вы наносите повышенный урон зависящий от ловкости на " + QString::number(koefSword) + "% за каждый ровень способности");
}

QString attackSword::name()
{
    return ("Удар мечём");
}

void attackSword::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,((hero.stats.getAgi() * (koefSword * level)) + hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * hero.stats.getCrit() )) + " единиц урона";
    }else {
        text = "вы нанесли " + QString::number(damage(NPC,(hero.stats.getAgi() * (koefSword * level)) + hero.equip.getGeneralAttack() + hero.stats.getBaseAttack())) + " единиц урона";

    }
    coolDown = CD();
}

int attackSword::CD()
{
    return 0;
}

QString attackDagger::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: вы наносите повышенный критический урон на " + QString::number(koefDagger) + "% за каждый ровень способности");
}

QString attackDagger::name()
{
    return ("Удар кинжалом");
}

void attackDagger::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * (hero.stats.getCrit() + (koefDagger * level)) )) + " единиц урона";

    }else {
        text = "вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack() ))) + " единиц урона";

    }
    coolDown = CD();
}

int attackDagger::CD()
{
    return 0;
}

QString luckyHit::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: ваш шанс крита выше на " + QString::number(koefDagger) + "% за каждый ровень способности");
}

QString luckyHit::name()
{
    return ("Удачный удар");
}

void luckyHit::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance() + (koefCrit * level))){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack()) * (hero.stats.getCrit()) )) + " единиц урона";

    }else {
        text = "вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + hero.stats.getBaseAttack() ))) + " единиц урона";

    }
    coolDown = CD();
}

int luckyHit::CD()
{
    return 0;
}

QString heal::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: вы востанавливаете себе 5% от максимального здоровья за каждый уровень способности + 30");
}

QString heal::name()
{
    return ("Лечение");
}

void heal::effect(EnemyHero &NPC, Person &hero)
{
    int heal;

    if(chance(hero.stats.getCritMagicChance())){
        heal = round((level * percent(5,hero.stats.getMaxHP()) + 5 * level * hero.stats.getHealPower() * hero.stats.getCritMagic()));
        text = "критическое лечение! восстановлено " + QString::number(heal) + " единиц здоровья";
    }else {
        heal = round(level * percent(5,hero.stats.getMaxHP()) + 5 * level * hero.stats.getHealPower());
        text = "восстановлено " + QString::number(heal) + " единиц здоровья";
    }
    hero.stats.addHP(heal);
    coolDown = CD();
}

int heal::CD()
{
    return 0;
}

QString mana::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает вашу манну на " + QString::number(koefMana) + " за каждый уровень способности");
}

QString mana::name()
{
    return "Единство с магией";
}

void mana::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addBaseMP(level * 15);
    }else{
        hero.stats.addBaseMP(-(level * 15));
    }
}

int mana::CD()
{
    return 0;
}

QString health::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваше здоровье на " + QString::number(koefHealth) + " за каждый уровень способности");

}

QString health::name()
{
    return ("Крепкое телосложение");

}

void health::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addBaseHP(level * 15);
    }else{
        hero.stats.addBaseHP(-(level * 15));
    }
}

int health::CD()
{
    return 0;
}

QString Crit::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваш крит на " + QString::number(koefCrit) + " за каждый уровень способности");
}

QString Crit::name()
{
    return "Хорошая заточка";
}

void Crit::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addCrit(koefCrit * level);
    }else{
        hero.stats.addCrit(-koefCrit * level);
    }
}

int Crit::CD()
{
    return 0;
}

QString evasion::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваш шанс уворота на " + QString::number(koefEvasion) + " за каждый уровень способности");
}

QString evasion::name()
{
    return ("Повышение шанса уворота");
}

void evasion::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addEvasion(koefEvasion * level);
    }else{
        hero.stats.addEvasion(-koefEvasion * level);
    }
}

int evasion::CD()
{
    return 0;
}

QString critChance::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваш шанс крита на " + QString::number(koefCritChance) + " за каждый уровень способности");
}

QString critChance::name()
{
    return ("Знание слабых мест");
}

void critChance::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addCritChance(koefCritChance * level);
    }else{
        hero.stats.addCritChance(-koefCritChance * level);
    }
}

int critChance::CD()
{
    return 0;
}

QString ColdInc::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваш урон льдом на " + QString::number(koefInc) + " за каждый уровень способности");
}

QString ColdInc::name()
{
    return ("единство с магией льда");
}

void ColdInc::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addColdIncrease(koefInc * level);
    }else{
        hero.stats.addColdIncrease(-koefInc * level);
    }
}

int ColdRes::CD()
{
    return 0;
}

QString ColdRes::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает вашу защиту от магии льда на " + QString::number(koefRes) + " за каждый уровень способности");
}

QString ColdRes::name()
{
    return ("единство с магией льда");
}

void ColdRes::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addColdResistance(koefRes * level);
    }else{
        hero.stats.addColdResistance(-koefRes * level);
    }
}

int ColdInc::CD()
{
    return 0;
}

QString poisInc::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает ваш урон ядом на " + QString::number(koefInc) + " за каждый уровень способности");
}

QString poisInc::name()
{
    return ("знание ядов");
}

void poisInc::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addPoisonIncrease(koefInc * level);
    }else{
        hero.stats.addPoisonIncrease(-koefInc * level);
    }
}

int poisInc::CD()
{
    return 0;
}

int poisRes::CD()
{
    return 0;
}

QString poisRes::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает вашу защиту от магии льда на " + QString::number(koefRes) + " за каждый уровень способности");
}

QString poisRes::name()
{
    return ("знание ядов");
}

void poisRes::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addPoisonResistance(koefRes * level);
    }else{
        hero.stats.addPoisonResistance(-koefRes * level);
    }
}

int fireRes::CD()
{
    return 0;
}

QString fireRes::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает вашу защиту от магии огня на " + QString::number(koefRes) + " за каждый уровень способности");
}

QString fireRes::name()
{
    return ("дружба с огнём");
}

void fireRes::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addFireResistance(koefRes * level);
    }else{
        hero.stats.addFireResistance(-koefRes * level);
    }
}

int ArmorUp::CD()
{
    return 0;
}

QString ArmorUp::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: повышает вашу броню на " + QString::number(7) + " за каждый уровень способности");
}

QString ArmorUp::name()
{
    return ("стальная кожа");
}

void ArmorUp::effect(EnemyHero &NPC, Person &hero)
{
    if(used == 0){
        hero.stats.addBaseArmor(7 * level);
    }else{
        hero.stats.addBaseArmor(-7 * level);
    }
}

QString fireAttack::description()
{

}

QString fireAttack::name()
{
    return "удар огнём";
}

void fireAttack::effect(EnemyHero &NPC, Person &hero)
{
    double d;
    if(chance(NPC.stats.getCritChance())){
        d = NPC.stats.getAttack() * NPC.stats.getCrit();
        text = "критический урон! вам нанесли " + QString::number(damage(d,hero)) + " единиц физического урона";
        d = d/100 * 15 * level;
        text.append("\nвы получили " + QString::number(damageNoArm((d * NPC.stats.getFireIncrease()) * hero.stats.getFireResistance(),hero)) + " урона огнём");

    }else {
        d = NPC.stats.getAttack();
        text = "вам нанесли " + QString::number(damage(d,hero)) + " единиц физического урона";
        d = d/100 * 15 * level;
        text.append("\nвы получили " + QString::number(damageNoArm((d * NPC.stats.getFireIncrease()) * hero.stats.getFireResistance(),hero)) + " урона огнём");
    }
}

int fireAttack::CD()
{
    return 0;
}

QString poisonAttack::description()
{

}

QString poisonAttack::name()
{
    return "poision";
}

void poisonAttack::effect(EnemyHero &NPC, Person &hero)
{
    double d;
    if(chance(NPC.stats.getCritChance())){
        d = NPC.stats.getAttack() * NPC.stats.getCrit();
        text = "критический урон! вам нанесли " + QString::number(damage(d,hero)) + " единиц физического урона";
        d = d/100 * 15 * level;
        text.append("\nвы получили " + QString::number(damageNoArm((d * NPC.stats.getPoisonIncrease()) * hero.stats.getPoisonResistance(),hero)) + " урона ядом");

    }else {
        d = NPC.stats.getAttack();
        text = "вам нанесли " + QString::number(damage(d,hero)) + " единиц физического урона";
        d = d/100 * 15 * level;
        text.append("\nвы получили " + QString::number(damageNoArm((d * NPC.stats.getPoisonIncrease()) * hero.stats.getPoisonResistance(),hero)) + " урона ядом");
    }
}

int poisonAttack::CD()
{
    return 0;
}

void attackDaggerNPC::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(NPC.stats.getCritChance())){
        text = "критический урон! вам нанесли " + QString::number(damage((NPC.stats.getAttack()) * (NPC.stats.getCrit() + (koefDagger * level)),hero )) + " единиц урона";

    }else {
        text = "вам нанесли " + QString::number(damage((NPC.stats.getAttack() ),hero)) + " единиц урона";

    }
    coolDown = CD();
}

void attackSwordNPC::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(NPC.stats.getCritChance())){
        text = "критический урон! вам нанесли " + QString::number(damage(((NPC.stats.getAgi() * (koefSword * level)) + NPC.stats.getAttack()) * NPC.stats.getCrit(),hero )) + " единиц урона";

    }else {
        text = "вам нанесли " + QString::number(damage((NPC.stats.getAgi() * (koefSword * level)) + NPC.stats.getAttack(),hero)) + " единиц урона";

    }
    coolDown = CD();
}

QString manaRecovery::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: вы востанавливаете себе 5% от максимальной маны за каждый уровень способности");

}

QString manaRecovery::name()
{
    return "Востановление маны";
}

void manaRecovery::effect(EnemyHero &NPC, Person &hero)
{
    int heal;

    if(chance(hero.stats.getCritMagicChance())){
        heal = round(level * percent(5,hero.stats.getMaxMP()) + 5 * level * hero.stats.getManaPower() * hero.stats.getCritMagic());
        text = "критическое лечение! восстановлено " + QString::number(heal) + " единиц маны";
    }else {
        heal = round(level * percent(5,hero.stats.getMaxMP()) + 5 * level * hero.stats.getManaPower());
        text = "восстановлено " + QString::number(heal) + " единиц маны";
    }
    hero.stats.addMP(heal);
    coolDown = CD();
}

int manaRecovery::CD()
{
    return 0;
}

QString fireball::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + "урона огнём ");
}

QString fireball::name()
{
    return "Огненый шар";
}

void fireball::effect(EnemyHero &NPC, Person &hero)
{
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            text = "критический урон! вы нанесли " + QString::number(damageFire(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease() * hero.stats.getCritMagic())) + " единиц огненого урона";
        }else {
            text = "вы нанесли " + QString::number(damageFire(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease())) + " единиц огненого урона";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы нанесли " + QString::number(damageFire(NPC,(((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease()) / 2 )) + " единиц огненого урона";
        coolDown = CD() * 2;
    }
}

int fireball::CD()
{
    return 1;
}

QString fireballStaff::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + "урона огнём ");
}

QString fireballStaff::name()
{
    return "Огненый выстрел";
}

void fireballStaff::effect(EnemyHero &NPC, Person &hero)
{
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            text = "критический урон! вы нанесли " + QString::number(damageFire(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease() * hero.stats.getCritMagic())) + " единиц огненого урона";
        }else {
            text = "вы нанесли " + QString::number(damageFire(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease())) + " единиц огненого урона";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы нанесли " + QString::number(damageFire(NPC,(((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getFireIncrease()) / 2 )) + " единиц огненого урона";
        coolDown = CD() * 2;
    }
}

int fireballStaff::CD()
{
    return 0;
}

QString blockOfStone::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + " физического урона");

}

QString blockOfStone::name()
{
    return "Каменная глыба";
}

void blockOfStone::effect(EnemyHero &NPC, Person &hero)
{
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            text = "критический урон! вы нанесли " + QString::number(damage(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getCritMagic())) + " единиц урона";
        }else {
            text = "вы нанесли " + QString::number(damage(NPC,(valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2)))) + " единиц урона";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы нанесли " + QString::number(damage(NPC,(valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2)) / 2 )) + " единиц урона";
        coolDown = CD() * 2;
    }
}

int blockOfStone::CD()
{
    return 1;
}

QString blockOfIce::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + "урона льдом ");

}

QString blockOfIce::name()
{
    return "Ледяная глыба";
}

void blockOfIce::effect(EnemyHero &NPC, Person &hero)
{
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            text = "критический урон! вы нанесли " + QString::number(damageCold(NPC,((valueLevel[level - 1] + hero.equip.getGeneralAttack())) * hero.stats.getColdIncrease() * hero.stats.getCritMagic())) + " единиц урона холодом";
        }else {
            text = "вы нанесли " + QString::number(damageCold(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getColdIncrease())) + " единиц урона холодом";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы нанесли " + QString::number(damageCold(NPC,(((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getColdIncrease()) / 2 )) + " единиц урона холодом";
        coolDown = CD() * 2;
    }
}

int blockOfIce::CD()
{
    return 1;
}

QString IceStaff::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + "урона льдом ");

}

QString IceStaff::name()
{
    return "Ледяной выстрел";
}

void IceStaff::effect(EnemyHero &NPC, Person &hero)
{
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            text = "критический урон! вы нанесли " + QString::number(damageCold(NPC,((valueLevel[level - 1] + hero.equip.getGeneralAttack())) * hero.stats.getColdIncrease() * hero.stats.getCritMagic())) + " единиц урона холодом";
        }else {
            text = "вы нанесли " + QString::number(damageCold(NPC,((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getColdIncrease())) + " единиц урона холодом";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы нанесли " + QString::number(damageCold(NPC,(((valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2))) * hero.stats.getColdIncrease()) / 2 )) + " единиц урона холодом";
        coolDown = CD() * 2;
    }
}

int IceStaff::CD()
{
    return 1;
}

QString unityOfMagic::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит" + QString::number(valueLevel[level]) + "урона стихиями ");
}

QString unityOfMagic::name()
{
    return "Единство стихий";
}

void unityOfMagic::effect(EnemyHero &NPC, Person &hero)
{
    double d;
    if(hero.stats.getMP() >= manaCostLevel[level - 1]){
        hero.stats.addMP(-manaCostLevel[level - 1]);
        if(chance(hero.stats.getCritMagicChance())){
            d = (valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2)) * hero.stats.getColdIncrease() * hero.stats.getFireIncrease() * hero.stats.getCritMagic();
            text = "критический урон! вы нанесли " + QString::number(damageCold(NPC,round(d / 2))) + " единиц урона холодом и " + QString::number(damageFire(NPC,round(d / 2))) + " единиц урона огнём";
        }else {
            d = (valueLevel[level - 1] + (hero.equip.getGeneralAttack() / 2)) * hero.stats.getColdIncrease() * hero.stats.getFireIncrease();
            text = "вы нанесли " + QString::number(damageCold(NPC,round(d / 2))) + " единиц урона холодом и " + QString::number(damageFire(NPC,round(d / 2))) + " единиц урона огнём";
        }
        coolDown = CD();
    }
    else
    {
        text = "вы не смогли удержать мощь магии и нанесли себе 20 урона";
        hero.stats.addHP(-20);
        coolDown = CD() * 2;
    }
}

int unityOfMagic::CD()
{
    return 2;
}

QString strongBeat::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: наносит двойной урон");
}

QString strongBeat::name()
{
    return "Мощный удар";
}

void strongBeat::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,hero.equip.getGeneralAttack() * 2 * hero.stats.getCrit())) + " единиц урона";
    }else {
        text = "вы нанесли " + QString::number(damage(NPC,hero.equip.getGeneralAttack() * 2)) + " единиц урона";
    }
    coolDown = CD();
}

int strongBeat::CD()
{
    return 6 - level;
}

QString furiousBlow::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: переносит часть силы в урон");
}

QString furiousBlow::name()
{
    return "Яростный удар";
}

void furiousBlow::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + percent(level * 10 + 30,hero.stats.getStr())) * hero.stats.getCrit())) + " единиц урона";
    }else {
        text = "вы нанесли " + QString::number(damage(NPC,hero.equip.getGeneralAttack() + percent(level * 10 + 30,hero.stats.getStr()))) + " единиц урона";
    }
    coolDown = CD();
}

int furiousBlow::CD()
{
    return 3;
}

QString toRam::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: переносит часть брони в урон");
}

QString toRam::name()
{
    return "Удар великана";
}

void toRam::effect(EnemyHero &NPC, Person &hero)
{
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() + percent(level * 10 + 30,(hero.equip.getGeneralArmor() + hero.stats.getBaseArmor()))) * hero.stats.getCrit())) + " единиц урона";
    }else {
        text = "вы нанесли " + QString::number(damage(NPC,hero.equip.getGeneralAttack() + percent(level * 10 + 30,(hero.equip.getGeneralArmor() + hero.stats.getBaseArmor())))) + " единиц урона";
    }
    coolDown = CD();
}

int toRam::CD()
{
    return 2;
}

QString berserkerRage::description()
{
    return ("Уровень:" + QString::number(level) + "\nЭффект: чем меньше у вас здоровья тем больше урона вы нанесёте");
}

QString berserkerRage::name()
{
    return "Ярость берсерка";
}

void berserkerRage::effect(EnemyHero &NPC, Person &hero)
{
    double d;
    d = percentNumNum(hero.stats.getMaxHP(),hero.stats.getMaxHP() - hero.stats.getHP());
    d = round(d / 20);
    if(chance(hero.stats.getCritChance())){
        text = "критический урон! вы нанесли " + QString::number(damage(NPC,(hero.equip.getGeneralAttack() * ((level * 0.1 + 1.5) * d)) * hero.stats.getCrit())) + " единиц урона";
    }else {
        text = "вы нанесли " + QString::number(damage(NPC,hero.equip.getGeneralAttack() * ((level * 0.1 + 1.5) * d))) + " единиц урона";
    }
    coolDown = CD();
}

int berserkerRage::CD()
{
    return 3;
}
