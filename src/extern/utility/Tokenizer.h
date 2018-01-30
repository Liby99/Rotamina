#pragma once

#include <cstdlib>
#include <iostream>
#include <ctype.h>

// The Tokenizer class for reading simple ascii data files. The getToken function
// just grabs tokens separated by whitespace, but the GetInt and GetFloat functions
// specifically parse integers and floating point numbers. skipLine will skip to
// the next carraige return. findToken searches for a specific token and returns
// true if it found it.

class Tokenizer {
    public:
        
        Tokenizer();
        ~Tokenizer();

        bool open(const char *file);
        bool close();

        bool abort(char *error);    // Prints error & closes file, and always returns false

        // Tokenization
        char getChar();
        char checkChar();
        int getInt();
        float getFloat();
        bool getToken(char *str);
        bool findToken(const char *tok);
        bool skipWhitespace();
        bool skipLine();
        bool reset();
        
        bool isEOF() {
            return feof((FILE *) File);
        }
        
        // Access functions
        char * getFileName() {
            return FileName;
        }
        
        int getLineNum() {
            return LineNum;
        }

    private:
        void *File;
        char FileName[256];
        int LineNum;
};
