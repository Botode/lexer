//defs.hpp
#ifndef __DEFS_H
#define __DEFS_H

#include <map>
#include <string>

const int MAX_TEXT = 1000000;
const int MAX_TOKEN = 255;

enum class Token
{
    CONSTANT = 2,
    IDENTIFIER = 3,
    OPENING_BRACKET = 5,
    CLOSING_BRACKET = 6,
    OPENING_PARENTHESIS = 7,
    CLOSING_PARENTHESIS = 8,
    OPENING_BRACE = 9,
    CLOSING_BRACE = 10,
    QUESTION_MARK = 11,
    SEMICOLON = 12,
    COMMA = 13,
    ELLIPSIS = 16,
    PLUS = 17,
    PLUS_PLUS = 18,
    PLUS_EQUAL = 19,
    MINUS = 20,
    MINUS_MIUNS = 21,
    MINUS_EQUAL = 22,
    PERCENT = 23,
    PERCENT_EQUAL = 24,
    ALT_CLOSING_BRACE = 25,
    LESS = 26,
    LESS_EQUAL = 27,
    ALT_OPENING_BRACKET = 28,
    ALT_OPENING_BRACE = 29,
    ASTERISK = 30,
    ASTERISK_EQUAL = 31,
    SLASH = 32,
    SLASH_EQUAL = 33,
    GREATER = 34,
    GREATER_EQUAL = 35,
    EQUAL_EQUAL = 37,
    EQUAL_SIGN = 36,
    COLON = 38,
    ALT_CLOSING_BRACKET = 39,
    NOT_EQUAL = 41,
    END_OF_MODULE = 53,
    ELSE = 54,
    IF = 55,
    INT = 56,
    RETURN = 57,
    VOID = 58,
    BOOL = 59,
    ERROR = -1
};

typedef std::map<std::string, int> KeyMap;
typedef std::map<Token, std::string> TokenMap;

KeyMap Keywords = {
	{"else", 54}, {"if", 55}, {"int", 56},
    {"return", 57}, {"void", 58}, {"_Bool", 59}
};

TokenMap Tokens = {
    {Token::CONSTANT, "CONSTANT"},
    {Token::IDENTIFIER, "IDENTIFIER"},
    {Token::OPENING_BRACKET, "OPENING_BRACKET"},
    {Token::CLOSING_BRACKET, "CLOSING_BRACKET"},
    {Token::OPENING_PARENTHESIS, "OPENING_PARENTHESIS"},
    {Token::CLOSING_PARENTHESIS, "CLOSING_PARENTHESIS"},
    {Token::OPENING_BRACE, "OPENING_BRACE"},
    {Token::CLOSING_BRACE, "CLOSING_BRACE"},
    {Token::QUESTION_MARK, "QUESTION_MARK"},
    {Token::SEMICOLON, "SEMICOLON"},
    {Token::COMMA, "COMMA"},
    {Token::ELLIPSIS, "ELLIPSIS"},
    {Token::PLUS, "PLUS"},
    {Token::PLUS_PLUS, "PLUS_PLUS"},
    {Token::PLUS_EQUAL, "PLUS_EQUAL"},
    {Token::MINUS, "MINUS"},
    {Token::MINUS_MIUNS, "MINUS_MIUNS"},
    {Token::MINUS_EQUAL, "MINUS_EQUAL"},
    {Token::PERCENT, "PERCENT"},
    {Token::PERCENT_EQUAL, "PERCENT_EQUAL"},
    {Token::ALT_CLOSING_BRACE, "ALT_CLOSING_BRACE"},
    {Token::LESS, "LESS"},
    {Token::LESS_EQUAL, "LESS_EQUAL"},
    {Token::ALT_OPENING_BRACKET, "ALT_OPENING_BRACKET"},
    {Token::ALT_OPENING_BRACE, "ALT_OPENING_BRACE"},
    {Token::ASTERISK, "ASTERISK"},
    {Token::ASTERISK_EQUAL, "ASTERISK_EQUAL"},
    {Token::SLASH, "SLASH"},
    {Token::SLASH_EQUAL, "SLASH_EQUAL"},
    {Token::GREATER, "GREATER"},
    {Token::GREATER_EQUAL, "GREATER_EQUAL"},
    {Token::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {Token::EQUAL_SIGN, "EQUAL_SIGN"},
    {Token::COLON, "COLON"},
    {Token::ALT_CLOSING_BRACKET, "ALT_CLOSING_BRACKET"},
    {Token::NOT_EQUAL, "NOT_EQUAL"},
    {Token::END_OF_MODULE, "END_OF_MODULE"},
    {Token::ELSE, "ELSE"},
    {Token::IF, "IF"},
    {Token::INT, "INT"},
    {Token::RETURN, "RETURN"},
    {Token::VOID, "VOID"},
    {Token::BOOL, "BOOL"},
    {Token::ERROR, "ERROR"}
};

#endif