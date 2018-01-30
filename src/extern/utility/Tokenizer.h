#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>

namespace rotamina {
    class Tokenizer {
        private:
            void * file;
            char fileName[256];
            int lineNum;
        public:
            Tokenizer();
            ~Tokenizer();
            bool open(const char * file);
            bool close();
            bool abort(char * error);
            char getChar();
            char checkChar();
            int getInt();
            float getFloat();
            bool getToken(char * str);
            bool findToken(const char * tok);
            bool skipWhitespace();
            bool skipLine();
            bool reset();
            bool isEOF();
            char * getFileName();
            int getLineNum();
    };
}

#endif
