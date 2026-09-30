#include "CsvWriter.h"
#include <fstream>
#include <iostream>

bool CsvWriter::write(const std::string& outputFile,
                      const std::vector<std::pair<std::string, int>>& sortedWords,
                      int countOfWords) const {
    std::ofstream CSVFile(outputFile);
    if (!CSVFile.is_open()) {
        std::cerr << "Error: cannot open output file \"" << outputFile << "\"" << std::endl;
        return false;
    }

    CSVFile << "Word,Frequency,Frequency (%)" << std::endl;
    for (const auto& pair : sortedWords) {
        double percent = countOfWords > 0
                         ? 100.0 * pair.second / countOfWords
                         : 0.0;
        CSVFile << pair.first << "," << pair.second << "," << percent << std::endl;
    }
    CSVFile.close();
    return true;
}