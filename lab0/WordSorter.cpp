#include "WordSorter.h"
#include <algorithm>

void WordSorter::sort(const std::map<std::string, int>& wordFrequency) {
    sortedWords.assign(wordFrequency.begin(), wordFrequency.end());

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const std::pair<std::string, int>& a,
           const std::pair<std::string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
}

const std::vector<std::pair<std::string, int>>& WordSorter::getSortedWords() const {
    return sortedWords;
}