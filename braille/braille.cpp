#include<cstring>
#include<cctype>
#include<iostream>
#include "braille.h"
using namespace std;
int encode_character (char ch, char braille[]){
	if (isalpha(ch)&&islower(ch)){
		character_mapping(ch, braille);
		return 6;
	}
	if (ispunct(ch)){
		character_mapping(ch, braille);
		return 6;
	}
	if (isalpha(ch)&&isupper(ch)){
		char lower = tolower(ch);
		strcpy(braille, ".....0");
		char braille2[6];
		character_mapping(lower, braille2);
		strcat(braille,braille2);
		return 12;
	}
	if (isdigit(ch)){
		char digitchar = digit_map(ch);
		strcpy(braille, "..0000");
		char braille2[6];
		character_mapping(digitchar, braille2);
		strcat(braille,braille2);
		return 12;
	}
	return -1;
}
	
bool encode(const char* sentence, char* braille){
	if (*sentence == '\0'){
		return true;
	}
	int position = encode_character(*sentence,braille);
	return(encode(sentence+1,braille+position));
}

void print_braille(const char* sentence, ostream& output){
	char braille[512];
	braille[0] = '\0';
	encode(sentence,braille);
	int length = strlen(braille);
	for (int j=0;j<3;j++){
		for (int i=0; i<length; i+=6){
			output<<braille[i+(j*2)]<<braille[(i+1+j*2)]<<"  ";
		}
		output<<endl;
	}
	int sentencelength = strlen(sentence);
	output<<" ";
	for (int i=0;i<sentencelength;i++){
		if ((isalpha(*(sentence+i))&&islower(*(sentence+i)))||ispunct(*(sentence+i))){
			output<<*(sentence+i)<<"   ";
		}
		else output<<"    "<<*(sentence+i)<<"   ";
	}
}

 
void character_mapping(char ch, char braille[]){
	switch(ch){
		case 'a': strcpy(braille,"0.....");break;
		case 'b': strcpy(braille,"00....");break;
		case 'c': strcpy(braille,"0..0..");break;
		case 'd': strcpy(braille,"0..00.");break;
		case 'e': strcpy(braille,"0...0.");break;
		case 'f': strcpy(braille,"00.0..");break;
		case 'g': strcpy(braille, "00.00.");break;
		case 'h': strcpy(braille, "00.00.");break;
		case 'i': strcpy(braille, ".0.0..");break;
		case 'j': strcpy(braille, ".0.00.");break;
		case 'k': strcpy(braille, "..0...");break;
		case 'l': strcpy(braille, "000...");break;
		case 'm': strcpy(braille, "0.00..");break;
		case 'n': strcpy(braille, "0.000.");break;
		case 'o': strcpy(braille, "0.0.0.");break;
		case 'p': strcpy(braille, "0000..");break;
		case 'q': strcpy(braille, "00000.");break;
		case 'r': strcpy(braille, "000.0.");break;
		case 's': strcpy(braille, ".000..");break;
		case 't': strcpy(braille, ".0000.");break;
		case 'u': strcpy(braille, "0.0..0");break;
		case 'v': strcpy(braille, "000..0");break;
		case 'w': strcpy(braille, ".0.000");break;
		case 'x': strcpy(braille, "0.00.0");break;
		case 'y': strcpy(braille, "0.0000");break;
		case 'z': strcpy(braille, "0.0.00");break;
		case '.': strcpy(braille, ".0..00");break;
		case ',': strcpy(braille, ".0....");break;
		case '-': strcpy(braille, "..0..0");break;
		case ';': strcpy(braille, ".00...");break;
		case '!': strcpy(braille, ".00.0.");break;
		case '?': strcpy(braille, ".00..0");break;
		case '(': 
		case ')': strcpy(braille, ".00.00");break;
		default: strcpy(braille, "......");
	}
}

char digit_map(char digit){
	switch(digit){
		case '1': return 'a';
		case '2': return 'b';
		case '3': return 'c';
		case '4': return 'd';
		case '5': return 'e';
		case '6': return 'f';
		case '7': return 'g';
		case '8': return 'h';
		case '9': return 'i';
		default: return '\0';
	} 
}
