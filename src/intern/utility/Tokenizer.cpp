#define _CRT_SECURE_NO_WARNINGS

#include "utility/Tokenizer.h"

Tokenizer::Tokenizer() {
	File=0;
	LineNum=0;
	strcpy(FileName, "");
}

Tokenizer::~Tokenizer() {
	if (File) {
		printf("ERROR: Tokenizer::~Tokenizer()- Closing file '%s'\n", FileName);
		fclose((FILE *) File);
	}
}

bool Tokenizer::open(const char * fname) {
	File = (void*)fopen(fname,"r");
	LineNum = 1;
	if (File == 0) {
		printf("ERROR: Tokenzier::Open()- Can't open file '%s'\n",fname);
		return false;
	}
	strcpy(FileName, fname);
	return true;
}

bool Tokenizer::close() {
	if (File) fclose((FILE *) File);
	else return false;

	File = 0;
	return true;
}

bool Tokenizer::abort(char * error) {
	printf("ERROR '%s' line %d: %s\n", FileName, LineNum, error);
	close();
	return false;
}

char Tokenizer::getChar() {
	char c = char(getc((FILE *) File));
	if (c == '\n') LineNum++;
	return c;
}

char Tokenizer::checkChar() {
	int c = getc((FILE *) File);
	ungetc(c, (FILE *) File);
	return char(c);
}

int Tokenizer::getInt() {
	skipWhitespace();
	int pos = 0;
	char temp[256];

	// Get first character ('-' or digit)
	char c = checkChar();
	if (c == '-') {
		temp[pos++] = getChar();
		c = checkChar();
	}
	if(!isdigit(c)) {
		printf("ERROR: Tokenizer::getInt()- Expecting int on line %d of '%s'\n",LineNum,FileName);
		return 0;
	}
	temp[pos++]=getChar();

	// Get integer potion
	while(isdigit(c=checkChar())) temp[pos++]=getChar();

	// Finish
	temp[pos++]='\0';
	return atoi(temp);
}

float Tokenizer::getFloat() {
	skipWhitespace();
	int pos=0;
	char temp[256];

	// Get first character ('-' or digit)
	char c=checkChar();
	if(c=='-') {
		temp[pos++]=getChar();
		c=checkChar();
	}
	if(!isdigit(c)) {
		printf("ERROR: Tokenizer::getFloat()- Expecting float on line %d of '%s' '%c'\n",LineNum,FileName,c);
		return 0.0f;
	}
	temp[pos++]=getChar();

	// Get integer potion of mantissa
	while(isdigit(c=checkChar())) temp[pos++]=getChar();

	// Get fraction component
	if(c=='.') {
		temp[pos++]=getChar();
		while(isdigit(c=checkChar())) temp[pos++]=getChar();
	}

	// Get exponent
	if(c=='e' || c=='E') {
		temp[pos++]=getChar();
		c=checkChar();
		if(c=='+' || c=='-') {
			temp[pos++]=getChar();
			c=checkChar();
		}
		if(!isdigit(c)) {
			printf("ERROR: Tokenizer::getFloat()- Poorly formatted float exponent on line %d of '%s'\n",LineNum,FileName);
			return 0.0f;
		}
		while(isdigit(c=checkChar())) temp[pos++]=getChar();
	}

	// Finish
	temp[pos++]='\0';
	return float(atof(temp));
}

bool Tokenizer::getToken(char *str) {
	skipWhitespace();

	int pos=0;
	char c=checkChar();
	while(c!=' ' && c!='\n' && c!='\t' && c!='\r' && !feof((FILE*)File)) {
		str[pos++]=getChar();
		c=checkChar();
	}
	str[pos]='\0';
	return true;
}

bool Tokenizer::findToken(const char *tok) {
	int pos=0;
	while(tok[pos]!='\0') {
		if(feof((FILE*)File)) return false;
		char c=getChar();
		if(c==tok[pos]) pos++;
		else pos=0;
	}
	return true;
}

bool Tokenizer::skipWhitespace() {
	char c=checkChar();
	bool white=false;
	while(isspace(c)) {
		getChar();
		c=checkChar();
		white=true;
	}
	return white;
}

bool Tokenizer::skipLine() {
	char c=getChar();
	while(c!='\n') {
		if(feof((FILE*)File)) return false;
		c=getChar();
	}
	return true;
}

bool Tokenizer::reset() {
	if (fseek((FILE*)File,0,SEEK_SET))
		return false;
	return true;
}
