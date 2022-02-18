#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define PLAYER_NAME_SIZE 8
/* DATA STRUCTURES */
typedef enum game_results GameResults;
enum game_results {
    GR_Viable = 1,
    GR_P1_Won = 2,
    GR_P2_Won = 4,
    GR_Draw = 8
};
typedef struct player_info Player;
struct player_info {
    char *Name;
    char Symbol;
    char *Id;
};

/* GLOBALS */
char board[3][3];
Player *players[2];

/*DEFINITIONS*/
void init_board(void);

void setup_game(void);

void draw_board(void);

void get_player1_input(int *, int *);

void get_player2_input(int *, int *);

int examine_input(int, int, int);

GameResults examine_board(void);

void publish_results(GameResults result);

void clear_input_stream(FILE *stream);

char *generate_random_id(int size) {
/* Read logic at
 * http://stackoverflow.com/questions/2999075/generate-a-random-number-within-range/2999130#2999130
 * OR
 * we could have used:
 * #include <time.h>
 * #include <stdlib.h>
 * srand(time(NULL));
 * int r = rand();
 * FROM
 * http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
 *
 */
    char *id = (char *) malloc(sizeof(char) * (size + 1));
    char *valid_chars = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_-";
    int i = 0;
    int limit = 63; //validchars count is 64, max index in 63
    int divisor = RAND_MAX / (limit + 1);
    int index = 0;

    for (i = 0; i < size; i++) {
        do {
            index = rand() / divisor;
        } while (index > limit);

        id[i] = valid_chars[index];
    }
    id[i] = '\0';
    return id;
}


void initiate_randomness(void) {
#ifndef INITIATED_RANDOMNESS
    srand(time(NULL));
#define INITIATED_RANDOMNESS
#endif
}

int generate_random_number(void) {
    initiate_randomness();
    int r = rand();
    return r;
}

int generate_limited_random_number(int limit) {
    int divisor = RAND_MAX / (limit + 1);
    int number = 0;
    initiate_randomness();
    do {
        number = rand() / divisor;
    } while (number > limit);
    return number;
}


/*DECLARATIONS*/
int main(int argc, char *argv[]) {
    int col, row;
    int total_chances = 9;
    char play_again = 'Y';
    GameResults result;
    do {
        init_board();
        setup_game();
        draw_board();
        while (((result = examine_board()) == GR_Viable) && total_chances-- > 0) {
            if (total_chances & 1) {
                get_player2_input(&row, &col);
            } else {
                get_player1_input(&row, &col);
            }
        }
        //since game has stopped, check why?
        publish_results(result);

        printf("\nDo you want to play again? Y/y:> ");
        scanf("%c", &play_again);
    } while (play_again == 'Y' || play_again == 'y');


    return 0;
}

void init_board(void) {
    int i = 0, j = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void setup_game(void) {
    players[0] = (Player *) malloc(sizeof(Player));
    players[0]->Name = (char *) malloc(sizeof(char) * PLAYER_NAME_SIZE);
    players[1] = (Player *) malloc(sizeof(Player));
    players[1]->Name = (char *) malloc(sizeof(char) * PLAYER_NAME_SIZE);

    //BUG AVERSION
    //note: different sizes absolutely gurantees the different ids
    //generate and assign random ids to the players.
    players[0]->Id = generate_random_id(7);
    players[1]->Id = generate_random_id(8);

    //get their names and symbol
    //get player 1 info
    printf("\nPlayer 1 (id: %s), enter your name:> ", players[0]->Id);
    scanf("%s", players[0]->Name);
    clear_input_stream(stdin);
    printf("\nPlayer 1, enter your symbol:> ");
    scanf("%c", &players[0]->Symbol);
    clear_input_stream(stdin);
    //get player 2 info
    printf("\nPlayer 2 (id: %s), enter your name:> ", players[1]->Id);
    scanf("%s", players[1]->Name);
    clear_input_stream(stdin);
    printf("\nPlayer 2, enter your symbol:> ");
    scanf("%c", &players[1]->Symbol);
    clear_input_stream(stdin);

    //BUG AVERSION. issue 1.
    //check if both player have same symbol, make second player choose different one
    while (players[0]->Symbol == players[1]->Symbol) {
        printf("\nBoth players have same symbol. Player 2 choose another:> ");
        scanf("%c", &players[1]->Symbol);
        clear_input_stream(stdin);
    }
}

void draw_board(void) {
    // Print out the grid
    printf("   1   2   3    \n");
    printf("1  %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("  ---+---+---   \n");
    printf("2  %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("  ---+---+---   \n");
    printf("3  %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);

}

void get_player1_input(int *row, int *col) {
    // Get input for player 1
    printf("Player 1 please enter the row and col,\nwhere you wish to place your mark (%c):> ", players[0]->Symbol);
    scanf("%d %d", row, col);
    clear_input_stream(stdin);
    while (examine_input((*row), (*col), 1) < 0) { // while movement is not permitted.
        printf("Please select a valid row, col: ");
        scanf("%d %d", row, col);
        clear_input_stream(stdin);
    }

    draw_board();
}

void get_player2_input(int *row, int *col) {
    // Get input for player 2
    printf("Player 2 please enter the row and col,\nwhere you wish to place your mark (%c):> ", players[1]->Symbol);
    scanf("%d %d", row, col);
    clear_input_stream(stdin);
    while (examine_input((*row), (*col), 2) < 0) { // while movement is not permitted.
        printf("Please select a valid row, col: ");
        scanf("%d %d", row, col);
        clear_input_stream(stdin);
    }

    draw_board();
}

int examine_input(int row, int col, int playerId) {
    /* return values:
    * failure:-
    * -1 : wrong boundaries
    * -2 : position already filled
    *
    * success: 1
    */
    if (!((col >= 1 && col <= 3) && (row >= 1 && row <= 3))) {
        printf("Error: Wrong boundaries!\n");
        return -1; // error: wrong boundaries
    }

    col -= 1;
    row -= 1;
    if (board[row][col] != players[1]->Symbol && board[row][col] != players[0]->Symbol) { // Move is allowed
        board[row][col] = (playerId == 1) ? players[0]->Symbol : players[1]->Symbol;
    } else {
        printf("Error: There is already a mark there!\n");
        return -2; // error: position already filled
    }
    return 1; // Successfull
}

GameResults examine_board() {
    int i, j;
    i = 0;
    j = 3;
    int flag_playable = 0; //not playable = 0
    //check rows
    for (i = 0; i < j; i++) {
        if (board[i][0] == players[0]->Symbol && board[i][1] == players[0]->Symbol &&
            board[i][2] == players[0]->Symbol) {
            return GR_P1_Won;
        }
        if (board[i][0] == players[1]->Symbol && board[i][1] == players[1]->Symbol &&
            board[i][2] == players[1]->Symbol) {
            return GR_P2_Won;
        }
        //check cols
        if (board[0][i] == players[0]->Symbol && board[1][i] == players[0]->Symbol &&
            board[2][i] == players[0]->Symbol) {
            return GR_P1_Won;
        }
        if (board[0][i] == players[1]->Symbol && board[1][i] == players[1]->Symbol &&
            board[2][i] == players[1]->Symbol) {
            return GR_P2_Won;
        }
    }
    //check diagonal
    if (board[0][0] == players[0]->Symbol && board[1][1] == players[0]->Symbol && board[2][2] == players[0]->Symbol) {
        return GR_P1_Won;
    }
    if (board[0][0] == players[1]->Symbol && board[1][1] == players[1]->Symbol && board[2][2] == players[1]->Symbol) {
        return GR_P2_Won;
    }

    //check if game is still playable:
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return GR_Viable;
            }
        }
    }
    return GR_Draw;
}

void publish_results(GameResults result) {
    switch (result) {
        case GR_P1_Won :
            printf("\nPlayer 1 won. Congragulations %s.", players[0]->Name);
            break;
        case GR_P2_Won:
            printf("\nPlayer 2 won. Congragulations %s.", players[1]->Name);
            break;
        case GR_Draw:
            printf("\nGame ended at draw. Thanks for playing %s and %s.", players[0]->Name, players[1]->Name);
            break;
        default :
            printf("\n Don't know why this message ran. Report Error : Invalid Game Result Case.");
            break;
    }
}

void clear_input_stream(FILE *stream) {
    int input;
    while ((input = fgetc(stream)) != EOF && input != '\n');
}
