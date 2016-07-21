#include "soundex.h"
#include <cstring>
#include <iostream>	
#include <map>
#include <cctype>
using namespace std;

void encode(const char* surname, char* soundex){
	soundex[0]='\0';
	map<char,char>encoder;
	encoder['b']='1';
	encoder['f']='1';
	encoder['p']='1';
	encoder['v']='1';
	encoder['c']='2';
	encoder['g']='2';
	encoder['j']='2';
	encoder['k']='2';
	encoder['q']='2';
	encoder['s']='2';
	encoder['x']='2';
	encoder['z']='2';
	encoder['d']='3';
	encoder['t']='3';
	encoder['l']='4';
	encoder['m']='5';
	encoder['n']='5';
	encoder['r']='6';
	*soundex = *surname;
	int length=strlen(surname);
	int position_filled=1;
	for (int i=1;i<length;i++){
		if(position_filled<4){
			if(!ignore(*(surname+i))){
				char encoded = encoder[*(surname+i)];
				if(encoded!=*(soundex+position_filled-1)){
					*(soundex+position_filled)=encoded;
					position_filled++;
				}
			}
		}
	}
	if(position_filled<4){
		for (int i=0;i<4-position_filled;i++){
			soundex[position_filled+i]='0';
		}
	}
	soundex[4]='\0';	

}

bool ignore(char character){
	switch(character){
		case 'a':
		case 'e':
		case 'h':
		case 'i':
		case 'o':
		case 'u':
		case 'w': return true;
		default: return false;
	}
}

int compare(const char* soundex1, const char* soundex2){
	if (*soundex1=='\0'){
		return true;
	}
	if (*soundex1==*soundex2){
		return (compare(soundex1+1, soundex2+1));
	}
	return false;
}

int count(const char* surname, const char* sentence){
	char soundexbase[5];
	char word[128];
	encode(surname,soundexbase);
	int count = 0;
	while(get_word(sentence,word)){
		char soundexword[5];
		encode(word,soundexword);
		if (compare(soundexbase,soundexword)){
			count++;
		}
	}
	return count;
}

bool get_word(const char *&sentence, char *word) {
  while(*sentence && !isalpha(*sentence))
    sentence++;
  if (!*sentence) 
    return false;
  else {
    while(isalpha(*sentence)) 
      *word++ = *sentence++;
    *word = '\0';
    return true;
  }
}

