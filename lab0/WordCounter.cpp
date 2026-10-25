#include "WordCounter.h"

std::unordered_map<std::string, int> WordCounter::countWords(const std::vector<std::string>& words) const {
    std::unordered_map<std::string, int> frequency;
    for (const auto& word : words) {
        frequency[word]++;
    }
    return frequency;
}