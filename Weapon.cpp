#include "Weapon.h"
#include "Tools.h"

Weapon::Weapon()
{
    name = "Unarmed";
    level = 1;
    minDamage = 1;
    maxDamage = 2;
}

int Weapon::getCritRoll() { return critRoll; }
int Weapon::getDoubleHitRoll() { return doubleHitRoll; }
int Weapon::getMissRoll() { return missRoll; }
int Weapon::getMinDamage() { return minDamage; }
int Weapon::getMaxDamage() { return maxDamage; }
std::string Weapon::getName() { return name; }
int Weapon::getLevel() { return level; }
int Weapon::getCurrentDurability() { return currentDurability; }
int Weapon::getMaxDurability() { return maxDurability; }

void Weapon::generateStats(std::string weaponName, int type, WeaponClass weaponCategory, int weaponLevel)
{
    if (type == 1)
    {
        minDamage = 6 + (weaponLevel - 1) * 1.5;
        maxDamage = 12 + (weaponLevel - 1) * 1.5;
        currentDurability = 100;
        maxDurability = 100;
    }
    else if (type == 2)
    {
        minDamage = 12 + (weaponLevel - 1) * 2.5;
        maxDamage = 20 + (weaponLevel - 1) * 2.5;
        currentDurability = 100;
        maxDurability = 100;
    }
    else if (type == 3)
    {
        minDamage = 20 + (weaponLevel - 1) * 3;
        maxDamage = 32 + (weaponLevel - 1) * 3;
        currentDurability = 100;
        maxDurability = 100;
    }
    
    // DEFAULT (fallback — arme speciale gen Wrench, Claws)
missRoll = 10; critRoll = 5; doubleHitRoll = 5;

if (weaponCategory == WeaponClass::Dagger) {
    missRoll = 5; critRoll = 8; doubleHitRoll = 15;
}
else if (weaponCategory == WeaponClass::LightSword) {
    missRoll = 8; critRoll = 6; doubleHitRoll = 10;
}
else if (weaponCategory == WeaponClass::MediumSword) {
    missRoll = 10; critRoll = 5; doubleHitRoll = 8;
}
else if (weaponCategory == WeaponClass::HeavySword) {
    missRoll = 18; critRoll = 4; doubleHitRoll = 0;
}
else if (weaponCategory == WeaponClass::Axe) {
    missRoll = 20; critRoll = 4; doubleHitRoll = 0;
}
else if (weaponCategory == WeaponClass::Spear) {
    missRoll = 8; critRoll = 5; doubleHitRoll = 10;
}
else if (weaponCategory == WeaponClass::Bow) {
    missRoll = 15; critRoll = 7; doubleHitRoll = 0;
}
    name = weaponName;
    level = weaponLevel;
}

void Weapon::weaponUpgradeStats(int weaponLevel)
{
    minDamage += (weaponLevel - 1) * 2.5;
    maxDamage += (weaponLevel - 1) * 2.5;
    if (critRoll < 30)

    {
        critRoll += 2;
    }
    if (critRoll >= 30)

    {
        critRoll = 30;
    }
    if (missRoll > 5)

    {
        missRoll -= 2;
    }
    if (missRoll <= 5)

    {
        missRoll = 5;
    }

    if (doubleHitRoll < 30)

    {
        doubleHitRoll += 2;
    }
    if (doubleHitRoll >= 30)

    {
        doubleHitRoll = 30;
    }
    level++;
}
void Weapon::decreaseDurability(int amount)
{
    currentDurability -= amount;
    if (currentDurability < 0)
    {
        currentDurability = 0;
    }
}
void Weapon::repairWeapon(int amount)
{
    currentDurability += amount;
    if (currentDurability > maxDurability)
    {
        currentDurability = maxDurability;
    }
}

bool Weapon::isBroken()
{
    if (currentDurability <= 0)
    {
        return true;
    }
    return false;
}
int Weapon::calculateRepairCost(bool isFullRepair)
{
    int repairPoints = maxDurability - currentDurability;
    int basePricePerPoint = 2;
    int costTotal = 0;
    if (isFullRepair == true)
    {
        costTotal = repairPoints * basePricePerPoint;
        if (isBroken())
        {
            costTotal = repairPoints * 3;
        }
        return costTotal;
    }
    else 
    {
        costTotal = 50 * basePricePerPoint;
        if (isBroken())
        {
            costTotal = repairPoints * 3;
        }
        return costTotal;
    }
}
