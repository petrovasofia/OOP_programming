#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>
#include <utility>

class CsvWriter {
public:
    bool write(const std::string& outputFile,
               const std::vector<std::pair<std::string, int>>& sortedWords,
               int countOfWords) const;
};

#endif