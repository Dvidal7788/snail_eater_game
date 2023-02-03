# snail_eater_game
ASCII-based, Pacman style game. Written in C.
<h3>How to run program</h3>
<ul>
	<li>Download the repository from https://github.com/Dvidal7788/snail_eater_game.</li>
	<li>Use your terminal to cd into the 'snail_eater_game' directory.</li>
	<li>Type 'make' in your terminal. This will compile the program in the correct format for your system.</li>
	<li>Type 'make play' or './bin' to run the program</li>
</ul>


<h3>Basic Gameplay:</h3>
PLAYER: 'x' <br>
SNAILS: '@' <br>
GHOSTS: 'G' <br>
BLOCKS: '##' <br>
<ul>
	<li>Player is 'x'. <br> </li>
	<li>Use w,s,a,d to move up, down, left, right respectively. Hit enter after selecting which direction to move.<br></li>
	<li>Eat all of the snails (represented as '@') to proceed to next level. <br></li>	
	<li>If you run into a ghost or if a ghost runs into you, you lose! (i.e. you must repeat the level).</li>
	<li>The player and ghosts can not go through blocks (represented as '#')</li>
	<li>The player CAN go though border edge of the gameboard to wrap around to the other side (hint: very useful in avoiding ghost who can NOT wrap around the border)</li>
	<li>Each new level: 1 more ghost, 1 more snail and 1 more block will appear.</li>
	<li>Type 'quit' anytime to quit! Otherwise, keep playing indefinitely; there are no lives lost for dying, you simply repeat the level!</li>
</ul>
<h4>How the ghosts (represented as 'G') move in each mode:</h4>
	<h6>Easy Mode:</h6>
		<li>Each ghost will 33/33/33 randomly decide whether to move 1 space horizontally towards player, 1 space vertically towards player or not move at all.</li>
	<h6>Hard Mode:</h6>
		<li>Each ghost will 50/50 randomly decide whether to move 1 space horizontally towards player or 1 space vertically towards player.</li>
	<li>This means that unless blocked by a block or snail, each ghost will move 1 space towards player on every turn.</li>
	<h6>Impossible Mode:</h6><li>Each ghost will move both horizontally and vertically towards player if possible (which means they can move diagonally!...in addition to always moving towards the player on each turn.)</li>
	<h6>Hint: Ghosts can not move through blocks or snails (in any mode). This mean they can get stuck behind blocks or snails depending on their orientation in relation to the player. Use this to your advantage!</h6>

<h3>GAMEBOARD:</h3>
                         	

             ~~~ SNAIL GAME ~~~
                 - Level 3 -

             - - - - - - - - - 
             G - - - # # - x - 
             - - - # # - - - - 
             - @ - - - - # - - 
             - - - - - - # - - 
             - - - - - - - - - 
             - - # # - - - - # 
             - - @ - - - - - # 
             - - - G - - - G @              Snails left: 3
GO!:![Snail Game Screenshot](https://user-images.githubusercontent.com/91298183/216680057-b206ffc9-1971-479a-914b-ddcf78848bad.png)




<h3>LIST OF FUNCTIONS:</h3>

___ RESET_BOARD() ___
<br>
void reset_board(void)
<ul>
  <li> PARAMETERS: No input
  <ol>
	<li> Uses nested loop to go through each space in the board[][] char 2D array, setting each char to '-' (using the macro BLANK).</li>
  </ol>
  <li> RETURN: No return value.
</ul>
<br>
___ PRINT_BOARD() ___
<br>
void print_board(uint16_t level)
<ul>
  <li>- PARAMETERS: takes integer as input to display the current level at the top of the screen</li>
  <ol>
  	<li> Uses nested loop to print each char in the 2D char array baord[][], using the macros HEIGHT and WIDTH to easily be able to change the board size.</li>
  </ol>
  <li> RETURN: No return value.</li>
</ul>

<br>
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
	
<br>
___ SPAWN_BLOCKS()___ <br>
void spawn_blocks(uint16_t n)
<ul>
  <li>PARAMETERS: Takes unsigned integer as input, determing how many blocks to spawn.</li>
  <ol>
	<li>Uses random number generator/modulo operator to find random spot for pairs of blocks to appear on the board, and checks that space is empty.</li>
	<li>Every other pair of blocks changes orientation.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

<br>	
___ SPAWN SNAILS()___ <br>
void spawn_ghosts(uint16_t n)
<ul>
  <li>PARAMETERS: Takes unsigned integer as input, determing how many snails to spawn.</li>
  <ol>
	<li>Uses random number generator and modulo operator to find random spot for snails to appear on the board, and checks that that space is empty.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

<br>	
___ SPAWN GHOSTS() ___ <br>
void spawn_ghosts(uint16_t n, coordinates ghost_pos[])
<ul>
  <li>PARAMETERS: Takes unsigned integer and array of coordinates struct as input</li>
  <ol>
	<li>Uses random number generator and modulo operator to find random spot for snails to appear on the board, and checks that that space is empty.</li>
	<li>Keeps track of ghost positions using array of coordinates (which is a struct I declared in the header file, consisting of 2 integers).</li>
  </ol>
  <li>RETURN: No return value</li>
</ul>

<br>	
___ INF_BUFFER() ____
<br>
char *inf_buffer(char *prompt)
<ul>
<li> PARAMETERS: Takes string as input.</li>
  <ol>
	<li>Prompts user with string given as input.</li>
	<li>Mallocs initial char. Reallocs one char at a time until '\n' is reached, at which point that char will be changed to '\0'.</li>
  </ol>
<li> RETURN: Will return dynamically allocated string. It is up to the programmer to free this string in the calling function.</li>
</ul>

<br>	
___ PLAYER_MOVE() ___ <br>
char player_move(void)
<ul>
  <li>PARAMETERS: Takes no input.</li>
  <ol>
	<li>Uses inf_buffer() to ask user for input (i.e. w, s, a, d to move up, down, left, right)</li>
	<li>Determines if player is at the border or not and checks if the direction the player wants to move is blocked by a block or if a ghost is there (taking into account that if the player is at the border, the other side of the board needs to be checked, since the player can wrap around the border)</li>
	<li>If the space is free, rhe player moves to the new space and player position is saved in macros p_x and p_y.</li>
	<li>If the space is occupied by a block, the player does not move.</li>
	<li>If the space is occupied by a snail, player moves, the new player position is remembered and snail_count macro is decremeneted by 1.</li>
	<li>If the space is occupied by ghost, the player loses.</li>
  </ol>
  <li>RETURN: Returns char to inform calling function if player has ran into a ghost, decided to quit or nothing happened.</li>
</ul>

<br>	
__ GHOST_MOVE() ___ <br>
char ghost_move_easy/ghost_move_hard/ghost_move_impossible(uint16_t ghost_num, coordinates ghost_pos[])<br>
NOTE: 3 different ghost_move functions. One per difficulty level.
<ul>
  <li>PARAMETERS: Takes unsigned integer and array of coordinated structs as input.</li>
  <ol>
	<li>EASY:</li>
	<li>For each ghost, uses random number generator to determine 33/33/33 chance if ghost will move horizontally towards player, vertically towards player or not move at all.</li>
	<li>If the ghost is blocked in the direction that has been randomly chosen, the ghost will not move</li>
	<li>HARD:</li>
	<li>For each ghost, uses random number generator to determine 50/50 chance if the ghost will move horizontally towards player or vertically towards player.</li>       	
	<li>If the ghost is blocked in the direction that has been chosen, the ghost will not move. Otherwise ghost will always move towards player on every turn.</li>
	<li>IMPOSSIBLE:</li>
	<li>Each ghost will move both horizontally and veritcally towards player if possible to move in that direction. This means that the ghost can move diagonally.</li>
  </ol>
  <li>RETURN: Returns char letting calling function know if player has been eaten or not.</li>
</ul>

<br>	
___ IF_ERROR() ___
<br>
void if_error(int16_t error_num)
<ul>
  <li> PARAMETERS: Takes integer (i.e. error code) as input.  </li>
  <ol>
	<li> Opens file errorKey.txt (which contains all of the potential error codes), scans the error key file for the appropriate corresponding error message.</li>
	<li> Reads error message into dynamically allocated buffer (for ultimate modularity and ability for expansion moving forward).</li>
	<li> Creates timestamp.</li>
	<li> Opens errorlog.csv, appends error code, error message and timestamp to error log.</li>
	<li> Prints error code/error message to the terminal.</li>
	<li> Exits program, returning correct error message from main().</li>
   </ol>
  <li> RETURN: No return value. (Exits program before returning.)</li>
</ul>

<br>
___ START_SCREEN() ___ <br>
void start_screen(void)
<ul>
  <li>PARAMETERS: Takes no inputs.</li>
  <ol>
	<li>Prints start messages character by character (with milliseconds of sleep in between) to emulate typing.</li>
	<li>Gives breif description of how to play the game.</li>
	<li>Calls print_ascii_art() function to print ASCII art of a snail and ghost.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

<br>
___ COUNTDOWN() ___ <br>
void countdown(uint16_t level)
<ul>
  <li>PARAMETERS: Takes usigned integer as input so the function knows whcih level to display.</li>
  <ol>
	<li>Counts down from 3 to 1 letting player know the next level going to start.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

<br>	
___ PRINT_ASCII_ART() ___ <br>
void print_ascii_art(char c)
<ul>
  <li>PARAMETERS: Takes character as input to let function know which ASCII art to print</li>
  <ol>
	<li>Prints ASCII art (either snail or ghost) character by character.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

<br>	
___ CHOOSE_DIFFICULTY() ___<br>
char *choose_difficulty(void)
<ul>
  <li>PARAMETERS: No inputs.</li>
  <ol>
	<li>Uses inf_buffer() to prompt user to enter difficulty level.</li>
	<li>Keeps looping until user types either 'easy', 'hard', or 'impossible', which is then returned.</li>
  </ol>
  <li>RETURN: Returns dynamically allocated string. Must be freed in calling function.</li>
</ul>

<br>	
___ DISPLAY_HIGHEST_SCORE() ___
uint16_t display_highest_scores(char *difficulty)
<ul>
  <li>PARAMETERS: Takes string as input to determine which csv file to read from.</li>
  <ol>
	<li>Each difficulty level has its own csv file keeping track of the scores users have recorded.</li>
	<li>Uses system() to execute bash commands to pipeline the output of 'cat' for the correct scores csv into the bash 'sort' program. Then pipelines the output of 'sort' into a sorted csv file.</li>
	<li>The sorted csv file is now opened in read mode, reading each score entry until the second place score is found. This way we can keep track of all the people who have tied for first place, (if there are ties for 1st), as opposed to simply reading the top entry. These entries are kept track of in an array of strings.</li>
	<li>Either the single top scorer or all of the people who have tied for the top score are displayed for the player to see.</li>
	<li>An integer of the top score is returned to the calling function, to let the player know if they have beaten or tied the top score.</li>
  </ol>
  <li>RETURN: Returns unsigned integer of the all time highest score.</li>
</ul>
 
<br>	
___ RECORD_NEW_SCORE() ___  
void record_new_score(char *difficulty, uint16_t score)
<ul>
  <li>PARAMETERS: Takes string of difficulty level as well as unisgned integer of the players score as input.</li>
  <li>Asks player if they wish to record their score. Keeps looping until either 'yes' or 'no' is given as an answer.</li>
  <li>Asks for player's name, then asks if the name they typed is correct. Keeps looking until either 'yes' or 'no' is given. If 'no' is given, it will loop around and ask for their name again.</li>
  <li>Opens correct csv file (in append mode) based on difficulty level given as input.</li>
  <li>A timestamp is created.</li>
  <li>Score (given as input to function), name and timestamp are appended to csv file.</li>
  <li>RETURN: No return value.</li>
</ul>
