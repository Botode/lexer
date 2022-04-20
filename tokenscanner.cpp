//tokenscanner.cpp
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <string>
#include "tokenscanner.hpp"

TokenScanner::TokenScanner() {
    initScanner();
    setInput("");
}

TokenScanner::TokenScanner(std::string str) {
    initScanner();
    setInput(str);
}

TokenScanner::TokenScanner(std::istream & infile) {
    initScanner();
    setInput(infile);
}

TokenScanner::~TokenScanner() {
    if (stringInputFlag) delete isp;
}

void TokenScanner::setInput(std::string str) {
    stringInputFlag = true;
    std::string buffer = str;
    isp = new std::istringstream(buffer);
}

void TokenScanner::setInput(std::istream & infile) {
    stringInputFlag = false;
    isp = &infile;
}

bool TokenScanner::nextToken(bool onlyErrors=false) {
    std::string errMsg = "";
    int state = 0;
    bool isEnd = false;
    int len = 0;
    std::string token = "";
    int ch = EOF;
    int oldState = 0;
    int oldLine = line;
    int oldPos = pos;
    int oldCharCount = charCount;
    for (int l = 0; !isEnd; ++l) {
        if (len > MAX_TOKEN) errMsg = "wrong token length";
        if (charCount > MAX_TEXT) {
            errMsg = "wrong text length";
            isEnd = true;
            continue;
        }
        if (state == 0) {
            if (errMsg != "") {
                isEnd = true;
                continue;
            }
            len = 0;
            token = "";
        } else if (charCount != oldCharCount) {
            token += char(ch);
        }
        oldCharCount = charCount;
        ch = getChar(); len++;
        switch (state) {
            case 0:
                if (ch != '0' && std::isdigit(ch)) { state = 1; continue; }
                if (std::isalpha(ch) || ch == '_') { state = 3; continue; }
                switch (ch) {
                    case '0': state = 2; continue;
                    case '[': state = 5; continue;
                    case ']': state = 6; continue;
                    case '(': state = 7; continue;
                    case ')': state = 8; continue;
                    case '{': state = 9; continue;
                    case '}': state = 10; continue;
                    case '?': state = 11; continue;
                    case ';': state = 12; continue;
                    case ',': state = 13; continue;
                    case '.': state = 14; continue;
                    case '+': state = 17; continue;
                    case '-': state = 20; continue;
                    case '%': state = 23; continue;
                    case '<': state = 26; continue;
                    case '*': state = 30; continue;
                    case '/': state = 32; continue;
                    case '>': state = 34; continue;
                    case '=': state = 36; continue;
                    case ':': state = 38; continue;
                    case '!': state = 40; continue;
                    case ' ': case '\t': case '\v':
                    case '\f': continue;
                    case '\n': oldState = 0; state = 60; continue;
                    case '\r': oldState = 0; state = 61; continue;
                    case EOF: state = 53; isEnd = true; continue;
                };
                errMsg = "wrong character"; token += ch; continue;
            case 1:
                if (std::isdigit(ch)) continue;
                if (std::isalpha(ch)) {
                    errMsg = "wrong constant"; continue;
                }
                state = 2; isEnd = true; ungetChar(ch); len--; continue;
            case 2:
                if (std::isalpha(ch) || std::isdigit(ch)) {
                    errMsg = "wrong constant"; continue;
                }
                isEnd = true; ungetChar(ch); len--; continue;
            case 3:
                if (std::isalnum(ch) || ch == '_') continue;
                isEnd = true; ungetChar(ch); len--; continue;
            case 5: case 6: case 7: case 8: case 9:
            case 10: case 11: case 12: case 13:
            case 16: case 18: case 19: case 21:
            case 22: case 24: case 25: case 27:
            case 28: case 29: case 31: case 33:
            case 35: case 37: case 39: case 41:
            case 53:
                isEnd = true; ungetChar(ch); len--; continue;
            case 14:
                if (ch == '.') { state = 15; continue; }
                errMsg = "wrong token"; ungetChar(ch); isEnd = true; continue;
            case 15:
                if (ch == '.') { state = 16; continue; }
                errMsg = "wrong token"; ungetChar(ch); isEnd = true; continue;
            case 17:
                if (ch == '+') { state = 18; continue; }
                if (ch == '=') { state = 19; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 20:
                if (ch == '-') { state = 21; continue; }
                if (ch == '=') { state = 22; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 23:
                if (ch == '=') { state = 24; continue; }
                if (ch == '>') { state = 25; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 26:
                if (ch == '=') { state = 27; continue; }
                if (ch == ':') { state = 28; continue; }
                if (ch == '%') { state = 29; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 30:
                if (ch == '=') { state = 31; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 32:
                if (ch == '=') { state = 33; continue; }
                if (ch == '*') { state = 42; continue; }
                if (ch == '/') { state = 46; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 34:
                if (ch == '=') { state = 35; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 36:
                if (ch == '=') { state = 37; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 38:
                if (ch == '=') { state = 39; continue; }
                isEnd = true; ungetChar(ch); len--; continue;
            case 40:
                if (ch == '=') { state = 41; continue; }
                errMsg = "wrong token"; ungetChar(ch); isEnd = true; continue;
            case 42:
                len = 0;
                if (ch == '\n') { oldState = 42; state = 60; continue; }
                if (ch == '\r') { oldState = 42; state = 61; continue; }
                if (ch != EOF && ch != '*') continue;
                if (ch == '*') { state = 44; continue; }
                errMsg = "unterminated comment"; ungetChar(ch); isEnd = true; continue;
            case 44:
                len = 0;
                if (ch == '\n') { oldState = 42; state = 60; continue; }
                if (ch == '\r') { oldState = 42; state = 61; continue; }
                if (ch != EOF && ch != '*' && ch != '/') { state = 42; continue; }
                if (ch == '*') continue;
                if (ch == '/') { state = 0; oldState = 0; continue; }
                errMsg = "unterminated comment"; ungetChar(ch); isEnd = true; continue;
            case 46:
                len = 0;
                if (ch != EOF && ch != '\n' && ch != '\r') { continue; }
                state = 0; ungetChar(ch); len--; continue;
            case 60:
                state = oldState; ungetChar(ch); ++line; pos = 0; continue;
            case 61:
                if (ch == '\n') { state = 60; continue; }
                state = oldState; ungetChar(ch); ++line; pos = 0; continue;
            case -1:
                ungetChar(ch); isEnd = true; continue;
            default:
                errMsg = "wrong state"; ungetChar(ch); isEnd = true; continue;
        }
    }

    if (!isEnd) errMsg = "wrong token length";

    if (errMsg != "") state = -1;

    if (state == 3) {
        KeyMap::iterator it;
        it = Keywords.find(token);
        if (it != Keywords.end()) state = it->second;
    }

    Token tkn = static_cast<Token>(state);

    if (tkn == Token::ERROR) {
        printError(token, errMsg, oldLine + 1, oldPos + 1);
    }
    else if (!onlyErrors) {
        printToken(tkn, token, oldLine + 1, oldPos + 1);
    }

    return (charCount > MAX_TEXT || state == 53);
}

int TokenScanner::getChar() {
    ++charCount;
    ++pos;
    return isp->get();
}

void TokenScanner::ungetChar(int ch) {
    --charCount;
    --pos;
   isp->unget();
}

void TokenScanner::printToken(Token tkn, std::string str, int line, int pos) {
    TokenMap::iterator it;
    it = Tokens.find(tkn);
    if (it != Tokens.end())
        std::cout << std::setw(25) << it->second + ": ";
    else
        std::cout << "!!" << std::setw(23) << "WRONG TOKEN (" + std::to_string(static_cast<int>(tkn)) + "): ";

    std::cout << std::setw(25) << "'" + str + "'" << " (" << line << ":" << pos << ")" << std::endl;
}

void TokenScanner::printError(std::string str, std::string errMsg, int line, int pos) {
    std::cout << "!!" << std::setw(23) << "ERROR: " << std::setw(20) << errMsg << ": ";

    std::cout << "'" + str + "'" << " (" << line << ":" << pos << ")" << std::endl;
}

void TokenScanner::initScanner() {
    charCount = 0;
    line = 0;
    pos = 0;
}