#pragma once
#include <iostream>

// function to display header- Title of the game and one liner
void displayHeader()
{
    std:: cout << std::endl;
    std::cout << "             Tic Tac Toe      " << std::endl;
    std::cout << "       A turn based board game   " << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

// function to display the main menu
void displayMenu()
{
    displayHeader();
    std::cout << "   [Menu] > 1. Play" << std::endl;
    std::cout << "            2. History" << std::endl;
    std::cout << "            3. Help" << std::endl;
    std::cout << "            4. Quit" << std::endl;
}