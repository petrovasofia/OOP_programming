#include "trie.h"

#include <map>
#include <ostream>
#include <utility>

struct Trie::Node {
    std::map<unsigned char, Node*> children;
    bool terminal = false;
    size_type subtree_words = 0;

    Node() = default;
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

void destroy_node(Trie::Node* node) {
    if (!node) return;
    for (auto& [ch, child] : node->children) {
        destroy_node(child);
    }
    delete node;
}

Trie::Node* clone_node(const Trie::Node* node) {
    if (!node) return nullptr;
    Trie::Node* copy = new Trie::Node();
    copy->terminal = node->terminal;
    copy->subtree_words = node->subtree_words;
    for (const auto& [ch, child] : node->children) {
        copy->children[ch] = clone_node(child);
    }
    return copy;
}

bool nodes_equal(const Trie::Node* a, const Trie::Node* b) {
    if (a->terminal != b->terminal) return false;
    if (a->children.size() != b->children.size()) return false;
    auto ita = a->children.begin();
    auto itb = b->children.begin();
    for (; ita != a->children.end(); ++ita, ++itb) {
        if (ita->first != itb->first) return false;
        if (!nodes_equal(ita->second, itb->second)) return false;
    }
    return true;
}

void collect_words(const Trie::Node* node, std::string& buffer,
                   std::vector<std::string>& out, Trie::size_type limit) {
    if (node->terminal) {
        out.push_back(buffer);
        if (limit != 0 && out.size() >= limit) return;
    }
    for (const auto& [ch, child] : node->children) {
        buffer.push_back(static_cast<char>(ch));
        collect_words(child, buffer, out, limit);
        buffer.pop_back();
        if (limit != 0 && out.size() >= limit) return;
    }
}

Trie::Trie() : root_(new Node()), size_(0) {}

Trie::~Trie() {
    destroy_node(root_);
}

Trie::Trie(const Trie& other)
    : root_(clone_node(other.root_)), size_(other.size_) {}

Trie::Trie(Trie&& other) noexcept
    : root_(other.root_), size_(other.size_) {
    other.root_ = new Node();
    other.size_ = 0;
}

Trie& Trie::operator=(const Trie& other) {
    if (this != &other) {
        Trie tmp(other);
        std::swap(root_, tmp.root_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}

Trie& Trie::operator=(Trie&& other) noexcept {
    if (this != &other) {
        destroy_node(root_);
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = new Node();
        other.size_ = 0;
    }
    return *this;
}

Trie::Node* Trie::find_node(std::string_view s) const {
    Node* cur = root_;
    for (unsigned char ch : s) {
        auto it = cur->children.find(ch);
        if (it == cur->children.end()) return nullptr;
        cur = it->second;
    }
    return cur;
}

void Trie::insert(std::string_view s) {
    Node* cur = root_;
    if (!cur->terminal && s.empty()) {
        cur->terminal = true;
        ++cur->subtree_words;
        ++size_;
        return;
    }
    if (s.empty()) return;

    std::vector<Node*> path;
    path.push_back(cur);
    for (unsigned char ch : s) {
        auto it = cur->children.find(ch);
        if (it == cur->children.end()) {
            Node* child = new Node();
            cur->children[ch] = child;
            cur = child;
        } else {
            cur = it->second;
        }
        path.push_back(cur);
    }
    if (cur->terminal) return;
    cur->terminal = true;
    ++size_;
    for (Node* n : path) ++n->subtree_words;
}

bool Trie::contains(std::string_view s) const {
    Node* n = find_node(s);
    return n && n->terminal;
}

bool Trie::erase(std::string_view s) {
    Node* node = find_node(s);
    if (!node || !node->terminal) return false;

    std::vector<std::pair<Node*, unsigned char>> path;
    Node* cur = root_;
    for (unsigned char ch : s) {
        path.emplace_back(cur, ch);
        cur = cur->children[ch];
    }

    node->terminal = false;
    --size_;
    --node->subtree_words;

    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        Node* parent = it->first;
        unsigned char ch = it->second;
        Node* child = parent->children[ch];
        --parent->subtree_words;
        if (child->children.empty() && !child->terminal) {
            parent->children.erase(ch);
            delete child;
        } else {
            break;
        }
    }
    return true;
}

Trie::size_type Trie::prefix_count(std::string_view pref) const {
    Node* n = find_node(pref);
    return n ? n->subtree_words : 0;
}

std::vector<std::string> Trie::words_with_prefix(
    std::string_view pref, size_type limit) const {
    std::vector<std::string> result;
    Node* n = find_node(pref);
    if (!n) return result;
    std::string buffer(pref);
    collect_words(n, buffer, result, limit);
    return result;
}

void Trie::clear() {
    destroy_node(root_);
    root_ = new Node();
    size_ = 0;
}

bool Trie::empty() const {
    return size_ == 0;
}

Trie::size_type Trie::size() const {
    return size_;
}

bool Trie::operator==(const Trie& other) const {
    return nodes_equal(root_, other.root_);
}

bool Trie::operator!=(const Trie& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Trie& trie) {
    std::vector<std::string> words;
    std::string buffer;
    collect_words(trie.root_, buffer, words, 0);
    for (const auto& w : words) os << w << '\n';
    return os;
}