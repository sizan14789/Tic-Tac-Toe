#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include "main.h" // UI header

#define ESC "\033["

// keyboard keys
#define ESCAPE 27
#define ENTER 13
#define UP 224 + 72
#define LEFT 224 + 75
#define RIGHT 224 + 77
#define DOWN 224 + 80

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// forward declaration as Board class was used inside Player class
class Board;

// super class for Players
class Player
{
public:
    string name;
    char symbol;

    // constructors
    Player(string name) : name(name) {}
    Player(string name, char symbol) : name(name), symbol(symbol) {}

protected:
    // check horizontal line
    bool checkHorizontal(vector<vector<char>> grid, int row)
    {
        int n = grid.size();
        for (int i = 0; i < n; i++)
            if (grid[row][i] != symbol)
                return false;
        return true;
    }

    // check vertical line
    bool checkVertical(vector<vector<char>> grid, int col)
    {
        int n = grid.size();
        for (int i = 0; i < n; i++)
            if (grid[i][col] != symbol)
                return false;
        return true;
    }

    // check diagonal line
    bool checkDiagonal(vector<vector<char>> grid)
    {
        int n = grid.size();

        bool matched = true;
        // check up left to right bottom
        for (int i = 0, j = 0; i < n && j < n; i++, j++)
            if (grid[i][j] != symbol)
            {
                matched = false;
                break;
            }
        if (matched)
            return true;

        // check up right to down left
        for (int i = 0, j = n - 1; i < n && j >= 0; i++, j--)
            if (grid[i][j] != symbol)
                return false;

        return true;
    }

    // function to check if any cell is occupied
    bool isCellOccupied(vector<vector<char>> grid, int row, int col)
    {
        return grid[row][col] == 'X' || grid[row][col] == 'O';
    }

public:
    // function to check if draw
    static bool isDraw(vector<vector<char>> grid)
    {
        int n = grid.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] != 'X' && grid[i][j] != 'O')
                    return false;
        return true;
    }

    // function to place symbol and check if game is over
    virtual int placeMove(Board &board) = 0;
};

// class for Board
class Board
{
public:
    vector<vector<char>> grid;
    int n;

    // constructors
    Board() {}
    Board(int dimension)
    {
        this->n = dimension;

        // resizing the grid
        grid.resize(n);
        for (int i = 0; i < n; i++)
        {
            grid[i].resize(n);
        }

        // adding placeholders in the grid
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // grid[i][j] = (char)(i * n + j + 48 + 1);
                grid[i][j] = ' ';
            }
        }
    }

    // function to display the board
    void displayBoard()
    {
        displayBoard(-1, -1);
    }

    // function to display the board for given row col
    void displayBoard(int row, int col)
    {
        clearScreen();
        cout << "[Game Board] > " << endl;
        for (int i = 0; i < n; i++)
        {
            // board top border
            if (i == 0)
            {
                cout << "        ";
                for (int j = 0; j < n; j++)
                {
                    if (j == 0)
                        cout << " ";
                    cout << "----";
                }
                cout << endl;
            }

            cout << "        ";
            // board elements
            for (int j = 0; j < n; j++)
            {
                if (j == 0)
                    cout << "|";

                if (i == row && j == col)
                    cout << ">" << grid[i][j] << "<|";
                else
                    cout << " " << grid[i][j] << " |";
            }
            cout << endl;

            cout << "        ";
            // bottom border
            for (int j = 0; j < n; j++)
            {
                if (j == 0)
                    cout << " ";
                cout << "----";
            }
            cout << endl;
        }
    }
};

// Human class
class Human : public Player
{
public:
    Human(string name, char symbol) : Player(name, symbol) {}

    // function to place symbol an check if the game is over
    int placeMove(Board &board) override
    {
        int gridBody = board.grid.size();
        int row = 0;
        int col = 0;

        // Getting move from human player
        while (true)
        {
            board.displayBoard(row, col);
            cout << name << "'s turn";
            int cursor = getKeyPress();

            if (cursor == UP)
            {
                if (row == 0)
                    row = gridBody - 1;
                else
                    row--;
            }
            else if (cursor == LEFT)
            {
                if (col == 0)
                    col = gridBody - 1;
                else
                    col--;
            }
            else if (cursor == DOWN)
            {
                if (row == (gridBody - 1))
                    row = 0;
                else
                    row++;
            }
            else if (cursor == RIGHT)
            {
                if (col == (gridBody - 1))
                    col = 0;
                else
                    col++;
            }
            else if (cursor == ENTER)
            {
                if (!isCellOccupied(board.grid, row, col))
                    break;
            }
            else if (cursor == ESCAPE)
            {
                return ESCAPE;
            }
        }

        // placing the move on the board
        board.grid[row][col] = this->symbol;

        // checking for game over
        return checkHorizontal(board.grid, row) || checkVertical(board.grid, col) || checkDiagonal(board.grid);
    }
};

// AI class
class AI : public Player
{
public:
    AI(string name, char symbol) : Player(name, symbol) {}

    // function to get available moves from AI
    vector<vector<int>> getAvailableMoves(vector<vector<char>> grid)
    {
        int gridDimension = grid.size();
        vector<vector<int>> availableMoves;

        for (int i = 0; i < gridDimension; i++)
        {
            for (int j = 0; j < gridDimension; j++)
            {
                if (grid[i][j] != 'X' && grid[i][j] != 'O')
                {
                    vector<int> v(2);
                    v[0] = i;
                    v[1] = j;
                    availableMoves.push_back(v);
                }
            }
        }

        return availableMoves;
    }

    // a function the check if a potential move will result in win based on the given symbol
    bool checkIfWin(vector<vector<char>> grid, int row, int col, char symbol)
    {
        grid[row][col] = symbol;

        bool horizontal = true;
        bool vertical = true;
        bool diagonal1 = true;
        bool diagonal2 = true;

        int n = grid.size();
        for (int i = 0; i < n; i++)
            if (grid[row][i] != symbol)
            {
                horizontal = false;
                break;
            }

        for (int i = 0; i < n; i++)
            if (grid[i][col] != symbol)
            {
                vertical = false;
                break;
            }

        // check up left to right bottom
        for (int i = 0, j = 0; i < n && j < n; i++, j++)
            if (grid[i][j] != symbol)
            {
                diagonal1 = false;
                break;
            }

        // check up right to down left
        for (int i = 0, j = n - 1; i < n && j >= 0; i++, j--)
            if (grid[i][j] != symbol)
            {
                diagonal2 = false;
                break;
            }

        return horizontal || vertical || diagonal1 || diagonal2;
    }

    //? remove temporary function to display a vector
    void displayVector(vector<vector<int>> v)
    {
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            int l = v[i].size();
            for (int j = 0; j < l; j++)
            {
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // function to place symbol an check if the game is over
    virtual int placeMove(Board &board) = 0;
};

// Easy AI class
class EasyAI : public AI
{
public:
    EasyAI(string name, char symbol) : AI(name, symbol) {}

    // function to place symbol (and check if the game is over) - Easy AI
    int placeMove(Board &board) override
    {
        cout << "Easy AI's Turn: Neko is Thinking...";
        Sleep(2000);
        vector<vector<int>> v = getAvailableMoves(board.grid);

        int availableMovesCount = v.size();
        int randomMoveIndex = rand() % availableMovesCount;
        vector<int> randomMoveSet = v[randomMoveIndex];

        int row = randomMoveSet[0];
        int col = randomMoveSet[1];

        board.grid[row][col] = this->symbol;

        // checking for game over
        return checkHorizontal(board.grid, row) || checkVertical(board.grid, col) || checkDiagonal(board.grid);
    }
};

// Medium AI class
class MediumAI : public AI
{
public:
    MediumAI(string name, char symbol) : AI(name, symbol) {}

    // function to place symbol (and check if the game is over) - Medium AI
    int placeMove(Board &board) override
    {
        cout << "Medium AI's Turn: Tora is Thinking...";
        Sleep(2000);
        vector<vector<int>> v = getAvailableMoves(board.grid);
        int availableMovesCount = v.size();

        vector<int> aiMove;
        // check if any move = win
        bool hasWinningMove = false;
        for (int i = 0; i < availableMovesCount; i++)
        {
            vector<int> move = v[i];
            if (checkIfWin(board.grid, move[0], move[1], this->symbol))
            {
                aiMove = move;
                hasWinningMove = true;
                break;
            }
        }

        // check if for opponent, any move = win
        bool hasDefendingMove = false;
        if (!hasWinningMove)
        {
            for (int i = 0; i < availableMovesCount; i++)
            {
                vector<int> move = v[i];
                if (checkIfWin(board.grid, move[0], move[1], 'X'))
                {
                    aiMove = move;
                    hasDefendingMove = true;
                    break;
                }
            }
        }

        // random move if no winning or defending move
        if (!hasWinningMove && !hasDefendingMove)
        {
            int randomMoveIndex = rand() % availableMovesCount;
            aiMove = v[randomMoveIndex];
        }

        int row = aiMove[0];
        int col = aiMove[1];

        board.grid[row][col] = this->symbol;

        // checking for game over
        return checkHorizontal(board.grid, row) || checkVertical(board.grid, col) || checkDiagonal(board.grid);
    }
};

// function to start a match
void play(int n, Player *player1, Player *player2)
{
    bool gameOver = false;
    Board board(n);

    // Match loop
    Player *turn = player1;
    Player *winner = nullptr;
    while (!gameOver)
    {
        if (turn == player1)
        {
            int moveResult = player1->placeMove(board);
            if (moveResult == ESCAPE)
                return;
            gameOver = moveResult;
            board.displayBoard();
            winner = player1;
            turn = player2;
        }
        else
        {
            int moveResult = player2->placeMove(board);
            if (moveResult == ESCAPE)
                return;

            gameOver = moveResult;
            board.displayBoard();
            winner = player2;
            turn = player1;
        }
        bool draw = Player::isDraw(board.grid);
        if (!gameOver && draw)
        {
            gameOver = true;
            winner = nullptr;
        }
    }

    if (winner == nullptr)
    {
        string toBeSaved = player1->name + " vs " + player2->name + " - [" + std::to_string(n) + "x" + std::to_string(n) + "] " + " -> Draw\n";
        savetoFile(toBeSaved);
        cout << "Game Over!!! Draw" << endl
             << endl;
    }
    else
    {
        string toBeSaved = player1->name + " vs " + player2->name + " - [" + std::to_string(n) + "x" + std::to_string(n) + "] " + " -> Winner: " + winner->name + "\n";
        savetoFile(toBeSaved);
        cout << "Game Over!!! Winner: " << (winner->name) << endl
             << endl;
    }

    // setting up restart window
    int option = 1;
    int cursorAdder = (n - 3) * 2; // variable to set the cursor such that it doesn't overwrite the board
    while (true)
    {
        // getting option
        while (true)
        {
            // manual cursor placing
            std::cout << ESC << (15 + cursorAdder) << ";0H";
            std::cout << ESC << "J";

            // showing options
            cout << "  [Match] > " << (option == 1 ? "  " : "") << "1. Restart" << endl;
            cout << "            " << (option == 2 ? "  " : "") << "2. Back" << endl;

            int cursor = getKeyPress();

            if (cursor == DOWN || cursor == UP)
            {
                if (option == 2)
                    option = 1;
                else
                    option = 2;
            }
            else if (cursor == ENTER)
            {
                break;
            }
            else if (cursor == ESCAPE)
            {
                option = 2;
                break;
            }
        }

        // using option
        if (option == 1)
        {
            play(n, player1, player2);
            return;
        }
        else if (option == 2)
        {
            return;
        }
        else
        {
            displayWarning();
        }
    }
}

void gridSelection(); // forward prototype declaration

// function to choose between AIs if Human vs Ai mode was chosen
int getAINo()
{
    // todo more options to be added here
    int aiNo = 1;
    // getting aiNo
    while (true)
    {
        clearScreen();
        cout << "[AI Level]> " << (aiNo == 1 ? "  " : "") << "1. Easy AI" << endl;
        cout << "            " << (aiNo == 2 ? "  " : "") << "2. Medium AI" << endl;
        cout << "            " << (aiNo == 3 ? "  " : "") << "3. back" << endl;

        int cursor = getKeyPress();

        if (cursor == DOWN)
        {
            if (aiNo == 3)
                aiNo = 1;
            else
                ++aiNo;
        }
        else if (cursor == UP)
        {
            if (aiNo == 1)
                aiNo = 3;
            else
                --aiNo;
        }
        else if (cursor == ENTER)
        {
            break;
        }
        else if (cursor == ESCAPE)
        {
            aiNo = 3;
            break;
        }
    }
    return aiNo;
}

// function to select mode and name players
void modeSelection(int dimension)
{
    // Player setup based on mode chosen
    Player *player1 = new Human("", 'X');
    Player *player2;

    // setup to choose between 2 modes
    clearScreen();

    int option = 1;
    while (true)
    {
        // getting option
        while (true)
        {
            clearScreen();
            displayPlay(option);
            int cursor = getKeyPress();

            if (cursor == DOWN)
            {
                if (option == 4)
                    option = 1;
                else
                    ++option;
            }
            else if (cursor == UP)
            {
                if (option == 1)
                    option = 4;
                else
                    --option;
            }
            else if (cursor == ENTER)
            {
                break;
            }
            else if (cursor == ESCAPE)
            {
                option = 3;
                break;
            }
        }

        // putting option to use
        if (option == 1)
        {
            player2 = new Human("", 'O');
            break;
        }
        else if (option == 2)
        {
            // todo hard mode to be added here
            int aiNo = getAINo();

            if (aiNo == 1)
            {
                player2 = new EasyAI("Neko", 'O');
            }
            else if (aiNo == 2)
            {
                player2 = new MediumAI("Tora", 'O');
            }
            else if (aiNo == 3)
            {
                modeSelection(dimension);
                return;
            }
            break;
        }
        else if (option == 3)
        {
            delete player1;
            gridSelection();
            return;
        }
        else if (option == 4)
        {
            delete player1;
            return;
        }
    }

    // setting up player names
    string player1Name, player2Name;
    while (player1Name == "")
    {
        clearScreen();
        cout << "  [Player 1]> Enter name:_";
        getline(cin, player1Name);
    }
    player1->name = player1Name;

    if (option == 1)
    {
        while (player2Name == "")
        {
            clearScreen();
            cout << "  [Player 2]> Enter name:_";
            getline(cin, player2Name);
        }
        player2->name = player2Name;
    }

    // match starting loop
    play(dimension, player1, player2);

    // free memory
    delete player1;
    delete player2;
}

// function to get dimensions
void gridSelection()
{
    int dimension = 3;
    // selecting dimension
    while (true)
    {
        clearScreen();
        gridSelectorDisplay(dimension);

        int cursor = getKeyPress();

        if (cursor == UP)
        {
            if (dimension == 3)
                dimension = 7;
            else
                dimension--;
        }
        else if (cursor == DOWN)
        {
            if (dimension == 7)
                dimension = 3;
            else
                dimension++;
        }
        else if (cursor == ENTER)
        {
            break;
        }
        else if (cursor == ESCAPE)
        {
            return;
        }
    }
    if (dimension == 7)
    {
        return;
    }

    modeSelection(dimension);
}

int main()
{
    // Game loop
    displayHeader();
    while (true)
    {
        // taking input
        int option = 1;
        while (true)
        {
            clearScreen();
            displayMenu(option);
            int cursor = getKeyPress();

            if (cursor == DOWN)
            {
                if (option == 5)
                    option = 1;
                else
                    ++option;
            }
            else if (cursor == UP)
            {
                if (option == 1)
                    option = 5;
                else
                    --option;
            }
            else if (cursor == ENTER)
            {
                break;
            }
            else if (cursor == ESCAPE)
            {
                option = 5;
                break;
            }
        }

        // putting input to use
        switch (option)
        {
        case 1:
            gridSelection();
            break;
        case 2:
            history();
            break;
        case 3:
            rule();
            break;
        case 4:
            help();
            break;
        case 5:
            cout << "Thanks for playing";
            Sleep(2000);
            return 0;
            break;
        default:
            displayWarning();
            break;
        }
    }
    return 0;
}