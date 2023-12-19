// File Name: BoggleDriver.cpp
// Author: trietruo
// Description: Driver utilizing the Boggle class to play a game of Boggle; prompts user
//     for inputs and the computer solves the rest of the words the user did not find
// Last Changed: 4.24.2023

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "Boggle.h"


int main() {
    // Open both the board and dictionary file
    std::ifstream infile1;
    std::ifstream infile2;
    Boggle boggleGame(infile1, infile2);

    // Prompt user to enter words
    boggleGame.printBoard();
    std::cout << "Enter as many words as you can! Enter \"q\" to quit." << std::endl;

    std::string userWord;
    std::cin >> userWord;
    while (userWord != "q" || userWord != "Q") {
        if (userWord == "q" || userWord == "Q") {
            break;
        }

        boggleGame.insertIfLegal(userWord);
        std::cin >> userWord;
    }

    // Prints the words the user found
    std::cout << std::endl;
    boggleGame.printFoundWords(true);
    std::cout << std::endl;

    // Solve for the words from each square on the board
    for (size_t r = 0; r < SIZE; ++r) {
        for (size_t c = 0; c < SIZE; ++c) {
            boggleGame.solve("", r, c);
        }
    }

    // Print out all computer-found words the user did not find
    boggleGame.printFoundWords(false);

    return 0;
}
