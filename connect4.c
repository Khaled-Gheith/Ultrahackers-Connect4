#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char player1[30];
char player2[30];
char winner[30];
int entry;
double timeTakenByPlayerHavingRed = 0;
double timeTakenByPlayerHavingYellow = 0;
clock_t start;
clock_t end;
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
    for (int row=5; row>=0; row--){ 
        for (int column=3; column>=0; column--){ 
            if(board[row][column] != 0 && board[row][column] == board[row][column+1] && board[row][column] == board[row][column+2] && board[row][column] == board[row][column+3]){
                return 1;
        }
    }
    return 0;
}
}
//requires: nothing
//effects: returns 1 if there is a vertical line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkVertically(){
    for (int column=0; column<=6; column++){
        for (int row=2; row>=0; row--){
            if(board[row][column] != 0 && board[row][column] == board[row+1][column] && board[row][column] == board[row+2][column] && board[row][column] == board[row+3][column]){
                return 1;
        }
    }
    return 0;
}
}
//requires: nothing
//effects: returns 1 if there is a diagonal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkDiagonally(){
    for(int row=0;row<=2;row++){
        for(int column=0; column<=3;column++ ){
            if(board[row][column] != 0 && board[row][column]==board[row+1][column+1] && board[row][column] ==board[row+2][column+2] && board[row][column]==board[row+3][column+3]){
                return 1;
            }
            
        }
    }
    for(int row=0;row<=2;row++){
        for(int column=6; column>=3;column--){
            if(board[row][column] != 0 && board[row][column]==board[row+1][column-1] && board[row][column] ==board[row+2][column-2] && board[row][column]==board[row+3][column-3]){
                return 1;
            }
        }
    }
    return 0;
}

//requires: A +ve int int the range of [0-6] representing the column selectd by the player 
//effects: returns 1 if the corresponding column is full, and 0 otherwise. 
int checkColumnFull(int col){
    if (board[0][col]){
        return 1;
    }
    return 0;
}
//requires: The updated board
//effects: returns 1 if the board is full; 0 otherwise.
int isBoardFull(){
    int counter = 0;
    for(int column=0; column <= 6; column++){
        if(checkColumnFull(column)) counter++; }
    if(counter==7) return 1;
    return 0;
}

//requires: a +ve int in the range [0-6] representing the intended column by the user.
//effects: returns the number of the row corresponding to the first empty cell (for bottom to top)
//         of the entered column; -1 if the column is full.
int getFirstEmptyRow(int column){
    for(int row = 5; row >= 0; row--){
        if(board[row][column] == 0){
            return row;
        }
    }
    return -1;
}
//requires: a +ve int in the range [0-6] corresponding to the column entered by the user. And a +ve int [1-2]
//          corresponding to the color of the player.
//effects: updates the board based on the player's choice. 
void updateBoard(int column, int color){
    if(!checkColumnFull(column)){
        int row = getFirstEmptyRow(column);
        board[row][column] = color;
        return;
    }
    else if (column < 6){
        updateBoard(column+1, color);

    }else{
        updateBoard(0, color);
    }
    
}
//requires: nothing 
//effects: returns 1 if the player connected 4 entries successfully, 0 otherwise 
int winningMove(){
    if(checkHorizentally() || checkVertically() || checkDiagonally()){
        return 1;
    }else{
        return 0;
    }
}
int main(){
    printf("player 1: Enter your name (single word, no spaces): ");
    scanf("%s",player1);
    printf("player 2: Enter your name (single word, no spaces): ");
    scanf("%s",player2);

    char* playerHavingRed = pickPlayer();
    char* playerHavingYellow = (strcmp(playerHavingRed,player1) == 0) ? player2 : player1;
    printf("%s you'll take the red color, \n%s you'll take the yellow color\n",playerHavingRed, playerHavingYellow);
    printBoard();

    while(!isBoardFull(board)){
        printf("\n");
        printf("%s select a column number (between 0 and 6): ", playerHavingRed);
        start = clock();
        scanf("%d", &entry);
        end = clock();
        updateBoard(entry, 1);
        printBoard();
        if(winningMove()){
            strcpy(winner, playerHavingRed);
            printf("Congrats %s, you\'re the winner!",playerHavingRed);
            break;
        }
        timeTakenByPlayerHavingRed += (double)(end-start)/CLOCKS_PER_SEC;
        printf("%s select a column number (between 0 and 6): ", playerHavingYellow);
        start = clock();
        scanf("%d", &entry);
        end = clock();
        updateBoard(entry, 2);
        printBoard();
        if(winningMove()){
            strcpy(winner, playerHavingYellow);
            printf("Congrats %s, you\'re the winner!",playerHavingYellow);
            break;
        }
        timeTakenByPlayerHavingYellow += (double)(end-start)/CLOCKS_PER_SEC;
    }
    if(isBoardFull()){
        if(timeTakenByPlayerHavingRed < timeTakenByPlayerHavingYellow){
            printf("Time taken by %s = %d seconds.\n",playerHavingRed,timeTakenByPlayerHavingRed);
            printf("Time taken by %s = %d seconds.\n",playerHavingYellow,timeTakenByPlayerHavingYellow);
            printf("Congrats %s, you\'re the winner!",playerHavingRed);
        } 
        else{
            printf("Time taken by %s = %d seconds.\n",playerHavingYellow,timeTakenByPlayerHavingYellow);
            printf("Time taken by %s = %d seconds.\n",playerHavingRed,timeTakenByPlayerHavingRed);
            printf("Congrats %s, you\'re the winner!",playerHavingYellow);
        }
    }
    return 0;
}
