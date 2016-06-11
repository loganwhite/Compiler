typedef int BOOL;

typedef enum _tagType {
	ALPHABET,
	NUMBER,
	EQUALS,
	PLUS,
	MINUS,
	ASTERISK,
	DBL_ASTERISK,
	COMMA,
	LBRACKET,
	RBRACKET,
	OTHERS
} tokenType;

typedef enum _tagLexStatus {
	LEX_INITIAL,
	LEX_0,
	LEX_1,
	LEX_3,
	LEX_7,
	LEX_8,
	LEX_TERMINAL
} LexStatus;

static char types[11][15] = {
	"ALPHABET",
	"NUMBER",
	"EQUALS",
	"PLUS",
	"MINUS",
	"ASTERISK",
	"DBL_ASTERISK",
	"COMMA",
	"LBRACKET",
	"RBRACKET",
	"OTHERS"
};

typedef struct _tagToken {
	union {
		char word[256];
		double nu;
	};
	tokenType type;
} token;

BOOL isDigit(char chara);
BOOL isLetter(char chara);

void reader(const char* filename);
void scanner(char * word, token* tok);