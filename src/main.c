/* Program: Tic Tac Toe
 * Author: megatr0nz
 * 
 */


// Libraries
#include <stdio.h>

// Global variables
char array[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

// Function Prototypes
void draw_grid(void);
void getInput_O(int *, int *);
void getInput_X(int *, int *);
int checkInput(int, int, int);


// Main function
int main( int argc, char *argv[] )
{
    // Variables of function main
    int column, row;
    
    draw_grid();
    getInput_O(&column, &row);
    getInput_X(&column, &row);

    return 0;
}

// Functions

void draw_grid(void)
{
    // Print out the grid
    printf("   1   2   3    \n");
    printf("1  %c | %c | %c \n", array[0][0], array[0][1], array[0][2]);
    printf("  ---+---+---   \n");
    printf("2  %c | %c | %c \n", array[1][0], array[1][1], array[1][2]);
    printf("  ---+---+---   \n");
    printf("3  %c | %c | %c \n", array[2][0], array[2][1], array[2][2]);

}

void getInput_O(int *column_p, int *row_p)
{
    // Get input for player 1
    printf("Player 1 please enter the row and column,\nwhere you wish to place your mark (O): ");
    scanf("%d %d", column_p, row_p);

    while( checkInput((*column_p), (*row_p), 1) < 0 ) { // while movement is not permitted.
        printf("Please select a valid column, row: ");
        scanf("%d %d", column_p, row_p);
    }

    draw_grid();
}

void getInput_X(int *column_p, int *row_p)
{
    // Get input for player 2
    printf("Player 2 please enter the row and column,\nwhere you wish to place your mark (X): ");
    scanf("%d %d", column_p, row_p);

    while( checkInput((*column_p), (*row_p), 2) < 0 ) { // while movement is not permitted.
        printf("Please select a valid column, row: ");
        scanf("%d %d", column_p, row_p);
    }
    
    draw_grid();
}

int checkInput(int column, int row, int playerId)
{

    if( !((column >= 1 && column <= 3) && ( row >= 1 && row <= 3)) ) {
        printf("Error: Wrong boundaries!\n");
        return -1; // Wrong boundaries
    }

    column -= 1;
    row    -= 1;
    if( array[column][row] == ' ' ) { // Move is allowed
        array[column][row] = (playerId == 1) ? 'O' : 'X';
    } else {
        printf("Error: There is already a mark there!\n");
        return -2; // Error. There is already a mark in that position
    }
    return 1; // Successfull
}
