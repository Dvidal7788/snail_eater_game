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
        while (true)
        {
            uint16_t x = rand() % HEIGHT;
            uint16_t y = rand() % WIDTH;

            if (board[x][y] == BLANK)
            {
                board[x][y] = BLOCK;
                break;
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

//      -------- GHOST MOVE --------
char ghost_move(uint16_t ghost_num, coordinates ghost_pos[])
{
    bool player_eaten = false;
    for (int i = 0; i < ghost_num; i++)
    {
        // Random decide whether ghost will move
        if (rand()%2 == 0)
        {
            // GHOST AI: MOVE TOWARD PLAYER
            // Random decide IF to move x or y axis
            if (rand()%2 == 1)
            {
                // MOVE on X AXIS (if needed)
                if (p_x < ghost_pos[i].x)
                {
                    // Up
                    if (board[ghost_pos[i].x-1][ghost_pos[i].y] == BLANK || board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER)
                    {
                        if (board[ghost_pos[i].x-1][ghost_pos[i].y] == PLAYER)
                        {
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
                        if (board[ghost_pos[i].x+1][ghost_pos[i].y] == PLAYER)
                        {
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
                        if (board[ghost_pos[i].x][ghost_pos[i].y-1] == PLAYER)
                        {
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
                        if (board[ghost_pos[i].x][ghost_pos[i].y+1] == PLAYER)
                        {
                            player_eaten = true;
                        }
                        board[ghost_pos[i].x][ghost_pos[i].y] = BLANK;
                        board[ghost_pos[i].x][ghost_pos[i].y+1] = GHOST;
                        ghost_pos[i].y++;
                    }
                }
            }
        }
    }

    if (player_eaten == true) {
        return 'g';
    }
    else return ' ';
}

//      ------- IF_ERROR() -------
void if_error(uint8_t error_num)
{
    //      -- READ FROM ERROR KEY --

    // Key Path
    const char *keyPath = "src/resources/errorKey.txt";
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
    const char *logPath = "src/resources/error_log.csv";

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
    for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); usleep(20000);}

    usleep(100000);
    print_ascii_art('s', 1);
    usleep(1500000);

    usleep(100000);
    char s2[] = "    *** DON'T LET THE GHOSTS EAT YOU!! (G) ***\n\n";
    for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); usleep(20000);}
    print_ascii_art('g', 1);
    usleep(1500000);

    usleep(100000);
    char s3[] = "  *** Type 'a', 's', 'w', 'd' to move!! ***\n\n";
    for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); usleep(20000);}
    // usleep(1500000);

    usleep(100000);
    char s4[] = " *** Or type 'quit' at any time to exit game! ***";
    for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); usleep(20000);}
    usleep(1500000);
    printf("\n");

    // Countdown
    char s5[] = "\n\t     LEVEL 1 BEGINS IN:\n\n";
    for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); usleep(20000);}
    usleep(40000);

    // Each number (3,2,1)
    for (int i = 3; i > 0; i--)
    {
        printf("\t           ");

        char tmp[] = "~ ";
        for (uint8_t j = 0; j < strlen(tmp); j++) {printf("%c", tmp[j]); usleep(76000);}
        printf("%i", i);
        usleep(40000);
        char tmp2[] = " ~\n\n";
        for (uint8_t j = 0; j < strlen(tmp); j++) {printf("%c", tmp2[j]); usleep(76000);}
        usleep(1200000);
        printf("\n");
    }
    char go[] = "\n\t\t~~~ GO! ~~~\n";
    for (uint8_t i = 0; i < strlen(go); i++) {printf("%c", go[i]); usleep(40000);}
    usleep(800000);
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
        for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); usleep(16000);}
        // usleep(time);
        char s2[] = "\t        / .-\"-.`.  \\v/\n";
        for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); usleep(16000);}
        // usleep(time);
        char s3[] = "\t        | | '\\ \\ \\_/ )\n";
        for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); usleep(16000);}
        // usleep(time);
        char s4[] = "\t      ,-\\ `-.' /.'  /\n";
        for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); usleep(16000);}
        // usleep(time);
        char s5[] = "\t     '---`----'----'\n\n";
        for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); usleep(16000);}
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
        for (uint8_t i = 0; i < strlen(s); i++) {printf("%c", s[i]); usleep(18000);}
        usleep(time);
        char s2[] = "\t          (o o)\n";
        for (uint8_t i = 0; i < strlen(s2); i++) {printf("%c", s2[i]); usleep(18000);}
        usleep(time);
        char s3[] = "\t          | O \\\n";
        for (uint8_t i = 0; i < strlen(s3); i++) {printf("%c", s3[i]); usleep(18000);}
        usleep(time);
        char s4[] = "\t           \\   \\\n";
        for (uint8_t i = 0; i < strlen(s4); i++) {printf("%c", s4[i]); usleep(18000);}
        usleep(time);
        char s5[] = "\t           `~~~'\n\n";
        for (uint8_t i = 0; i < strlen(s5); i++) {printf("%c", s5[i]); usleep(18000);}
        usleep(time);
    }
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