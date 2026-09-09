#pragma once
#include <string>

enum class WeaponClass {
    Dagger,
    LightSword,
    MediumSword,
    HeavySword,
    Axe,
    Spear,
    Bow

};
class Weapon
{
private:
    std::string name;
    int level;
    int minDamage;
    int maxDamage;
    int critRoll;
    int doubleHitRoll;
    int missRoll;
    int currentDurability;
    int maxDurability;

public:
    Weapon();
    int getLevel();
    std::string getName();
    int getMinDamage();
    int getMaxDamage();
    int getCritRoll();
    int getDoubleHitRoll();
    int getMissRoll();
    int getCurrentDurability();
    int getMaxDurability();
    void generateStats(std::string weaponName, int type, WeaponClass weaponCategory, int weaponLevel);
    void weaponUpgradeStats(int weaponLevel);
    void decreaseDurability(int amount);
    void repairWeapon(int amount);
    bool isBroken();
    int calculateRepairCost(bool isFullRepair);
};