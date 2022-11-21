#ifndef HEADER_H
#define HEADER_H

// HEADER FILE FOR snail_eater.c
    // Declares globals, declares struct for coordinates and defines functions

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h>

// Board dimensions
#define HEIGHT 9
#define WIDTH HEIGHT

// Declare Globals as extern
extern const char BLANK;
extern const char PLAYER;
extern const char BLOCK;
extern const char SNAIL;
extern const char GHOST;
extern char board[HEIGHT][WIDTH];
extern int p_x, p_y, snail_count;

// Define struct
typedef struct coordinates
{
    uint16_t x;
    uint16_t y;
}
coordinates;

// Function Prototypes
void reset_board(void);
void print_board(uint16_t level);
void spawn_player(void);
void spawn_blocks(uint16_t  n);
void spawn_snails(uint16_t n);
void spawn_ghosts(uint16_t  n, coordinates ghost_pos[]);
char *inf_buffer(char *prompt);
char player_move(void);
char ghost_move(uint16_t ghost_num, coordinates ghost_pos[]);
void if_error(uint8_t n);
void start_screen(void);
void print_ascii_art(char c, uint64_t time);
void check_high_score(int16_t current_score);
void record_score(uint64_t highscore, FILE *ptr);

#endif /* HEADER_H */