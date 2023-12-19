// File Name: Trie.cpp
// Author: trietruo
// Description: Implements from Trie.h; using an empty root pointer, implements public
//     functions such as insert(), loadFromFile(), isWord(), isPrefix(), print(), and
//     wordCount()
// Last Changed: 4.17.2023

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"

// Default constructor.
// post: creates a root with a space as a character
Trie::Trie() : root(' ', false)
{
}

// Insert the parameter word into the Trie.
// pre: string is valid (lowercase, no spaces, not empty)
// post: string is inserted with each letter being a TrieNode
void Trie::insert(const std::string& word)
{
    root.insert(word);
}

// Insert all words in the specified file into the Trie. Throws a
// std::invalid_argument exception if the specified file cannot be
// opened.
// pre: a valid file is passed
// post: an invalid file will throw an exception, a valid file will have all data processed
void Trie::loadFromFile(const std::string& filename)
{
    std::ifstream infile;

    infile.open(filename.c_str());
    if (infile.fail()) {
        throw std::invalid_argument("Error opening input data file.");
    }

    std::string data;
    while (infile >> data) {
        root.insert(data);
    }
}

// Returns true if word is in the Trie, else returns false.
// pre: a string is passed
// post: returns a boolean if the word was identified within the TrieNode tree
bool Trie::isWord(const std::string& word) const
{
    return root.isWord(word);
}

// Returns true if pre is a prefix of a word in the Trie, else returns false.
// pre: a string is passed
// post: returns a boolean if the prefix was identified within the TrieNode tree
bool Trie::isPrefix(const std::string& pre) const
{
    return root.isPrefix(pre);
}

// Print all words in the Trie, one per line. Print in alphabetical order.
// post: using TrieNode's print, all words are printed out alphabetically
void Trie::print() const
{
    root.print("");
}

// Returns a count of all the words in the Trie.
size_t Trie::wordCount() const
{
    return root.wordCount();
}
