// SNAIL EATER
    // Player is 'x'
    // Avoid the ghosts (G) and eat the snails (@)
    // Eat all snails (@) to proceed to next level
    // Player can wrap around the border of the gameboard to the other side. Ghosts can not.

#include <header.h>

// Define Extern Globals (declared in header.h)
const char BLANK = '-';
const char PLAYER = 'x';
const char BLOCK = '#';
const char SNAIL = '@';
const char GHOST = 'G';
char board[HEIGHT][WIDTH];
int p_x, p_y, snail_count;

int main(void)
{

    // ~~~~~ SET UP ~~~~~

    // Set Level 1 snail_count and ghost_num (snail_count is global)
    uint16_t starting_amt = 1;
    snail_count = starting_amt;
    uint16_t ghost_num = starting_amt, level = 1;

    start_screen();
    char *difficulty = choose_difficulty();
    countdown(level);

    // ~~~~~ ~~~~~ ~~~~~ ~~~~~ BEGIN GAME ~~~~~ ~~~~~ ~~~~~ ~~~~~
    while (true)
    {
        // Variables
        coordinates ghost_pos[ghost_num];
        char result = 0;

        // Setup
        reset_board();
        spawn_player();
        spawn_blocks(level+2);
        spawn_ghosts(ghost_num, ghost_pos);
        spawn_snails(snail_count);

        // ---------- START LEVEL ----------
        while (true)
        {
            print_board(level);

            // -- PLAYER MOVE --
            result = player_move();

            // Check if player ate all the snails, ran into ghost or quit
            if (snail_count == 0 || result == 'g' || result == 'q') {
                break;
            }

            // -- GHOST MOVE --
            if (strcasecmp(difficulty, "easy") == 0) {
                result = ghost_move_easy(ghost_num, ghost_pos);
            }
            else if (strcasecmp(difficulty, "hard") == 0) {
                result = ghost_move_hard(ghost_num, ghost_pos);
            }
            else {
                result = ghost_move_impossible(ghost_num, ghost_pos);
            }

            // Check if player eaten by ghost
            if (result == 'g') {
                break;
            }
        }

        // ~~~~~~~ LEVEL END SCREEN ~~~~~~~
        print_board(0);
        if (result == 'q') {
            break;
        }
        else if (snail_count == 0) {
            printf("\n\n\n\t   YOU PASSED LEVEL %i!!!\n\n", level);
            level++;
            snail_count = starting_amt + level-1;
            ghost_num = snail_count;
        }
        else if (result == 'g') {
            printf("\n\n\n\t\t YOU LOSE!!\n\n\t\tREDO LEVEL %i\n", level);
            snail_count = starting_amt + level-1;
            ghost_num = snail_count;
        }

        // COUNTDOWN
        countdown(level);
    }

    // ~~~~~~~~~~~~~~~~~~ FINAL END SCREEN ~~~~~~~~~~~~~~~~~~
    printf("\n\n      Thanks for playing SNAIL EATER!!\n\n\t      ~~ GOODBYE!! ~~\n\n");
    print_ascii_art('s');
    print_ascii_art('g');

    // HIGHEST SCORE/RECORD SCORE
    uint16_t score = level-1;
    uint16_t all_time = display_highest_scores(difficulty);

    if (score > all_time) {
        printf("\n~~~ CONGRATULATIONS! YOU BEAT THE ALL TIME HIGH SCORE OF %i!!! ~~~\n\n", all_time);
    }
    else if (score == all_time) {
        printf("\n~~~ CONGRATULATIONS! YOU TIED THE ALL TIME HIGH SCORE OF %i!!! ~~~\n\n", all_time);
    }

    record_new_score(difficulty, score);

    // END
    free(difficulty);
    difficulty = NULL;


    return EXIT_SUCCESS;
}
