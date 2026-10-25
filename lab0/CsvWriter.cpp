#include "CsvWriter.h"
#include <fstream>
#include <iostream>

bool CsvWriter::write(const std::string& outputFile,
                      const std::string& header,
                      const std::vector<std::string>& lines) const {
    std::ofstream csvFile(outputFile);
    if (!csvFile.is_open()) {
        std::cerr << "Error: cannot open output file \"" << outputFile << "\"" << std::endl;
        return false;
    }

    csvFile << header << std::endl;
    for (const auto& line : lines) {
        csvFile << line << std::endl;
    }
    return true;
}