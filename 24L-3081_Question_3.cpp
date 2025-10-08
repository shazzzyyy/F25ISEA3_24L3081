#include <iostream>
using namespace std;

const int boardSize = 3;   
/**
 * This function initializes the board with just spaces
 */
void initializeBoard(char board[boardSize][boardSize]) 
{
    for (int rows = 0; rows < boardSize; rows++) 
    {
        for (int col = 0; col < boardSize; col++) 
        {
            board[rows][col] = ' ';
        }
    }
}

/**
 * Displays the board 
 */
void displayBoard(const char board[boardSize][boardSize]) 
{
    cout <<endl;
    cout << "-------------"<<endl;
    for (int rows=0; rows <boardSize; rows++)
    {
        cout << "[ ";
        for (int col=0; col< boardSize; col++) 
        {
            cout << board[rows][col] << " ] ";
        }
        cout << endl<<"-------------"<<endl;
    }
    cout <<endl;
}
/**
 * This function checks if there is any player who has won by completing a row
 * or by completing a column or a diagonal
 */
bool checkWinner(const char board[boardSize][boardSize], char player) 
{
    for (int i = 0; i < boardSize; i++) 
    {
        // this is check for row wise or column wise 
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    // this is a check for diagonal 
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}
/**
 * THis checks if the board if complete like all moves done and no player has won
 * then it returns true
 * and if there is a space left then return false
 */
bool isDraw(const char board[boardSize][boardSize]) 
{
    for (int rows = 0; rows < boardSize; rows++) 
    {
        for (int column = 0; column <boardSize; column++) 
        {
            if (board[rows][column] == ' ')
            {
                return false;
            } 
        }
    }
    return true;
}
/**
 * This function handles player input 
 * and sets the player move into the board
 */
void playerMove(char board[boardSize][boardSize], char player) 
{
    int row, col;
    while (true) 
    {
        cout<<"Player "<<player<<" enter row number (1-3) : ";
        cin>>row;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter numbers only! "<<endl;
            continue;
        }

        cout<<"Now enter column number (1-3) : ";
        cin>>col;

        row--; 
        col--;
        // if invalid cin then this handles it 
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter numbers only! "<<endl;
            continue;
        }

        if (row<0 || row>= boardSize || col<0 || col >=boardSize)
        {
            cout<<"Invalid position! Please choose between 1 and 3"<<endl;
        }

        else if (board[row][col] !=' ') 
        {
            cout<<"That spot is already taken! Try again."<<endl;
        } 
        else 
        {
            board[row][col] = player;
            break;
        }
    }
}
/**
 * This is the main functions that runs the whole game
 * first initializes the grid 
 * then runs a loop loop and shows the grid each time then call player move to get the players values
 * then checks if any of em has won or not 
 * if yes then declares the player winner and ends the game 
 * else check if there is a draw if not  switch the player turn and keeps looping until a draw happens or a player wins
 */
void playTicTacToe() 
{
    char board[boardSize][boardSize];

    initializeBoard(board);
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) 
    {
        displayBoard(board);
        playerMove(board, currentPlayer);

        if (checkWinner(board, currentPlayer)) 
        {
            displayBoard(board);
            cout<<"Player "<<currentPlayer<<" wins! "<<endl;
            gameOver = true;
        } 
        else if (isDraw(board)) 
        {
            displayBoard(board);
            cout<<"Game Drawn!"<<endl;
            gameOver = true;
        } 
        else 
        {
            // switching player turn
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}
int main() 
{
    cout<<"--------------------------------------"<<endl;
    cout<<"              Tic tac toe             "<<endl;
    cout<<"--------------------------------------"<<endl;

    playTicTacToe();  

    cout<<endl<<"--------------------------------------"<<endl;
    cout<< "               Game Ended               "<<endl;
    cout<< "--------------------------------------"<<endl;
    return 0;
}
