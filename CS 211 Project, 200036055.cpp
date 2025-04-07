#include <iostream>
#include <cctype>
#include <string>

int charClass;
std::string lexeme;
char nextChar;
int lexLen;
int nextToken;

std::string inputString = "A+B*(C-1)";
size_t inputIndex = 0;

#define LETTER 0
#define DIGIT  1
#define UNKNOWN 99

#define INT_LIT      10
#define IDENT        11
#define ASSIGN_OP    20
#define ADD_OP       21
#define SUB_OP       22
#define MULT_OP      23
#define DIV_OP       24
#define LEFT_PAREN   25
#define RIGHT_PAREN  26

void addChar();
void getChar();
void getNonBlank();
int lookup(char ch);
int lex();

int main() {
    getChar();
    do {
        lex();
    } while (nextToken != -1);
    
    return 0;
}

int lookup(char ch) {
    switch(ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = -1;
            break;
    }
    return nextToken;
}

void addChar() {
    lexeme.push_back(nextChar);
    lexLen++;
}

void getChar() {
    if (inputIndex < inputString.size()) {
        nextChar = inputString[inputIndex++];
        if (std::isalpha(nextChar))
            charClass = LETTER;
        else if (std::isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = -1;
    }
}

void getNonBlank() {
    while (std::isspace(nextChar))
        getChar();
}

int lex() {
    lexeme.clear();
    lexLen = 0;
    getNonBlank();
    
    switch(charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
            
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
            
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
            
        case -1:
            nextToken = -1;
            lexeme = "EOF";
            break;
    }
    
    std::cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << std::endl;
    return nextToken;
}
