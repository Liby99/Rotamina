#include "utility/Tokenizer.h"

using namespace rotamina;

Tokenizer::Tokenizer() {
    file = 0;
    lineNum = 0;
    strcpy(fileName, "");
}

Tokenizer::~Tokenizer() {
    if (file) {
        printf("ERROR: Tokenizer::~Tokenizer() - Closing file '%s'\n", fileName);
        fclose((FILE *) file);
    }
}

bool Tokenizer::open(const char * fileName) {
    file = (void *)fopen(fileName, "r");
    lineNum = 1;
    if (file == 0) {
        printf("ERROR: Tokenzier::Open() - Can't open file '%s'\n", fileName);
        return false;
    }
    strcpy(this->fileName, fileName);
    return true;
}

bool Tokenizer::close() {
    if (file) {
        fclose((FILE *) file);
        file = 0;
        return true;
    }
    else {
        return false;
    }
}

bool Tokenizer::abort(char * error) {
    printf("ERROR '%s' line %d: %s\n", fileName, lineNum, error);
    close();
    return false;
}

char Tokenizer::getChar() {
    char c = char(getc((FILE *) file));
    if (c == '\n') lineNum++;
    return c;
}

char Tokenizer::checkChar() {
    int c = getc((FILE *) file);
    ungetc(c, (FILE *) file);
    return char(c);
}

int Tokenizer::getInt() {
    skipWhitespace();
    int pos = 0;
    char temp[256];
    
    char c = checkChar();
    if (c == '-') {
        temp[pos++] = getChar();
        c = checkChar();
    }
    
    if (!isdigit(c)) {
        printf("ERROR: Tokenizer::getInt() - Expecting int on line %d of '%s'\n", lineNum, fileName);
        return 0;
    }
    temp[pos++] = getChar();
    
    while (isdigit(c = checkChar())) {
        temp[pos++] = getChar();
    }
    
    temp[pos++] = '\0';
    return atoi(temp);
}

float Tokenizer::getFloat() {
    skipWhitespace();
    int pos = 0;
    char temp[256];
    
    char c = checkChar();
    if (c == '-') {
        temp[pos++] = getChar();
        c = checkChar();
    }
    
    if (!isdigit(c)) {
        printf("ERROR: Tokenizer::getFloat() - Expecting float on line %d of '%s' '%c'\n", lineNum, fileName, c);
        return 0.0f;
    }
    
    temp[pos++] = getChar();
    
    while (isdigit(c = checkChar())) {
        temp[pos++] = getChar();
    }
    
    if (c == '.') {
        temp[pos++] = getChar();
        while (isdigit(c = checkChar())) {
            temp[pos++] = getChar();
        }
    }
    
    if (c == 'e' || c == 'E') {
        temp[pos++] = getChar();
        c = checkChar();
        if (c == '+' || c == '-') {
            temp[pos++] = getChar();
            c = checkChar();
        }
        if (!isdigit(c)) {
            printf("ERROR: Tokenizer::getFloat() - Poorly formatted float exponent on line %d of '%s'\n", lineNum, fileName);
            return 0.0f;
        }
        while (isdigit(c = checkChar())) {
            temp[pos++] = getChar();
        }
    }
    
    temp[pos++] = '\0';
    return float(atof(temp));
}

bool Tokenizer::getToken(char * str) {
    skipWhitespace();
    int pos = 0;
    char c = checkChar();
    while (c != ' ' && c != '\n' && c != '\t' && c != '\r' && !feof((FILE *) file)) {
        str[pos++] = getChar();
        c = checkChar();
    }
    str[pos] = '\0';
    return true;
}

bool Tokenizer::findToken(const char * tok) {
    int pos = 0;
    while (tok[pos] != '\0') {
        if (feof((FILE *) file)) {
            return false;
        }
        char c = getChar();
        if (c == tok[pos]) {
            pos++;
        }
        else {
            pos = 0;
        }
    }
    return true;
}

bool Tokenizer::skipWhitespace() {
    char c = checkChar();
    bool white = false;
    while (isspace(c)) {
        getChar();
        c = checkChar();
        white = true;
    }
    return white;
}

bool Tokenizer::skipLine() {
    char c = getChar();
    while (c != '\n') {
        if (feof((FILE *) file)) {
            return false;
        }
        c = getChar();
    }
    return true;
}

bool Tokenizer::reset() {
    if (fseek((FILE *) file, 0, SEEK_SET)) {
        return false;
    }
    else {
        return true;
    }
}

bool Tokenizer::isEOF() {
    return feof((FILE *) file);
}

char * Tokenizer::getFileName() {
    return fileName;
}

int Tokenizer::getLineNum() {
    return lineNum;
}
