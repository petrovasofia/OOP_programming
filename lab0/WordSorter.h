#ifndef WORD_SORTER_H
#define WORD_SORTER_H

#include <string>
#include <vector>
#include <unordered_map>

class WordSorter {
public:
    std::vector<std::pair<std::string, int>> sort(const std::unordered_map<std::string, int>& frequency) const;
};

#endif