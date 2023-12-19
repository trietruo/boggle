// File Name: Boggle.h
// Author: trietruo
// Description: Declares a game of Boggle from two files (board file and dictionary file)
//     including functions to solve for and print found words
// Last Changed: 4.24.2023

#ifndef PROJECT10_BOGGLE_H
#define PROJECT10_BOGGLE_H
#include <cstddef>
#include <stdexcept>
#include <string>
#include "Trie.h"


const std::string BOARD_NAME("boggle-in.txt");
const std::string DICTIONARY_NAME("ospd.txt");
const int SIZE(4);

class Boggle {
private:
    char boggleBoard[SIZE][SIZE]; // Boggle board imported from boggle-in.txt
    bool visitedBoard[SIZE][SIZE]; // A matching matrix to check which boxes are visited
    Trie validWords; // Dictionary-imported Trie (ospd.txt)
    Trie foundWords; // Words the computer found
    Trie userFoundWords; // Words the user found

    // Helper function that opens files for the constructor; throws std::runtime_error if
    // file fails to open
    // pre: an input stream is prepared as well as a valid file name
    // post: the file is open or an error is thrown
    void openFile(std::ifstream &infile, std::string fileName);

    // Helper function that finds if a word can be found given the current board
    // pre: to be called with a valid word (no spaces, all lowercase), curR as 0, and curC as 0
    // post: returns true if the word is possible and false otherwise
    bool isOnBoard(std::string word, size_t curR, size_t curC);

    void isOnBoard2(std::string word, size_t curR, size_t curC);


public:
    // Constructor
    // pre: two input streams are prepared
    // post: the board is set as designated and the dictionary is imported into a Trie
    Boggle(std::ifstream &infile1, std::ifstream &infile2);

    // Main solving function that recursively finds all words that can be found from a
    // starting point
    // pre: the board is set as designated and the dictionary is imported; the first
    //     call should have word be "", prevR be 0, and prevC be 0
    // post: the foundWords Trie should be loaded with all the found words from the
    //     starting point
    void solve(std::string word, size_t nextR, size_t nextC);

    // Prints out the found words alphabetically and how many words; prints
    // different Tries depending on whether userInput is true or false
    // pre: true or false is set depending on if the user's information should be printed
    // post: if userInput is true, userFoundWords is printed; if userInput is false, foundWords is printed
    void printFoundWords(bool userInput);

    // Prints the Boggle board to the output
    void printBoard();

    // Determines if a word the user entered is legal by validating if it has at least
    // 4 characters, is a word in the dictionary, is not already found, and is possible
    // on the board
    // pre: a valid word (no spaces, all lowercase)
    // post: the word is inserted if it meets all criteria
    void insertIfLegal(std::string word);
};


#endif //PROJECT10_BOGGLE_H
