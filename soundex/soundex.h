void encode(const char* surname, char* soundex);
bool ignore(char character);
int compare(const char* soundex1, const char* soundex2);
int count(const char* surname, const char* sentence);
bool get_word(const char *&sentence, char *word);