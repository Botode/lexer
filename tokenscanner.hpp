//tokenscanner.hpp
#ifndef __TOKENSCANNER_H
#define __TOKENSCANNER_H

#include <iostream>
#include <string>
#include "defs.hpp"

class TokenScanner
{
public:
    TokenScanner();
    TokenScanner(std::string str);
    TokenScanner(std::istream &infile);

    virtual ~TokenScanner();

    void setInput(std::string str);
    void setInput(std::istream & infile);

    bool nextToken(bool onlyErrors);

    int getChar();
    void ungetChar(int ch);

    void printToken(Token tkn, std::string str, int line, int pos);
    void printError(std::string str, std::string errMsg, int line, int pos);

private:
    std::istream *isp; //поток с текстом для лескического разбора
    bool stringInputFlag; //флаг, создан ли поток из строки или из файла
    int charCount; // счетчик символов в потоке
    int line; // текущая строка
    int pos; // текущая позиция в строке

    void initScanner();
};

#endif
