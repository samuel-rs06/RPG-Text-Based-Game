#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "Tools.h"
#include "Item.h"
#include "Weapon.h"
#include "Inventory.h"
#include "Entity.h"

using namespace std;

Item generateItem(string itemName, string itemRarity, int ID, int quantity, int value)
{
    return Item(itemName, ID, "Unknown", value, quantity, itemRarity);
}

struct LootDrop
{
    string name;
    int id;
    string rarity;
    int chance; // cate iteme de genul exista si pot sa pice
};

Item generateConsumable(int enemyLevel) // GENERATE CONSUMABLE
{
    Item loot;
    int itemRoll = getRandomNumber(1, 100);

    if (itemRoll <= 30)
    {

        loot = generateItem("Bandage", "Common", 1, getRandomNumber(1, 2), 5);
    }

    else if (itemRoll <= 55)
    {

        loot = generateItem("Healing Potion", "Uncommon", 2, 1, 10);
    }

    else if (itemRoll <= 68)
    {

        loot = generateItem("Surface Mana Crystal", "Uncommon", 3, 1, 30);
    }

    else if (itemRoll <= 80)
    {

        loot = generateItem("Verdant Spores", "Rare", 4, 1, 45);
    }

    else if (itemRoll <= 88)
    {

        loot = generateItem("Liquid Mana Flask", "Rare", 5, 1, 75);
    }

    else if (itemRoll <= 94)
    {

        loot = generateItem("Acid Flask", "Mythic", 6, 1, 90);
    }

    else if (itemRoll <= 97)
    {

        loot = generateItem("Halo Dust", "Mythic", 7, 1, 150);
    }

    else if (itemRoll <= 99)
    {

        loot = generateItem("Moonveil Water", "Legendary", 8, 1, 180);
    }

    else if (itemRoll == 100)
    {

        loot = generateItem("Pure Rejuvenation Elixir", "Legendary", 9, 1, 340);
    }
    loot.setCategory("Consumable");
    return loot;
}
Item generateMaterial(int enemyLevel) // GENERATE MATERIAL
{
    Item loot;
    int idCount = 100;
    loot.setCategory("Material");
    loot.addQuantity(1);
    string possibleNames[22] = {"Iron Ore", "Scrap Metal", "Mermaid Scale", "Goblin Eye", "Obsidian", "Magma Marrow", "Cindersilk", "Abyssal Coral", "Black Pearl", "Tide Glass", "Saltstone", "Rootsteel", "Permafrost Shards", "Seraphim Feathers", "Solar Glass", "White Iron", "Truth Crystal", "Red Steel", "Black Mithril", "Coldforge Iron", "Orc Ear", "Toxic Sludge"};
    LootDrop dropTable[] = {
        {"Scrap Metal", 100, "Common", 100},
        {"Iron Ore", 101, "Common", 100},
        {"Goblin Eye", 102, "Common", 100},
        {"Orc Ear", 103, "Common", 100},
        {"Toxic Sludge", 104, "Common", 100},
        {"Obsidian", 105, "Uncommon", 50},
        {"Tide Glass", 106, "Uncommon", 50},
        {"Saltstone", 107, "Uncommon", 50},
        {"Cindersilk", 108, "Uncommon", 50},
        {"Magma Marrow", 109, "Rare", 10},
        {"Rootsteel", 110, "Rare", 15},
        {"Solar Glass", 111, "Rare", 10},
        {"Red Steel", 112, "Rare", 15},
        {"Coldforge Iron", 113, "Rare", 10},
        {"Mermaid Scale", 114, "Mythic", 3},
        {"Black Pearl", 115, "Mythic", 2},
        {"Abyssal Coral", 116, "Mythic", 5},
        {"Permafrost Shards", 117, "Mythic", 2},
        {"White Iron", 118, "Mythic", 5},
        {"Truth Crystal", 119, "Mythic", 2},
        {"Black Mithril", 120, "Mythic", 3},
        {"Seraphim Feathers", 121, "Legendary", 1},
    };

    int numberOfItems = sizeof(dropTable) / sizeof(dropTable[0]);

    int totalChance = 0;
    for (int i = 0; i < numberOfItems; i++)
    {
        totalChance += dropTable[i].chance;
    }
    int itemDrop = getRandomNumber(1, totalChance);

    for (int i = 0; i < numberOfItems; i++)
    {
        itemDrop -= dropTable[i].chance;

        if (itemDrop <= 0)
        {
            int calculatedValue = 0;
            if (dropTable[i].rarity == "Common")
                calculatedValue = enemyLevel * 3;
            else if (dropTable[i].rarity == "Uncommon")
                calculatedValue = enemyLevel * 15;
            else if (dropTable[i].rarity == "Rare")
                calculatedValue = enemyLevel * 30;
            else if (dropTable[i].rarity == "Mythic")
                calculatedValue = enemyLevel * 50;
            else if (dropTable[i].rarity == "Legendary")
                calculatedValue = enemyLevel * 100;

            // Acum cream itemul cu TOATE datele corecte de la inceput!
            loot = Item(dropTable[i].name, dropTable[i].id, "Material", calculatedValue, 1, dropTable[i].rarity);
            break;
        }
    }

    return loot;
}
Item generateNoDrop()
{
    return Item("Nothing", 0, "None", 0, 0, "None");
}

Item generateArtifact(int enemyLevel)
{
    Item loot;
    loot.setCategory("Artifact"); // santier de lucru
    loot.addQuantity(1);
    return loot;
}

Item generateRandomLoot(int enemyLevel)
{
    int luckRoll = getRandomNumber(1, 100);
    if (luckRoll <= 30)
    {
        return generateNoDrop();
    }
    int lootRoll = getRandomNumber(1, 100);
    if (lootRoll <= 50)
        return generateConsumable(enemyLevel);
    else if (lootRoll <= 85)
        return generateMaterial(enemyLevel);
    else
        return generateArtifact(enemyLevel);
}


    /*void restock()
        {
            stockArrows = maxArrows;
            stockBandages = maxBandages;
            stockPotions = maxPotions;
            stockPoisonArrows = maxPoisonArrows;
        }

        int calculatePrice(int itemID, int playerlevel)
        {
            int inflation = (playerlevel - 1) * 2;
            if (itemID == 1)
                return basePricePotion + inflation;
            else if (itemID == 2)
                return basePriceVenomArrow + (inflation * 2);
            else if (itemID == 3)
                return basePriceBandages + inflation;
            else if (itemID == 4)
                return basePriceArrow + inflation;
            else if (itemID == 5)
                return basePriceWeaponUpgrade + (inflation * 5);

            return 99999;
        }*/

struct AttackResult
{
    int damage;
    bool isCrit;
    bool isDouble;
};
AttackResult calculateAttackDamage(Weapon &attackerWeapon) // CALCULATE ATTACK DAMAGE
{
    AttackResult result = {0, false, false};

    int isMiss = getRandomNumber(1, 100);
    if (isMiss <= attackerWeapon.getMissRoll())
    {
        std::cout << "\033[31m* SWOOSH! Attack MISSED! *\033[0m\n";
        return result;
        ;
    }
    else
    {
        int damage = getRandomNumber(attackerWeapon.getMinDamage(), attackerWeapon.getMaxDamage());
        int isCrit = getRandomNumber(1, 100);
        if (isCrit <= attackerWeapon.getCritRoll())

        {
            result.isCrit = true;
        }

        int isDoubleHit = getRandomNumber(1, 100);
        int strikes = 1;
        if (isDoubleHit <= attackerWeapon.getDoubleHitRoll())

        {
            result.isDouble = true;
            strikes = 2;
        }
        if (result.isCrit)
        {
            std::cout << "\033[33m* CRITICAL HIT! *\033[0m\n";
            damage += attackerWeapon.getMaxDamage() * 1.5;
        }
        if (result.isDouble)
        {
            std::cout << "\033[36m* FAST REFLEXES! DOUBLE HIT! *\033[0m\n";
            damage = damage + (damage / 2);
        }

        result.damage = damage;
        return result;
    }
}
void runIntro(Entity &player) // FUNCTIE PLAY INTRO
{
    system("cls");

    std::cout << "\n\033[3mDrip... Drip... Drip...\033[0m\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "The acidic rain of Mograndia bites at your skin.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "You open your eyes. The air is thick with sulfur, coal, and the stinging scent of burned mana.\n";
    std::cout << "You are in the gutters of Level 4: The Sump. The lowest of the low.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Next to you in the mud lies a man. Dead. A smuggler from the Rust Markets.\n";
    std::cout << "Suddenly, the ground vibrates. Heavy, metallic footsteps echo through the smog.\n";
    std::cout << "\033[31mThe Pyre Guard.\033[0m They are coming this way.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "If they find you next to a dead body, you are bound for the Indenture mines. Or worse.\n";
    std::cout << "You must run. But you can't survive The Sump unarmed.\n";
    std::cout << "The smuggler's coat is torn open. Inside, you see a few rusted tools of survival.\n";
    std::cout << "You only have time to grab ONE before the guards turn the corner:\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "--------------------------------------------\n";
    std::cout << "\033[1m[1] A massive, jagged piece of iron.\033[0m\n";
    std::cout << "    *It's heavy and slow to swing, but a single clean hit will crush armor.* (Heavy Sword)\n\n";

    std::cout << "\033[1m[2] A standard, soot-stained guard blade.\033[0m\n";
    std::cout << "    *Perfectly balanced. Reliable in any situation.* (Medium Sword)\n\n";

    std::cout << "\033[1m[3] A short, needle-like shiv.\033[0m\n";
    std::cout << "    *Lacks raw power, but its precision guarantees you almost never miss a vital spot.* (Small Sword)\n\n";

    std::cout << "\033[1m[4] A brutal, rusted cleaver.\033[0m\n";
    std::cout << "    *Unwieldy, but its jagged edge promises devastating, deep wounds.* (Axe)\n\n";

    std::cout << "\033[1m[5] A sharpened iron rebar.\033[0m\n";
    std::cout << "    *Light enough to let you quickly thrust twice before the enemy reacts.* (Spear)\n\n";

    std::cout << "\033[1m[6] A mechanical contraption with steel strings.\033[0m\n";
    std::cout << "    *Hard to aim in the dark, but a well-placed shot is absolutely lethal.* (Bow)\n\n";

    std::cout << "\033[1m[7] Twin blades hidden in the smuggler's boots.\033[0m\n";
    std::cout << "    *Weak alone, but they allow for an overwhelming flurry of lightning-fast strikes.* (Daggers)\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "\033[1mQUICK! CHOOSE YOUR WEAPON (1-7): \033[0m";

    int ok = 0;
    std::string weaponChoice;

    while (ok == 0)

    {
        std::cin >> weaponChoice;
        for (int i = 0; i < weaponChoice.length(); i++)
            weaponChoice[i] = toupper(weaponChoice[i]);

        if (weaponChoice == "1" || weaponChoice == "HEAVY SWORD")

        {
            player.equippedWeapon.generateStats("Heavy Sword", 3, WeaponClass::HeavySword, 1);
            std::cout << "\033[32mYou heave the heavy iron onto your shoulder.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "2" || weaponChoice == "MEDIUM SWORD")

        {
            player.equippedWeapon.generateStats("Medium Sword", 2, WeaponClass::MediumSword, 1);
            std::cout << "\033[32mYou grip the balanced blade tightly.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "3" || weaponChoice == "SMALL SWORD")

        {
            player.equippedWeapon.generateStats("Small Sword", 1, WeaponClass::LightSword, 1);
            std::cout << "\033[32mYou test the needle point of the shiv.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "4" || weaponChoice == "AXE")

        {
            player.equippedWeapon.generateStats("Axe", 3, WeaponClass::Axe, 1);
            std::cout << "\033[32mYou grab the rusted cleaver, feeling its brutal weight.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "5" || weaponChoice == "SPEAR")

        {
            player.equippedWeapon.generateStats("Spear", 2, WeaponClass::Spear, 1);
            std::cout << "\033[32mYou pick up the iron rebar, pointing its sharp end towards the shadows.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "6" || weaponChoice == "BOW")

        {
            player.equippedWeapon.generateStats("Bow", 2, WeaponClass::Bow, 1);
            std::cout << "\033[32mYou sling the mechanical bow over your shoulder, hoping your aim is true.\033[0m\n";
            ok = 1;
        }
        else if (weaponChoice == "7" || weaponChoice == "DAGGERS")

        {
            player.equippedWeapon.generateStats("Daggers", 2, WeaponClass::Dagger, 1);
            std::cout << "\033[32mYou slip the twin blades into your sleeves, ready to strike from the dark.\033[0m\n";
            ok = 1;
        }
        else
        {
            std::cout << "\033[31mThe guards are almost here! Pick a valid weapon (1-7)!\033[0m\n";
        }
    }

    std::cout << "\n\033[32mYou snatch the weapon, your hands shaking, and dive into the labyrinth of steam pipes just as the guards arrive.\033[0m\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    system("cls");
    std::cout << "You run blindly through the dark alleys until you hit a dead end.\n";
    std::cout << "Suddenly, a spark illuminates the shadows.\n";
    std::cout << "A Goblin mechanic drops from a rusty pipe, holding a sparking wrench. He blocks your only exit.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "\033[33m'Who are you, surface-rat?!' \033[0mhe snarls, raising his tool. \033[33m'Give me a name to put on your gravestone!'\033[0m\n";
    std::cout << "\n\033[1mENTER YOUR NAME: \033[0m";

    std::string inputName;
    std::cin >> inputName;
    player.setName(inputName);

    // Observă că pentru a-l afișa din nou, trebuie să folosești Getter-ul:
    std::cout << "\n\033[33m'" << player.getName() << "?' \033[0mthe Goblin spits... \n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "\033[1m\033[31m*** INITIATING COMBAT ***\033[0m\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void runFirstLoreFight(Entity &player, Entity &goblin, Inventory &entityInventory) // FUNCTIE PLAY FIRST LORE BATTLE
{
    system("cls");
    std::cout << "*You are now fighting a Goblin!*\n";

    goblin.enemyLevel(2, 80, 0);
    goblin.setCoins(getRandomNumber(50, 70));

    goblin.equippedWeapon.generateStats("Sparking Wrench", 2, WeaponClass::MediumSword, 2);

    std::cout << "The Goblin swings his sparking wrench at you!\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "\033[3m--------------------FIGHT--------------------\n";

    char playerChoice[256];

    while (goblin.getCurrentHP() > 0 && player.getCurrentHP() > 0)

    {

        std::cout << "Current player HP is " << player.getCurrentHP() << ".\n";
        std::cout << "Current goblin HP is " << goblin.getCurrentHP() << ".\n";
        std::cout << "Choose your action: \n[1] Attack\n[2] Heal\n";

        std::cin >> playerChoice;
        for (int i = 0; i < strlen(playerChoice); i++)
            playerChoice[i] = toupper(playerChoice[i]);

        if (strcmp("HEAL", playerChoice) == 0 || strcmp("2", playerChoice) == 0)

        {
            std::cout << "\033[31mYou have no potions yet!\033[0m\n";
            continue; // Sarim peste atacul inamicului
        }
        else if (strcmp("ATTACK", playerChoice) == 0 || strcmp("1", playerChoice) == 0)

        {
            AttackResult attack = calculateAttackDamage(player.equippedWeapon);
            if (attack.damage > 0)
            {
                if (player.equippedWeapon.isBroken())
                {
                    attack.damage = 1;
                    std::cout << "\033[31mYou strike with a broken weapon! It barely leaves a scratch (1 DMG)!\033[0m\n";
                }
                else
                {
                    int durLoss = 1;
                    if (attack.isCrit)
                        durLoss += 2;

                    if (attack.isDouble)
                        durLoss += 1;

                    player.equippedWeapon.decreaseDurability(durLoss);
                    if (player.equippedWeapon.isBroken())
                    {
                        std::cout << "\033[31m*CRACK* Your weapon just broke on impact!\033[0m\n";
                    }
                }

                goblin.damage(attack.damage);
                std::cout << "You dealt \033[1m" << attack.damage << " damage\033[0m to the Goblin!\n";

                // --- MAGIA CINEMATICĂ ---
                // Verificăm dacă ACEASTĂ lovitură îl va ucide pe Goblin
                if (goblin.getCurrentHP() <= 0)
                {
                    std::cout << "\n\033[1m\033[31m*** COMBAT INTERRUPTED ***\033[0m\n\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    // Mesajul tău personalizat:
                    std::cout << "\033[33mYour strike was a critical, devastating blow!\033[0m\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    std::cout << "You see the goblin slowly retreating, bleeding heavily from the wound.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    std::cout << "\033[33m'You're crazy, surface-rat! You don't know who you're messing with!'\033[0m he coughs, spitting black blood.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    std::cout << "He throws a handful of rusted gears and smoke-pellets at your feet. A thick, foul-smelling cloud erupts.\n";
                    std::cout << "By the time the smoke clears, the alley is empty. You hear his voice echoing through the pipes above:\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    std::cout << "\033[33m'The Rust-Jaw Clan will remember this! We'll find you!'\033[0m\n\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    std::cout << "He is gone. But in his panic, he dropped a small, greasy pouch of coins.\n";

                    // Setăm HP la 0 în culise ca să știe jocul că ai câștigat, apoi oprim lupta.
                    goblin.setCurrentHP(0);
                    break;
                }
            }
        }

        if (goblin.getCurrentHP() > 0)

        {
            AttackResult attack = calculateAttackDamage(goblin.equippedWeapon);
            if (attack.damage > 0)
            {
                player.damage(attack.damage);
                std::cout << "Enemy dealt \033[1m" << attack.damage << " damage\033[0m to you!\n";
            }
            if (player.getCurrentHP() <= 0)

            {
                std::cout << "\n\033[1m\033[31m*** COMBAT INTERRUPTED ***\033[0m\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "You fall to your knees, gasping for air. The Goblin raises his weapon for the final, lethal blow.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout << "Suddenly, a chilling, unnatural screech echoes from the dark pipes above. The temperature drops freezing cold.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout << "The Goblin stops dead in his tracks. Pure terror washes over his face as he stares into the shadows right behind you.\n";
                std::cout << "\033[33m'The... The Pale King...' \033[0mhe stammers, dropping a pouch of coins as his hands tremble violently.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout << "\033[33m'You're marked, rat! You're already dead!' \033[0mhe screams, before scrambling away into the darkness.\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                player.setCurrentHP(1);
                goblin.setCurrentHP(0);
                break;
            }
        }
    }

    if (goblin.getCurrentHP() <= 0 && goblin.getCurrentHP() != -999)

    {
        std::cout << "\n\033[32mYOU WON!\033[0m\n";
        std::cout << "You survived the Goblin and found " << goblin.getCoins() << " coins!\n";
        player.addCoins(goblin.getCoins());
        player.addExp(25);
        player.checkLevelUp();

        std::cout << "\n\033[1m\033[36m*** AREA CLEARED ***\033[0m\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "You are left alone in the dark alley. The adrenaline fades, and the pain from your wounds sets in.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "As you bend down to pick up the Goblin's dropped coins, you notice something glowing near the dead smuggler's body.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "It's an elegant, glass vial filled with a pulsing golden-red liquid. It looks completely out of place in The Sump.\n";
        std::cout << "The intricate label reads: \033[35m'Pure Rejuvenation Elixir - Property of Level 2 Gilded Ring'\033[0m.\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << "Next to it, you find a smaller, dirty flask with a murky green liquid: A standard Healing Potion.\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "You are bleeding. Without hesitating, you uncap the rare Elixir and drink it.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        player.setCurrentHP(player.getMaxHP());
        entityInventory.addItem(Item("Healing Potion", 2, "Consumable", 10, 1, "Uncommon"));

        std::cout << "\033[32mInstantly, a warm sensation spreads through your veins. Your deep wounds close before your eyes!\033[0m\n";
        std::cout << "\033[1m\033[32m* HP FULLY RESTORED! (" << player.getCurrentHP() << "/" << player.getMaxHP() << ") *\033[0m\n\n";

        std::cout << "\033[33m* Added 1x Healing Potion to Inventory *\033[0m\n\n";
        std::cout << "Press [ENTER] to step out of the shadows and enter the city...\n";

        std::string continueKey;
        std::cin.ignore();
        std::getline(std::cin, continueKey);
    }
}

void setupArenaEnemy(Entity &enemy, int enemyID, int playerLevel) // ENEMY SPAWNER
{
    int weaponDamageCount = (enemy.getLevel() / 3) + 1;

    if (enemyID == 1) //!!ENEMY GOBLIN!!

    {
        std::cout << "*A vicious Goblin enters the Arena!*\n";
        enemy.enemyLevel(playerLevel, 60, 10);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Daggers", 2, WeaponClass::Dagger, weaponDamageCount);
            std::cout << "He is wielding a pair of deadly Daggers!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Knifes", 1, WeaponClass::Dagger, weaponDamageCount);
            std::cout << "He is wielding quick Kitchen Knifes!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Wooden Club", 1, WeaponClass::LightSword, weaponDamageCount);
            std::cout << "He is swinging a brutal Wooden Club!\n";
        }
    }
    else if (enemyID == 2) //!!ENEMY GIANT!!

    {
        std::cout << "*A massive Giant shakes the Arena floor!*\n";
        enemy.enemyLevel(playerLevel, 100, 25);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Dreadnought Greatsword", 3, WeaponClass::HeavySword, weaponDamageCount);
            std::cout << "It wields a Dreadnought Greatsword, a blade as tall as you are!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Executioner's Greataxe", 3, WeaponClass::Axe, weaponDamageCount);
            std::cout << "It heaves an Executioner's Greataxe, its edge chipped and bloodied!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Iron-Banded Maul", 3, WeaponClass::HeavySword, weaponDamageCount);
            std::cout << "It rests an Iron-Banded Maul on its shoulder, a weapon meant to crush armor!\n";
        }
    }
    else if (enemyID == 3) //!!ENEMY PIRATE!!

    {
        std::cout << "*A pirate from Thalassys enters the Arena floor!*\n";
        enemy.enemyLevel(playerLevel, 90, 15);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Hook", 1, WeaponClass::LightSword, weaponDamageCount);
            std::cout << "It wields a Hook, a curved blade as pointy as a needle!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Medium Sword", 2, WeaponClass::MediumSword, weaponDamageCount);
            std::cout << "He swing a Pirate Sword, its edge chipped and bloodied!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Whaler's Harpoon", 2, WeaponClass::Spear, weaponDamageCount);
            std::cout << "He rests on his shoulder a Whaler's Harpoon , a weapon meant to pierce armor!\n";
        }
    }
    else if (enemyID == 4) //!!ENEMY ELF!!

    {
        std::cout << "*A slender, pale figure drops from the shadows—a rogue Elf!*\n";
        enemy.enemyLevel(playerLevel, 45, 6);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Glass Dagger", 1, WeaponClass::Dagger, weaponDamageCount);
            std::cout << "He twirls a Glass Dagger, moving with deadly silence!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Engraved Rapier", 1, WeaponClass::LightSword, weaponDamageCount);
            std::cout << "He draws an Engraved Rapier, assuming a noble dueling stance!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Silent Recurve Bow", 2, WeaponClass::Bow, weaponDamageCount);
            std::cout << "He nocks an arrow into his Silent Recurve Bow, taking careful aim!\n";
        }
    }
    else if (enemyID == 5) //!!ENEMY MERFOLK!!

    {
        std::cout << "*A scaled Merfolk slithers out of a rusted grate, hissing toxically!*\n";
        enemy.enemyLevel(playerLevel, 65, 10);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Rusted Trident", 2, WeaponClass::Spear, weaponDamageCount);
            std::cout << "It points a Rusted Trident at you, dripping with sewer water!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Coral Spear", 2, WeaponClass::Spear, weaponDamageCount);
            std::cout << "It grips a jagged Coral Spear, sharpened by the undercurrents!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Deepwater Harpoon", 2, WeaponClass::Spear, weaponDamageCount);
            std::cout << "It levels a massive Deepwater Harpoon, ready to impale you!\n";
        }
    }
    else if (enemyID == 6) //!!ENEMY ORC!!

    {
        std::cout << "*A massive, soot-stained Orc steps heavily into the light, roaring in fury!*\n";
        enemy.enemyLevel(playerLevel, 85, 14);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Heavy Mining Pickaxe", 3, WeaponClass::Axe, weaponDamageCount);
            std::cout << "He raises a Heavy Mining Pickaxe, meant to shatter stone and bone alike!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Scrap-Metal Cleaver", 3, WeaponClass::Axe, weaponDamageCount);
            std::cout << "He heaves a brutal Scrap-Metal Cleaver, welded from ship hulls!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Sledgehammer", 3, WeaponClass::HeavySword, weaponDamageCount);
            std::cout << "He slams a colossal Sledgehammer into the ground, shaking the arena!\n";
        }
    }
    else if (enemyID == 7) //!!ENEMY HYBRID!!

    {
        std::cout << "*A twisted, grotesque Hybrid lumbers forward, driven by erratic magic!*\n";
        enemy.enemyLevel(playerLevel, 75, 12);
        int weaponRoll = getRandomNumber(1, 3);

        if (weaponRoll == 1) // PRIMA ARMA

        {
            enemy.equippedWeapon.generateStats("Mutated Claws", 1, WeaponClass::Dagger, weaponDamageCount);
            std::cout << "It bares Mutated Claws, crackling with unstable energy!\n";
        }
        else if (weaponRoll == 2) // A DOUA ARMA

        {
            enemy.equippedWeapon.generateStats("Bone Longsword", 2, WeaponClass::MediumSword, weaponDamageCount);
            std::cout << "It wields a crude Bone Longsword, torn from a forgotten beast!\n";
        }
        else if (weaponRoll == 3) // A TREIA ARMA

        {
            enemy.equippedWeapon.generateStats("Torn Iron Pipe", 3, WeaponClass::HeavySword, weaponDamageCount);
            std::cout << "It blindly swings a Torn Iron Pipe, howling uncontrollably!\n";
        }
    }
}

bool startArenaBattle(Entity &player, Entity &enemy, Inventory &entityInventory) // FUNCTIE START BATTLE
{
    std::cout << "--------------------------------------------\n";
    std::cout << "\033[3m--------------------FIGHT--------------------\n";

    char playerChoice[256];

    while (enemy.getCurrentHP() > 0 && player.getCurrentHP() > 0)

    {
        std::cout << "\nCurrent player HP is " << player.getCurrentHP() << ".\n";
        std::cout << "Current enemy HP is " << enemy.getCurrentHP() << ".\n";
        std::cout << "Choose your action: \n[1] Attack\n[2] Use Item\n[3] Surrender\n";

        std::cin >> playerChoice;
        for (int i = 0; i < strlen(playerChoice); i++)
            playerChoice[i] = toupper(playerChoice[i]);

        if (strcmp("3", playerChoice) == 0)

        {
            std::cout << "\033[33mYou surrendered and fled the arena!\033[0m\n";
            return false;
        }

        else if (strcmp("2", playerChoice) == 0)
{
    std::cout << "\n\033[1m\033[33m+------------------------------------------------------------+\033[0m\n";
    std::cout << "\033[1m\033[33m|\033[0m  \033[32m[ USE ITEM - COMBAT ]\033[0m\n";
    std::cout << "\033[1m\033[33m+------------------------------------------------------------+\033[0m\n";
    std::cout << "\033[1m\033[33m|\033[0m\n";
    
    entityInventory.printConsumables();
    
    std::cout << "\033[1m\033[33m|\033[0m\n";
    std::cout << "\033[1m\033[33m+------------------------------------------------------------+\033[0m\n";
    std::cout << "\nEnter item \033[1mID\033[0m to use (or \033[1m0\033[0m to cancel): ";
    
    int itemID;
    std::cin >> itemID;
    
    if (itemID == 0)
    {
        std::cout << "\033[33mYou decided not to use anything.\033[0m\n";
        continue;  // nu trece turul inamicului
    }
    
    bool used = entityInventory.useConsumableItem(itemID, player, enemy);
    if (!used)
    {
        continue;  // item invalid sau nu l-ai putut folosi — nu trece turul
    }
    // dacă a reușit, turul inamicului continuă normal
}

        else if (strcmp("ATTACK", playerChoice) == 0 || strcmp("1", playerChoice) == 0)

        {
            AttackResult attack = calculateAttackDamage(player.equippedWeapon);
            if (attack.damage > 0)
            {
                if (player.equippedWeapon.isBroken())
                {
                    attack.damage = 1;
                    std::cout << "\033[31mYou strike with a broken weapon! It barely leaves a scratch (1 DMG)!\033[0m\n";
                }
                else
                {
                    int durLoss = 1;
                    if (attack.isCrit)
                        durLoss += 2;

                    if (attack.isDouble)
                        durLoss += 1;

                    player.equippedWeapon.decreaseDurability(durLoss);
                    if (player.equippedWeapon.isBroken())
                    {
                        std::cout << "\033[31m*CRACK* Your weapon just broke on impact!\033[0m\n";
                    }
                }

                enemy.damage(attack.damage);
                std::cout << "You dealt \033[1m" << attack.damage << " damage\033[0m to the enemy!\n";
            }
        }
        else
        {
            std::cout << "Invalid action!\n";
            continue;
        }

        if (enemy.getCurrentHP() > 0)

        {
            AttackResult attack = calculateAttackDamage(enemy.equippedWeapon);
            if (attack.damage > 0)
            {
                player.damage(attack.damage);
                std::cout << "Enemy dealt \033[1m" << attack.damage << " damage\033[0m to you!\n";
            }
        }
    }

    if (enemy.getCurrentHP() <= 0)

    {
        std::cout << "\n\033[32mYOU WON THE ARENA MATCH!\033[0m\n";
        std::cout << "You defeated the enemy and claimed " << enemy.getCoins() << " coins!\n";
        player.addCoins(enemy.getCoins());
        player.addExp(25);
        player.checkLevelUp();
        Item reward = generateRandomLoot(enemy.getLevel());
        if (reward.getId() != 0)
        {
            std::cout << "\nThe enemy dropped: " << reward.getQuantity() << "x " << reward.getName() << " (" << reward.getRarity() << ")!\n";
            entityInventory.addItem(reward);
        }
        else
        {
            cout << "\nThe enemy dropped nothing.\n";
        }
        return true;
    }

    if (player.getCurrentHP() <= 0)

    {
        std::cout << "\n\033[31mGAME OVER! YOU DIED!\033[0m\n";
        return true;
    }
    return true;
}

int main() // INT MAIN
{
    Entity player;
    Entity goblin;
    Inventory inventory;

    srand(time(0));

    runIntro(player);

    if (player.getCurrentHP() > 0)

    {
        runFirstLoreFight(player, goblin, inventory);
    }

    if (player.getCurrentHP() > 0)

    {
        system("cls");
        std::cout << "\nWelcome to Mograndia! A city where everything is about political classes, the lower class, lives in very poor conditions, in contrast with the rich, but more about this you will find out in your adventure! \n";
        std::cout << "What is it that you wish to do here? You have the posibility to visit a shop or search for the arena. The arena is a place where adventurers fight for gaining EXP and level up. and also a method to gain coins. \n";

        while (player.getCurrentHP() > 0)

        {
            std::cout << "\nPRESS [1] TO VISIT THE SHOP \n";
            std::cout << "PRESS [2] TO BATTLE IN THE ARENA \n";
            std::cout << "PRESS [3] TO OPEN YOUR INVENTORY \n";
            std::cout << "PRESS [4] TO START THE MAIN QUEST \n\n";

            std::string alegere_shop_arena;
            std::cin >> alegere_shop_arena;

            if (alegere_shop_arena == "3")

            {
                std::string invMessage = "";
                while (alegere_shop_arena == "3")

                {
                    system("cls");
                    std::cout << "\n\033[1m\033[33m+=/\\=========================================================+\033[0m\n";
                    std::cout << "\033[1m\033[33m|/  \\ \033[37m[ INVENTORY ]\033[0m\n";
                    std::cout << "\033[1m\033[33m+------------------------------------------------------------+\033[0m\n";

                    std::cout << "\033[1m\033[33m|\033[0m  \033[36m[ HERO ]\033[0m  " << player.getName() << " (Lvl " << player.getLevel() << ")\n";
                    std::cout << "\033[1m\033[33m|\033[0m  \033[31m[ HP   ]\033[0m  " << player.getCurrentHP() << " / " << player.getMaxHP() << "\n";
                    std::cout << "\033[1m\033[33m|\033[0m  \033[35m[ EXP  ]\033[0m  " << player.getExp() << " / " << player.getMaxExp() << "\n";
                    std::cout << "\033[1m\033[33m|\033[0m  \033[32m[ GOLD ]\033[0m  $ " << player.getCoins() << "\n";

                    std::cout << "\033[1m\033[33m+------------------------------------------------------------+\033[0m\n";
                    std::cout << "\033[1m\033[33m|\033[0m  \033[37m[ EQUIPPED WEAPON ]\033[0m\n";
                    std::cout << "\033[1m\033[33m|\033[0m  > " << player.equippedWeapon.getName()
                              << " (Lvl " << inventory.getWeaponLevel() << ") | DMG: "
                              << player.equippedWeapon.getMinDamage() << " - " << player.equippedWeapon.getMaxDamage() << "\n";

                    std::cout << "\033[1m\033[33m+============================================================+\033[0m\n";
                    std::cout << "\033[1m\033[33m|\033[0m  \033[37m[ BACKPACK CONTENTS ]\033[0m\n";
                    std::cout << "\033[1m\033[33m|\033[0m\n";

                    if (inventory.isEmpty())

                    {
                        std::cout << "\033[1m\033[33m|\033[0m   \033[30m(Your backpack is completely empty...)\033[0m\n";
                    }
                    else
                    {
                        // Afisam itemele pe rand
                        inventory.printBackpack();
                    }

                    std::cout << "\033[1m\033[33m|\033[0m\n";
                    std::cout << "\033[1m\033[33m+\\===========================================================+\033[0m\n";

                    // Aici se afiseaza mesajele sistemului (daca ai incercat sa folosesti ceva)
                    if (invMessage != "")

                    {
                        std::cout << "\n  \033[1m\033[33m>> " << invMessage << " <<\033[0m\n";
                        invMessage = ""; // Se reseteaza dupa afisare
                    }

                    std::cout << "\nPRESS THE \033[1m[ID]\033[0m OF AN ITEM TO USE IT.\n";
                    std::cout << "PRESS \033[1m[0]\033[0m TO CLOSE INVENTORY AND RETURN TO CITY.\n";

                    std::string exitInventory;
                    std::cin >> exitInventory;

                    if (exitInventory == "0")

                    {
                        alegere_shop_arena = "0"; // Iesire
                    }
                    else
                    {
                        // Incercam sa transformam textul intr-un numar
                        try

                        {
                            int idTastat = std::stoi(exitInventory);

                            // Daca am reusit, chemam Dispecerul tau!
                            // Daca returneaza 'false' (adică a dat fail), Dispecerul tau a printat deja eroarea in consola
                            inventory.useConsumableItem(idTastat, player, goblin);

                            // Asteptam 2 secunde ca jucatorul sa citeasca rezultatul (ex: "Ai baut potiunea")
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                        catch (const std::invalid_argument &e)

                        {
                            // Daca a tastat litere (gen "abc") in loc de numere
                            invMessage = "Please enter a valid Item ID number!";
                        }
                    }
                }
            }

            else if (alegere_shop_arena == "1")

            {
                std::string shopMessage = "";
                while (alegere_shop_arena == "1")

                {
                    system("cls");
                    std::cout << "\n\033[1m\033[36m+=======================================================+\033[0m\n";
                    std::cout << "\033[1m\033[36m|\033[0m                    \033[1m$$$ ITEM SHOP $$$\033[0m                  \033[1m\033[36m|\033[0m\n";
                    std::cout << "\033[1m\033[36m+=======================================================+\033[0m\n";
                    std::cout << "\033[1m\033[36m|\033[0m Welcome, adventurer! Look at my finest selection.    \033[1m\033[36m|\033[0m\n";
                    std::cout << "\033[1m\033[36m|\033[0m Your Pouch: \033[1m\033[33m$ " << player.getCoins() << " Gold\033[0m";
                    int spacesAfterGold = 29 - std::to_string(player.getCoins()).length();
                    for (int i = 0; i < spacesAfterGold; i++)
                        std::cout << " ";
                    std::cout << "\033[1m\033[36m|\033[0m\n";
                    std::cout << "\033[1m\033[36m+-------------------------------------------------------+\033[0m\n";
                    std::cout << "\033[1m\033[36m|\033[0m ID   ITEM NAME                     PRICE               \033[1m\033[36m|\033[0m\n";
                    std::cout << "\033[1m\033[36m+-------------------------------------------------------+\033[0m\n";

                    // std::cout << "\033[1m\033[36m|\033[0m [1]  Healing Potion               \033[33m" << shop.calculatePrice(1, player.level) << " Gold\033[0m               \033[1m\033[36m|\033[0m\n";
                    // std::cout << "\033[1m\033[36m|\033[0m [2]  Arrow of Venom               \033[33m" << shop.calculatePrice(2, player.level) << " Gold\033[0m               \033[1m\033[36m|\033[0m\n";
                    // std::cout << "\033[1m\033[36m|\033[0m [3]  Bandages                     \033[33m" << shop.calculatePrice(3, player.level) << " Gold\033[0m               \033[1m\033[36m|\033[0m\n";
                    // std::cout << "\033[1m\033[36m|\033[0m [4]  Iron Arrow (Lvl 2)           \033[33m" << shop.calculatePrice(4, player.level) << " Gold\033[0m               \033[1m\033[36m|\033[0m\n";
                    // std::cout << "\033[1m\033[36m|\033[0m [5]  Weapon Upgrade (Next Lvl)   \033[33m" << shop.calculatePrice(5, player.level) << " Gold\033[0m               \033[1m\033[36m|\033[0m\n";
                    std::cout << "\033[1m\033[36m+=======================================================+\033[0m\n";

                    if (shopMessage != "")

                    {
                        std::cout << "\n  \033[1m\033[33m>> " << shopMessage << " <<\033[0m\n";
                        shopMessage = "";
                    }

                    std::cout << "\nEnter the \033[1mID\033[0m of the item you wish to buy, or \033[1m[0]\033[0m to leave:\n";

                    std::string wantedItem;
                    std::cin >> wantedItem;

                    if (wantedItem == "0")

                    {
                        std::cout << "\nFarewell, traveler. Come back when you need better steel!\n";
                        alegere_shop_arena = "0";
                    }
                    /* else if (wantedItem == "1")
                     {
                         int price = shop.calculatePrice(1, player.level);
                         if (shop.stockPotions <= 0)
                             shopMessage = "*OUT OF STOCK!*";
                         else if (inventory.potionNumber >= inventory.maxLimitPotions)
                             shopMessage = "*INVENTORY FULL!*";
                         else if (player.goldCoins < price)
                             shopMessage = "*NOT ENOUGH GOLD*";
                         else
                         {
                             player.goldCoins -= price;
                             inventory.potionNumber++;
                             shop.stockPotions--;
                             shopMessage = "*PURCHASE SUCCESSFUL*";
                         }
                     }
                     else if (wantedItem == "2")
                     {
                         int price = shop.calculatePrice(2, player.level);
                         if (shop.stockPoisonArrows <= 0)
                             shopMessage = "*OUT OF STOCK!*";
                         else if (player.goldCoins < price)
                             shopMessage = "*NOT ENOUGH GOLD*";
                         else
                         {
                             player.goldCoins -= price;
                             inventory.arrowOfVenomNumber++;
                             shop.stockPoisonArrows--;
                             shopMessage = "*PURCHASE SUCCESSFUL*";
                         }
                     }
                     else if (wantedItem == "3")
                     {
                         int price = shop.calculatePrice(3, player.level);
                         if (shop.stockBandages <= 0)
                             shopMessage = "*OUT OF STOCK!*";
                         else if (inventory.bandagesNumber >= inventory.maxLimitBandages)
                             shopMessage = "*INVENTORY FULL!*";
                         else if (player.goldCoins < price)
                             shopMessage = "*NOT ENOUGH GOLD*";
                         else
                         {
                             player.goldCoins -= price;
                             inventory.bandagesNumber++;
                             shop.stockBandages--;
                             shopMessage = "*PURCHASE SUCCESSFUL*";
                         }
                     }
                     else if (wantedItem == "4")
                     {
                         int price = shop.calculatePrice(4, player.level);
                         if (shop.stockArrows <= 0)
                             shopMessage = "*OUT OF STOCK!*";
                         //else if (inventory.arrowNumber >= inventory.maxLimitArrows)
                        //     shopMessage = "*INVENTORY FULL!*";
                         else if (player.goldCoins < price)
                             shopMessage = "*NOT ENOUGH GOLD*";
                         else
                         {
                             player.goldCoins -= price;
                             //inventory.arrowNumber++;
                             shop.stockArrows--;
                             shopMessage = "*PURCHASE SUCCESSFUL*";
                         }
                     }
                     else if (wantedItem == "5")
                     {
                         int price = shop.calculatePrice(5, inventory.weaponLevel);
                         if (inventory.weaponLevel >= 5)
                             shopMessage = "*WEAPON ALREADY MAX LEVEL*";
                         else if (player.goldCoins < price)
                             shopMessage = "*NOT ENOUGH GOLD*";
                         else
                         {
                             player.goldCoins -= price;
                             inventory.weaponLevel++;
                             player.equippedWeapon.minDamage += 5;
                             player.equippedWeapon.maxDamage += 5;
                             shopMessage = "*WEAPON UPGRADED!*";
                         }
                     }*/
                    else
                    {
                        shopMessage = "*INVALID ID*";
                    }
                }
            }

            else if (alegere_shop_arena == "2")

            {
                system("cls");
                std::cout << "You enter a big place, with high walls and a circular area in the middle. High up, people are cheering.\n";
                std::cout << "--------------------------------------------\n";
                std::cout << "\033[1m*YOU ENTERED THE ARENA!*\033[0m\n\n";

                float arenaFee = player.getCoins() * 0.1;
                if (arenaFee < 1)
                    arenaFee = 1;

                std::cout << "To enter a fight you must pay a fee of " << arenaFee << " coins!\n";

                if (player.getCoins() >= arenaFee)

                {
                    std::cout << "Are you willing to pay this fee? [Y/N]\n";
                    std::string payingFee;
                    std::cin >> payingFee;
                    for (int i = 0; i < payingFee.length(); i++)
                        payingFee[i] = toupper(payingFee[i]);

                    if (payingFee == "YES" || payingFee == "Y")

                    {
                        player.addCoins(-arenaFee);

                        std::cout << "\nYou have been accepted into the arena!\n";
                        std::cout << "--------------------------------------------\n";
                        std::cout << "An enemy was randomly chosen for you...\n\n";

                        int randomEnemyID = getRandomNumber(1, 7);
                        Entity arenaEnemy;
                        setupArenaEnemy(arenaEnemy, randomEnemyID, player.getLevel());
                        startArenaBattle(player, arenaEnemy, inventory);
                    }
                    else
                        std::cout << "You walked away from the arena.\n";
                }
                else
                    std::cout << "You don't have enough money to pay the fee!\n";

                alegere_shop_arena = "0";
            }
            else if (alegere_shop_arena == "4")

            {
                std::cout << "\n\033[36m[The Main Quest is currently under construction by the Developer!]\033[0m\n";
            }
        }
    }
    return 0;
}