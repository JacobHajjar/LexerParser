#include "functions.hpp"



/*                           Keyword,    identifier,  seperator,  operator,   integer,    real,      space,     unknown      IGNORE*/
int stateTable[][10] = { {0, KEYWORD,    IDENTIFIER,  SEPERATOR,  OPERATOR,   INTEGER,    REAL,      SPACE,     UNKNOWN,     IGNORE},
/* STATE 1 */   {KEYWORD,    KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 2 */   {IDENTIFIER, KILLSTATE,  IDENTIFIER,  KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 3 */   {SEPERATOR,  KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  REAL,      KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 4 */   {OPERATOR,   KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 5 */   {INTEGER,    KILLSTATE,  KILLSTATE,   REAL,       KILLSTATE,  INTEGER,    KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 6 */   {REAL,       KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  REAL,       KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 7 */   {SPACE,      KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 8 */   {UNKNOWN,    KILLSTATE,  UNKNOWN,     KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, UNKNOWN,     IGNORE},
/* STATE 9 */   {IGNORE,     IGNORE,     IGNORE,      IGNORE,     IGNORE,     IGNORE,     IGNORE,    IGNORE,    IGNORE,      UNKNOWN}};

vector<TokenStruct> Lexer(string expression)
{
    TokenStruct tokenObjectFound;
    vector<TokenStruct> tokens;
    char currentChar = ' ';
    int col = KILLSTATE;
    int currentState = KILLSTATE;
    int prevState = KILLSTATE;
    string currentToken = "";

   
    for (unsigned i = 0; i < expression.length();)
    {
        currentChar = expression[i];

       
        col = Get_FSM_Col(currentChar);

        
        currentState = stateTable[currentState][col];

       
        if (currentState == KILLSTATE)
        {
            if (prevState != SPACE) 
            {
                
                tokenObjectFound.token = currentToken;
                if (findKeywords(tokenObjectFound.token)) {
                    tokenObjectFound.lexeme = KEYWORD;
                }
                else {
                    tokenObjectFound.lexeme = prevState;
                }
                
                tokenObjectFound.lexemeName = GetLexemeName(tokenObjectFound.lexeme);
                tokens.push_back(tokenObjectFound);
            }
            currentToken = "";
        }
        else
        {
            currentToken += currentChar;
            i++;
        }
        prevState = currentState;

    }
    // this ensures the last token gets saved when
    // we reach the end of the loop (if a valid token exists)
    if (currentState != SPACE && currentToken != "")
    {// ^^ we dont care about whitespace
        tokenObjectFound.token = currentToken;
        if (findKeywords(tokenObjectFound.token)) {
            tokenObjectFound.lexeme = KEYWORD;
        }
        else {
            tokenObjectFound.lexeme = currentState;
        }

        tokenObjectFound.lexemeName = GetLexemeName(tokenObjectFound.lexeme);
        tokens.push_back(tokenObjectFound);
    }
    return tokens;
}

int Get_FSM_Col(char currentChar) {
    // check for whitespace
    if (isspace(currentChar))
    {
        return SPACE;
    }
    else if (findOperator(currentChar)) {
        return OPERATOR;
    }
    else if (findSeperator(currentChar)) {
        return SEPERATOR;
    }
    else if (findIdentifier(currentChar)) {
        return IDENTIFIER;
    }
    else if (findInteger(currentChar)) {
        return INTEGER;
    } 
    else if (currentChar == '!') {
        return IGNORE;
    }

    return UNKNOWN;
}
string GetLexemeName(int lexeme) {
    switch (lexeme)
    {
    case KEYWORD:
        return "KEYWORD";
        break;
    case IDENTIFIER:
        return "IDENTIFIER";
        break;
    case SEPERATOR:
        return "SEPERATOR";
        break;
    case OPERATOR:
        return "OPERATOR";
        break;
    case INTEGER:
        return "INTEGER";
        break;
    case REAL:
        return "REAL  ";
        break;
    case SPACE:
        return "SPACE";
        break;
    case UNKNOWN:
        return "UNKNOWN";
        break;
    case IGNORE:
        return "IGNORE";
        break;
    default:
        return "ERROR";
        break;
    }
}

bool findOperator(char opper) {
    switch (opper)
    {
    case '*':
        return true;
        break;
    case '+':
        return true;
        break;
    case '-':
        return true;
        break;
    case '=':
        return true;
        break;
    case '/':
        return true;
        break;
    case '>':
        return true;
        break;
    case '<':
        return true;
        break;
    case '%':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool findSeperator(char seperator) {
    switch (seperator)
    {
    case '(':
        return true;
        break;
    case ')':
        return true;
        break;
    case '{':
        return true;
        break;
    case '}':
        return true;
        break;
    case '[':
        return true;
        break;
    case ']':
        return true;
        break;
    case ',':
        return true;
        break;
    case '.':
        return true;
        break;
    case ':':
        return true;
        break;
    case ';':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool findKeywords(string keyword) {
    
    string keywords[] = { 
        "int", "float", "bool", "True", "False", "if", "else", 
        "then", "endif", "endelse", "while", "whileend", "do", 
        "enddo", "for", "endfor", "STDinput", "STDoutput", "and", 
        "or" , "not" };
    for (int i = 0; i < 19; i++)
    if (keyword == keywords[i]) {
        return true;
    }
    return false;
}
bool findIdentifier(char ident) {
    string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
    string alphabetHigher = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < alphabetHigher.length(); i++) {
        if (ident == alphabetLower[i] || ident == alphabetHigher[i]) {
            return true;
        }
    }
    return false;
}

bool findInteger(char integer) {
    switch (integer)
    {
    case '0':
        return true;
        break;
    case '1':
        return true;
        break;
    case '2':
        return true;
        break;
    case '3':
        return true;
        break;
    case '4':
        return true;
        break;
    case '5':
        return true;
        break;
    case '6':
        return true;
        break;
    case '7':
        return true;
        break;
    case '8':
        return true;
        break;
    case '9':
        return true;
        break;
    default:
        return false;
        break;
    }
}