# snail_eater_game_python
ASCII-based, Pacman style game. Written in C.

PLAYER: 'x' <br>
SNAILS: '@' <br>
GHOSTS: 'G' <br>
BLOCKS: '##' <br>

<h3>Basic Gameplay:</h3>
<ol>
<li>Player is 'x'. <br> </li>
<li>Use w,s,a,d to move up, down, left, right respectively. <br></li>
<li>Eat all of the snails (represented as '@') to proceed to next level. <br></li>
</ol> 

<ol>
<li>The ghosts (represented as 'G') will randomly decide to move towards player after each turn (or if in impossible mode, will always move toward player after each turn).</li>
<li>If you run into a ghost or if a ghost runs into you, you lose! (i.e. you must repeat the level).</li>
<li>The player and ghosts can not go through blocks (represented as '#')</li>
<li>The player CAN go though border edge of the gameboard to wrap around to the other side (hint: very useful in avoiding ghost who can NOT wrap around the border)</li>
<li>Each new level: 1 more ghost, 1 more snail and 1 more block will appear.</li>
</ol>

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
<ul>
<li>- PARAMETERS: Takes string as input.</li>
  <ol>
    <li>- Prompts user with string given as input.</li>
    <li>- Mallocs initial char. Reallocs one char at a time until '\n' is reached, at which point that char will be changed to '\0'.</li>
  </ol>
<li>- RETURN: Will return dynamically allocated string. It is up to the programmer to free this string in the calling function.</li>
</ul>

___ IF_ERROR() ___
<br>
void if_error(int16_t error_num)
<ul>
  <li>- PARAMETERS: Takes integer (i.e. error code) as input.  </li>
  <ol>
    <li> Opens file errorKey.txt (which contains all of the potential error codes), scans the error key file for the appropriate corresponding error message.</li>
    <li> Reads error message into dynamically allocated buffer (for ultimate modularity and ability for expansion moving forward)</li>
    <li> Creates timestamp</li>
    <li> Opens errorlog.csv, prints error code, error message and timestamp to error log</li>
    <li> Prints error code/error message to the terminal</li>
    <li> Exits program, returning correct error message from main().</li>
    <li> Note: The 1st iteration of this function took an error message as an input, however, when creating a program in C and trying to make it as robust as possible, of course there are many NULL checks and error checks throughout the program, each of which has an if statement that calls this if_error() function, if triggered. Since each of those calls to if_error() initially took an error message string as input, this began to quickly make the code look very messy. So, for ultimate modularity, ease of use and maintenance moving forward (in addition to cleaning up messy code in the calling function), this function was redesigned to read the corresponding error message from an error key).</li>
   </ol>
  <li>- RETURN: No return value. Exits program before returning.</li>
</ul>

___ RESET_BOARD() ___
<br>
void reset_board(void)
<ul>
  <li> PARAMETERS: No input
  <ol>
    <li> Uses nested loop to go through each space in the board[][] char 2D array, setting each char to '-' (using the macro BLANK)</li>
  </ol>
  <li> RETURN: No return value.
</ul>
___ PRINT_BOARD() ___
<br>
void print_board(uint16_t level)
<ul>
  <li>- PARAMETERS: takes integer as input to display the current level at the top of the screen</li>
  <ol>
  <li> Uses nested loop to print each char in the 2D char array baord[][], using the macros HEIGHT and WIDTH to easily be able to change the board size.</li>
  </ol>
</ul>


___ SPAWN_PLAYER() ___
<br>
void spawn_player(void)
<ul>
  <li>PARAMETERS: No input.</li>
  <ol>
    <li> Uses random number generator along with the modulo operator to find a random spot on the board for the player to start at.</li>
    <li> Since the player is the first to spawn, this function does not need to check if the space is empty. All spaces are empty at this point.</li>
  </ol>
  <li>RETURN: No return value</li>
</ul>

___SPAWN_BLOCKS()___
<br>
void spawn_blocks(uint16_t n)
<ul>
  <li>PARAMETERS: Takes unsigned integer as input, determing how many blocks to spawn.</li>
  <ol>
    <li>Uses random number generator/modulo operator to find random spot for pairs of blocks to appear on the board, and checks that space is empty.</li>
    <li>Every other pair of blocks changes orientation.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>
d
___ __SPAWN GHOSTS()___
<ul>
  <li>PARAMETERS: Takes unsigned integer as input, determing how many snails to spawn.</li>
  <ol>
    <li>Uses random number generator/modulo operator to find random spot for snails to appear on the board, and checks that space is empty.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>


<ul>
  <li>PARAMETERS: </li>
  <ol>
    <li></li>
  </ol>
  <li>RETURN:</li>
</ul>
