#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <cctype>

bool FileReader::read(const std::string& inputFile) {
    std::ifstream textFile(inputFile);
    if (!textFile.is_open()) {
        std::cerr << "Error: cannot open input file \"" << inputFile << "\"" << std::endl;
        return false;
    }

    wordFrequency.clear();
    totalWords = 0;

    std::string line;
    while (std::getline(textFile, line)) {
        std::string currentWord;
        for (char ch : line) {
            if (std::isalnum(static_cast<unsigned char>(ch))) {
                currentWord += ch;
            } else if (!currentWord.empty()) {
                wordFrequency[currentWord]++;
                currentWord.clear();
            }
        }
        if (!currentWord.empty()) {
            wordFrequency[currentWord]++;
        }
    }
    textFile.close();

    for (const auto& pair : wordFrequency) {
        totalWords += pair.second;
    }
    return true;
}

const std::map<std::string, int>& FileReader::getWordFrequency() const {
    return wordFrequency;
}

int FileReader::getTotalWords() const {
    return totalWords;
}