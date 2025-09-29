#include <iostream>
#include <vector>
#include <string>
#include "main.h" // UI header

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
                // grid[i][j] = (char)(i * n + j + 48 + 1);
                grid[i][j] = ' ';
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
                    cout << "| ";
                cout << grid[i][j] << " | ";
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
    bool placeMove(Board &board) override
    {
        int gridBody = board.grid.size();
        int position;

        while (true)
        {
            cout << name << "'s turn. Place your move: ";
            cin >> position;
            if (position > gridBody * gridBody)
            {
                cout << position << " is out of the grid. Position must be <= " << gridBody * gridBody << endl;
            }
            else
            {
                break;
            }
        }

        // calculating row from position
        int row = position <= gridBody ? 0 : (position - 1) / gridBody;
        // calculating column from position
        int col = position <= gridBody ? position - 1 : (position - 1) % gridBody;

        if (isCellOccupied(board.grid, row, col))
        {
            cout << "Position occupied.Choose a different position please." << endl;
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

    //? remove temporary function to display a vector
    void displayVector(vector<vector<int>> v)
    {
        int n = v.size();
        for (int i = 0; i < n; i++){
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
    bool placeMove(Board &board) override
    {   
        cout << "AI's Turn:"<< endl;

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

// function to start a match
void play(int n, Player *player1, Player *player2)
{
    bool gameOver = false;
    Board board(n);

    // Match loop
    board.displayBoard();
    Player *turn = player1;
    Player *winner = nullptr;
    while (!gameOver)
    {
        if (turn == player1)
        {
            gameOver = player1->placeMove(board);
            board.displayBoard();
            winner = player1;
            turn = player2;
        }
        else
        {
            gameOver = player2->placeMove(board);
            board.displayBoard();
            winner = player2;
            turn = player1;
        }
        bool draw = Player::isDraw(board.grid);
        if (draw)
        {
            gameOver = true;
            winner = nullptr;
        }
    }
    if (winner == nullptr)
    {
        cout << "Game Over!!! Draw" << endl;
    }
    else
    {
        cout << "Game Over!!! Winner: " << (winner->name) << endl;
    }

    // setting up restart window
    displayHeader();
    cout << "   [Match] > 1. Restart" << endl;
    cout << "             2. Back" << endl;

    char option;
    cin >> option;
    if (option == '1')
    {
        play(n, player1, player2);
    }
    else if (option == '2')
    {
        return;
    }
    else
    {
        displayHeader();
        displayWarning();
    }
}

// function to start the game
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

    // Player setup based on mode chosen
    Player *player1 = new Human("", 'X');
    Player *player2;

    // setup to choose between 2 modes
    char option;
    while (true)
    {
        displayHeader();
        cout << "[Play] > 1. Human vs Human" << endl;
        cout << "         2. Human vs AI" << endl;
        cin >> option;
        if (option == '1')
        {
            player2 = new Human("", 'O');
            break;
        }
        else if (option == '2')
        {
            player2 = new AI("AI", 'O');
            break;
        }
        else
        {
            displayWarning();
        }
    }

    // setting up player names
    string player1Name, player2Name;
    cout << "Enter player 1 name: ";
    cin >> player1Name;
    player1->name = player1Name;

    if (option == '1')
    {
        cout << "Enter player 2 name: ";
        cin >> player2Name;
        player2->name = player2Name;
    }

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
        char option;
        cin >> option;
        switch (option)
        {
        case '1':
            runGame();
            break;
        case '2':
            cout << "Coming soon!!!" << endl;
            break;
        case '3':
            cout << "Coming soon!!!" << endl;
            break;
        case '4':
            cout << "Coming Soon!!!";
            return 0;
            break;
        case '5':
            cout << "Thanks for playing";
            return 0;
            break;
        default:
            displayWarning();
            break;
        }
    }

    return 0;
}