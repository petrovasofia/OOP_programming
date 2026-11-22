// main.cpp
#include "trie.h"

#include <iostream>
#include <string>

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");
    trie.insert("");

    std::cout << "size = " << trie.size() << "\n";
    std::cout << "contains(app) = " << trie.contains("app") << "\n";
    std::cout << "contains(ap) = " << trie.contains("ap") << "\n";
    std::cout << "prefix_count(ap) = " << trie.prefix_count("ap") << "\n";
    std::cout << "prefix_count(ban) = " << trie.prefix_count("ban") << "\n";

    std::cout << "\nWords with prefix 'ban':\n";
    for (const auto& w : trie.words_with_prefix("ban")) {
        std::cout << "  " << w << "\n";
    }

    std::cout << "\nAll words:\n" << trie;

    trie.erase("band");
    std::cout << "\nafter erase(band):\n" << trie;

    Trie copy = trie;
    std::cout << "\ncopy == trie: " << (copy == trie) << "\n";
    copy.erase("app");
    std::cout << "copy != trie: " << (copy != trie) << "\n";

    return 0;
}