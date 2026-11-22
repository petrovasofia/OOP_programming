#ifndef TRIE_H
#define TRIE_H

#include <cstddef>
#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

class Trie final {
public:
    using size_type = std::size_t;

    Trie();
    ~Trie();
    Trie(const Trie& other);
    Trie(Trie&& other) noexcept;
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other) noexcept;

    void insert(std::string_view s);
    bool contains(std::string_view s) const;
    bool erase(std::string_view s);
    size_type prefix_count(std::string_view pref) const;
    std::vector<std::string> words_with_prefix(
        std::string_view pref, size_type limit = 0) const;

    void clear();
    bool empty() const;
    size_type size() const;

    bool operator==(const Trie& other) const;
    bool operator!=(const Trie& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Trie& trie);

private:
    struct Node;

    Node* root_;
    size_type size_;

    Node* find_node(std::string_view s) const;

    friend void destroy_node(Node* node);
    friend Node* clone_node(const Node* node);
    friend bool nodes_equal(const Node* a, const Node* b);
    friend void collect_words(const Node* node, std::string& buffer,
                              std::vector<std::string>& words, size_type max_count);
};

#endif