#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <map>

class FileReader {
public:
    bool read(const std::string& inputFile);

    const std::map<std::string, int>& getWordFrequency() const;
    int getTotalWords() const;

private:
    std::map<std::string, int> wordFrequency;
    int totalWords = 0;
};

#endif