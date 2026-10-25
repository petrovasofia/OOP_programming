#include "WordSorter.h"
#include <algorithm>

std::vector<std::pair<std::string, int>> WordSorter::sort(const std::unordered_map<std::string, int>& frequency) const {
    std::vector<std::pair<std::string, int>> sortedWords(frequency.begin(), frequency.end());

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    return sortedWords;
}