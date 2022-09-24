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
