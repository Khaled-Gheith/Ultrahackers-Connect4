#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char player1[30];
char player2[30];
int board[6][7]= {
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0}
                  };
//requires: nothing 
//effects: prints the board of 6 rows and 7 columns 
void printBoard(){
    printf("- - - - - - - - - - - - - - -\n");
    for(int row= 0; row<6; row++){
        for(int col=0; col<7; col++){
            printf("| ");
            printf("%d ", board[row][col]);
        }
        printf("|\n");
    }
    printf("- - - - - - - - - - - - - - -\n");
}

//requires: nothing
//effects: returns a random float number between 0 and 1

int fairCoin(){
    srand(time(NULL));
    return rand()%10;
}
//requires: nothing
//effects: returns the name of the player having the red color
//if the value returned by fairCoin() is [0-4], player1 will be red. Otherwise, player2 will take thwe red color.
char* pickPlayer(){
    int randomNumber = fairCoin();
    if (0 <= randomNumber && randomNumber <= 4){
        return player1;
    }
    else{
        return player2;
    }
}
//requires: takes the updated board
//effects: returns 1 if there is a horizontal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkHorizentally(){
    for (int row=0; row<6; row++){ 
        for (int column=0; column<=3; column++){ 
            if(board[row][column] == board[row][column+1] && board[row][column] == board[row][column+2] && board[row][column] == board[row][column+3]){
                return 1;
        }
    }
    return 0;
}
}
//requires: nothing
//effects: returns 1 if there is a vertical line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkVertically(){
    for (int column=0; column<7; column++){
        for (int row=0; row<=2; row++){
            if(board[row][column] == board[row][column+1] && board[row][column] == board[row][column+2] && board[row][column] == board[row][column+3]){
                return 1;
        }
    }
    return 0;
}
}
//requires: nothing
//effects: returns 1 if there is a diagonal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkDiagonally(){
    for(int row=0;row<=3;row++){
        for(int column=0; column<=2;column++ ){
            if(board[row][column]==board[row+1][column+1] && board[row][column] ==board[row+2][column+2] && board[row][column]==board[row+3][column+3]){
                return 1;
            }
            
        }
    }
    for(int row=4;row<=6;row++){
        for(int column=0; column<=2;column++ ){
            if(board[row][column]==board[row-1][column-1] && board[row][column] ==board[row-2][column-2] && board[row][column]==board[row-3][column-3]){
                return 1;
            }
        }
    }
    return 0;
}

//requires: A +ve int int the range of [0-6] representing the column selectd by the player 
//effects: returns 1 if the corresponding column is full, and 0 otherwise. 
int checkColumnFull(int col){
    int flag = 1;
    for (int row=0; row<=5; row++){
        if (board[row][col]==0){
            flag = 0;
            break;
        }
    }
    return flag;
}
//requires: The updated board
//effects: returns 1 if the board is full; 0 otherwise.
int isBoardFull(){
    int flag = 1;
    for(int column=0; column <= 6; column++){
        if(!checkColumnFull(column)){
            flag = 0;
            break;
    }
    return flag;
}
}
int main(){
    printf("player 1: Enter your name (single word, no spaces): ");
    scanf("%s",player1);
    printf("player 2: Enter your name (single word, no spaces): ");
    scanf("%s",player2);

    const char* playerHavingRed = pickPlayer();
    const char* playerHavingYellow = (strcmp(playerHavingRed,player1) == 0) ? player2 : player1;
    printf("%s you'll take the red color, \n%s you'll take the yellow color",playerHavingRed, playerHavingYellow);
    return 0;
}
