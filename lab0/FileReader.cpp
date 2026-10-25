#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <cctype>

std::vector<std::string> FileReader::readWords(const std::string& inputFile) const {
    std::vector<std::string> words;
    std::ifstream textFile(inputFile);

    if (!textFile.is_open()) {
        std::cerr << "Error: cannot open input file \"" << inputFile << "\"" << std::endl;
        return words;
    }

    std::string line;
    while (std::getline(textFile, line)) {
        std::string currentWord;
        for (char ch : line) {
            if (std::isalnum(static_cast<unsigned char>(ch))) {
                currentWord += ch;
            } else if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        if (!currentWord.empty()) {
            words.push_back(currentWord);
        }
    }
    return words;
}