#include"piglatin.h"
#include<cstring>
#include<cctype>
#include<iostream>
using namespace std;
int findFirstVowel(const char* word){
	int length = strlen(word);
	for (int i=0; i<length;i++){
		int vowel_ind = isvowel(tolower(*(word+i)));
		if(vowel_ind){
			if(vowel_ind==2&&i!=0&&i!=length-1){
				return i;
			} 
			if(vowel_ind==1){
				return i;
			}
		}
	}
	return -1;
}

int isvowel(char character){
	switch(character){
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return 1;
		case 'y': return 2;
		default: return 0;
	}
}

void translateWord(const char* english, char piglatin[]){
	int first_vowel = findFirstVowel(english);
	int length = strlen(english);
	if (first_vowel==0){
		for(int i=0;i<length;i++){
			piglatin[i]=tolower(*(english+i));
		}
		piglatin[length]='w';
		adday(piglatin,length+1);
	}
	if (first_vowel==-1){
		for(int i=0;i<length;i++){
			piglatin[i]=tolower(*(english+i));
		}
		adday(piglatin,length);
	}
	if (first_vowel>0){
		for (int i=0;i<=length-first_vowel;i++){
			piglatin[i]=tolower(*(english+i+first_vowel));
		}
		for (int i=0;i<first_vowel;i++){
			piglatin[length-first_vowel+i]=tolower(*(english+i));
		}
		adday(piglatin,length);
	}
	if(isupper(*english)){
		char upper = toupper(piglatin[0]);
		piglatin[0]=upper;
	}
	if(isdigit(*english)){
		for(int i=0;i<length;i++){
			piglatin[i]=*(english+i);
		}
	}
}

void adday(char piglatin[],int position){
	piglatin[position]='a';
	piglatin[position+1]='y';	
	piglatin[position+2]='\0';

}

void translateStream(istream& in, ostream& out){
	char word[64];
	char piglatin[70];
	piglatin[0]='\0';
	word[0]='\0';
	in>>word;
	while(!in.eof()){
		translateWord(word,piglatin);
		out<<piglatin<<" ";
		translateStream(in,out);
	}
}