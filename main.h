#pragma once

#include <iostream>
#include <conio.h>
#include <fstream>
#define ESC "\033["

// colors
#define RESET "\033[0m"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

#define BRED "\033[91m"
#define BGREEN "\033[92m"
#define BYELLOW "\033[93m"
#define BBLUE "\033[94m"
#define BMAGENTA "\033[95m"
#define BCYAN "\033[96m"
#define BWHITE "\033[97m"

// function to display header- Title of the game and one liner
void displayHeader()
{
    std::cout << std::endl;
    std::cout << BCYAN << "             Tic Tac Toe      " << RESET << std::endl;
    std::cout << "       A turn based board game   " << std::endl;
    std::cout << BWHITE << "-------------------------------------" << RESET << std::endl;
}

// Dynamic selection displays
void displayMenu(int option)
{
    std::cout << BMAGENTA "   [Menu] > " RESET << (option == 1 ? GREEN "  " : "") << "1. Play" << (option == 1 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 2 ? GREEN "  " : "") << "2. History" << (option == 2 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 3 ? GREEN "  " : "") << "3. Rules" << (option == 3 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 4 ? GREEN "  " : "") << "4. Help" << (option == 4 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 5 ? RED "  " : "") << "5. Quit" << (option == 5 ? RESET : "") << std::endl;
}

void displayPlay(int option)
{
    std::cout << BMAGENTA "   [Mode] > " RESET << (option == 1 ? GREEN "  " : "") << "1. Human vs Human" << (option == 1 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 2 ? GREEN "  " : "") << "2. Human vs AI" << (option == 2 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 3 ? RED "  " : "") << "3. Back" << (option == 3 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 4 ? CYAN "  " : "") << "4. Menu" << (option == 4 ? RESET : "") << std::endl;
}

void gridSelectorDisplay(int option)
{
    std::cout << BMAGENTA "  [Dimension] > " RESET << (option == 3 ? GREEN "  " : "") << "3" << (option == 3 ? " " : "") << "x" << (option == 3 ? " " : "") << "3" << (option == 3 ? RESET : "") << std::endl;
    std::cout << "                " << (option == 4 ? GREEN "  " : "") << "4" << (option == 4 ? " " : "") << "x" << (option == 4 ? " " : "") << "4" << (option == 4 ? RESET : "") << std::endl;
    std::cout << "                " << (option == 5 ? GREEN "  " : "") << "5" << (option == 5 ? " " : "") << "x" << (option == 5 ? " " : "") << "5" << (option == 5 ? RESET : "") << std::endl;
    std::cout << "                " << (option == 6 ? GREEN "  " : "") << "6" << (option == 6 ? " " : "") << "x" << (option == 6 ? " " : "") << "6" << (option == 6 ? RESET : "") << std::endl;
    std::cout << "                " << (option == 7 ? RED "  " : "") << "Back" << (option == 7 ? RESET : "") << std::endl;
}

void aiSelectorDisplay(int option, int dimension)
{
    std::cout << BMAGENTA "[AI Level]> " RESET << (option == 1 ? BGREEN "  " : "") << "1. Easy AI" << (option == 1 ? RESET : "") << std::endl;
    std::cout << "            " << (option == 2 ? BYELLOW "  " : "") << "2. Medium AI" << (option == 2 ? RESET : "") << std::endl;
    if (dimension == 3)
    {
        std::cout << "            " << (option == 3 ? BMAGENTA "  " : "") << "3. Hard AI (Unbeatable)" << (option == 3 ? RESET : "") << std::endl;
        std::cout << "            " << (option == 4 ? BRED "  " : "") << "4. back" << (option == 4 ? RESET : "") << std::endl;
    }
    else
    {
        std::cout << "            " << (option == 4 ? BRED "  " : "") << "3. back" << (option == 4 ? RESET : "") << std::endl;
    }
}

// Dynamic selection displays END

// function to clear screen below the title
void clearScreen()
{
    std::cout << ESC << "5;0H"; // going to 5th row
    std::cout << ESC << "J";    // clear all below
}

// function to display warning
void displayWarning()
{
    std::cout << RED "Invalid Option. Please choose between the given options." RESET;
}

// Display Prototype function for help
void displayHelp()
{

    std::cout << BMAGENTA "[Help] > " RESET << std::endl
              << std::endl;
    std::cout << RED "---DO NOT run on integrated terminal terminal of any Code Editor, animations won't work." RESET << std::endl;
    std::cout << "The game is entirely controlled by keyboard keys UP, LEFT, RIGHT, DOWN." << std::endl;
    std::cout << "Esc button can be used anywhere to go back, except name selection screen." << std::endl;
    std::cout << "Rules can be viewed from Menu -> 3." << std::endl;
    std::cout << RED "DO NOT resize the terminal, it will result in a not so good looking UI." RESET << std::endl;
    std::cout << "Many used functions are windows only as it uses many window specific APIs. This app was not tested in any other OS." << std::endl
              << std::endl;

    std::cout << CYAN "Press any key to go back to the menu..." RESET;
}

// Main help function
void help()
{
    clearScreen();
    displayHelp();
    getch();
}

// Display Prototype function for rules // todo highlight the winning X using Green/BMAGENTA
void displayRules()
{
    std::cout << BMAGENTA "[Rules] > " RESET << std::endl
              << std::endl;
    std::cout << "Tic-Tac-Toe Rules (n x n):" << std::endl;
    std::cout << "   1. Two players take turns placing their symbols (X and O) on an empty cell." << std::endl;
    std::cout << "   2. A move is valid only if the cell is empty." << std::endl;
    std::cout << "   3. First to fill an entire row, column, or diagonal with their symbol wins. Example:" << std::endl
              << std::endl;

    std::cout << "         -------------      -------------      -------------" << std::endl;
    std::cout << "         | X | X | X |      | X |   | O |      | X |   | O |" << std::endl;
    std::cout << "         -------------      -------------      -------------" << std::endl;
    std::cout << "         |   | O |   |      | X | O |   |      | O | X |   |" << std::endl;
    std::cout << "         -------------      -------------      -------------" << std::endl;
    std::cout << "         |   |   | O |      | X |   |   |      | O |   | X |" << std::endl;
    std::cout << "         -------------      -------------      -------------" << std::endl;
    std::cout << "           Horizontal         Vertical            Diagonal  " << std::endl
              << std::endl;

    std::cout << "   4. If the board is full and nobody wins -> draw." << std::endl;
    std::cout << "   5. Usually, X goes first and turns alternate." << std::endl
              << std::endl;
    std::cout << "That's all...enjoy!!!" << std::endl
              << std::endl;
    std::cout << CYAN "Press any key to go back to the menu..." RESET;
}

// Main rule function
void rule()
{
    clearScreen();
    displayRules();
    getch();
}

// function for history and file handling
void savetoFile(std::string line)
{
    std::ofstream file("history.txt", std::ios::app);
    file << line;
    file.close();
}

// function to check if the line is empty
bool empty(std::string line)
{
    int n = line.size();
    for (char c : line)
        if (c != ' ')
            return false;
    return true;
}

// function for the option history in menu
void history()
{
    clearScreen();

    std::cout << BMAGENTA "[History] > " RESET << std::endl
              << std::endl;

    // load from file
    std::ifstream history("history.txt");

    std::string line;
    while (getline(history, line))
    {
        if (!empty(line))
            std::cout << "    " << line << std::endl;
    }

    std::cout << CYAN "\nPress any key to go back to the menu..." RESET;
    getch();
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

// functions directly related to the game
void askNameDisplay(int n)
{
    std::cout << (n == 1 ? BRED : BBLUE) << "  [Player " << n << "]> " RESET "Enter name:_"; // todo add color based on player turn
}