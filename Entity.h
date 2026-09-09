#pragma once
#include <string>
#include "Weapon.h"


class Entity
{
private:
    std::string name;
    int level;
    int currentHP;
    int maxHP;
    int exp;
    int maxExp;
    int coins;
    int maxMana;
    int currentMana;

public:
    Entity();
    Weapon equippedWeapon;
    std::string getName();
    void setName(std::string newName);
    int getLevel();
    int getCurrentHP();
    int getMaxHP();
    int getExp();
    int getMaxExp();
    int getCoins();
    int getMaxMana();
    int getCurrentMana();
    void heal(int amount);
    void damage(int amount);
    void checkLevelUp();
    void enemyLevel(int playerLevel, float baseHP, float bonusHP);
    void addCoins(int amount);
    void addExp(int amount);
    void setCurrentHP(int hp);
    void setCoins(int amount);
    bool useMana(int amount);
    void restoreMana(int amount);
};