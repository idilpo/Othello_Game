#ifndef OTHELLO_GAME_HEADER_H
#define OTHELLO_GAME_HEADER_H
//function declarations:
void instructions(void);
void initializing_board(char board[8][8]);
void print_board(char board[8][8]);
bool checking_direction(char board[8][8], int digit, int letter, int i, int j, char color, char opposite);
void updating_board(char board[8][8], int digit, int letter, int i, int j, char color);
void making_moves(char board[8][8], char color, char opposite);
void print_move(int digit, int letter);
int scoreboard(char board[8][8], char color);
int valid_moves(char board[8][8], char color, char opposite);
#endif OTHELLO_GAME_HEADER_H

