/* Program:      Tic Tac Toe
 * Author:       xmpf
 * Contributors: xmpf & IAmAnubhavSaini
 * License:      MIT
 */


// Libraries
#include <stdio.h>

// In-line Functions
static inline void
clear_buffer( FILE *fp )
{
    int cfp;
    while( (cfp = fgetc(fp)) != EOF && cfp != '\n' )
        ;
}

typedef enum gameResults GameResults;
enum gameResults {
    
    GR_PLAYABLE  = 0,
    GR_U1_Won    = 1,
    GR_U2_Won    = 2,
    GR_TIE       = 3,
    
};

// Global variables
char array[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};
char user1_symbol;
char user2_symbol;

// Function Prototypes
void init_board(void);
void setup_game(void);
void draw_grid(void);
void getInput_U1(int *, int *);
void getInput_U2(int *, int *);
int checkInput(int, int, int);
GameResults winnerExists(void);
void displayWinner(GameResults);

// Main function
int main( int argc, char *argv[] )
{
    // Variables of function main.
    char reply = ' ';
    int tail = 9; // 3x3 grid
    int column, row;
    GameResults results = GR_PLAYABLE;

    do {

        init_board(); // Initialize array
        setup_game(); // sets up user game preferences. can be called from init_board. 
        draw_grid();  // Draw initial grid
        
        results = GR_PLAYABLE;
        tail    = 9;

        while( (results == GR_PLAYABLE) && tail > 0 ) {
        
            if( tail & 1 ) {
                getInput_U1(&column, &row); // Get player 1 input
            } else {
                getInput_U2(&column, &row); // Get player 2 input
            }

            tail -= 1;
            results = winnerExists();
        }

    displayWinner( results );
        
    printf("\n\nDo you want to play again? (Y/N): ");
    scanf(" %c", &reply);

    } while( (reply == 'y') || (reply == 'Y') );

    return 0;
}

// Functions
void init_board(void)
{
    /*******************************
     * Function to initialize array
     * useful when program will ask
     * the user if he wants to play
     * again the tic-tac-toe game..
     *******************************/
    int i, j;
    for( i = 0; i < 3; i++ )
        for( j = 0; j < 3; j++ )
            array[i][j] = ' ';
}
void setup_game(void){
  printf("\nPlease enter 1 character symbol for user 1 and user 2 in consecutive space-less manner like @# or $^ or !* etc.");
  user1_symbol = getchar();
  user2_symbol = getchar();
}
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

void getInput_U1(int *column_p, int *row_p)
{
    // Get input for player 1
    printf("Player 1 please enter the row and column,\nwhere you wish to place your mark (%c): ", user1_symbol);
    scanf("%d %d", column_p, row_p);
    clear_buffer( stdin );

    while( checkInput((*column_p), (*row_p), 1) < 0 ) { // while movement is not permitted.
        printf("Please select a valid row, column: ");
        scanf("%d %d", column_p, row_p);
        clear_buffer( stdin );
    }

    draw_grid();
}

void getInput_U2(int *column_p, int *row_p)
{
    // Get input for player 2
    printf("Player 2 please enter the row and column,\nwhere you wish to place your mark (%c): ", user2_symbol);
    scanf("%d %d", column_p, row_p);
    
    clear_buffer( stdin );

    while( checkInput((*column_p), (*row_p), 2) < 0 ) { // while movement is not permitted.
        printf("Please select a valid row, column: ");
        scanf("%d %d", column_p, row_p);
        clear_buffer( stdin );
    }

    draw_grid();
}

int checkInput(int column, int row, int playerId)
{
    /* ERRORS:
     *          (-1) -> Wrong boundaries.
     *          (-2) -> Movement not allowed.
     */

    if( !((column >= 1 && column <= 3) && ( row >= 1 && row <= 3)) ) {
        printf("Error: Wrong boundaries!\n");
        return -1; // Wrong boundaries
    }

    column -= 1;
    row    -= 1;
    if( array[column][row] == ' ' ) { // Move is allowed
        array[column][row] = (playerId == 1) ? user1_symbol : user2_symbol;
    } else {
        printf("Error: There is already a mark there!\n");
        return -2; // Error. There is already a mark in that position
    }
    return 1; // Successfull
}

GameResults winnerExists(void)
{
    // Variables of function winnerExists.
    int i, j;

    for( i = 0; i < 3; i++ ) {
        // Check horizontal for player 1
        if( (array[i][0] == user1_symbol ) && (array[i][1] == user1_symbol) && (array[i][2] == user1_symbol) )
            return GR_U1_Won;
        // Check horizontal for player 2
        else if( (array[i][0] == user2_symbol) && (array[i][1] == user2_symbol) && (array[i][2] == user2_symbol) )
            return GR_U2_Won;
            
        // Check vertical for player 1
        if( (array[0][i] == user1_symbol) && (array[1][i] == user1_symbol) && (array[2][i] == user1_symbol) )
            return GR_U1_Won;
        // Check vertical for player 2
        else if( (array[0][i] == user2_symbol) && (array[1][i] == user2_symbol) && (array[2][i] == user2_symbol) )
            return GR_U2_Won;
    }

    // Diagonal check for player 1
    if( (array[0][0] == user1_symbol) && (array[1][1] == user1_symbol) && (array[2][2] == user1_symbol) ) {
            return GR_U1_Won;
    }
    else if( (array[0][2] == user1_symbol) && (array[1][1] == user1_symbol) && (array[2][0] == user1_symbol) ) {
            return GR_U1_Won;
    }

    // Diagonal check for player 2
    if( (array[0][0] == user2_symbol) && (array[1][1] == user2_symbol) && (array[2][2] == user2_symbol) ) {
        return GR_U2_Won;
    }
    else if( (array[0][2] == user2_symbol) && (array[1][1] == user2_symbol) && (array[2][0] == user2_symbol) ) {
        return GR_U2_Won;
    }

    for( i = 0; i < 3; i++ ) {
        for( j = 0; j < 3; j++ ) {
            if( array[i][j] == ' ' )
                return GR_PLAYABLE; // No winner yet.
        }
    }

    // This is a tie. Nobody wins.
    return GR_TIE;
}

void displayWinner( GameResults results )
{
    switch( results ) {
        case GR_U1_Won:
            printf("Player 1 is the winner!\n");
            break;
        
        case GR_U2_Won:
            printf("Player 2 is the winner!\n");
            break;

        case GR_TIE:
            printf("Nobody wins!\n");
            break;

        default:
            break;
    }  
}
