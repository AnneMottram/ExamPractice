#include<cstring>
#include<iostream>
using namespace std;
int findFirstVowel(const char* word);
int isvowel(char character);
void translateWord(const char* english, char piglatin[]);
void adday(char piglatin[],int position);
void translateStream(istream& in, ostream& out);