#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <string>
#include <vector>
#include <unordered_map>

class WordCounter {
public:
    std::unordered_map<std::string, int> countWords(const std::vector<std::string>& words) const;
};

#endif