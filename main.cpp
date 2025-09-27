#include <iostream>
#include <vector>
#include <string>
#include "display.h" // UI header

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
    // function to place symbol and check if game is over
    virtual bool placeMove(Board &board) = 0;
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
                grid[i][j] = (char)(i * n + j + 48 + 1);
            }
        }
    }

    // function to display the board
    void displayBoard()
    {
        for (int i = 0; i < n; i++)
        {
            // board top border
            if (i == 0)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j == 0)
                        cout << " ";
                    cout << "----";
                }
                cout << endl;
            }

            // board elements
            for (int j = 0; j < n; j++)
            {
                if (j == 0)
                    cout << "| ";
                cout << grid[i][j] << " | ";
            }
            cout << endl;

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
    bool placeMove(Board &board) override
    {
        int gridBody = board.grid.size();
        int position;
        cout << name << "'s turn. Place your move: ";
        cin >> position;

        // calculating row from position
        int row = position <= gridBody ? 0 : (position - 1) / gridBody;
        // calculating column from position
        int col = position <= gridBody ? position - 1 : (position - 1) % gridBody;

        if (isCellOccupied(board.grid, row, col))
        {
            cout << " Cell occupied.Choose a different position." << endl;
            return placeMove(board);
        }

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

    // function to place symbol an check if the game is over
    bool placeMove(Board &board) override
    {
        int gridBody = board.grid.size();
        int position;
        cout << name << "'s turn. Place your move: ";
        cin >> position;

        // calculating row from position
        int row = position <= gridBody ? 0 : (position - 1) / gridBody;
        // calculating column from position
        int col = position <= gridBody ? position - 1 : (position - 1) % gridBody;

        if (isCellOccupied(board.grid, row, col))
        {
            cout << " Cell occupied.Choose a different position." << endl;
            return placeMove(board);
        }

        board.grid[row][col] = this->symbol;

        // checking for game over
        return checkHorizontal(board.grid, row) || checkVertical(board.grid, col) || checkDiagonal(board.grid);
    }
};

// function to play against human opponent
void play(int n, Player *player1, Player *player2)
{
    bool gameOver = false;
    Board board(n);

    // Match loop
    board.displayBoard();
    bool turn = false;
    while (!gameOver)
    {
        turn = !turn;
        if (turn)
        {
            gameOver = player1->placeMove(board);
            board.displayBoard();
        }
        else
        {
            gameOver = player2->placeMove(board);
            board.displayBoard();
        }
    }

    Player *winner = turn ? player1 : player2;
    cout << "Game Over. Winner: " << (winner->name) << endl;
    cout << "-------------------------------------" << endl
         << endl;

    // setting up restart window
    displayHeader();
    cout << "   [Match] > 1. Restart" << endl;
    cout << "             2. Back" << endl;

    int option;
    cin >> option;
    if (option == 1)
    {
        play(n, player1, player2);
    }
    else if (option == 2)
    {
        return;
    }
    else
    {
        displayHeader();
        cout << "Invalid Option. Please choose between the given options" << endl;
    }
}

// function to play
void runGame()
{
    int n;
    displayHeader();
    cout << "Enter grid size: ";
    cin >> n;

    // todo n<3 for production
    if (n < 2)
    {
        displayHeader();
        cout << "At least 3x3 dimension is required for fair gameplay." << endl;
        runGame();
        return;
    }

    // setup to choose between 2 modes
    displayHeader();
    cout << "[Play] > 1. Human vs Human" << endl;
    cout << "         2. Human vs AI" << endl;

    // Player setup based on mode chosen
    int vsHuman;
    cin >> vsHuman;

    string player1Name, player2Name;
    cout << "Enter player 1 name: ";
    cin >> player1Name;

    if (vsHuman == 1)
    {
        cout << "Enter player 2 name: ";
        cin >> player2Name;
    }

    Player *player1 = new Human(player1Name, 'X');
    Player *player2;

    if (vsHuman == 1)
        player2 = new Human(player2Name, 'O');
    else
        player2 = new AI("AI", 'O');

    // match starting loop
    play(n, player1, player2);
}

// main function
int main()
{
    // Game loop
    while (true)
    {
        displayMenu();
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            runGame();
            break;
        case 2:
            cout << " Coming soon!!!" << endl;
            break;
        case 3:
            cout << " Coming soon!!!" << endl;
            break;
        case 4:
            cout << " Thanks for playing";
            return 0;
            break;
        default:
            cout << " Invalid option. Choose between a given option please" << endl;
            break;
        }
    }

    return 0;
}