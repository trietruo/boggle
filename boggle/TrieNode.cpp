// File Name: TrieNode.cpp
// Author: trietruo
// Description: Implements from TrieNode.h; provides big 3 as well as functions like
//     insert(), isWord(), isPrefix(), print(), and wordCount()
// Last Changed: 4.17.2023

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include "TrieNode.h"


// The constructor. Takes a character for the node, and a bool
// indicating whether it represents the end of a word. Note, there is no
// default ctor.
// post: myChar and isEndWord is created based upon c and b
TrieNode::TrieNode(char c, bool b) : myChar(c), isEndWord(b), alphaArray()
{
}

// Copy constructor.
// pre: parameter object, rhs, exists
// post: TrieNode is created to be a copy of the parameter TrieNode
TrieNode::TrieNode(const TrieNode& rhs) : myChar(rhs.myChar), isEndWord(rhs.isEndWord)
{
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        if (rhs.alphaArray[i] != nullptr) {
            alphaArray[i] = new TrieNode(*rhs.alphaArray[i]);
        }else{
            alphaArray[i] = nullptr;
        }
    }
}

// Destructor.
// pre: the stack exists
// post: the stack is destroyed and any dynamic memory is returned to the system
TrieNode::~TrieNode()
{
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        delete alphaArray[i];
        alphaArray[i] = nullptr;
    }
}

// Assignment operator.
// pre: both class objects exist
// post: this class object gets assigned a copy of the parameter class object
const TrieNode& TrieNode::operator= (const TrieNode& rhs)
{
    if (this != &rhs) {
        TrieNode temp(rhs);
        std::swap(myChar, temp.myChar);
        std::swap(isEndWord, temp.isEndWord);
        std::swap(alphaArray, temp.alphaArray);
    }

    return *this;
}

// Insert str starting with the given TrieNode. Create new TrieNodes
// as needed and be sure to set the boolean flag on the last node to
// true.
// pre: string is valid (lowercase, no spaces, not empty)
// post: string is inserted with each letter being a TrieNode
void TrieNode::insert(const std::string& str) {
    if (str.length() == 0) {
        isEndWord = true;
        return;
    }

    size_t index = tolower(str.at(0)) - 'a';

    if (alphaArray[index] == nullptr) {
        alphaArray[index] = new TrieNode(tolower(str.at(0)), false);
    }

    alphaArray[index]->insert(str.substr(1));
}

// Returns true if str is in the sub-Trie starting at the given TrieNode,
// else returns false.
// pre: a string is passed
// post: returns a boolean if the word was identified within the TrieNode tree
bool TrieNode::isWord(const std::string& str) const
{
    if (str.length() == 0) {
        return isEndWord;
    }

    size_t index = str.at(0) - 'a';

    if (alphaArray[index] == nullptr) {
        return false;
    } else {
        return alphaArray[index]->isWord(str.substr(1));
    }
}

// Returns true if pre is a prefix of a word in the sub-Trie starting at
// the given TrieNode, else returns false.
// pre: a string is passed
// post: returns a boolean if the prefix was identified within the TrieNode tree
bool TrieNode::isPrefix(const std::string& pre) const
{
    if (pre.length() == 0) {
        return true;
    }

    size_t index = pre.at(0) - 'a';

    if (alphaArray[index] == nullptr) {
        return false;
    } else {
        return alphaArray[index]->isPrefix(pre.substr(1));
    }
}

// Prints all words starting at the given TrieNode. The parameter
// string str stores the letters of all previous TrieNode objects up to
// the node currently being processed.
// pre: intended to be passed an empty string in order to store values properly
// post: the words in alphabetical order are outputted
void TrieNode::print(const std::string& str) const
{
    std::string word = str;

    if (myChar != ' ') {
        word += myChar;
    }

    if (isEndWord) {
        std::cout << word << std::endl;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        if (alphaArray[i] != nullptr) {
            alphaArray[i]->print(word);
        }
    }
}

// Returns a count all the nodes in the sub-Trie that end a word.
size_t TrieNode::wordCount() const
{
    size_t count = 0;

    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        if (alphaArray[i] != nullptr) {
            count += alphaArray[i]->wordCount();
        }
    }

    if (isEndWord) {
        ++count;
    }

    return count;
}
