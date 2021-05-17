#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "header.h"

//struct to hold the player information:
struct playerInfo {
    //declaring variables:
    char name[20];
    char color;
    int score;
};

struct playerInfo data(struct playerInfo details, int choice)
{
    if (choice == 1) //runs if player choice is 1
    {
        printf("Enter name for the player playing black: ");
        fgets(details.name, 20, stdin);
        int lenB = strlen(details.name); //lenB is assigned as the length of the black player's name
        details.name[lenB-1] = '\0'; //decreasing the null character from the length
        details.color = 'B'; //color is assigned as black
        details.score = 2; //score is assigned as 2 since there are two pieces on the board in the beginning
    }
    if (choice == 2) //runs if player choice is 2
    {
        printf("Enter name for the player playing white: ");
        fgets(details.name, 20, stdin);
        int lenW = strlen(details.name); //lenW is assigned as the length of the white player's name
        details.name[lenW-1] = '\0'; //decreasing the null character from the length
        details.color = 'W'; //color is assigned as white
        details.score = 2; //score is assigned as 2 since there are two pieces on the board in the beginning
    }
    return details; //returns the details of players' info
}

int main()
{
    //declarations:
    struct playerInfo black;
    struct playerInfo white;
    int count; //counts the valid moves
    char current_player = 'B';
    char opponent_player = 'W';
    char board[8][8];
    char temp; //holds the player temporary
    bool game_over = false; //game status is set to false in the beginning, meaning the game is not finished

    printf("Welcome to Othello!\n");
    instructions(); //function call to display the rules of the game

    black = data(black, 1); //player that is playing with black
    white = data(white, 2); //player that is playing with white

    initializing_board(board); //game board is initialized with this function call
    printf("\nScoreboard: (%s) %d:%d (%s).\n", black.name, black.score, white.score, white.name);
    print_board(board);

    while (game_over != true) //while loop keeps running until the game is over
    {
        if (current_player == 'B') {printf("\n%s's (black) turn.", black.name);}
        if (current_player == 'W') {printf("\n%s's (white) turn.", white.name);}
        count = valid_moves(board, current_player, opponent_player); //valid move  count is set using its function

        if (count == 0)
        {
            printf("NO VALID MOVES!\n");
            //players' turn change according to the current player:
            if (current_player == 'W') {printf("\n%s's (black) turn.", black.name);}
            if (current_player == 'B') {printf("\n%s's (white) turn.", white.name);}
            count = valid_moves(board, opponent_player, current_player); //valid move  count is set using its function

            if (count == 0)
            {
                printf("No valid moves, the game is over.\n");
                game_over = true; //game status is set to true, meaning the game is finished
                break;
            }
            else
            {
                //using a temporary variable to change the player:
                temp = current_player;
                current_player = opponent_player;
                opponent_player = temp;
            }
        }

        making_moves(board, current_player, opponent_player); //function call that allows making moves

        if (current_player == 'B') //if black is currently playing
        {
            //both black and white player scores are set according to the scoreboard function
            black.score = scoreboard(board, current_player);
            white.score = scoreboard(board, opponent_player);
        }

        if (current_player == 'W') //if white is currently playing
        {
            //both black and white player scores are set according to the scoreboard function
            black.score = scoreboard(board, opponent_player);
            white.score = scoreboard(board, current_player);
        }

        printf("\nScoreboard: (%s) %d:%d (%s).\n", black.name, black.score, white.score, white.name);
        print_board(board); //function call that prints the board
        //using a temporary variable to change the player:
        temp = current_player;
        current_player = opponent_player;
        opponent_player = temp;
    }

    FILE *fp;
    fp = fopen("othello-results.txt", "a");
    time_t t; time(&t); //used when printing out date and time

    if (black.score > white.score) //runs when black wins
    {
        printf("%s wins!!! The final scoreboard is %d:%d.\n", black.name, black.score, white.score);
        fprintf(fp, "%s wins!!! The final scoreboard is %d:%d. (%s)\n", black.name, black.score, white.score, ctime(&t));
    }
    else if (white.score > black.score) //runs when white wins
    {
        printf("%s wins!!! The final scoreboard is %d:%d.\n", white.name, white.score, black.score);
        fprintf(fp, "%s wins!!! The final scoreboard is %d:%d. (%s)\n", black.name, black.score, white.score, ctime(&t));
    }
    else //runs in case of a draw (when black and white score equally)
    {
        printf("It's a draw!!! The final scoreboard is %d:%d.", black.score, white.score);
        fprintf(fp, "%s drew against %s %s\n", black.name, white.name, ctime(&t));
    }
}
