
#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

// Token types
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER,
    REAL,
    OPERATOR,
    SEPARATOR,
    COMMENT,
    UNKNOWN
};

// Structure to hold token information
struct Token {
    std::string lexeme;
    TokenType type;
};

class LexicalAnalyzer {
private:
    // Regular expressions for token recognition
    const std::regex keywordRegex;
    const std::regex identifierRegex;
    const std::regex integerRegex;
    const std::regex realRegex;
    const std::regex operatorRegex;
    const std::regex separatorRegex;
    const std::regex singleLineCommentRegex;
    
    // Keywords list
    std::unordered_map<std::string, bool> keywords;

public:
    LexicalAnalyzer();
    
    // Remove comments and unnecessary whitespace
    std::string preprocessCode(const std::string& code);
    
    // Tokenize the input code
    std::vector<Token> tokenize(const std::string& code);
    
    // Display the tokens
    void displayTokens(const std::vector<Token>& tokens);
};

#endif // LEXICALANALYZER_H
