#include<cstring>
#include "substring.h"
using namespace std;

bool is_prefix(const char* string1, const char* string2){
	if(*string1=='\0'){
		return true;
	}
	else if (*string1!=*string2){
		return false;
	}
	else {
		return (is_prefix(string1+1,string2+1));
	}
}

int substring_position(const char* string1, const char* string2){
	int position = 0;
	if (is_substring(string1, string2, position)){
		return position;
	}
	return -1;
}

bool is_substring (const char* string1, const char* string2, int& position){
	if (*string2=='\0'){
		return false;
	}
	else if (is_prefix(string1, string2)){
		return true;
	}
	else{
		position++;
		return (is_substring(string1, string2+1, position));
	}
}