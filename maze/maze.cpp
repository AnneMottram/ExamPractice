#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include "maze.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char**m, int height, int width, int& row, int& column){
  for (row=0;row<height;row++){
    for (column=0;column<width;column++){
      if(m[row][column]==ch){
        return true;
      }
    }
  }
  return false;
}

bool valid_solution(const char* path, char**m, int height, int width){
  int row, col;
  find_marker('>',m,height,width,row,col);
  while(*path!='\0'){
    update_position(*path,row,col);
    if (row>=height||row<0||col>=width||col<0){
      return false;
    }
    if (occupied_cell(m,row,col)){
      return false;
    }
    path++;
  }
  if (m[row][col]!='X'){
    return false;
  }
  return true;
}

void update_position(char direction,int& row, int& col){
  switch(direction){
    case 'N': row--;break;
    case 'E': col++;break;
    case 'W': col--;break;
    case 'S': row++; break;
    default: return;
  }
}

bool occupied_cell(char** m, int row, int col){
  char ch = m[row][col];
  switch (ch){
    case '+': return true;
    case '-': return true;
    case '|': return true;
    default: return false;
  }
}

char* find_path(char**m, int height, int width, char start, char end){
  int row,col;
  find_marker(start,m,height,width,row,col);
  char* path;
  path = new char [128];
  path[0]='\0';
  if (recursive(m,height,width,row,col,end,path)){
    return path;
  }
  else {
    return "No solution";
  }
  delete [] path;
}

bool valid_move(char**m, int height, int width, int row, int col, char direction,char end){
  update_position(direction,row,col);
  if (row>=height||row<0||col>=width||col<0){
      return false;
  }
  if (occupied_cell(m,row,col)&&(m[row][col]!=end)){
      return false;
  }
 return true;
}

bool find_move(char**m,int height, int width, int row, int col, char& direction,char end){
  char directions[5]="NESW";
  for (int i=0;i<4;i++){
    if (valid_move(m,height,width,row,col,directions[i],end)){
      direction = directions[i];
      return true;
    }
  }
  return false;
}

bool recursive(char**m,int height,int width, int row, int col, char end, char* path){
  if(m[row][col]==end){
    *path='\0';
    return true;
  }
  char directions[5] = {'N','E','S','W','\0'};
  int temp_row,temp_col;
  for (int i=0;i<4;i++){
    temp_row=row;
    temp_col=col;
    m[row][col]='#';
    if(valid_move(m,height,width,row,col,directions[i],end)){
      update_position(directions[i],row,col);
      cout<<row<<col<<endl;
      //if (recursive(m,height,width,row,col,end,path+1)){
        *path = directions[i];
      //  cout<<row<<col<<endl;
        return true;
      
    }
    row = temp_row;
    col = temp_col;
    m[row][col]=' '; 
   return false;
 }
 }




