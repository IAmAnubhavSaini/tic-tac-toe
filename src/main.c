/* Program: Tic Tac Toe
* Author: megatr0nz, github.com/IAmAnubhavSaini
*/

#include <stdio.h>
typedef enum game_results GameResults;
enum game_results{
  GR_Viable =  1,
    GR_O_Won =   2,
    GR_X_Won =   4,
    GR_Draw =    8
};

char board[3][3] = {' '};

void draw_grid(void);
void get_input_O(int *, int *);
void get_input_X(int *, int *);
int check_input(int, int, int);
GameResults examine_grid(void);//return 1 if game is still viable: if game is won by O, returns 2, if by X, returns 3, if draw returns 4 : Uses GameResults 

int main( int argc, char *argv[] )
{
  int column, row;
  GameResults result;
  draw_grid();
  while((result = examine_grid())&& result == GR_Viable){
    get_input_O(&column, &row);
    get_input_X(&column, &row);
  }
  switch(result){
  case GR_O_Won :
    printf("\nO won. Congragulations."); break;
  case GR_X_Won:
    printf("\nX won. Congragulations."); break;
  case GR_Draw:
    printf("\nGame ended at draw. Thanks for playing."); break;
  default :
    printf("\n Don't know why this message ran. Report Error : Invalid Game Result Case."); break;
  }

  return 0;
}

void draw_grid(void)
{
  // Print out the grid
  printf("   1   2   3    \n");
  printf("1  %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
  printf("  ---+---+---   \n");
  printf("2  %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
  printf("  ---+---+---   \n");
  printf("3  %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);

}

void get_input_O(int *column_p, int *row_p)
{
  // Get input for player 1
  printf("Player 1 please enter the row and column,\nwhere you wish to place your mark (O): ");
  scanf("%d %d", column_p, row_p);

  while( check_input((*column_p), (*row_p), 1) < 0 ) { // while movement is not permitted.
    printf("Please select a valid column, row: ");
    scanf("%d %d", column_p, row_p);
  }

  draw_grid();
}

void get_input_X(int *column_p, int *row_p)
{
  // Get input for player 2
  printf("Player 2 please enter the row and column,\nwhere you wish to place your mark (X): ");
  scanf("%d %d", column_p, row_p);

  while( check_input((*column_p), (*row_p), 2) < 0 ) { // while movement is not permitted.
    printf("Please select a valid column, row: ");
    scanf("%d %d", column_p, row_p);
  }

  draw_grid();
}

int check_input(int column, int row, int playerId)
{

  if( !((column >= 1 && column <= 3) && ( row >= 1 && row <= 3)) ) {
    printf("Error: Wrong boundaries!\n");
    return -1; // Wrong boundaries
  }

  column -= 1;
  row    -= 1;
  if( board[column][row] != 'X' || board[column][row] != 'O' ) { // Move is allowed
    board[column][row] = (playerId == 1) ? 'O' : 'X';
  } else {
    printf("Error: There is already a mark there!\n");
    return -2; // Error. There is already a mark in that position
  }
  return 1; // Successfull
}
GameResults examine_grid(){
  int i, j;
  i = 0; j = 3;
  int flag_playable = 0; //not playable = 0
  //check rows
  for(i =0; i < j; i++){
    if(board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O'){
      return GR_O_Won;
    }

    //check cols
    if(board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X'){
      return GR_X_Won;
    }
  }
  //check diagonal
  if(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O' ){
    return GR_O_Won;
  }
  if(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X' ) {
    return GR_X_Won;
  }

  //check if game is still playable:
  for(i = 0 ; i < 3; i++){
    for(j = 0; j<3; j++){
      if(board[i][j] ==' '){
        return GR_Viable;
      }
    }
  }
  return GR_Draw;
}