#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include "lexicalanalyzer.h"

int main() {
    std::string filename;
    std::cout << "Enter the input file name: ";
    std::cin >> filename;
    
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }
    
    // Read the entire file content
    std::string code;
    std::string line;
    while (std::getline(inputFile, line)) {
        code += line + "\n";
    }
    inputFile.close();
    
    // Create and use the lexical analyzer
    LexicalAnalyzer analyzer;
    std::vector<Token> tokens = analyzer.tokenize(code);
    analyzer.displayTokens(tokens);
    
    return 0;
}
