#ifndef _STATE_HEAD_
#define _STATE_HEAD_
#include <stdio.h>
#include <string.h>
#include "state.h"

BOOL isDigit(char chara) {return chara >= '0' && chara <= '9';}
BOOL isLetter(char chara) {return ((chara >= 'A' && chara <= 'Z') || (chara >= 'a' && chara <= 'z'));}
extern char types[11][15];

void reader(const char* filename) {
	FILE* fp;
	static char buf[1024];
	token temp;
	fp = fopen(filename,"r");
	while (fscanf(fp,"%s",buf) == 1) {
		scanner(buf,&temp);
		printf("(%s,%s,%d)\n",buf,types[temp.type],temp.type);
	}
	fclose(fp);
}

void scanner(char * word, token* tok) {
	LexStatus status = LEX_INITIAL;
	int i = 0;

	while (word[i] == ' ') i++;
	if (isLetter(word[i]) && status == LEX_INITIAL) {
		status = LEX_1;
		while(status == LEX_1) {
			if (!(isLetter(word[++i]) || isDigit(word[++i]))) {
				status = LEX_TERMINAL;
				break;
			}
		}
		status = LEX_INITIAL;
		tok->type = ALPHABET;
		strcpy(tok->word,word);
	}

	else if (isDigit(word[i]) && status == LEX_INITIAL) {
		status = LEX_3;
		while(status == LEX_3) {
			if (!(isDigit(word[++i] || word[++i] == '.'))) {
				status = LEX_TERMINAL;
				break;
			}
		}
		status = LEX_INITIAL;
		tok->type = NUMBER;
		sscanf(word,"%lf",&(tok->nu));
	}

	else if (status == LEX_INITIAL){
		switch (word[i]) {
		case '=':
			tok->type = EQUALS;
			break;
		case '+':
			tok->type = PLUS;
			break;
		case '-':
			tok->type = MINUS;
			break;
		case '*':
			status = LEX_7;
			if (word[++i] != '*') status = LEX_8;
			tok->type = (status == LEX_8) ? ASTERISK : DBL_ASTERISK;
			break;
		case ',':
			tok->type = COMMA;
			break;
		case '(':
			tok->type = LBRACKET;
			break;
		case ')':
			tok->type = RBRACKET;
			break;
		default:
			tok->type = OTHERS;
			break;
		}
		strcpy(tok->word,word);
	}

}

#endif