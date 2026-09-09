#include "Item.h"
#include "Tools.h"

// 1. CONSTRUCTORUL IMPLICIT (Default)
// Acesta este apelat automat când scrii doar "Item loot;"
Item::Item()
{
    name = "Unknown";
    id = 0;
    category = "None";
    value = 0;
    quantity = 0;
    rarity = "Common";
}

// 2. CONSTRUCTORUL PRINCIPAL (Builder-ul)
// Acesta te ajută să creezi iteme valide dintr-o singură linie de cod
Item::Item(std::string newName, int newId, std::string newCategory, int newValue, int newQuantity, std::string newRarity)
{
    name = newName;
    id = newId;
    category = newCategory;
    value = newValue;
    quantity = newQuantity;
    rarity = newRarity;
}

// 3. GETTERE (Oferă acces de citire pentru variabilele private)
std::string Item::getName()
{
    return name;
}
int Item::getId()
{
    return id;
}
std::string Item::getCategory()
{
    return category;
}
int Item::getValue()
{
    return value;
}
int Item::getQuantity()
{
    return quantity;
}
std::string Item::getRarity()
{
    return rarity;
}

// 4. SETTERE (Oferă acces modificat și controlat)
void Item::addQuantity(int amount)
{
    if (amount > 0)
    {
        quantity += amount;
    }
}

void Item::removeQuantity(int amount)
{
    if (amount > 0)
    {
        quantity -= amount;

        // Filtrul de siguranță: Nu putem avea cantitate negativă în ghiozdan!
        if (quantity < 0)
        {
            quantity = 0;
        }
    }
}
void Item::setCategory(std::string newCategory)
{
    category = newCategory;
}
void Item::setValue(int amount)
{
    value = amount;
}