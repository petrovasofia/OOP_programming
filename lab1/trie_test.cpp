#include "trie.h"
#include <gtest/gtest.h>

TEST(TrieTest, DefaultConstructor) {
    Trie trie;
    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieTest, InsertSingleWord) {
    Trie trie;
    trie.insert("hello");
    EXPECT_FALSE(trie.empty());
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("hello"));
}

TEST(TrieTest, InsertEmptyString) {
    Trie trie;
    trie.insert("");
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains(""));
}

TEST(TrieTest, InsertDuplicate) {
    Trie trie;
    trie.insert("apple");
    trie.insert("apple");
    EXPECT_EQ(trie.size(), 1);
}

TEST(TrieTest, ContainsNonExistent) {
    Trie trie;
    trie.insert("apple");
    EXPECT_FALSE(trie.contains("app"));
    EXPECT_FALSE(trie.contains("appl"));
    EXPECT_FALSE(trie.contains(""));
}

TEST(TrieTest, EraseExisting) {
    Trie trie;
    trie.insert("band");
    EXPECT_TRUE(trie.erase("band"));
    EXPECT_FALSE(trie.contains("band"));
    EXPECT_EQ(trie.size(), 0);
    EXPECT_TRUE(trie.empty());
}

TEST(TrieTest, EraseNonExistent) {
    Trie trie;
    trie.insert("band");
    EXPECT_FALSE(trie.erase("banana"));
    EXPECT_EQ(trie.size(), 1);
}

TEST(TrieTest, EraseEmptyString) {
    Trie trie;
    trie.insert("");
    EXPECT_TRUE(trie.erase(""));
    EXPECT_FALSE(trie.contains(""));
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieTest, PrefixCount) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    EXPECT_EQ(trie.prefix_count("ap"), 3);
    EXPECT_EQ(trie.prefix_count("app"), 2);
    EXPECT_EQ(trie.prefix_count("b"), 1);
    EXPECT_EQ(trie.prefix_count("z"), 0);
}

TEST(TrieTest, PrefixCountEmptyPrefix) {
    Trie trie;
    trie.insert("a");
    trie.insert("b");
    EXPECT_EQ(trie.prefix_count(""), 2);
}

TEST(TrieTest, WordsWithPrefix) {
    Trie trie;
    trie.insert("ban");
    trie.insert("band");
    trie.insert("banana");
    trie.insert("apple");
    auto words = trie.words_with_prefix("ban");
    ASSERT_EQ(words.size(), 3);
}

TEST(TrieTest, WordsWithPrefixLimit) {
    Trie trie;
    trie.insert("a");
    trie.insert("ab");
    trie.insert("abc");
    auto words = trie.words_with_prefix("a", 2);
    ASSERT_EQ(words.size(), 2);
}

TEST(TrieTest, WordsWithPrefixNotFound) {
    Trie trie;
    trie.insert("apple");
    auto words = trie.words_with_prefix("xyz");
    EXPECT_TRUE(words.empty());
}

TEST(TrieTest, Clear) {
    Trie trie;
    trie.insert("a");
    trie.insert("b");
    trie.clear();
    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieTest, CopyConstructor) {
    Trie t1;
    t1.insert("hello");
    t1.insert("world");
    Trie t2(t1);
    EXPECT_EQ(t1, t2);
    EXPECT_EQ(t2.size(), 2);
}

TEST(TrieTest, CopyAssignment) {
    Trie t1;
    t1.insert("test");
    Trie t2;
    t2 = t1;
    EXPECT_EQ(t1, t2);
}

TEST(TrieTest, MoveConstructor) {
    Trie t1;
    t1.insert("move");
    Trie t2(std::move(t1));
    EXPECT_TRUE(t1.empty());
    EXPECT_EQ(t2.size(), 1);
    EXPECT_TRUE(t2.contains("move"));
}

TEST(TrieTest, MoveAssignment) {
    Trie t1;
    t1.insert("move");
    Trie t2;
    t2 = std::move(t1);
    EXPECT_TRUE(t1.empty());
    EXPECT_EQ(t2.size(), 1);
}

TEST(TrieTest, EqualityOperator) {
    Trie t1, t2;
    t1.insert("x");
    t2.insert("x");
    EXPECT_EQ(t1, t2);
    t2.insert("y");
    EXPECT_NE(t1, t2);
}

TEST(TrieTest, NotEqualOperator) {
    Trie t1, t2;
    t1.insert("a");
    EXPECT_NE(t1, t2);
}

TEST(TrieTest, MultipleInsertErase) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    EXPECT_EQ(trie.size(), 3);
    trie.erase("app");
    EXPECT_EQ(trie.size(), 2);
    EXPECT_FALSE(trie.contains("app"));
    EXPECT_TRUE(trie.contains("apple"));
}

TEST(TrieTest, OutputOperator) {
    Trie trie;
    trie.insert("b");
    trie.insert("a");
    std::ostringstream oss;
    oss << trie;
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a") != std::string::npos);
    EXPECT_TRUE(output.find("b") != std::string::npos);
}