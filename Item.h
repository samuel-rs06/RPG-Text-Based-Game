#pragma once
#include <string>

class Item
{
private:
    // Aici stau datele ascunse. Nimeni din afara clasei nu le poate modifica direct.
    std::string name;
    int id;
    std::string category;
    int value;
    int quantity;
    std::string rarity;

public:
    // 1. CONSTRUCTORUL IMPLICIT (Default)
    // C++ are nevoie de el când creezi un vector gol de iteme.
    Item();

    // 2. CONSTRUCTORUL PRINCIPAL (The Builder)
    // Te forțează să dai aceste date când creezi un item nou. Nu poți crea un item "pe jumătate".
    Item(std::string newName, int newId, std::string newCategory, int newValue, int newQuantity, std::string newRarity);

    // 3. GETTERE (Metode de acces)
    // Deoarece variabilele de mai sus sunt private, folosim aceste funcții ca să le putem "citi" din Inventar.
    std::string getName();
    int getId();
    std::string getCategory();
    int getValue();
    int getQuantity();
    std::string getRarity();

    // 4. SETTERE (Metode de modificare controlată)
    // Permitem modificarea cantității (ex: când bei o poțiune sau cumperi una)
    void addQuantity(int amount);
    void removeQuantity(int amount);
    void setCategory(std::string newCategory);
    void setValue(int amount);
};