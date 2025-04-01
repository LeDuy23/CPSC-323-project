
#include "lexicalanalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() : 
    keywordRegex("\\b(if|else|while|for|return|int|float|char|void|double|struct|class|public|private|protected)\\b"),
    identifierRegex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b"),
    integerRegex("\\b[0-9]+\\b"),
    realRegex("\\b[0-9]+\\.[0-9]+\\b"),
    operatorRegex("[+\\-*/=<>!&|^%]|>=|<=|==|!=|\\+\\+|\\-\\-|&&|\\|\\|"),
    separatorRegex("[;,(){}\\[\\]]"),
    singleLineCommentRegex("\\/\\/.*$")
{
    // Initialize keywords map
    std::vector<std::string> keywordsList = {
        "if", "else", "while", "for", "return", "int", "float", "char", 
        "void", "double", "struct", "class", "public", "private", "protected"
    };
    
    for (const auto& keyword : keywordsList) {
        keywords[keyword] = true;
    }
}

std::string LexicalAnalyzer::preprocessCode(const std::string& code) {
    // Remove comments
    std::string result = std::regex_replace(code, singleLineCommentRegex, "");
    
    // Compress multiple whitespace characters into one
    std::regex multipleSpacesRegex("\\s+");
    result = std::regex_replace(result, multipleSpacesRegex, " ");
    
    return result;
}

std::vector<Token> LexicalAnalyzer::tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::string processedCode = preprocessCode(code);
    
    // Regular expression for tokenizing
    std::regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*)|([0-9]+\\.[0-9]+)|([0-9]+)|([+\\-*/=<>!&|^%]|>=|<=|==|!=|\\+\\+|\\-\\-|&&|\\|\\|)|([;,(){}\\[\\]])|(\\/\\/.*$)|(.)");
    
    auto words_begin = std::sregex_iterator(processedCode.begin(), processedCode.end(), tokenRegex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string lexeme = match.str();
        
        // Skip whitespace
        if (std::regex_match(lexeme, std::regex("\\s+"))) {
            continue;
        }
        
        // Determine token type
        TokenType type;
        if (keywords.find(lexeme) != keywords.end()) {
            type = TokenType::KEYWORD;
        } else if (std::regex_match(lexeme, identifierRegex)) {
            type = TokenType::IDENTIFIER;
        } else if (std::regex_match(lexeme, integerRegex)) {
            type = TokenType::INTEGER;
        } else if (std::regex_match(lexeme, realRegex)) {
            type = TokenType::REAL;
        } else if (std::regex_match(lexeme, operatorRegex)) {
            type = TokenType::OPERATOR;
        } else if (std::regex_match(lexeme, separatorRegex)) {
            type = TokenType::SEPARATOR;
        } else {
            type = TokenType::UNKNOWN;
        }
        
        tokens.push_back({lexeme, type});
    }
    
    return tokens;
}

void LexicalAnalyzer::displayTokens(const std::vector<Token>& tokens) {
    std::cout << "Set of lexemes and tokens (<lexemes> = <tokens>)\n\n";
    
    for (const auto& token : tokens) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::KEYWORD:
                typeStr = "keyword";
                break;
            case TokenType::IDENTIFIER:
                typeStr = "identifier";
                break;
            case TokenType::INTEGER:
                typeStr = "integer";
                break;
            case TokenType::REAL:
                typeStr = "real";
                break;
            case TokenType::OPERATOR:
                typeStr = "operator";
                break;
            case TokenType::SEPARATOR:
                typeStr = "separator";
                break;
            case TokenType::COMMENT:
                typeStr = "comment";
                break;
            default:
                typeStr = "unknown";
        }
        
        std::cout << "\"" << token.lexeme << "\" = " << typeStr << std::endl;
    }
}
