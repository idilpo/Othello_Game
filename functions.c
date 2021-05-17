#include <stdio.h>
#include <stdbool.h>


void instructions(void) //function that runs when the user wants to see the rules of the game
{
    printf("---------------------------------------------------------RULES OF OTHELLO---------------------------------------------------------");
    printf("\nOthello is a strategy board game for two players (Black and White), played on an 8 by 8 board. The game traditionally begins with\n"
           "four discs placed in the middle of the board. Black moves first. Black must place a black disc on the board, in such a way that there\n"
           "is at least one straight (horizontal, vertical, or diagonal) occupied line between the new disc and another black disc, with one or\n"
           "more contiguous white pieces between them. After placing the disc, Black flips all white discs lying on a straight line between the\n"
           "new disc and any existing black discs. All flipped discs are now black, after this it's White's turn to play. This player operates\n"
           "under the same rules, with the roles reversed: White lays down a white disc, causing black discs to flip. Players alternate taking\n"
           "turns. If a player does not have any valid moves, play passes back to the other player. When neither player can move, the game ends.\n"
           "A game of Othello may end before the board is completely filled. The player with the most discs on the board at the end of the\n"
           "game wins. If both players have the same number of discs, then the game is a draw.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------");
    printf("\nYou are now ready to play! The game will start.\n");
}


void initializing_board(char board[8][8]) //function that runs when initializing the board
{
    for (int m=0; m<8; m++) //digit loop
    {
        for (int n=0; n<8; n++) //letter loop
        {
            board[m][n] = ' '; //board is initialized
        }
    }
    //first four discs are placed as such in the beginning of the game:
    board[3][3] = 'W';
    board[3][4] = 'B';
    board[4][3] = 'B';
    board[4][4] = 'W';
}


void print_board(char board[8][8])
{
    for (int m=0; m<8; m++)
    {
        int digit = 1+m; //allows to display number at the side of the board
        printf("   --- --- --- --- --- --- --- --- \n"); //top of the board
        printf("%d |", digit); //digits of the board (left)
        for (int n=0; n<8; n++)
        {
            printf(" %c |", board[m][n]); //corresponds each square
        }
        printf("\n");
    }
    printf("   --- --- --- --- --- --- --- --- \n"); //bottom of the board
    printf("    a   b   c   d   e   f   g   h  \n"); //letters of the board (bottom)
}


bool checking_direction(char board[8][8], int digit, int letter, int m, int n, char color, char opposite)
{
    digit += m;
    letter += n;

    if (board[digit][letter] == color || board[digit][letter] == ' ') {return false;}

    digit += m;
    letter += n;

    while (board[digit][letter] != ' ' && digit < 8 && letter < 8 && digit >= 0 && letter >= 0)
    {
        if (board[digit][letter] == color) {return true;}
        if (board[digit][letter] == opposite)
        {
            digit += m;
            letter += n;
        }
    }
    return false;
}


void updating_board(char board[8][8], int digit, int letter, int m, int n, char color) //function that updates the board according to the move
{
    digit += m;
    letter += n;

    while (board[digit][letter] != color) //while loop keeps running until the disc's color in the current square is not the same as the variable "color"
    {
        board[digit][letter] = color;
        digit += m;
        letter += n;
    }
}


void making_moves(char board[8][8], char color, char opposite) //function that allows to make moves on the board
{
    char move[2]; //stores 2 characters, a digit and a letter which corresponds to the move that the player makes
    int count = 0; //valid moves count is set to 0 in the beginning

    printf("\nPlease enter the move you'd like to play: ");
    gets(move); //player's move is stored

    //variables are initialized
    int digit = (move[0] - '0') - 1;
    int letter = move[1] - 'a';

    if (checking_direction(board, digit, letter, 1, 0, color, opposite) == true) //direction: down
    {
        updating_board(board, digit, letter ,1 , 0, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, -1, 0, color, opposite) == true) //direction: up
    {
        updating_board(board, digit, letter ,-1 , 0, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, 0, 1, color, opposite) == true) //direction: right
    {
        updating_board(board, digit, letter ,0, 1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, 0, -1, color, opposite) == true) //direction: left
    {
        updating_board(board, digit, letter ,0 , -1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, 1, 1, color, opposite) == true) //direction: down right
    {
        updating_board(board, digit, letter ,1 , 1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, 1, -1, color, opposite) == true) //direction: down left
    {
        updating_board(board, digit, letter ,1 , -1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, -1, 1, color, opposite) == true) //direction: up right
    {
        updating_board(board, digit, letter ,-1 , 1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    if (checking_direction(board, digit, letter, -1, -1, color, opposite) == true) //direction: up left
    {
        updating_board(board, digit, letter ,-1, -1, color); //board is updated accordingly
        count++; //valid moves count is incremented
    }
    board[digit][letter] = color;
}


void print_move(int digit, int letter) //function that prints the move made by the player
{
    printf("%d", digit + 1);
    char also_letter = letter + 'a';
    printf("%c ", also_letter);
}


int scoreboard(char board[8][8], char color) //function that calculates the score
{
    int score = 0; //score is set to 0 in the beginning
    for (int m=0; m<8; m++)
    {
        for (int n=0; n<8; n++)
        {
            if (board[m][n] == color) {score++;} //the loop keeps checking each square and incrementing the score as it goes along
        }
    }
    return score;
}


int valid_moves(char board[8][8], char color, char opposite)
{
    int count = 0; //valid moves count is set to 0 in the beginning
    printf("\nValid moves to play: ");

    for (int digit=0; digit<8; digit++) //loop for digits
    {
        for (int letter=0; letter<8; letter++) //loop for letters
        {
            if (board[digit][letter] == ' ') //if the current square is not occupied by any disc
            {
                if (checking_direction(board, digit, letter, 1, 0, color, opposite) == true) //direction: down
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, -1, 0, color, opposite) == true) //direction: up
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, 0, 1, color, opposite) == true) //direction: right
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, 0, -1, color, opposite) == true) //direction: left
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, 1, 1, color, opposite) == true) //direction: down right
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, 1, -1, color, opposite) == true) //direction: down left
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, -1, 1, color, opposite) == true) //direction: up right
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
                else if (checking_direction(board, digit, letter, -1, -1, color, opposite) == true) //direction: up left
                {
                    print_move(digit, letter); count++; //move that is made is printed and count is incremented
                }
            }
        }
    }
    return count; //valid move count is returned
}
