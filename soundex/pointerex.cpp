#include<cstring>
#include<<iostream>
#include<cctype>
using namespace std;
bool alphabetical(const char* string1, const char* string2);
int main(){
	if (alphabetical("Hello","Hullo"))
		cout<<"Hello < Hullo"<<endl;
}

bool alphabetical(const char* string1, const char* string2){
	if (*string1=='\0'){
		return true;
	}
	while(*string1!=\'0'){
		if(tolower(*string1)<tolower(*string2)){
			return (alphabetical(string1+1,string2+1));
		}
	}
	return false;
}
