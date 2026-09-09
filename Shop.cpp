#include "Shop.h"
#include "Entity.h"
#include "Inventory.h"
using namespace std;

Shop::Shop(string nm, string reg) : name(nm), region(reg), restockTimer(0) {}

void Shop::addItem(Item item)
{
    stock.push_back(item);
}

string Shop::getName() const { return name; }
string Shop::getRegion() const { return region; }

void Shop::printStock()
{
    std::cout << "\n\033[1m\033[33m+=======================================================+\033[0m\n";
    std::cout << "\033[1m\033[33m|\033[0m  \033[37m[ " << name << " - " << region << " ]\033[0m\n";
    std::cout << "\033[1m\033[33m+=======================================================+\033[0m\n";
    std::cout << "\033[1m\033[33m|\033[0m\n";

    if (stock.empty())
    {
        std::cout << "\033[1m\033[33m|\033[0m   \033[30m(This shop has no items in stock...)\033[0m\n";
    }
    else
    {
        for (int i = 0; i < stock.size(); i++)
        {
            std::string rawName = "[" + std::to_string(stock[i].getId()) + "] " + stock[i].getName() + " (" + stock[i].getRarity() + ")";

            int dotCount = 40 - rawName.length();
            if (dotCount < 1) dotCount = 1;
            std::string dots(dotCount, '.');

            std::string colorCode = "\033[37m";
            if (stock[i].getRarity() == "Uncommon")       colorCode = "\033[32m";
            else if (stock[i].getRarity() == "Rare")      colorCode = "\033[34m";
            else if (stock[i].getRarity() == "Mythic")    colorCode = "\033[35m";
            else if (stock[i].getRarity() == "Legendary") colorCode = "\033[33m";

            std::cout << "\033[1m\033[33m|\033[0m   "
                      << colorCode << rawName << "\033[0m"
                      << " \033[30m" << dots << "\033[0m"
                      << " \033[1m\033[33m" << stock[i].getValue() << " gold\033[0m"
                      << " \033[30m(x" << stock[i].getQuantity() << ")\033[0m\n";
        }
    }

    std::cout << "\033[1m\033[33m|\033[0m\n";
    std::cout << "\033[1m\033[33m+=======================================================+\033[0m\n";
}

bool Shop::buyItem(int itemID, Entity &player, Inventory &inventory)
{
    int foundIndex = -1;
    for (int i = 0; i < stock.size(); i++)
    {
        if (stock[i].getId() == itemID)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        std::cout << "\033[31mThere is no item with that ID in this shop!\033[0m\n";
        return false;
    }

    if (stock[foundIndex].getQuantity() <= 0)
    {
        std::cout << "\033[31mThat item is out of stock!\033[0m\n";
        return false;
    }

    int price = stock[foundIndex].getValue();

    if (player.getCoins() < price)
    {
        std::cout << "\033[31mYou don't have enough gold! You need \033[1m"
                  << price << " gold\033[0m\033[31m but only have \033[1m"
                  << player.getCoins() << " gold\033[0m\033[31m.\033[0m\n";
        return false;
    }

    player.addCoins(-price);
    inventory.addItem(Item(stock[foundIndex].getName(), stock[foundIndex].getId(),
                           stock[foundIndex].getCategory(), stock[foundIndex].getValue(),
                           1, stock[foundIndex].getRarity()));
    stock[foundIndex].removeQuantity(1);

    std::cout << "\033[32mYou purchased \033[1m" << stock[foundIndex].getName()
              << "\033[0m\033[32m for \033[1m" << price
              << " gold\033[0m\033[32m. Remaining gold: \033[1m"
              << player.getCoins() << "\033[0m\033[32m.\033[0m\n";

    return true;
}