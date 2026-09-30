#ifndef WORD_SORTER_H
#define WORD_SORTER_H

#include <string>
#include <vector>
#include <map>

class WordSorter {
public:
    void sort(const std::map<std::string, int>& wordFrequency);

    const std::vector<std::pair<std::string, int>>& getSortedWords() const;

private:
    std::vector<std::pair<std::string, int>> sortedWords;
};

#endif