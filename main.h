#pragma once

#include <iostream>
#include <conio.h>
#define ESC "\033["

// function to display header- Title of the game and one liner
void displayHeader()
{
    std::cout << std::endl;
    std::cout << "             Tic Tac Toe      " << std::endl;
    std::cout << "       A turn based board game   " << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

// Dynamic selection displays
void displayMenu(int option)
{
    std::cout << "   [Menu] > " << (option == 1 ? "  " : "") << "1. Play" << std::endl;
    std::cout << "            " << (option == 2 ? "  " : "") << "2. History" << std::endl;
    std::cout << "            " << (option == 3 ? "  " : "") << "3. Rules" << std::endl;
    std::cout << "            " << (option == 4 ? "  " : "") << "4. Help" << std::endl;
    std::cout << "            " << (option == 5 ? "  " : "") << "5. Quit" << std::endl;
}

void displayPlay(int option)
{
    std::cout << "   [Mode] > " << (option == 1 ? "  " : "") << "1. Human vs Human" << std::endl;
    std::cout << "            " << (option == 2 ? "  " : "") << "2. Human vs AI" << std::endl;
    std::cout << "            " << (option == 3 ? "  " : "") << "3. Back" << std::endl;
    std::cout << "            " << (option == 4 ? "  " : "") << "4. Menu" << std::endl;
}

void gridSelectorDisplay(int option)
{
    std::cout << "  [Dimension] > " << (option == 3 ? " " : "") << "3" << (option == 3 ? " " : "") << "x" << (option == 3 ? " " : "") << "3" << std::endl;
    std::cout << "                " << (option == 4 ? " " : "") << "4" << (option == 4 ? " " : "") << "x" << (option == 4 ? " " : "") << "4" << std::endl;
    std::cout << "                " << (option == 5 ? " " : "") << "5" << (option == 5 ? " " : "") << "x" << (option == 5 ? " " : "") << "5" << std::endl;
    std::cout << "                " << (option == 6 ? " " : "") << "6" << (option == 6 ? " " : "") << "x" << (option == 6 ? " " : "") << "6" << std::endl;
    std::cout << "                " << (option == 7 ? "  " : "") << "Back" << std::endl;
}
// Dynamic selection displays

// function to clear screen below the title
void clearScreen()
{
    std::cout << ESC << "5;0H";
    std::cout << ESC << "J";
}

// function to display warning
void displayWarning()
{
    std::cout << "Invalid Option. Please choose between the given options.";
}

// Display Prototype function for help
void displayHelp()
{

    std::cout << "Help:" << std::endl
              << std::endl;
    std::cout << "DO NOT run on integrated terminal terminal of any Code Editor, animations won't work." << std::endl;
    std::cout << "The game is entirely controlled by keyboard keys UP, LEFT, RIGHT, DOWN." << std::endl;
    std::cout << "Esc button can be used anywhere to go back, except name selection screen." << std::endl;
    std::cout << "Rules can be viewed from Menu -> 4." << std::endl;
    std::cout << "DO NOT resize the terminal, it will result in a not so good looking UI." << std::endl;
    std::cout << "Many used functions are windows only as it uses many window specific APIs. This app was not tested in any other OS." << std::endl
              << std::endl;

    std::cout << "Press any key to go back to the menu...";
}

// Main help function
void help()
{
    clearScreen();
    displayHelp();
    getch();
}

// Display Prototype function for rules
void displayRules()
{
    std::cout << "Tic-Tac-Toe Rules (n x n):" << std::endl;
    std::cout << "  1. Two players take turns placing their symbols (X and O) on an empty cell." << std::endl;
    std::cout << "  2. A move is valid only if the cell is empty." << std::endl;
    std::cout << "  3. First to fill an entire row, column, or diagonal with their symbol wins. Example:" << std::endl
              << std::endl;

    // std::cout << "  Example:" << std::endl;
    std::cout << "        -------------      -------------      -------------" << std::endl;
    std::cout << "        | X | X | X |      | X |   | O |      | X |   | O |" << std::endl;
    std::cout << "        -------------      -------------      -------------" << std::endl;
    std::cout << "        |   | O |   |      | X | O |   |      | O | X |   |" << std::endl;
    std::cout << "        -------------      -------------      -------------" << std::endl;
    std::cout << "        |   |   | O |      | X |   |   |      | O |   | X |" << std::endl;
    std::cout << "        -------------      -------------      -------------" << std::endl;
    std::cout << "          Horizontal         Vertical            Diagonal  " << std::endl
              << std::endl;

    std::cout << "  4. If the board is full and nobody wins -> draw." << std::endl;
    std::cout << "  5. Usually, X goes first and turns alternate." << std::endl
              << std::endl;
    std::cout << "That's all...enjoy!!!" << std::endl
              << std::endl;
    std::cout << "Press any key to go back to the menu...";
}

// Main rule function
void rule()
{
    clearScreen();
    displayRules();
    getch();
}

// function for history
void history()
{
}

//? keyboard input function
int getKeyPress()
{
    int cursor = getch();
    if (cursor == 224)
    {
        cursor += getch();
    }
    return cursor;
}