// File Name: TrieNode.h
// Author: trietruo
// Description: Declares big 3 as well as functions like insert(), isWord(),
//     isPrefix(), print(), and wordCount()
// Last Changed: 4.17.2023

#ifndef TRIENODE_H
#define TRIENODE_H
#include <cstddef>
#include <stdexcept>
#include <string>


const size_t ALPHABET_SIZE = 26;

class TrieNode
{
private:
    char myChar;
    bool isEndWord;
    TrieNode* alphaArray[ALPHABET_SIZE];


public:
    // The constructor. Takes a character for the node, and a bool
    // indicating whether it represents the end of a word. Note, there is no
    // default ctor.
    // post: myChar and isEndWord is created based upon c and b
    TrieNode(char c, bool b);

    // Copy constructor.
    // pre: parameter object, rhs, exists
    // post: TrieNode is created to be a copy of the parameter TrieNode
    TrieNode(const TrieNode& rhs);

    // Destructor.
    // pre: the stack exists
    // post: the stack is destroyed and any dynamic memory is returned to the system
    ~TrieNode();

    // Assignment operator.
    // pre: both class objects exist
    // post: this class object gets assigned a copy of the parameter class object
    const TrieNode& operator= (const TrieNode& rhs);

    // Insert str starting with the given TrieNode. Create new TrieNodes
    // as needed and be sure to set the boolean flag on the last node to
    // true.
    // pre: string is valid (lowercase, no spaces, not empty)
    // post: string is inserted with each letter being a TrieNode
    void insert(const std::string& str);

    // Returns true if str is in the sub-Trie starting at the given TrieNode,
    // else returns false.
    // pre: a string is passed
    // post: returns a boolean if the word was identified within the TrieNode tree
    bool isWord(const std::string& str) const;

    // Returns true if pre is a prefix of a word in the sub-Trie starting at
    // the given TrieNode, else returns false.
    // pre: a string is passed
    // post: returns a boolean if the prefix was identified within the TrieNode tree
    bool isPrefix(const std::string& pre) const;

    // Prints all words starting at the given TrieNode. The parameter
    // string str stores the letters of all previous TrieNode objects up to
    // the node currently being processed.
    // pre: intended to be passed an empty string in order to store values properly
    // post: the words in alphabetical order are outputted
    void print(const std::string& str) const;

    // Returns a count all the nodes in the sub-Trie that end a word.
    size_t wordCount() const;
};


#endif
