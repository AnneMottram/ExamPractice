#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include <cctype>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

bool is_complete(const char board[9][9]){
  for (int i=0; i<9; i++){
    for (int j=0;j<9;j++){
      if (board[i][j]=='.'){
        return false;
      }
    }
  }
  return true;
}

bool make_move(const char* position, char digit, char board[9][9]){
  int row = *position - 'A';
  int col = *(position+1) - '1';
  if (row>8||col>8){
    return false;
  }
  for (int i=0;i<9;i++){
    if(board[i][col]==digit){
      return false;
    }
    if (board[row][i]==digit){
      return false;
    }
  }
  int row_square = row/3;
  int col_square = col/3;
  for (int i = row_square; i<row_square+3;i++){
    for (int j = col_square;j<col_square+3;j++){
      if(board[i][j]==digit){
        return false;
      }
    }
  }
  board[row][col]=digit;
  return true;
}

bool save_board(const char* filename, const char board [9][9]){
  ofstream out;
  out.open(filename);
  if (!out){
    return false;
  }
  for (int i=0; i<9; i++){
    for (int j=0;j<9;j++){
      out<<board[i][j];
    }
    out<<endl;
  }
  out.close();
  return true;
}

bool solve_board(char board[9][9]){
  int row, col;
  if (find_next_empty(row, col, board)){
    for (char digit = '1'; digit<='9'; digit++){
      char position[2];
      position[0]=static_cast<char>(row+65);
      position[1]=static_cast<char>(col+49);
      if (make_move(position, digit, board))
        if (solve_board(board))
          return true;
        board[row][col] = '.';
    }
    return false;
  }
  if (is_complete(board)){
    return true;
  }
  return false;
}

bool find_next_empty(int& row, int& col, const char board[9][9]){
  for (row=0;row<9;row++)
    for (col=0;col<9;col++)
      if (board[row][col]=='.')
        return true;
  return false;
}

/* add your functions here */