# snail_eater_game_python
ASCII-based, Pacman style game. Written in C.

PLAYER: 'x' <br>
SNAILS: '@' <br>
GHOSTS: 'G' <br>
BLOCKS: '##' <br>

<h3>Basic Gameplay:</h3>
<ul>
<li>Player is 'x'. <br> </li>
<li>Use w,s,a,d to move up, down, left, right respectively. <br></li>
<li>Eat all of the snails (represented as '@') to proceed to next level. <br></li>
</ul> 

<ul>
<li>The ghosts (represented as 'G') will randomly decide to move towards player after each turn (or if in impossible mode, will always move toward player after each turn).</li>
<li>If you run into a ghost or if a ghost runs into you, you lose! (i.e. you must repeat the level).</li>
<li>The player and ghosts can not go through blocks (represented as '#')</li>
<li>The player CAN go though border edge of the gameboard to wrap around to the other side (hint: very useful in avoiding ghost who can NOT wrap around the border)</li>
<li>Each new level: 1 more ghost, 1 more snail and 1 more block will appear.</li>
</ul>

<ul>
<li>Type 'quit' anytime to quit! Otherwise, keep playing indefinitely; there are no lives lost for dying, you simply repeat the level!</li>
</ul>

<h3>GAMEBOARD:</h3>
                             ~~~ SNAIL EATER ~~~

                   - Level 1 -


                - - - - - # # - @ 
                - @ - - - - - - - 
                - - - - x - - - - 
                # # - - - - - G - 
                - - - - - - - - - 
                - - # # - - - - - 
                - - - - - - @ - - 
                - G - - - - - - - 
                - - - - - - G - - 

GO!: 

<h3>LIST OF FUNCTIONS:</h3>

___ INF_BUFFER() ____
<br>
char *inf_buffer(char *prompt)

- PARAMETERS: Takes string as input.
- 1. Prompts user with string given as input.
- 2. Mallocs initial char. Reallocs one char at a time until '\n' is reached, at which point that char will be changed to '\0'.
- RETURN: Will return dynamically allocated string. It is up to the programmer to free this string in the calling function.

___ IF_ERROR() ___
<br>
void if_error(int16_t error_num)
<ul>
  <li>- PARAMETERS: Takes integer (i.e. error code) as input.  </li>
  <li>- 1. Opens file errorKey.txt (which contains all of the potential error codes), scans the error key file for the appropriate corresponding error message.</li>
  <li>- 2. Reads error message into dynamically allocated buffer (for ultimate modularity and ability for expansion moving forward)</li>
  <li>- 3. Creates timestamp</li>
  <li>- 4. Opens errorlog.csv, prints error code, error message and timestamp to error log</li>
  <li>- 5. Prints error code/error message to the terminal</li>
  <li>- 6. Exits program, returning correct error message from main().</li>
  <li>- Note: The 1st iteration of this function took an error message as an input, however, when creating a program in C and trying to make it as robust as possible, of course there are many NULL checks and error checks throughout the program, each of which has an if statement that calls this if_error() function, if triggered. Since each of those calls to if_error() initially took an error message string as input, this began to quickly make the code look very messy. So, for ultimate modularity, ease of use and maintenance moving forward (in addition to cleaning up messy code in the calling function), this function was redesigned to read the corresponding error message from an error key).</li>
  <li>- RETURN: No return. Exits program before returning.</li>
</ul>

___ RESET_BOARD() ___
<br>
void reset_board(void)
<ul>
  <li>- 1. Uses nested loop to go through each space in the board[][] char 2D array, setting each char to '-' (using the macro BLANK)</li>
</ul>
___ PRINT_BOARD() ___
<br>
void print_board(uint16_t level)
<ul>
  <li>- PARAMETERS: takes integer as input to display the current level at the top of the screen</li>
  <li>-1. Uses nested loop to print each char in the 2D char array baord[][], using the macros HEIGHT and WIDTH to easily be able to change the board size.</li>
</ul>


___ SPAWN_PLAYER() ___
<br>
void spawn_player(void)
