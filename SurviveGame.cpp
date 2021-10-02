/*
Name(s):Darrian Belcher
Date: 05/17/21
Program Name: Survive Game
Program Description: Survive game that involves traversing a 2D board while trying to avoid enemies
*/

#include<iomanip>
#include<iostream>
#include <cstdlib>

using namespace std;
// Global variables used throughout program
const int boardHeight = 15;
const int boardWidth = 15;

class gameBoard; 

class gameBoard{
    public:
        char gameBoard[boardHeight][boardWidth];
        void fillBoard(); 
        void printBoard(); 

};

/*
Summary: Fills board with zeros
Reasoning: Needed to set board
Input: N/A
Output: N/A
*/
void gameBoard::fillBoard(){
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            gameBoard[i][j] = '0';
        }
    }
}

/*
Summary: Prints board to terminal
Reasoning: Needed to display board to player
Input: N/A
Output: N/A
*/
void gameBoard::printBoard(){
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            cout << gameBoard[i][j] << " ";
        }
        cout << endl;
    }
}

class characters
{
public:
    int XPosition;
    int YPosition;
};


    class user : characters
{
    friend class enemy;
    public:
        int numberOfMoves; 
        void moveUser(gameBoard *board);
        void setInitialPosition(gameBoard *board);
        void updatePosition(gameBoard *board);
        void teleport(gameBoard *board); 
};

/*
Summary: Generates random variables for the x and y position of the player for teleportation move
Reasoning: Needed to teleport user to a random position
Input: gameBoard *board
Output: N/A
*/
void user::teleport(gameBoard *board){
    board->gameBoard[XPosition][YPosition] = '0';
    
    int randomX = rand() % 15 + 1;
    int randomY = rand() % 15 + 1;

    XPosition = randomX; 
    YPosition = randomY; 
}

/*
Summary: Sets the initial position of the user's character
Reasoning: Set initial user position to the middle of the board
Input: gameBoard *board
Output: N/A
*/
void user::setInitialPosition(gameBoard *board)
{
    XPosition = 7;
    YPosition = 7;
    board->gameBoard[XPosition][YPosition] = 'P';
}

/*
Summary: Sets the updated position of the user's character
Reasoning: Needed to update user's position after they move
Input: gameBoard *board
Output: N/A
*/
void user::updatePosition(gameBoard *board){
    board->gameBoard[XPosition][YPosition] = 'P';
}

/*
Summary: Allows the user to input a number representing the direction they want to move. If the user can't move in that direction, they lose their turn. 
Reasoning: User control 
Input: gameBoard *board
Output: N/A
*/
void user::moveUser(gameBoard * board){
    board->gameBoard[XPosition][YPosition] = '0';
    int directionInput; 

    //Displays menue of user moves
    cout << "Please input a direction to move: " << endl; 
    cout << "1. UP" << endl;
    cout << "2. DOWN" << endl;
    cout << "3. LEFT" << endl;
    cout << "4. RIGHT" << endl;
    cout << "5. TELEPORT" << endl; 
    
    cin >> directionInput;

    switch(directionInput){
        case 1: 
            if (XPosition - 1 >= 0){
                XPosition -= 1;
            }
            else{
                cout << "You can't go that way! You lost your turn!" << endl; 
            }
            break; 
        case 2:
            if (XPosition + 1 <= 14){
                XPosition += 1;
            }
            else
            {
                cout << "You can't go that way! You lost your turn!" << endl;
            }
            break;
        case 3:
            if (YPosition - 1 >= 0){
                YPosition -=1; 
            }
            else{
                cout << "You can't go that way! You lost your turn!" << endl;
            }
            break; 
        case 4: 
            if (YPosition + 1 <= 14){
                YPosition +=1; 

            }
            else
            {
                cout << "You can't go that way! You lost your turn!" << endl;
            }
            break; 
        case 5:
            teleport(board); 
    }
    numberOfMoves += 1;
}

    class enemy : characters
{
    public:
        void setInitialPosition(int x, int y, gameBoard *board);
        void moveEnemyX(gameBoard *board, user user);
        void moveEnemyY(gameBoard *board, user user);
        void updatePosition(gameBoard *board);
        bool checkWinner(user user); 
};

/*
Summary: Sets the initial position of the enemy
Reasoning: Set initial enemy position 
Input: gameBoard *board
Output: N/A
*/
void enemy::setInitialPosition(int x, int y, gameBoard *board){
    XPosition = x;
    YPosition = y;
    board->gameBoard[XPosition][YPosition] = 'X';
}

/*
Summary: Uses if statements to move the enemy continuously closer to the user, tries to match the user's x position first
Reasoning: Needed to move the enemy towards user
Input: gameBoard *board, user user
Output: N/A
*/

void enemy::moveEnemyX(gameBoard *board, user user)
{
    board->gameBoard[XPosition][YPosition] = '0';
    
    
    if (XPosition > user.XPosition && (XPosition - 1) >= 0)
    {
        XPosition--;
    }
    else if (XPosition < user.XPosition && (XPosition + 1) <= 14)
    {
        XPosition++;
    }
    else if (YPosition > user.YPosition && (YPosition - 1) >= 0)
    {
        YPosition--; 
    }
    else if (YPosition < user.YPosition && (YPosition +1) <= 14){
        YPosition++; 
    }
    
}

/*
Summary: Uses if statements to move the enemy continuously closer to the user, tries to match the user's y position first
Reasoning: Needed to move the enemy towards user
Input: gameBoard *board
Output: N/A
*/

void enemy::moveEnemyY(gameBoard *board, user user)
{
    board->gameBoard[XPosition][YPosition] = '0';

    if (YPosition > user.YPosition && (YPosition - 1) >= 0)
    {
        YPosition--;
    }
    else if (YPosition < user.YPosition && (YPosition + 1) <= 14)
    {
        YPosition++;
    }
    else if (XPosition > user.XPosition && (XPosition - 1) >= 0)
    { 
        XPosition--;
    }
    else if (XPosition < user.XPosition && (XPosition + 1) <= 14)
    {
        XPosition++;
    }
}
/*
Summary: Updates the enemy's position after it has moved
Reasoning: Update enemy position after every move
Input: gameBoard *board
Output: N/A
*/
void enemy::updatePosition(gameBoard *board){
    board->gameBoard[XPosition][YPosition] = 'X';
}

/*
Summary: Uses if statement to determine if the enemy's position is equal to the user's position. Returns false if they are equal. 
Reasoning: Check if the enemy has overtaken the user's position and won.  
Input: gameBoard *board
Output: true or false
*/
bool enemy::checkWinner(user user){
    if (XPosition == user.XPosition && YPosition == user.YPosition){
        return false; 
    }
    else{
        return true; 
    }
}

int main(){
    int numberOfMoves; //stores number of moves the user has taken
    int numberOfLives = 3; 


    gameBoard board;
    user user; 

    enemy enemy1; 
    enemy enemy2; 
    enemy enemy3; 

  do{

  
    // fills the board and sets initial positions for user and enemy
    board.fillBoard();
    user.setInitialPosition(&board); 

    enemy1.setInitialPosition(8, 2, &board);
    enemy2.setInitialPosition(12, 9, &board);
    enemy3.setInitialPosition(5, 7, &board); 

    board.printBoard();

    // Game prompt
    cout << endl; 
    cout << "SURVIVE GAME!" << endl; 
    cout << "The origin of the board is in the top left-hand corner. Try to avoid the enemies! You have the ability to randomly teleport, but accidentally land on an enemy and you lose a life! Number of lives: " << numberOfLives << endl; 

    while(enemy1.checkWinner(user) && enemy2.checkWinner(user) && enemy3.checkWinner(user)){ // while loop that runs enemies position's are not equal to the user's
    
        user.moveUser(&board);
        user.updatePosition(&board);
        board.printBoard();

        // if statement that uses modulus so that enemeies only move once for every two user moves
        if (user.numberOfMoves % 2 == 0)
        {
            enemy1.moveEnemyX(&board, user);
            enemy1.updatePosition(&board);

            enemy2.moveEnemyX(&board, user);
            enemy2.updatePosition(&board);

            enemy3.moveEnemyY(&board, user);
            enemy3.updatePosition(&board);

            cout << endl; 
            cout << endl; 
            board.printBoard();
        }
    }
    cout << endl <<  "The enemy has taken your position. You lost a life!" << endl << endl;
    numberOfLives -=1; 
  } while (numberOfLives != 0); // Game runs untill the user loses all three lives

  cout << endl << "You have lost all three of your lives. GAME OVER!" << endl; 
}