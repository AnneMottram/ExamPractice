/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

bool find_marker(char ch,  char**m, int height, int width, int& row, int& column);

bool valid_solution(const char* path,  char**m, int height, int width);

void update_position(char direction,int& row, int& col);

bool occupied_cell( char** m, int row, int col);

char* find_path(char**m, int height, int width, char start, char end);

bool valid_move(char**m, int height, int width, int row, int col, char direction,char end);

bool find_move(char**m,int height, int width, int row, int col, char& direction,char end);

bool recursive(char**m,int height,int width, int row, int col, char end, char* path);