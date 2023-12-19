// File Name: Boggle.cpp
// Author: trietruo
// Description: Implements a game of Boggle from two files (board file and dictionary file)
//     including functions to solve for and print found words
// Last Changed: 4.24.2023

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "Boggle.h"


// Constructor
// pre: two input streams are prepared
// post: the board is set as designated and the dictionary is imported into a Trie
Boggle::Boggle(std::ifstream &infile1, std::ifstream &infile2)
{
    // Open and load characters into the boggleBoard matrix
    openFile(infile1, BOARD_NAME);

    for (size_t r = 0; r < SIZE; ++r) {
        for (size_t c = 0; c < SIZE; ++c) {
            infile1 >> boggleBoard[r][c];
        }
    }

    // Open and load words into the validWords Trie
    openFile(infile2, DICTIONARY_NAME);

    std::string data;
    while (infile2 >> data) {
        validWords.insert(data);
    }

    // Set bool matrix to false
    for (size_t r = 0; r < SIZE; ++r) {
        for (size_t c = 0; c < SIZE; ++c) {
            visitedBoard[r][c] = false;
        }
    }
}

// Main solving function that recursively finds all words that can be found from a
// starting point
// pre: the board is set as designated and the dictionary is imported; the first
//     call should have word be "", prevR be 0, and prevC be 0
// post: the foundWords Trie should be loaded with all the found words from the
//     starting point
void Boggle::solve(std::string word, size_t nextR, size_t nextC)
{
    if (nextR < 0 || nextR >= SIZE || nextC < 0 || nextC >= SIZE) { // If out of bounds, stop
        return;
    } else if (visitedBoard[nextR][nextC]) { // If it's visited, stop
        return;
    } else if (!validWords.isPrefix(word)) { // If it's not valid, stop
        return;
    }

    visitedBoard[nextR][nextC] = true;
    word += boggleBoard[nextR][nextC];

    // Inserts word if the word is valid (length is at least 4, it's in the dictionary,
    // and is not found yet); with the extra credit, it also checks if the user found the word
    if (word.length() >= 4 && validWords.isWord(word) && !foundWords.isWord(word) &&
            !userFoundWords.isWord(word)) {
        foundWords.insert(word);
    }

    // Solve on all the adjacent points
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            solve(word, nextR + i, nextC + j);
        }
    }

    visitedBoard[nextR][nextC] = false;
}

// Prints out the found words alphabetically and how many words; prints
// different Tries depending on whether userInput is true or false
// pre: true or false is set depending on if the user's information should be printed
// post: if userInput is true, userFoundWords is printed; if userInput is false, foundWords is printed
void Boggle::printFoundWords(bool userInput)
{
    std::string whoFoundWord;
    std::string amountWords;
    if (userInput) {
        whoFoundWord = "user";
        amountWords = std::to_string(userFoundWords.wordCount());
    } else {
        whoFoundWord = "computer";
        amountWords = std::to_string(foundWords.wordCount());
    }

    std::cout << "The " + whoFoundWord + " found the following words:" << std::endl;
    std::cout << "============" << std::endl;

    if (userInput) {
        userFoundWords.print();
    } else {
        foundWords.print();
    }

    std::cout << "============" << std::endl;
    std::cout << "The " + whoFoundWord + " found " + amountWords;
    if (amountWords == "1") {
        std::cout << " word." << std::endl;
    } else {
        std::cout << " words." << std::endl;
    }
}

// Prints the Boggle board to the output
void Boggle::printBoard()
{
    for (size_t r = 0; r < SIZE; ++r) {
        std::cout << std::endl;
        for (size_t c = 0; c < SIZE; ++c) {
            std::cout << boggleBoard[r][c];
        }
    }
    std::cout << std::endl;
    std::cout << "============" << std::endl;
}

// Determines if a word the user entered is legal by validating if it has at least
// 4 characters, is a word in the dictionary, is not already found, and is possible
// on the board
// pre: a valid word (no spaces, all lowercase)
// post: the word is inserted if it meets all criteria
void Boggle::insertIfLegal(std::string word) {
    if (word.length() < 4) {
        std::cout << "Word is invalid. Must be at least 4 characters." << std::endl;
        return;
    } else if (!validWords.isWord(word)) {
        std::cout << "Word is invalid. Not found in the dictionary." << std::endl;
        return;
    } else if (userFoundWords.isWord(word)) {
        std::cout << "Word is invalid. Already found." << std::endl;
        return;
    } else if (!isOnBoard(word, 0, 0)) {
        std::cout << "Word is invalid. Impossible with the given board." << std::endl;
        return;
    }

    std::cout << "Nice! Word is legal." << std::endl;
    userFoundWords.insert(word);
}

// Helper function that opens files for the constructor; throws std::runtime_error if
// file fails to open
// pre: an input stream is prepared as well as a valid file name
// post: the file is open or an error is thrown
void Boggle::openFile(std::ifstream &infile, std::string fileName)
{
    infile.open(fileName);
    if (infile.fail()) {
        std::string msg("Unable to open " + fileName + " for reading.");
        std::cout << msg << std::endl;
        throw std::runtime_error(msg);
    }
}

// Helper function that finds if a word can be found given the current board
// pre: to be called with a valid word (no spaces, all lowercase), curR as 0, and curC as 0
// post: returns true if the word is possible and false otherwise
bool Boggle::isOnBoard(std::string word, size_t curR, size_t curC) {
    // If the point to search is out of bounds, stop
    if (curR < 0 || curR >= SIZE || curC < 0 || curC >= SIZE) {
        return false;
    }

    if (word.at(0) != boggleBoard[curR][curC]) {
        if (curR == SIZE - 1) {
            return isOnBoard(word, 0, curC + 1);
        } else {
            return isOnBoard(word, curR + 1, curC);
        }
    } else if (word.at(0) == boggleBoard[curR][curC]) {
        if (word.length() == 1){
            return true;
        }

        // Check all neighbors
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (isOnBoard(word.substr(1), curR + i, curC + j)) {
                    return true;
                }
            }
        }
    }

    return false;
}
