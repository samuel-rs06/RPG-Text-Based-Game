#include <random>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Tools.h"

int getRandomNumber(int min, int max) // RANDOM NUMBER
{
    return rand() % (max - min + 1) + min;
}

std::string getPlayerInput() // FUNCTIE DE TOUPPER
{
    std::string input;
    std::cin >> input;
    for (int i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);
    return input;
}