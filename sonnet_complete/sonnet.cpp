#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(const char* line){
  int number=1;
  char* output_word;
  output_word = new char[25];
  while(get_word(line,number,output_word)){
    number++;
  }  
  return number-1;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending){
  ifstream in;
  in.open("dictionary.txt");
  if(!in){
      cerr<<"Failed to open dictionary";
  }
  while(!in.eof()){
    char* line;
    line = new char[512];
    in.getline(line,512);
    if (match(line,word)){
      int number_words = count_words(line);
      char last_word[25];
      char second_last_word[25];
      get_word(line,number_words,last_word);
      get_word(line,number_words-1,second_last_word);
      if(vowel_in(last_word)){
        strcpy(phonetic_ending,last_word);
        return true;
      }
      strcat(second_last_word,last_word);
      strcpy(phonetic_ending,second_last_word);
      return true;
    }
    delete [] line;
  }
  in.close();
  return false;
}

bool match(const char* line, const char* word){
  if (*word=='\0'){
    return true;
  }
  if (*line!=*word){
    return false;
  }
  while(*line!='\0'){
    if(*line==toupper(*word)){
      return (match(line+1,word+1));
    }
  }
}

bool find_rhyme_scheme(const char* filename,char* scheme){
  rhyming_letter(RESET);  
  ifstream in;
  in.open(filename);
  if(!in){
    return false;
  }
  while(!in.eof()){
    char* line;
    line = new char[512];
    in.getline(line,512);
      if(*line=='\0'){
      return true;
    }
    char last_word[25];
    int number_words = count_words(line);
    get_word(line,number_words,last_word);
    cout<<last_word<<"  ";
    char phonetic_ending[25];
    find_phonetic_ending(last_word,phonetic_ending);
    cout<<phonetic_ending<<endl;
    *scheme = rhyming_letter(phonetic_ending);
    phonetic_ending[0]='\0';
    last_word[0]='\0';
    scheme++;
  }
  in.close();
  return true;
}


bool vowel_in(const char* word){
  if(!*word){
    return false;
  }
  switch(*word){
      case 'A': return true;
      case 'E': return true;
      case 'I': return true;
      case 'O': return true;
      case 'U': return true;
      default: return (vowel_in(word+1));
    }
  }

  char* identify_sonnet(const char* filename){
    char* scheme;
    scheme = new char[512];
    char* sonnet;
    sonnet = new char[25];
    find_rhyme_scheme(filename,scheme);
    if (!strcmp(scheme,"ababcdcdefefgg")){
      strcpy(sonnet,"Shakespearean");
      delete [] scheme;
      return sonnet;
    }
    if (!strcmp(scheme,"abbaabbacdcdcd")){
      strcpy(sonnet,"Petrarchan");
      delete [] scheme;
      return sonnet;
    }
    if (!strcmp(scheme,"ababbcbccdcdee")){
      strcpy(sonnet,"Spenserian");
      delete [] scheme;
      return sonnet;
    }
    else{
      strcpy(sonnet,"Unknown");
      delete [] scheme;
      return sonnet;
    }
  }