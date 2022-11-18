#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
char player[30];
char* computer = "COMPUTER";
char winner[30];
int entry;
long double timeTakenByPlayerHavingRed = 0;
long double timeTakenByPlayerHavingYellow = 0;
clock_t start;
clock_t end;
int window_size = 4;
const int PLAYER = 1; 
int COMPUTER = 2;
int NUM_ROW = 6;
int NUM_COL = 7;
int turns = 0;
int MAX_DEPTH = 6;
int gameOver = 0;
int currentPlayer= 1;

//requires: a 2D board of 6 rows and 7 columns 
//effects: prints the board
void printBoard_Ultrahackers(int** board){
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
//effects: returns a random float number betaween 0 and 1

int fairCoin_Ultrahacker(){
    srand(time(NULL));
    return rand()%10;
}
//requires: nothing
//effects: returns the name of the player having the red color
//if the value returned by fairCoin_Ultrahacker() is [0-4], player1 will be red. Otherwise, player2 will take the red color.
char* pickPlayer_Ultrahackers(){
    int randomNumber = fairCoin_Ultrahacker();
    if (0 <= randomNumber && randomNumber <= 4){
        return player;
    }
    else{
        return computer;
    }
}
//requires: takes the updated board
//effects: returns 1 if there is a horizontal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkHorizontally_Ultrahackers(int** board, int player){
    for (int row=5; row>=0; row--){ 
        for (int column=3; column>=0; column--){ 
            if(board[row][column] != 0 && board[row][column]==player && board[row][column] == board[row][column+1] && board[row][column] == board[row][column+2] && board[row][column] == board[row][column+3]){
                return 1;
        }
    }
    }
    return 0;

}
//requires: takes the updated board
//effects: returns 1 if there is a vertical line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkVertically_Ultrahackers(int**board, int player){
    for (int column=0; column<=6; column++){
        for (int row=2; row>=0; row--){
            if(board[row][column] != 0 && board[row][column]==player && board[row][column] == board[row+1][column] && board[row][column] == board[row+2][column] && board[row][column] == board[row+3][column]){
                return 1;
        }
    }
    }
    return 0;

}
//requires: takes the updated board
//effects: returns 1 if there is a diagonal line of 4 consecutive pieces having the same color; otherwise, returns 0.
int checkDiagonally_Ultrahackers(int** board, int player){
    for(int row=0;row<=2;row++){
        for(int column=0; column<=3;column++ ){
            if(board[row][column] != 0 && board[row][column]==player && board[row][column]==board[row+1][column+1] && board[row][column] ==board[row+2][column+2] && board[row][column]==board[row+3][column+3]){
                return 1;
            }
            
        }
    }
    for(int row=0;row<=2;row++){
        for(int column=6; column>=3;column--){
            if(board[row][column] != 0 && board[row][column]==player && board[row][column]==board[row+1][column-1] && board[row][column] ==board[row+2][column-2] && board[row][column]==board[row+3][column-3]){
                return 1;
            }
        }
    }
    return 0;
}

//requires: A 2D board of 6 rows and 7 columns and a +ve int in the range of [0-6] representing the column selectd by the player 
//effects: returns 1 if the corresponding column is full, and 0 otherwise. 
int checkColumnFull_Ultrahackers(int** board ,int col){
    if (board[0][col]){
        return 1;
    }
    return 0;
} 
//requires: The updated board
//effects: returns 1 if the board is full; 0 otherwise.
int isBoardFull_Ultrahackers(int** board){
    int counter = 0;
    for(int column=0; column <= 6; column++){
        if(checkColumnFull_Ultrahackers(board,column)) counter++; }
    if(counter==7) return 1;
    return 0;
}

//requires: a 2D board of 6 rows and 7 columns and a +ve int in the range [0-6] representing the selected column by the user.
//effects: returns the number of the row corresponding to the first empty cell (from bottom to top)
//         of the entered column; -1 if the column is full.
int getFirstEmptyRow_Ultrahackers(int** board, int column){
    for(int row = 5; row >= 0; row--){
        if(board[row][column] == 0){
            return row;
        }
    }
    return -1;
}

// requires: nothing.
// effects: prompt the user to input a column index and returns it.
int userMove_Ultrahackers() {
	int move;
	printf("Enter a column: ");
	scanf("%d",&move);
	if(move > 6 || move < 0 || (sizeof(move) != sizeof(int))){
		printf("Invalid Input! Enter a valid column value!\n");
		return userMove_Ultrahackers();
	}
	return move;
}

//requires: a 2D board of 6 rows and 7 columns and a +ve int in the range [0-6] corresponding to the column entered by the user. And a +ve int [1-2]
//          corresponding to the color of the player.
//effects: updates the board with given color at the given column if not full
void updateBoard_Ultrahackers(int** board,int column, int color){
    if(!checkColumnFull_Ultrahackers(board, column)){
        int row = getFirstEmptyRow_Ultrahackers(board, column);
        board[row][column] = color;
        return;
	}
    else{
		printf("The column %d is full!\n", column);
		int column;
		column = userMove_Ultrahackers();
		updateBoard_Ultrahackers(board, column, color);
	}
}

//requires: a 2D board of 6 rows and 7 columns 
//effects: returns 1 if the player connected 4 entries successfully, 0 otherwise 
int winningMove_Ultrahackers(int** board, int player){
    if(checkHorizontally_Ultrahackers(board, player) || checkVertically_Ultrahackers(board, player) || checkDiagonally_Ultrahackers(board, player)){
        return 1;
    }else{
        return 0;
    }
}

// requires: a 2D board of 6 rows and 7 columns.
// effects: returns another 2D board that is a copy of the argument.
int** copyBoard_Ultrahackers(int** board) {
	int** newBoard;
    newBoard = (int**)malloc(sizeof(int*) * 6);
    for (int i = 0; i < 6; i++){
        newBoard[i] = (int*)malloc(sizeof(int)* 7);
    }
	for (unsigned int r = 0; r < NUM_ROW; r++) {
		for (unsigned int c = 0; c < NUM_COL; c++) {
			newBoard[r][c] = board[r][c];
		}
	}
	return newBoard;
}

// requires: an integer g representing the point in favor of the playor,
// 			 an integer b representing the point opposing the playor,
// 			 an integer z representing the empty point.
// effects: returns the score of a successive set of 4 points.
int heuristic_Ultrahackers(unsigned int goodPoints, unsigned int opposingPoints, unsigned int neutralPoints){
	int score = 0;
	if (goodPoints == 4) { score += 500001; }
	else if (goodPoints == 3 && neutralPoints == 1) { score += 5000; }
	else if (goodPoints == 2 && neutralPoints == 2) { score += 500; }
	else if (opposingPoints == 2 && neutralPoints == 2) { score -= 501; }
	else if (opposingPoints == 3 && neutralPoints == 1) { score -= 5001; }
	else if (opposingPoints == 4) { score -= 500000; }
	return score;
}

// requires: an array of positions and an integer representing the player.
// effects: returns the number of in-favor points, opposing points and neutral points.
int windowScore_Ultrahackers(int *target, unsigned int player) {
	unsigned int goodPoints = 0;
	unsigned int opposingPoints = 0;
	unsigned int neutralPoints = 0;
    
	for (unsigned int i = 0; i < window_size; i++){
		goodPoints += (target[i] == player) ? 1 : 0;
		opposingPoints += (target[i] == PLAYER || target[i] == COMPUTER) ? 1 : 0;
		neutralPoints += (target[i] == 0) ? 1 : 0;
	}
	opposingPoints -= goodPoints;
	return heuristic_Ultrahackers(goodPoints, opposingPoints, neutralPoints);
}

// requires: a 2D board of 6 rows and 7 columns and an integer representing the player.
// effects: returns the total score of all possible windows in the board.
int boardScore_Ultrahackers(int** board, unsigned int player) {
	int score = 0;
    int NUM_ROW = 6; 
    int NUM_COL = 7;
    int rs[7];
    int cs[6];
    int window[4];


	for (unsigned int r = 0; r < 6; r++) {
		for (unsigned int c = 0; c < NUM_COL; c++) {
			rs[c] = board[r][c];
		}
		for (unsigned int c = 0; c < NUM_COL - 3; c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = rs[c + i];
			}
			score += windowScore_Ultrahackers(window, player);
		}
	}


	for (unsigned int c = 0; c < NUM_COL; c++) {
		for (unsigned int r = 0; r < 6; r++) {
			cs[r] = board[r][c];
		}
		for (unsigned int r = 0; r < 3; r++) {
			for (int i = 0; i < 4; i++) {
				window[i] = cs[r + i];
			}
			score += windowScore_Ultrahackers(window, player);
		}
	}


	for (unsigned int r = 0; r < 3; r++) {
		for (unsigned int c = 0; c < NUM_COL; c++) {
			rs[c] = board[r][c];
		}
		for (unsigned int c = 0; c < NUM_COL - 3; c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r + i][c + i];
			}
			score += windowScore_Ultrahackers(window, player);
		}
	}
	for (unsigned int r = 0; r < 3; r++) {
		for (unsigned int c = 0; c < NUM_COL; c++) {
			rs[c] = board[r][c];
		}
		for (unsigned int c = 0; c < NUM_COL - 3; c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r + 3 - i][c + i];
			}
			score += windowScore_Ultrahackers(window, player);
		}
	}
	return score;
}

// requires: a 2D board of 6 rows and 7 columns, the depth of the board, the alpha integer, 
// 				the betaa integer, an integer representing the player.
// effects: returns an array of 2 values in which the 1st is the minimum score and the 2nd 
// 				is the maximum score.
int* miniMax_Ultrahackers(int** board, unsigned int depth, int alpha, int beta, unsigned int player) {

	if (depth == 0 || depth >= (NUM_COL * NUM_ROW) - turns) {
        int *result = (int*) malloc(sizeof(int)*2);
        result [0] = boardScore_Ultrahackers(board, COMPUTER);
        result [1] = -1;
		return result; 
	}
	if (player == COMPUTER){
        int* moveSoFar = (int*) malloc(sizeof(int)*2);
		moveSoFar[0] = INT_MIN;
        moveSoFar[1] = -1;
		if(winningMove_Ultrahackers(board, PLAYER)) {
			return moveSoFar;
		}
		for (unsigned int c = 0; c < NUM_COL; c++){
			if(board[0][c] == 0){
				int **newBoard = copyBoard_Ultrahackers(board);
				updateBoard_Ultrahackers(newBoard, c, player); 
				int * arr = miniMax_Ultrahackers(newBoard, depth - 1, alpha, beta, PLAYER); 
				int score = arr[0];
				if (score > moveSoFar[0]) {
					moveSoFar[0] = score;
                    moveSoFar[1] = c;
				}
				alpha = max(alpha, moveSoFar[0]);
				if (alpha >= beta) { break; } 
			}
		}
		return moveSoFar; 
	}
	else {
		int* moveSoFar = (int*)malloc(sizeof(int)*2);
        moveSoFar[0] = INT_MAX;
        moveSoFar[1] = -1; 
		if (winningMove_Ultrahackers(board, COMPUTER)) {
			return moveSoFar; 
		}
		for (unsigned int c = 0; c < NUM_COL; c++) {
			if (board[0][c] == 0) {
				int** newBoard = copyBoard_Ultrahackers(board);
				updateBoard_Ultrahackers(newBoard, c, player);
				int * arr = miniMax_Ultrahackers(newBoard, depth - 1, alpha, beta, COMPUTER);
				int score = arr[0];
				if (score < moveSoFar[0]) {
					moveSoFar[0] = score;
                    moveSoFar[1] = c;
				}
				beta = min(beta, moveSoFar[0]);
				if (alpha >= beta) { break; }
			}
		}
		return moveSoFar;
	}
}

// requires: a 2D board of 6 rows and 7 columns.
// effects: returns the index of the column at which the computer wishes to make the move.
int make_move_Ultrahackers(int** board) {
	printf("Computer is thinking about a move...\n" );
	int move = miniMax_Ultrahackers(board, MAX_DEPTH, 0 - INT_MAX, INT_MAX, COMPUTER)[1];
	return move;
}

// requires: nothing.
// effects: runs the whole game.
void playGame_Ultrahackers(){
    int** board= (int**) malloc(sizeof(int*)*6);
    for (int i = 0; i < 7; i++){
        board[i] = (int*)malloc(sizeof(int) *7);
    }
    for(int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            board[i][j] = 0;
        }
    }

	printf("Enter your name: ");
    scanf("%s", &player);

	char* playerHavingRed = pickPlayer_Ultrahackers();
	char* playerHavingYellow = (strcmp(playerHavingRed,player) == 0) ? computer : player;
	printf("%s you'll take the red color, \n%s you'll take the yellow color\n",playerHavingRed, playerHavingYellow);

	printBoard_Ultrahackers(board); 
	while (!gameOver) {
		if (strcmp(playerHavingRed, computer) == 0){
			currentPlayer = COMPUTER;
			start = clock();
			updateBoard_Ultrahackers(board, make_move_Ultrahackers(board), COMPUTER);
			end = clock();
			timeTakenByPlayerHavingRed+=(long double)(end-start)/CLOCKS_PER_SEC;
			printBoard_Ultrahackers(board);
		}
		else if (strcmp(playerHavingRed, player) == 0) {
			currentPlayer = PLAYER;
			start = clock();
			updateBoard_Ultrahackers(board, userMove_Ultrahackers(), PLAYER);
			end = clock();
			timeTakenByPlayerHavingRed+=(long double)(end-start)/CLOCKS_PER_SEC;
			printBoard_Ultrahackers(board);
		}
		else if (turns == NUM_ROW * NUM_COL) { 
			gameOver = 1;
		}

		if(winningMove_Ultrahackers(board, COMPUTER)){
			printf("Hard luck! Computer wins.");
			return;
		}
		else if(winningMove_Ultrahackers(board, PLAYER)){
			printf("Congrats %s, you\'re the winner!",player);
			return;
		}

		if (strcmp(playerHavingYellow, computer) == 0) {
			currentPlayer = COMPUTER;
			start = clock();
			updateBoard_Ultrahackers(board, make_move_Ultrahackers(board), COMPUTER);
			end = clock();
			timeTakenByPlayerHavingYellow+=(long double)(end-start)/CLOCKS_PER_SEC;
			printBoard_Ultrahackers(board);
		}
		else if (strcmp(playerHavingYellow, player) == 0) {
			currentPlayer = PLAYER;
			start = clock();
			updateBoard_Ultrahackers(board, userMove_Ultrahackers(), PLAYER);
			end = clock();
			timeTakenByPlayerHavingYellow+=(long double)(end-start)/CLOCKS_PER_SEC;
			printBoard_Ultrahackers(board);
		}
		else if (turns == NUM_ROW * NUM_COL) { 
			gameOver = 1;
		}
		gameOver = winningMove_Ultrahackers(board, currentPlayer);
		currentPlayer = (currentPlayer == COMPUTER) ? PLAYER : COMPUTER; 
		turns++; 
		printf("\n");

		if(winningMove_Ultrahackers(board, COMPUTER)){
			printf("Hard luck! Computer wins.");
			return;
		}
		else if(winningMove_Ultrahackers(board, PLAYER)){
			printf("Congrats %s, you\'re the winner!",player);
			return;
		}
	}

	if(isBoardFull_Ultrahackers(board)){
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
}

int main(){
    playGame_Ultrahackers();
    return 0;
}