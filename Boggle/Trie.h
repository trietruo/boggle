// File Name: Trie.h
// Author: trietruo
// Description: Declares empty root pointer privately as well as public functions such
//     as insert(), loadFromFile(), isWord(), isPrefix(), print(), and wordCount()
// Last Changed: 4.17.2023

#include <cstddef>
#include <stdexcept>
#include <string>
#include "TrieNode.h"


class Trie
{
private:
    TrieNode root;


public:
    // Default constructor; creates a root with a space as a character
    Trie();

    // Insert the parameter word into the Trie.
    // pre: string is valid (lowercase, no spaces, not empty)
    // post: string is inserted with each letter being a TrieNode
    void insert(const std::string& word);

    // Insert all words in the specified file into the Trie. Throws a
    // std::invalid_argument exception if the specified file cannot be
    // opened.
    // pre: a valid file is passed
    // post: an invalid file will throw an exception, a valid file will have all data processed
    void loadFromFile(const std::string& filename);

    // Returns true if word is in the Trie, else returns false.
    // pre: a string is passed
    // post: returns a boolean if the word was identified within the TrieNode tree
    bool isWord(const std::string& word) const;

    // Returns true if pre is a prefix of a word in the Trie, else returns false.
    // pre: a string is passed
    // post: returns a boolean if the prefix was identified within the TrieNode tree
    bool isPrefix(const std::string& pre) const;

    // Print all words in the Trie, one per line. Print in alphabetical order.
    // post: using TrieNode's print, all words are printed out alphabetically
    void print() const;

    // Returns a count of all the words in the Trie.
    size_t wordCount() const;
};

#endif 
