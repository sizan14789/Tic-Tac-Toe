#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Board;

class Player
{
public:
    string name;
    char symbol;

    // constructors
    Player(string name) : name(name) {}
    Player(string name, char symbol) : name(name), symbol(symbol) {}

private:
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
    bool placeMove(Board &board);
};

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

        grid.resize(n);
        for (int i = 0; i < n; i++)
        {
            grid[i].resize(n);
        }

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

    //? function to place move
    // void placeMove(Player *mover)
    // {
    //     mover->placeMove((*this));
    // }
};

// function to place symbol an check if the game is over
bool Player::placeMove(Board &board)
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
        cout << "Cell occupied.Choose a different position." << endl;
        return placeMove(board);
    }

    board.grid[row][col] = this->symbol;
    return checkHorizontal(board.grid, row) || checkVertical(board.grid, col) || checkDiagonal(board.grid);
}

void playVsHuman(int n)
{
    bool gameOver = false;
    Board board(n);

    string player1Name, player2Name;
    cout << "Enter player 1 name: ";
    cin >> player1Name;
    cout << "Enter player 2 name: ";
    cin >> player2Name;

    Player *player1 = new Player(player1Name, 'X');
    Player *player2 = new Player(player2Name, 'O');

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
}

void play()
{
    int n;
    cout << "enter grid size: ";
    cin >> n;

    while (true)
    {
        playVsHuman(n);
        int option;
        cout << "1. Start new game" << endl;
        cout << "2. Quit" << endl;
        cin >> option;
        if (option == 1)
        {
            play();
            return;
        } else if(option == 2) {
            return;
        } else {
            cout << "Invalid Option. Please choose between the given options" << endl;
        }
    }
}

int main()
{
    play();

    return 0;
}