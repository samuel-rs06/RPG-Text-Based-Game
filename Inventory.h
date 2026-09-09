#pragma once
#include <vector>
#include <iostream>
#include "Item.h" // Aici îi dăm Inventarului schița Itemului

class Entity;

class Inventory
{
private:
    std::vector<Item> items;
    int weaponLevel;

public:
    // Constructorul
    Inventory();

    // Metodele de bază
    void addItem(Item newItem);
    int getWeaponLevel();
    void upgradeWeapon();

    // Aici mutăm Dispecerul tău, el devine o metodă a Inventarului!
    // Am păstrat struct Entity& pentru că încă nu l-am transformat în clasă.
    bool useConsumableItem(int itemID, Entity &player, Entity &enemy);

    // O funcție nouă, extrem de utilă pentru viitor:
    void printBackpack();
    void printConsumables();

    bool isEmpty();
};