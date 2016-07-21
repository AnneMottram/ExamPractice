#include<cstring>
#include<cctype>
#include<iostream>
#include "multitap.h"
using namespace std;
int encode_character(const char ch, char* multitap){
	if(!isdigit(ch)&&!isupper(ch)){
		return character_map(ch,multitap);
	}
	if(!isdigit(ch)&&isupper(ch)){
		multitap[0]='#';
		return character_map(ch,multitap+1)+1;
	}
	if (isdigit(ch)){
		strcpy(multitap,"*");
		*(multitap+1)=ch;
		return 2;
	}
}

void encode(const char* plaintext, char* multitap){
	while(*plaintext!='\0'){
		int position = encode_character(*plaintext,multitap);
		if(check_repeat(*plaintext,*(plaintext+1))){
			multitap[position]='|';
			multitap++;
		}
		plaintext++;
		multitap+=position;

	}
}

bool check_repeat(char ch1, char ch2){
	char check1[5];
	char check2[5];
	int position = encode_character(ch1,check1);
	encode_character(ch2,check2);
	if (check1[position-1]==check2[0]){
		return true;
	}
	return false;
}

int character_map(char ch,char* multitap){
	switch(tolower(ch)){
		case'a': strcpy(multitap,"2");return 1;break;
		case'b': strcpy(multitap,"22");return 2;break;
		case'c': strcpy(multitap,"222");return 3;break;
		case'd': strcpy(multitap,"3");return 1;break;
		case'e': strcpy(multitap,"33");return 2;break;
		case'f': strcpy(multitap,"333");return 3;break;
		case'g': strcpy(multitap,"4");return 1;break;
		case'h': strcpy(multitap,"44");return 2;break;
		case'i': strcpy(multitap,"444");return 3;break;
		case'j': strcpy(multitap,"5");return 1;break;
		case'k': strcpy(multitap,"55");return 2;break;
		case'l': strcpy(multitap,"555");return 3;break;
		case'm': strcpy(multitap,"6");return 1;break;
			case'n': strcpy(multitap,"66");return 2;break;
		case'o': strcpy(multitap,"666");return 3;break;
			case'p': strcpy(multitap,"7");return 1;break;
			case'q': strcpy(multitap,"77");return 2;break;
			case'r': strcpy(multitap,"777");return 3;break;
			case's': strcpy(multitap,"7777");return 4;break;
			case't': strcpy(multitap,"8");return 1;break;
			case'u': strcpy(multitap,"88");return 2;break;
			case'v': strcpy(multitap,"888");return 3;break;
			case'w': strcpy(multitap,"9");return 1;break;
			case'x': strcpy(multitap,"99");return 2;break;
			case'y': strcpy(multitap,"999");return 3;break;
			case'z': strcpy(multitap,"9999");return 4;break;
			case' ': strcpy(multitap,"0");return 1;break;
			case'.': strcpy(multitap,"1");return 1;break;
			case',': strcpy(multitap,"11");return 2;break;
			case'!': strcpy(multitap,"111");return 3;break;
			case'?': strcpy(multitap,"1111");return 4;break;
			default: return -1;
		}
}