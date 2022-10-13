#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char player1[30];
char player2[30];
char winner[30];
int entry;
long double timeTakenByPlayerHavingRed = 0;
long double timeTakenByPlayerHavingYellow = 0;
clock_t start;
clock_t end;

//requires: a 2D board of 6 rows and 7 columns 
//effects: prints the board
void printBoard(int board[6][7]){
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
//if the value returned by fairCoin() is [0-4], player1 will be red. Otherwise, player2 will take the red color.
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
int checkHorizontally(int board[6][7]){
    for (int row=5; row>=0; row--){ 
        for (int column=3; column>=0; column--){ 
            if(board[row][column] != 0 && board[row][column] == board[row][column+1] && board[row][column] == board[row][column+2] && board[row][column] == board[row][column+3]){
                return 1;
        }
    }
    }
    return 0;

}
//requires: takes the updated board
//effects: returns 1 if there is a vertical line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkVertically(int board[6][7]){
    for (int column=0; column<=6; column++){
        for (int row=2; row>=0; row--){
            if(board[row][column] != 0 && board[row][column] == board[row+1][column] && board[row][column] == board[row+2][column] && board[row][column] == board[row+3][column]){
                return 1;
        }
    }
    }
    return 0;

}
//requires: takes the updated board
//effects: returns 1 if there is a diagonal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkDiagonally(int board[6][7]){
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

//requires: A 2D board of 6 rows and 7 columns and a +ve int in the range of [0-6] representing the column selectd by the player 
//effects: returns 1 if the corresponding column is full, and 0 otherwise. 
int checkColumnFull(int board[6][7] ,int col){
    if (board[0][col]){
        return 1;
    }
    return 0;
} 
//requires: The updated board
//effects: returns 1 if the board is full; 0 otherwise.
int isBoardFull(int board[6][7]){
    int counter = 0;
    for(int column=0; column <= 6; column++){
        if(checkColumnFull(board,column)) counter++; }
    if(counter==7) return 1;
    return 0;
}

//requires: a 2D board of 6 rows and 7 columns and a +ve int in the range [0-6] representing the selected column by the user.
//effects: returns the number of the row corresponding to the first empty cell (from bottom to top)
//         of the entered column; -1 if the column is full.
int getFirstEmptyRow(int board[6][7], int column){
    for(int row = 5; row >= 0; row--){
        if(board[row][column] == 0){
            return row;
        }
    }
    return -1;
}
//requires: a 2D board of 6 rows and 7 columns and a +ve int in the range [0-6] corresponding to the column entered by the user. And a +ve int [1-2]
//          corresponding to the color of the player.
//effects: returns 1 after a successful update of the board ( intended column is not full), 0 otherwise. 
int updateBoard(int board[6][7],int column, int color){
    if(!checkColumnFull(board, column)){
        int row = getFirstEmptyRow(board, column);
        board[row][column] = color;
        return 1;
        
    }
    return 0;

    
}
//requires: a 2D board of 6 rows and 7 columns 
//effects: returns 1 if the player connected 4 entries successfully, 0 otherwise 
int winningMove(int board[6][7]){
    if(checkHorizontally(board) || checkVertically(board) || checkDiagonally(board)){
        return 1;
    }else{
        return 0;
    }
}
int main(){
    int board[6][7]= {
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0}
                  };

    printf("player 1: Enter your name (single word, no spaces): ");
    scanf("%s",player1);
    printf("player 2: Enter your name (single word, no spaces): ");
    scanf("%s",player2);

    char* playerHavingRed = pickPlayer();
    char* playerHavingYellow = (strcmp(playerHavingRed,player1) == 0) ? player2 : player1;
    printf("%s you'll take the red color, \n%s you'll take the yellow color\n",playerHavingRed, playerHavingYellow);
    printBoard(board);

    while(!isBoardFull(board)){
        printf("\n");
        printf("%s select a column number (between 0 and 6): ", playerHavingRed);
        start = clock();
        scanf("%d", &entry);
        end = clock();
        while (entry < 0 || entry > 6){
            printf("\nThe selected column is out of range!\n");
            printBoard(board);
            printf("Enter another valid column number: ");
            start=clock();
            scanf("%d", &entry);
            end = clock();
            timeTakenByPlayerHavingRed+=(long double)(end-start)/CLOCKS_PER_SEC;
        }
        int isBoardUpdated1= updateBoard(board,entry, 1);
        while(!isBoardUpdated1){
            printf("\nThe selected column is full!\n");
            printBoard(board);
            printf("Enter another valid column number: ");
            start=clock();
            scanf("%d", &entry);
            end = clock();
            timeTakenByPlayerHavingRed+=(long double)(end-start)/CLOCKS_PER_SEC;
            isBoardUpdated1=updateBoard(board,entry,1);
        }
        printBoard(board);
        if(winningMove(board)){
            strcpy(winner, playerHavingRed);
            printf("Congrats %s, you\'re the winner!",playerHavingRed);
            return 0;
        }
        timeTakenByPlayerHavingRed += (long double)(end-start)/CLOCKS_PER_SEC;
        printf("%s select a column number (between 0 and 6): ", playerHavingYellow);
        start = clock();
        scanf("%d", &entry);
        end = clock();
        while (entry < 0 || entry > 6){
            printf("\nThe selected column is out of range!\n");
            printBoard(board);
            printf("Enter another valid column number: ");
            start=clock();
            scanf("%d", &entry);
            end = clock();
            timeTakenByPlayerHavingYellow+=(long double)(end-start)/CLOCKS_PER_SEC;
        }
        int isBoardUpdated2= updateBoard(board,entry, 2);
        while(!isBoardUpdated2){
            printf("\nThe selected column is full!\n");
            printBoard(board);
            printf("Enter another valid column number: ");
            start=clock();
            scanf("%d", &entry);
            end = clock();
            timeTakenByPlayerHavingYellow+=(long double)(end-start)/CLOCKS_PER_SEC;
            isBoardUpdated2=updateBoard(board,entry,2);
        }
        printBoard(board);
        if(winningMove(board)){
            strcpy(winner, playerHavingYellow);
            printf("Congrats %s, you\'re the winner!",playerHavingYellow);
            return 0;
        }
        timeTakenByPlayerHavingYellow += (long double)(end-start)/CLOCKS_PER_SEC;
    }
    if(isBoardFull(board)){
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
