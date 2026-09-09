#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include <iostream>

class Entity;
class Inventory;
class Shop
{
private:
    std::string name;
    std::string region;
    std::vector<Item> stock;
    int restockTimer;

public:
    Shop(std::string nm, std::string reg);
    void addItem(Item);
    void printStock();
    bool buyItem(int itemID, Entity &player, Inventory &inventory);
    std::string getName() const;
    std::string getRegion() const;
};
