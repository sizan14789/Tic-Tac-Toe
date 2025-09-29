#pragma once

#include <iostream>

// function to display header- Title of the game and one liner
void displayHeader()
{
    std::cout << std::endl;
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
    std::cout << "            3. Rules" << std::endl;
    std::cout << "            4. Help" << std::endl;
    std::cout << "            5. Quit" << std::endl;
}

// function to display warning
void displayWarning(){
    std::cout << "Invalid Option. Please choose between the given options" << std::endl;
}

// function for help
void help(){
  
}

// function for rules
void rules(){
  
}

// function for history
void history(){

}