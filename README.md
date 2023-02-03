# snail_eater_game
ASCII-based, Pacman style game. Written in C.
<h3>How to run program</h3>
<ul>
<li>Download the repository from https://github.com/Dvidal7788/snail_eater_game.</li>
<li>Use your terminal to cd into the 'snail_eater_game' directory.</li>
<li>Type 'make' in your terminal. This will compile the program in the correct format for your system.</li>
<li>Type 'make play' or './bin' to run the program</li>



<h3>Basic Gameplay:</h3>
PLAYER: 'x' <br>
SNAILS: '@' <br>
GHOSTS: 'G' <br>
BLOCKS: '##' <br>
<ol>
<li>Player is 'x'. <br> </li>
<li>Use w,s,a,d to move up, down, left, right respectively. Hit enter after selecting which direction to move.<br></li>
<li>Eat all of the snails (represented as '@') to proceed to next level. <br></li>	
<li>If you run into a ghost or if a ghost runs into you, you lose! (i.e. you must repeat the level).</li>
<li>The player and ghosts can not go through blocks (represented as '#')</li>
<li>The player CAN go though border edge of the gameboard to wrap around to the other side (hint: very useful in avoiding ghost who can NOT wrap around the border)</li>
<li>Each new level: 1 more ghost, 1 more snail and 1 more block will appear.</li>
</ol>
<h5>How the ghosts (represented as 'G') move in each mode:</h5>
	<h6>Easy Mode:</h6>
		<li>Each ghost will 33/33/33 randomly decide whether to move 1 space horizontally towards player, 1 space vertically towards player or not move at all.</li>
	<h6>Hard Mode:</h6>
		<li>Each ghost will 50/50 randomly decide whether to move 1 space horizontally towards player or 1 space vertically towards player.</li>
	<h6>Impossible Mode:</h6><li>Each ghost will move both horizontally and vertically towards player if possible (which means they can move diagonally!)</li>

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

___ SPAWN SNAILS()___ <br>
void spawn_ghosts(uint16_t n)
<ul>
  <li>PARAMETERS: Takes unsigned integer as input, determing how many snails to spawn.</li>
  <ol>
	<li>Uses random number generator/modulo operator to find random spot for snails to appear on the board, and checks that space is empty.</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

___ SPAWN GHOSTS() ___ <br>
void spawn_ghosts(uint16_t n, coordinates ghost_pos[])
<ul>
  <li>PARAMETERS: Takes unsigned integer and array of coordinates struct as input</li>
  <ol>
	<li>Uses random number generator/modulo operator to find random spot for snails to appear on the board, and checks that space is empty.</li>
	<li>Keeps track of ghost positions using array of coordinates (which is a struct I declared in the header file, consisting of 2 integers).</li>
  </ol>
  <li>RETURN: No return value</li>
</ul>

___ INF_BUFFER() ____
<br>
char *inf_buffer(char *prompt)
<ul>
<li> PARAMETERS: Takes string as input.</li>
  <ol>
	<li>- Prompts user with string given as input.</li>
	<li>- Mallocs initial char. Reallocs one char at a time until '\n' is reached, at which point that char will be changed to '\0'.</li>
  </ol>
<li> RETURN: Will return dynamically allocated string. It is up to the programmer to free this string in the calling function.</li>
</ul>

___ PLAYER_MOVE() ___ <br>
char player_move(void)
<ul>
  <li>PARAMETERS: Takes no input.</li>
  <ol>
	<li>Uses inf_buffer() to ask user for input (i.e. w, s, a, d to move up, down, left, right)</li>
	<li>Determines if player is at the boarder or not and checks if the direction the player wants to move is blocked by a block or if a ghost is there (taking into account that if the player is at the border, the other side of the board needs to be checked, since the player can wrap around the border)</li>
	<li>If space is free, player moves to new space and player position is saved in macros p_x and p_y.</li>
	<li>If space is occupied by a block, player does not move.</li>
	<li>If space is occupied by a snail, player moves, new player position is remembered and snail_count macro is decremeneted by 1.</li>
	<li>If space is occupied by ghost, player loses.</li>
  </ol>
  <li>RETURN: Return char letting calling function (i.e. main()) determing if player has ran into a ghost, decided to quit or nothing happened.</li>
</ul>

__ GHOST_MOVE() ___ <br>
char ghost_move_easy/ghost_move_hard/ghost_move_impossible(uint16_t ghost_num, coordinates ghost_pos[])<br>
NOTE: 3 different ghost_move functions. One per difficulty level.
<ul>
  <li>PARAMETERS: Takes unsigned integer and array of coordinated structs as input.</li>
  <ol>
	<li>EASY:</li>
	<li>For each ghost, uses random number generator to determine 33/33/33 chance if ghost will move horizontally towards player, vertically towards player or not move at all.</li>
	<li>If the ghost is blocked in the direction that has been chosen, ghost will not move</li>
	<li>HARD:</li>
	<li>For each ghost, uses random number generator to determin 50/50 chance if ghost will move horizontally towards player or vertically towards player. G</li>       	<li>If the ghost is blocked in the direction that has been chosen, ghost will not move. Otherwise ghsot will always move towards player on every turn.</li>
	<li>IMPOSSIBLE:</li>
	<li>Each ghost will move both horizontally and veritcally towards player if possible to move in that direction. This means that the ghost can move diagonally.</li>
  </ol>
  <li>RETURN:</li>
</ul>

___ IF_ERROR() ___
<br>
void if_error(int16_t error_num)
<ul>
  <li> PARAMETERS: Takes integer (i.e. error code) as input.  </li>
  <ol>
	<li> Opens file errorKey.txt (which contains all of the potential error codes), scans the error key file for the appropriate corresponding error message.</li>
	<li> Reads error message into dynamically allocated buffer (for ultimate modularity and ability for expansion moving forward)</li>
	<li> Creates timestamp</li>
	<li> Opens errorlog.csv, prints error code, error message and timestamp to error log</li>
	<li> Prints error code/error message to the terminal</li>
	<li> Exits program, returning correct error message from main().</li>
	<li> Note: The 1st iteration of this function took an error message as an input, however, when creating a program in C and trying to make it as robust as possible, of course there are many NULL checks and error checks throughout the program, each of which has an if statement that calls this if_error() function, if triggered. Since each of those calls to if_error() initially took an error message string as input, this began to quickly make the code look very messy. So, for ultimate modularity, ease of use and maintenance moving forward (in addition to cleaning up messy code in the calling function), this function was redesigned to read the corresponding error message from an error key).</li>
   </ol>
  <li> RETURN: No return value. Exits program before returning.</li>
</ul>


___ START_SCREEN() ___ <br>
void start_screen(void)
<ul>
  <li>PARAMETERS: Takes no inputs.</li>
  <ol>
	<li>Prints character by character to emulate typing.</li>
	<li>Gives breif description of how to play the game</li>
	<li>Calls print_ascii_art() function to print ASCII art of a snail and ghost</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>


___ COUNTDOWN() ___ <br>
void countdown(uint16_t level)
<ul>
  <li>PARAMETERS: Take usigned integer as input so the function knows whcih level to display.</li>
  <ol>
	<li>Counts down from 3 to 1 letting player know the next level going to start</li>
  </ol>
  <li>RETURN: No return value.</li>
</ul>

___ PRINT_ASCII_ART() ___ <br>
void print_ascii_art(char c)
<ul>
  <li>PARAMETERS: Take character as input to let function know which ASCII art to print</li>
  <ol>
	<li>Prints ASCII art (either snail or ghost) character by character.</li>
  </ol>
  <li>RETURN:</li>
</ul>

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

___ DISPLAY_HIGHEST_SCORE() ___
uint16_t display_highest_scores(char *difficulty)
<ul>
  <li>PARAMETERS: Takes string as input to determine which csv file to read from.</li>
  <ol>
	<li>Each difficulty level has its own csv file keeping track of the scores.</li>
	<li>Uses system() to execute bash commands to pipeline the output of cat for the correct scores csv into the bash sort program. Then pipelines the output of sort into a sorted csv file.</li>
	<li>The sorted csv file is now opened in read mode, reading each score entry until the second place score is found. This way we can keep track of all the people who have tied for first place, if there are ties, as opposed to simply reading the top entry. These entries are kept track of in an array of strings.</li>
	<li>Either the top scorer or the people who have tied for the top score are displayed for the player to see.</li>
	<li>An integer of the top score is returned to the calling function, to let the player know if they have beaten or tied the top score.</li>
  </ol>
  <li>RETURN: Returns unsigned integer of the all time highest score.</li>
</ul>
 
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
