using namespace std;
int encode_character (char ch, char braille[]);	
void character_mapping(char ch, char braille[]);
char digit_map(char digit);
bool encode(const char* sentence, char braille[]);
void print_braille(const char* sentence, ostream& output);