#include "Inventory.h"
#include "Tools.h"
#include "Entity.h"
#include <iostream>

Inventory::Inventory()
{
    items = {};
    weaponLevel = 1;
}

void Inventory::addItem(Item newItem)
{
    int ok = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getId() == newItem.getId())
        {
            items[i].addQuantity(newItem.getQuantity());
            ok = 1;
            break;
        }
    }
    if (ok == 0)
    {
        items.push_back(newItem);
    }
}

bool Inventory::useConsumableItem(int itemID, Entity &player, Entity &enemy)
{
    int foundIndex = -1;

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getId() == itemID)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1)
    {
        std::cout << "\033[31mYou don't have an item with that ID in your backpack!\033[0m\n";
        return false;
    }
    Item targetItem = items[foundIndex];

    if (targetItem.getCategory() != "Consumable")
    {
        std::cout << "\033[31mYou can't USE that right now! It's a " << targetItem.getCategory() << ".\033[0m\n";
        return false;
    }

    if (targetItem.getId() == 1) // BANDAGE
    {
        player.heal(15);
        std::cout << "\033[32mYou patch yourself up with the dirty Sump Bandage. (+15 HP)\033[0m\n";
    }
    else if (targetItem.getId() == 2) // HEALING POTION
    {
        player.heal(40);
        std::cout << "\033[32mYou drink the Healing Potion. A warm sensation fills your body! (+40 HP)\033[0m\n";
    }
    else if (targetItem.getId() == 3) // SURFACE MANA CRYSTAL
    {
        player.restoreMana(25);
        std::cout << "\033[36mYou crush the Surface Mana Crystal. A cool energy restores your mind. (+25 MP)\033[0m\n";
    }
    else if (targetItem.getId() == 4) // VERDANT SPORES
    {
    }
    else if (targetItem.getId() == 5) // LIQUID MANA FLASK
    {
        player.restoreMana(75);
        std::cout << "\033[36mYou drink the Liquid Mana. Pure arcane power flows through you! (+75 MP)\033[0m\n";
    }
    else if (targetItem.getId() == 6) // ACID FLASK
    {
        // Aici verificam daca suntem in lupta! Daca inamicul are maxHP 0, probabil suntem in oras.
        if (enemy.getMaxHP() <= 0)
        {
            std::cout << "\033[31mThere is no enemy to throw the Acid Flask at!\033[0m\n";
            return false; // Nu il consumam
        }

        enemy.damage(65);
        std::cout << "\033[35mYou smash the Acid Flask onto the enemy! The armor melts! (65 DMG)\033[0m\n";
    }
    else if (targetItem.getId() == 7) // HALO DUST
    {
    }
    else if (targetItem.getId() == 8) // MOONVEIL WATER
    {
    }
    else if (targetItem.getId() == 9) // PURE REJUVENATION ELIXIR
    {
        player.heal(player.getMaxHP()); // Heal complet
        std::cout << "\033[1m\033[33mThe Pure Elixir flows through you. You are completely restored!\033[0m\n";
        player.restoreMana(player.getMaxMana());
    }
    else if (targetItem.getId() == 10) // WHETSTONE
    {
        player.equippedWeapon.repairWeapon(15);
        std::cout << "\033[36mYou use the Whetstone to sharpen your weapon. (+15 Durability)\033[0m\n";
    }
    else
    {
        std::cout << "This item has no use effect yet.\n";
        return false;
    }

    items[foundIndex].removeQuantity(1);
    if (items[foundIndex].getQuantity() <= 0)
    {
        items.erase(items.begin() + foundIndex);
    }
    return true;
}

bool Inventory::isEmpty()
{
    return items.empty();
}

void Inventory::printBackpack()
{
    for (int i = 0; i < items.size(); i++)
    {
        // Salvam numele brut ca sa ii putem masura lungimea corect (fara culori ANSI)
        std::string rawName = "[" + std::to_string(items[i].getId()) + "] " + items[i].getName() + " (" + items[i].getRarity() + ")";

        // Calculam de cate puncte avem nevoie ca sa ajungem mereu la aceeasi margine
        int dotCount = 50 - rawName.length();
        if (dotCount < 1)
            dotCount = 1;
        std::string dots(dotCount, '.');

        // Sistemul de culori pentru Raritate!
        std::string colorCode = "\033[37m"; // White default (Common)
        if (items[i].getRarity() == "Uncommon")
            colorCode = "\033[32m"; // Green
        else if (items[i].getRarity() == "Rare")
            colorCode = "\033[34m"; // Blue
        else if (items[i].getRarity() == "Mythic")
            colorCode = "\033[35m"; // Magenta
        else if (items[i].getRarity() == "Legendary")
            colorCode = "\033[33m"; // Gold

        // Printam tot rândul asamblat
        std::cout << "\033[1m\033[33m|\033[0m   " << colorCode << rawName << " \033[30m" << dots << " \033[1m\033[32mx" << items[i].getQuantity() << "\033[0m\n";
    }
}

int Inventory::getWeaponLevel()
{
    return weaponLevel;
}

  void Inventory::printConsumables()
{
    bool found = false;

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getCategory() == "Consumable")
        {
            found = true;

            std::string rawName = "[" + std::to_string(items[i].getId()) + "] " + items[i].getName() + " (" + items[i].getRarity() + ")";

            int dotCount = 50 - rawName.length();
            if (dotCount < 1) dotCount = 1;
            std::string dots(dotCount, '.');

            std::string colorCode = "\033[37m";
            if (items[i].getRarity() == "Uncommon")      colorCode = "\033[32m";
            else if (items[i].getRarity() == "Rare")     colorCode = "\033[34m";
            else if (items[i].getRarity() == "Mythic")   colorCode = "\033[35m";
            else if (items[i].getRarity() == "Legendary") colorCode = "\033[33m";

            std::cout << "\033[1m\033[33m|\033[0m   " << colorCode << rawName << " \033[30m" << dots << " \033[1m\033[32mx" << items[i].getQuantity() << "\033[0m\n";
        }
    }

    if (!found)
        std::cout << "\033[1m\033[33m|\033[0m   \033[30m(You have no consumables in your backpack...)\033[0m\n";
}