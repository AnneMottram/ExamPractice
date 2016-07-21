#include<cstring>
#include("substring.h")
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
