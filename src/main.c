// SNAIL EATER
    // Player is 'x'
    // Avoid the ghosts (G) and eat the snails (@)
    // Eat all snails (@) to proceed to next level
    // You can wrap around the border of the gameboard to the other side
// 10.3.22
// 10.4.22 - added border protection system for player and ghost. Added levels.
    // 10.4.22: snail_again_seek.c: 4:30PM Adding ghost AI to seek player
    // 10.31.22: When I compile using gcc or clang, it will not print chars 1 by 1 in my for loop in the start_screen(). It doesn't stop to sleep in every iteration of the loop.
            // Only make will compile it the way I want. I don't understand why.

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
    // ~~~~~ ~~~~~ ~~~~~ ~~~~~ BEGIN GAME ~~~~~ ~~~~~ ~~~~~ ~~~~~
    start_screen();

    // Set Level 1 snail_count and ghost_num (snail_count is global)
    uint16_t starting_amt = 3;
    snail_count = starting_amt;
    uint16_t ghost_num = starting_amt, level = 1;
    while (true)
    {
        // Variables
        coordinates ghost_pos[ghost_num];
        char result = 0;

        // Setup
        reset_board();
        spawn_player();
        spawn_blocks(3);
        spawn_ghosts(ghost_num, ghost_pos);
        spawn_snails(snail_count);

        // ---------- START LEVEL ----------
        while (true)
        {
            print_board(level);

            result = player_move();
            if (snail_count == 0 || result == 'g' || result == 'q')
            {
                break;
            }

            result = ghost_move(ghost_num, ghost_pos);
            if (result == 'g')
            {
                break;
            }
        }

        // ~~~~~~~~~~~~~~~~~~ END SCREEN ~~~~~~~~~~~~~~~~~~
        print_board(0);
        if (result == 'q')
        {
            printf("\n\n\t You QUIT. Good seein' ya!!\n\n");
            // check_high_score(level-1);
            break;
        }
        else if (snail_count == 0)
        {
            printf("\n\n\n\t   YOU PASSED LEVEL %i!!!\n\n\t      Next Level in:\n", level);
            level++;
            snail_count = starting_amt + level-1;
            ghost_num = snail_count;
        }
        else if (result == 'g')
        {
            printf("\n\n\n\t\t YOU LOSE!!\n\n\t\tREDO LEVEL %i\n", level);
            snail_count = starting_amt + level-1;
            ghost_num = snail_count;
        }

        // COUNTDOWN
        for (int8_t i = 3; i >=0; i--) {
            if (i > 0) {printf("\n\n\t\t   ~ %i ~", i);}
            else {printf("\n\n\t         ~  GO! ~");}
            usleep(1250000);
        }
    }

    return 0;
}
