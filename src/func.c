#include <header.h>

//          ~~~~~~~~~~~~~~~~~~~~
//          FUNCTION DEFINITIONS
//          ~~~~~~~~~~~~~~~~~~~~


//      ------- RESET BOARD --------
void reset_board(void)
{
    for (uint16_t i = 0; i < HEIGHT; i++)
    {
        for (uint16_t j = 0; j < WIDTH; j++)
        {
            board[i][j] = BLANK;
        }
    }
    return;
}

//      ------- PRINT BOARD --------
void print_board(uint16_t level)
{
    printf("\n\n\n\t     ~~~ SNAIL GAME ~~~\n");
    if (level > 0)
        printf("\t         - Level %i -\n\n", level);

    for (uint16_t i = 0; i < HEIGHT; i++)
    {
        printf("\t     ");
        for (uint16_t j = 0; j < WIDTH; j++)
        {
            printf("%c ", board[i][j]);
        }
        if (i == HEIGHT-1)
            printf("\t\t    Snails left: %i", snail_count);
        printf("\n");
    }
    return;
}

//       ------- SPAWN PLAYER --------
void spawn_player(void)
{
    // If 1st to spawn, don't have to check for anything I think, we'll see...
    srand(time(0));

    uint16_t x = rand() % HEIGHT;
    uint16_t y = rand() % WIDTH;

    board[x][y] = PLAYER;
    p_x = x;
    p_y = y;
}

//      ------- SPAWN BLOCKS --------
void spawn_blocks(uint16_t n)
{
    srand(time(0));

    for (uint16_t i = 0; i < n; i++)
    {
        // Keep randomly getting x and y points until free spaces are found
        while (true)
        {
            uint16_t x = rand() % HEIGHT;
            uint16_t y = rand() % WIDTH;

            // Every other block changes orientation
            if (i % 2 == 0)
            {
                if (board[x][y] == BLANK && y != WIDTH+1 && board[x][y+1] == BLANK) {
                    board[x][y] = BLOCK;
                    board[x][y+1] = BLOCK;
                    break;
                }
            }
            else
            {
                if (board[x][y] == BLANK && x != HEIGHT+1 && board[x+1][y] == BLANK) {
                    board[x][y] = BLOCK;
                    board[x+1][y] = BLOCK;
                    break;
                }
            }
        }
    }
    return;
}

//      ------- SPAWN SNAILS --------
void spawn_snails(uint16_t n)
{
    srand(time(0));
    for (uint16_t i = 0; i < n; i++)
    {
        while (true)
        {
            uint16_t x = rand() % HEIGHT;
            uint16_t y = rand() % WIDTH;

            if (board[x][y] == BLANK)
            {
                board[x][y] = SNAIL;
                break;
            }
        }

    }
}

//      ------- SPAWN GHOSTS --------
void spawn_ghosts(uint16_t n, coordinates ghost_pos[])
{
    srand(time(0));
    for (uint16_t i = 0; i < n; i++)
    {
        while (true)
        {
            uint16_t x = rand() % HEIGHT;
            uint16_t y = rand() % WIDTH;

            if (board[x][y] == BLANK)
            {
                board[x][y] = GHOST;
                // Keep track ghost position
                ghost_pos[i].x = x;
                ghost_pos[i].y = y;
                break;
            }
        }
    }
}

//      ------- INFINITE BUFFER -------
char *inf_buffer(char *prompt)
{
    printf("%s", prompt);

    // Scan until \n
    char *s = malloc(sizeof(char));
    if (s == NULL) {if_error(1);}

    // Scan char by char
    uint8_t i = 0;
    while (true)
    {
        int8_t scan_return = scanf("%c", &s[i]);
        if (scan_return != 1) {if_error(2);}

        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
        else {
            s = realloc(s, sizeof(char)*(i+2));
            if (s == NULL) {if_error(3);}
            i++;
        }
    }

    return s;
}

//      ------- PLAYER MOVE --------
char player_move(void)
{
    char *s = inf_buffer("Enter:\n");

    if (tolower(s[0]) == 'w')
    {
        // ----- UP -----
        // If statements check:
            // If player is not at border, checks p_x - 1 for blocks/ghosts. If p_x is at border, checks other end (wrap around) for blocks/ghosts
            // We need to divide the if statement into p_x > 0 and p_x == 0 or else it will eat blocks on the other side of the border
        // If not at top the border..........................................          ...OR if at the top border
        if ((p_x > 0 && (board[p_x-1][p_y] != BLOCK && board[p_x-1][p_y] != GHOST)) || (p_x == 0 && (board[HEIGHT-1][p_y] != BLOCK && board[HEIGHT-1][p_y] != GHOST)))
        {
            // Eat snail or not
            if ((p_x > 0 && board[p_x-1][p_y] == SNAIL) || (p_x == 0 && board[HEIGHT-1][p_y] == SNAIL)) snail_count--;

            // Move player
            board[p_x][p_y] = BLANK;
            if (p_x == 0)
            {
                board[HEIGHT-1][p_y] = PLAYER;
                p_x = HEIGHT-1;
            }
            else
            {
                board[p_x-1][p_y] = PLAYER;
                p_x--;
            }
        }
        else if ((p_x > 0 && board[p_x-1][p_y] == BLOCK) || (p_x == 0 && board[HEIGHT-1][p_y] == BLOCK))
        {
            // BLOCKED
            printf("\n\tYou ran into a BLOCK!!\n");
        }
        else if ((p_x > 0 && board[p_x-1][p_y] == GHOST) || (p_x == 0 && board[HEIGHT-1][p_y] == GHOST))
        {
            // RAN into GHOST
            board[p_x][p_y] = BLANK;
            printf("\n\tYou ran into a GHOST!!\n");
            free(s); s = NULL;
            return 'g';
        }
    }
    else if (tolower(s[0]) == 's')
    {
        // ----- DOWN -----
        // CHECK: BORDER AND Check blocks/ghost
        // If not at bottom the border                                                     OR if at the bottom border
        if ((p_x < HEIGHT-1 && (board[p_x+1][p_y] != BLOCK && board[p_x+1][p_y] != GHOST)) || (p_x == HEIGHT-1 && (board[0][p_y] != BLOCK && board[0][p_y] != GHOST)))
        {
            // Eat snail or not
            if ((p_x < HEIGHT-1 && board[p_x+1][p_y] == SNAIL) || (p_x == HEIGHT-1 && board[0][p_y] == SNAIL)) snail_count--;

            // Move player
            board[p_x][p_y] = BLANK;
            if (p_x == HEIGHT-1)
            {
                board[0][p_y] = PLAYER;
                p_x = 0;
            }
            else
            {
                board[p_x+1][p_y] = PLAYER;
                p_x++;
            }
        }
        else if ((p_x < HEIGHT-1 && board[p_x+1][p_y] == BLOCK) || (p_x == HEIGHT-1 && board[0][p_y] == BLOCK))
        {
            // BLOCKED
            printf("\n\tYou ran into a BLOCK!!\n");
        }
        else if ((p_x < HEIGHT-1 && board[p_x+1][p_y] == GHOST) || (p_x == HEIGHT-1 && board[0][p_y] == GHOST))
        {
            // RAN into GHOST
            board[p_x][p_y] = BLANK;
            printf("\n\tYou ran into a GHOST!!\n");
            free(s); s = NULL;
            return 'g';
        }
    }
    else if (tolower(s[0]) == 'a')
    {
        // ----- LEFT -----
        if ((p_y > 0 && (board[p_x][p_y-1] != BLOCK && board[p_x][p_y-1] != GHOST)) || (p_y == 0 && (board[p_x][WIDTH-1] != BLOCK && board[p_x][WIDTH-1] != GHOST)))
        {
            // Eat snail or not
            if ((p_y > 0 && board[p_x][p_y-1] == SNAIL) || (p_y == 0 && board[p_x][WIDTH-1] == SNAIL)) snail_count--;

            // Move player
            board[p_x][p_y] = BLANK;
            if (p_y == 0)
            {
                board[p_x][WIDTH-1] = PLAYER;
                p_y = WIDTH-1;
            }
            else
            {
                board[p_x][p_y-1] = PLAYER;
                p_y--;
            }
        }
        else if ((p_y > 0 && board[p_x][p_y-1] == BLOCK) || (p_y == 0 && board[p_x][WIDTH-1] == BLOCK))
        {
            // BLOCKED
            printf("\n\tYou ran into a BLOCK!!\n");
        }
        else if ((p_y > 0 && board[p_x][p_y-1] == GHOST) || (p_y == 0 && board[p_x][WIDTH-1] == GHOST))
        {
            // RAN into GHOST
            board[p_x][p_y] = BLANK;
            printf("\n\tYou ran into a GHOST!!\n");
            free(s); s = NULL;
            return 'g';
        }

    }
    else if (tolower(s[0]) == 'd')
    {
        // ----- RIGHT -----
        // CHECK: BORDER AND Check blocks/ghost
        // If not at bottom the border                                                     OR if at the bottom border
        if ((p_y < WIDTH-1 && (board[p_x][p_y+1] != BLOCK && board[p_x][p_y+1] != GHOST)) || (p_y == WIDTH-1 && (board[p_x][0] != BLOCK && board[p_x][0] != GHOST)))
        {
            // Eat snail or not
            if ((p_y < WIDTH-1 && board[p_x][p_y+1] == SNAIL) || (p_y == WIDTH-1 && board[p_x][0] == SNAIL)) snail_count--;

            // Move player
            board[p_x][p_y] = BLANK;
            if (p_y == WIDTH-1)
            {
                board[p_x][0] = PLAYER;
                p_y = 0;
            }
            else
            {
                board[p_x][p_y+1] = PLAYER;
                p_y++;
            }
        }
        else if ((p_y < WIDTH-1 && board[p_x][p_y+1] == BLOCK) || (p_y == WIDTH-1 && board[p_x][0] == BLOCK))
        {
            // BLOCKED
            printf("\n\tYou ran into a BLOCK!!\n");
        }
        else if ((p_y < WIDTH-1 && board[p_x][p_y+1] == GHOST) || (p_y == WIDTH-1 && board[p_x][0] == GHOST))
        {
            // RAN into GHOST
            board[p_x][p_y] = BLANK;
            printf("\n\tYou ran into a GHOST!!\n");
            free(s); s = NULL;
            return 'g';
        }

    }
    else if (strcasecmp(s, "quit") == 0)
    {
        free(s); s = NULL;
        return 'q';
    }
    else
    {
        // WRONG INPUT
        printf("\n\nERROR: a,w,s,d  ONLY!\n\n");
    }


    free(s);
    s = NULL;
    return ' ';
}

//      -------- GHOST MOVE - EASY --------
char ghost_move_easy(uint16_t ghost_num, coordinates ghost_pos[])
{
    srand(time(0));
    bool player_eaten = false;

    // Iterate for each ghost on the board
    for (int i = 0; i < ghost_num; i++)
    {
        // Random decide whether ghost will move horizontal, vertical or not at all
        uint8_t random_return = rand() % 3;

        if (random_return == 0)
        {
            // MOVE on X AXIS (if needed)
            if (p_x < ghost_pos[i].x)
            {
                // Up
                if (board[ghost_pos[i].x-1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER)
                {
                    if (board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x-1][ghost_pos[i].y] = GHOST;
                    ghost_pos[i].x--;
                }
            }
            else if (p_x > ghost_pos[i].x)
            {
                // Down
                if (board[ghost_pos[i].x+1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER)
                {
                    if (board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x+1][ghost_pos[i].y] = GHOST;
                    ghost_pos[i].x++;
                }
            }
        }
        else if (random_return == 1)
        {
            // MOVE on Y AXIS (If needed)
            if (p_y < ghost_pos[i].y)
            {
                // Left
                if (board[ghost_pos[i].x][ghost_pos[i].y-1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER)
                {
                    if (board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x][ghost_pos[i].y-1] = GHOST;
                    ghost_pos[i].y--;
                }
            }
            else if (p_y > ghost_pos[i].y)
            {
                // Right
                if (board[ghost_pos[i].x][ghost_pos[i].y+1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER)
                {
                    if (board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x][ghost_pos[i].y+1] = GHOST;
                    ghost_pos[i].y++;
                }
            }
        }
    }

    /* Return 'g', meaning ghost won (i.e. player eaten) - done this way instead of returning 'g' in for loop
     because I still want ghost to take over player spot so it shows on board */
    if (player_eaten) {
        return 'g';
    }
    // else return space char meaning nothing happened
    return ' ';
}

//      -------- GHOST MOVE - HARD --------
char ghost_move_hard(uint16_t ghost_num, coordinates ghost_pos[])
{
    srand(time(0));
    bool player_eaten = false;

    // Iterate for each ghost on the board
    for (int i = 0; i < ghost_num; i++)
    {
        // Random decide whether ghost will move horizontal or vertical, but not both
        uint8_t random_return = rand() % 2;

        if (random_return == 0)
        {
            // MOVE on X AXIS (if needed)
            if (p_x < ghost_pos[i].x)
            {
                // Up
                if (board[ghost_pos[i].x-1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER)
                {
                    if (board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x-1][ghost_pos[i].y] = GHOST;
                    ghost_pos[i].x--;
                }
            }
            else if (p_x > ghost_pos[i].x)
            {
                // Down
                if (board[ghost_pos[i].x+1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER)
                {
                    if (board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x+1][ghost_pos[i].y] = GHOST;
                    ghost_pos[i].x++;
                }
            }
        }
        else
        {
            // MOVE on Y AXIS (If needed)
            if (p_y < ghost_pos[i].y)
            {
                // Left
                if (board[ghost_pos[i].x][ghost_pos[i].y-1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER)
                {
                    if (board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x][ghost_pos[i].y-1] = GHOST;
                    ghost_pos[i].y--;
                }
            }
            else if (p_y > ghost_pos[i].y)
            {
                // Right
                if (board[ghost_pos[i].x][ghost_pos[i].y+1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER)
                {
                    if (board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER) {
                        player_eaten = true;
                    }
                    board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                    board[ghost_pos[i].x][ghost_pos[i].y+1] = GHOST;
                    ghost_pos[i].y++;
                }
            }
        }
    }

    /* Return 'g', meaning ghost won (i.e. player eaten) - done this way instead of returning 'g' in for loop
     because I still want ghost to take over player spot so it shows on board */
    if (player_eaten) {
        return 'g';
    }
    // else return space char meaning nothing happened
    return ' ';
}

//      -------- GHOST MOVE - IMPOSSIBLE --------
char ghost_move_impossible(uint16_t ghost_num, coordinates ghost_pos[])
{
    srand(time(0));
    bool player_eaten = false;

    // Iterate for each ghost on the board
    for (int i = 0; i < ghost_num; i++)
    {
        // Ghost will always move towards player and can move diagnol

        // MOVE on X AXIS (if needed)
        if (p_x < ghost_pos[i].x)
        {
            // Up
            if (board[ghost_pos[i].x-1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER)
            {
                if (board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER) {
                    player_eaten = true;
                }
                board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                board[ghost_pos[i].x-1][ghost_pos[i].y] = GHOST;
                ghost_pos[i].x--;
            }
        }
        else if (p_x > ghost_pos[i].x)
        {
            // Down
            if (board[ghost_pos[i].x+1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER)
            {
                if (board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER) {
                    player_eaten = true;
                }
                board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                board[ghost_pos[i].x+1][ghost_pos[i].y] = GHOST;
                ghost_pos[i].x++;
            }
        }

        // MOVE on Y AXIS (If needed)
        if (p_y < ghost_pos[i].y)
        {
            // Left
            if (board[ghost_pos[i].x][ghost_pos[i].y-1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER)
            {
                if (board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER) {
                    player_eaten = true;
                }
                board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                board[ghost_pos[i].x][ghost_pos[i].y-1] = GHOST;
                ghost_pos[i].y--;
            }
        }
        else if (p_y > ghost_pos[i].y)
        {
            // Right
            if (board[ghost_pos[i].x][ghost_pos[i].y+1] == BLANK || board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER)
            {
                if (board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER) {
                    player_eaten = true;
                }
                board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                board[ghost_pos[i].x][ghost_pos[i].y+1] = GHOST;
                ghost_pos[i].y++;
            }
        }

    }

    /* Return 'g', meaning ghost won (i.e. player eaten) - done this way instead of returning 'g' in for loop
     because I still want ghost to take over player spot so it shows on board */
    if (player_eaten) {
        return 'g';
    }
    // else return space char meaning nothing happened
    return ' ';
}

//      ------- IF_ERROR() -------
void if_error(uint8_t error_num)
{
    //      -- READ FROM ERROR KEY --

    // Key Path
    const char *keyPath = "./resources/errorKey.txt";
    // Read from Error KEY:
    FILE *key_file = fopen(keyPath, "r");
    if (key_file == NULL) {
        printf("\n** ERROR: Failure opening %s\n\n", keyPath);
        exit(-2);
    }

    // Allocate buffer
    char *msg = malloc(sizeof(char));
    if (msg == NULL) exit(-3);

    // Find Error Number & corresponding Error Message
    int8_t c_ret = 0;
    while ((c_ret = fgetc(key_file)-48) != error_num) {if (c_ret == EOF) exit(-5);}
    while ((c_ret = fgetc(key_file)) != '\n') {if (c_ret == EOF) exit(-5);}

    // Iterate until end of message ('\n'), reallocing along the way
    uint16_t i = 0;
    while (true) {

        // Scan char
        msg[i] = fgetc(key_file);
        if (msg[i] == EOF) {exit(-5);}

        // Check for '\n'
        if (msg[i] == '\n') {
            msg[i] = '\0';
            break;
        }
        else {
            msg = realloc(msg, sizeof(char)*(i+2));
            if (msg == NULL) {exit(-4);}
            i++;
        }
    }

    //     --- WRITE TO ERROR LOG ---

    // Log Path
    const char *logPath = "./resources/error_log.csv";

    // OPEN FILE: (Append Mode)
    FILE *log_file = fopen(logPath, "a");
    if (log_file == NULL) {
        printf("\n** ERROR: Failure opening %s\n\n", logPath);
        exit(-1);
    }

    // TIME
    time_t t;
    time(&t);
    uint8_t l = strlen(ctime(&t));
    char *timestamp = ctime(&t);
    timestamp[l-1] = '\0';

    // Print to Log csv
    fprintf(log_file, "%i, %s, %s\n", error_num, msg, timestamp);

    // Close file, handle dangling pointers, exit program
    fclose(log_file);
    fclose(key_file);
    log_file = key_file = NULL;
    msg = timestamp = NULL;
    exit(error_num);
}

//      ----- START_SCREEN() ------
void start_screen(void)
{

    char s[] = "\n\t   ~~~ EAT THE SNAILS!! (@) ~~~\n\n";
    for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); fflush(stdout); usleep(20000);}

    usleep(100000);
    print_ascii_art('s', 1);
    usleep(1500000);

    usleep(100000);
    char s2[] = "    *** DON'T LET THE GHOSTS EAT YOU!! (G) ***\n\n";
    for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); fflush(stdout); usleep(18000);}
    print_ascii_art('g', 1);
    usleep(1500000);

    usleep(100000);
    char s3[] = "  *** Type 'a', 's', 'w', 'd' to move!! ***\n\n";
    for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); fflush(stdout); usleep(18000);}
    // usleep(1500000);

    usleep(100000);
    char s4[] = " *** Or type 'quit' at any time to exit game! ***";
    for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); fflush(stdout); usleep(18000);}
    usleep(1500000);
    printf("\n");

    return;
}


//      ---- COUNTDOWN() ---
void countdown(uint16_t level)
{
    // -- Level x Begins in... --
    char s5[] = "\n\t     Level ";
    char s5_0[] = " begins in:\n\n";
    for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); fflush(stdout); usleep(18000);}
    if (level >= 100) {
        for (uint8_t i = 0; i < 3; i++) {printf("%i", level); fflush(stdout); usleep(18000);}
    }
    else if (level >= 10) {
        for (uint8_t i = 0; i < 2; i++) {printf("%i", level); fflush(stdout); usleep(18000);}
    }
    else {
        printf("%i", level); usleep(18000);
    }

    for (uint8_t i = 0; i < strlen(s5_0); i++) {printf("%c", s5_0[i]); fflush(stdout); usleep(18000);}

    usleep(40000);

    // 3,2,1 countdown
    for (int i = 3; i > 0; i--)
    {
        usleep(1000000);
        printf("\t           ");

        char tmp[] = "~ ";
        for (uint8_t j = 0; j < strlen(tmp); j++) {printf("%c", tmp[j]); fflush(stdout); usleep(18000);}
        printf("%i", i);
        usleep(40000);
        char tmp2[] = " ~\n\n";
        for (uint8_t j = 0; j < strlen(tmp); j++) {printf("%c", tmp2[j]); fflush(stdout); usleep(18000);}
        printf("\n");
    }
    usleep(1000000);
    char go[] = "\n\t\t~~~ GO! ~~~\n";
    printf("%s", go);
    // for (uint8_t i = 0; i < strlen(go); i++) {printf("%c", go[i]); usleep(40000);}
    usleep(900000);

    return;
}

//      ---- PRINT_ASCII_ART() -----
void print_ascii_art(char c, uint64_t time)
{
    if (c == 's' && time == 0)
    {
        printf("\t    .----.   @   @\n");
        printf("\t   / .-\"-.`.  \\v/\n");
        printf("\t   | | '\\ \\ \\_/ )\n");
        printf("\t ,-\\ `-.' /.'  /\n");
        printf("\t'---`----'----'\n");
    }
    else if (c == 's' && time != 0)
    {
        char s[] = "\t         .----.   @   @\n";
        for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); fflush(stdout); usleep(8000);}
        // usleep(time);
        char s2[] = "\t        / .-\"-.`.  \\v/\n";
        for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); fflush(stdout); usleep(8000);}
        // usleep(time);
        char s3[] = "\t        | | '\\ \\ \\_/ )\n";
        for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); fflush(stdout); usleep(8000);}
        // usleep(time);
        char s4[] = "\t      ,-\\ `-.' /.'  /\n";
        for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); fflush(stdout); usleep(8000);}
        // usleep(time);
        char s5[] = "\t     '---`----'----'\n\n";
        for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); fflush(stdout); usleep(8000);}
        // usleep(time);
    }
    else if (c == 'g' && time == 0)
    {
        printf("\t\t      .-.\n");
        printf("\t\t     (o o)\n");
        printf("\t\t     | O \\\n");
        printf("\t\t      \\   \\\n");
        printf("\t\t       `~~~'\n\n");
    }
    else if (c == 'g' && time != 0)
    {
        char s[] = "\t           .-.\n";
        for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); fflush(stdout); usleep(10000);}
        usleep(time);
        char s2[] = "\t          (o o)\n";
        for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); fflush(stdout); usleep(10000);}
        usleep(time);
        char s3[] = "\t          | O \\\n";
        for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); fflush(stdout); usleep(10000);}
        usleep(time);
        char s4[] = "\t           \\   \\\n";
        for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); fflush(stdout); usleep(10000);}
        usleep(time);
        char s5[] = "\t           `~~~'\n\n";
        for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); fflush(stdout); usleep(10000);}
        usleep(time);
    }
    return;
}

char *choose_difficulty(void)
{
    while (true) {

        char *difficulty = inf_buffer("Choose difficulty level (easy, hard, or impossible): ");

        if (strcasecmp(difficulty, "easy") == 0 || strcasecmp(difficulty, "hard") == 0 ||strcasecmp(difficulty, "impossible") == 0 ){
            return difficulty;
        }
        else {
            free(difficulty);
            printf("Please type 'easy', 'hard', or 'impossible' only.\n");
        }
    }
}

uint16_t display_highest_scores(char *difficulty)
{
    uint16_t all_time;
    // Use bash sort program to sort scores and open sorted csv in read mode
    FILE *file = NULL;
    if (strcasecmp(difficulty, "easy") == 0) {

        system("cat resources/scores_easy.csv | sort -n -r | cat > resources/scores_easy_sorted.csv");
        file = fopen("resources/scores_easy_sorted.csv", "r");
    }
    else if (strcasecmp(difficulty, "hard") == 0) {

        system("cat resources/scores_hard.csv | sort -n -r | cat > resources/scores_hard_sorted.csv");
        file = fopen("resources/scores_hard_sorted.csv", "r");
    }
    else {

        system("cat resources/scores_imposssible.csv | sort -n -r | cat > resources/scores_impossible_sorted.csv");
        file = fopen("resources/scores_impossible_sorted.csv", "r");
    }
    if (file == NULL) if_error(4);

    // ---- Retreive highest score from sorted csv -----

    // Allocate array of string pointers (1 entry per string)
    char **highest_scores = malloc(sizeof(char*));
    if (highest_scores == NULL) if_error(1);

    // Iterate through sorted file until end of first row (i.e. highest score)
    bool eof_reached = false;
    // bool highest_scores_found = false;
    uint16_t i, malloced, num_of_high_scores;
    i = malloced = num_of_high_scores = 0;
    char *score1, *score2;
    score1 = score2 = NULL;
    while (!eof_reached)
    {

        // Allocate first char in buffer for name string
        highest_scores[i] = malloc(sizeof(char));
        malloced++;
        if (highest_scores[i] == NULL) if_error(1);
        uint8_t j = 0;

        // Iterate until next row (i.e '\n')
        while ((highest_scores[i][j] = getc(file)) != '\n') {

            // Check for EOF
            if (highest_scores[i][j] == EOF) {eof_reached = true; break;}

            // Realloc
            if (highest_scores[i][j] != '\n') {

                highest_scores[i] = realloc(highest_scores[i], (sizeof(char)*(j+2)));
                if (highest_scores[i] == NULL) if_error(3);
                j++;
            }
            else break;
        }
        highest_scores[i][j] = '\0';

        // Check for ties to keep going
        if (i != 0) {

            // printf("INSIDE SCORES: \n%s\n%s\n", highest_scores[i], highest_scores[i-1]);
            uint8_t tmp_j = 0;
            score1 = malloc(sizeof(char));
            if (score1 == NULL) if_error(1);

            score1[tmp_j] = highest_scores[i-1][tmp_j];

            while (highest_scores[i-1][tmp_j] != ',') {

                score1 = realloc(score1, sizeof(char)*tmp_j+2);
                tmp_j++;

                score1[tmp_j] = highest_scores[i-1][tmp_j];
            }
            score1[tmp_j] = '\0';

            // Remember all time high score
            all_time = atoi(score1);

            uint8_t tmp_j2 = 0;
            score2 = malloc(sizeof(char));
            if (score2 == NULL) if_error(1);

            score2[tmp_j2] = highest_scores[i][tmp_j2];
            while (highest_scores[i][tmp_j2] != ',') {

                score2 = realloc(score2, sizeof(char)*tmp_j2+2);
                tmp_j2++;

                score2[tmp_j2] = highest_scores[i][tmp_j2];
            }
            score2[tmp_j2] = '\0';

            // printf("SCORE1: %s\nSCORE2: %s\n", score1, score2);
            if (atoi(score1) > atoi(score2)) {
                break;
            }
            free(score1);
            free(score2);
            score1 = score2 = NULL;
        }
        num_of_high_scores++;

        // i goes here because there will always be one last malloc for a string of size 0 (i.e when it reads the final '\n' and converts that to '\0', making a string of size 0, only having 1 byte for the nul char)
        i++;
        if (!eof_reached) {
            highest_scores = realloc(highest_scores, (sizeof(char*)*(i+1)));
            if (highest_scores == NULL) if_error(1);
        }
    }

    // Display
    printf("THE ALL TIME HIGH SCORE IS: %i\n", all_time);

    if (num_of_high_scores > 1) {
        printf("People who tied for highest score: \n");
        for (int i = 0; i < num_of_high_scores; i++) {printf("%s\n", highest_scores[i]);}
    }
    else {
        printf("Person with highest score: \n%s\n", highest_scores[0]);
    }


    // Free
    for (int i = 0; i < malloced; i++) {free(highest_scores[i]);}
    free(highest_scores);
    fclose(file);
    file = NULL;
    free(score1);
    free(score2);
    score1 = score2 = NULL;

    return all_time;
}

void record_new_score(char *difficulty, uint16_t score)
{
    // Does user want to record score
    char *record_score = NULL;
    while (true) {

        record_score = inf_buffer("Would you like to record your score? (yes or no): ");
        if (strcasecmp(record_score, "yes") != 0 && strcasecmp(record_score, "no") != 0) {
            printf("Please type 'yes' or 'no' only.\n");
        }
        else break;

        // Free
        free(record_score);
        record_score = NULL;
    }

    // Return if user does not want to record score
    if (strcasecmp(record_score, "no") == 0) return;

    // Get users name
    char *name = NULL, *yes_or_no = NULL;
    while (true) {

        name = inf_buffer("What is your name? ");

        // Confirm
        while (true) {

            printf("Is '%s' correct? (yes or no): ", name);
            yes_or_no = inf_buffer("");

            if (strcasecmp(yes_or_no, "yes") != 0 && strcasecmp(yes_or_no, "no") != 0) {
                printf("Please type 'yes' or 'no' only.\n");
            }
            else break;

            free(yes_or_no);
        }

        if (strcasecmp(yes_or_no, "yes") == 0) break;
        free(yes_or_no);
        free(name);
    }

    // Open csv file (append mode)
    FILE *file = NULL;
    if (strcasecmp(difficulty, "easy") == 0) {
        printf("HERE\n");
        file = fopen("resources/scores_easy.csv", "a");
    }
    else if (strcasecmp(difficulty, "hard") == 0) {
        file = fopen("resources/scores_hard.csv", "a");
    }
    else {
        file = fopen("resources/scores_impossible.csv", "a");
    }
    if (file == NULL) if_error(4);

    // Timestamp
    time_t t;
    time(&t);

    // Record score
    fprintf(file, "%i,", score);
    fprintf(file, "%s,", name);
    fprintf(file, "%s", ctime(&t));

    // Free
    fclose(file);
    file = NULL;
    free(name);
    free(yes_or_no);
    free(record_score);
    record_score = name = yes_or_no = NULL;

    return;
}


// // DOES NOT WORK YET:
// //      ____ CHECK HIGH SCORE ____
// void check_high_score(int16_t current_score)
// {
//     // Path
//     const char *highscorePath = "src/resources/high_scores.csv";

//     // Open File to Read
//     FILE *highscore_file = fopen(highscorePath, "r+");
//     if (highscore_file == NULL) {if_error(4);}

//     uint64_t i = 0;
//     char *fgetc_ret = malloc(sizeof(char));
//     if (fgetc_ret == NULL){ if_error(6);}


//     // Skip csv header (1st line)
//     while ((fgetc_ret[0] = fgetc(highscore_file)) != '\n');

//     // Next column (High Scores)
//     while ((fgetc_ret[0] = fgetc(highscore_file)) != ',');

//     // RECORD NEW SCORE (If blank or new score is higher):
//     while ((fgetc_ret[i] = fgetc(highscore_file)) != ',') i++;
//     fgetc_ret[i] = '\0';


//     printf("%s\n%li\n", fgetc_ret, strlen(fgetc_ret));
//     current_score++;
//     // if (strcmp(fgetc_ret, "BLANK") == 0) {
//     //     fseek(highscore_file, -6, SEEK_CUR);
//     //     record_score(current_score, highscore_file);
//     // }
//     // else if (current_score > atoi(fgetc_ret)) {
//     //     uint16_t l = 0;
//     //     while (fgetc(highscore_file) != '\n') l++;
//     //     fseek(highscore_file, l+1, SEEK_CUR);
//     //     record_score(current_score, highscore_file);
//     // }


//     fclose(highscore_file);
//     highscore_file = NULL;
//     free(fgetc_ret);
//     fgetc_ret = NULL;
//     return;

// }

// //      ____ RECORD NEW SCORE ____
// void record_score(uint64_t highscore, FILE *ptr)
// {
//     // User Enter Name
//     char *name = inf_buffer("\nCongrats! YOU SET A NEW HIGH SCORE!!!\nENTER YOUR NAME: ");

//     // TIME
//     time_t t;
//     time(&t);
//     uint8_t l = strlen(ctime(&t));
//     char *timestamp = ctime(&t);
//     timestamp[l-1] = '\0';

//     // Log New Score
//     int print_return = fprintf(ptr, "%ld,%s,%s", highscore, name, timestamp);
//     printf("fprintf RETURN: %i\n\n", print_return);

//     free(name);
//     name = NULL;
//     return;
// }