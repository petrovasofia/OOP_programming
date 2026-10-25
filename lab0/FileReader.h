#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

class FileReader {
public:
    std::vector<std::string> readWords(const std::string& inputFile) const;
};

#endif