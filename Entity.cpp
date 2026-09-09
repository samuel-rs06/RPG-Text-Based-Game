#include "Entity.h"
#include "Tools.h"
#include <iostream>

Entity::Entity()
{
    name = "Unnamed";
    level = 1;
    exp = 0;
    maxExp = 100;
    currentHP = 100;
    maxHP = 100;
    coins = 1;
    currentMana = 50;
    maxMana = 50;
}
std::string Entity::getName()
{
    return name;
}
int Entity::getLevel()
{
    return level;
}
int Entity::getCurrentMana()
{
    return currentMana;
}
int Entity::getMaxMana()
{
    return maxMana;
}
int Entity::getCurrentHP()
{
    return currentHP;
}
int Entity::getMaxHP()
{
    return maxHP;
}
int Entity::getExp()
{
    return exp;
}
int Entity::getMaxExp()
{
    return maxExp;
}
int Entity::getCoins()
{
    return coins;
}

void Entity::heal(int amount)

{
    if (currentHP + amount >= maxHP)
        currentHP = maxHP;
    else
        currentHP += amount;
}

void Entity::damage(int amount)

{
    currentHP -= amount;
    if (currentHP <= 0)
        currentHP = 0;
}

void Entity::checkLevelUp()

{
    while (exp >= maxExp)

    {
        exp = exp - maxExp;
        maxExp = maxExp * 2;
        maxHP = maxHP + 25;
        maxMana += 10;
        currentMana = maxMana;
        currentHP = maxHP;
        level++;
        std::cout << "\n\033[1m\033[33m*** LEVEL UP! You are now level " << level << " ***\033[0m\n";
    }
}

void Entity::enemyLevel(int playerLevel, float baseHP, float bonusHP)

{
    level = getRandomNumber(playerLevel - 2, playerLevel + 2);
    if (level < 1)
        level = 1;
    maxHP = baseHP + (level * bonusHP);
    currentHP = maxHP;
    coins = getRandomNumber(10 * level, 15 * level);
}
void Entity::setName(std::string newName)
{
    name = newName;
}
void Entity::addCoins(int amount)
{
    coins += amount;
}
void Entity::addExp(int amount)
{
    exp += amount;
}
void Entity::setCurrentHP(int hp)
{
    currentHP = hp;
    // O mică plasă de siguranță:
    if (currentHP > maxHP)
        currentHP = maxHP;
    if (currentHP < 0)
        currentHP = 0;
}
void Entity::setCoins(int amount)
{
    coins = amount;
}
bool Entity::useMana(int amount)
{
    if (currentMana >= amount)
    {
        currentMana -= amount;
        return true;
    }
    std::cout << "Not enough mana!\n";
    return false;
}
void Entity::restoreMana(int amount)
{
    currentMana += amount;
    if (currentMana >= maxMana)
    {
        currentMana = maxMana;
    }
}