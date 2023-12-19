# boggle

Allows user to play a game of Boggle ("Word Hunt") on a 4x4 grid. Upon entering all words the user can find, the computer responds by finding the rest of the words that were possible on the board using the official Scrabble dictionary.

Utilizes a trie as the primary data structure (Trie.h, Trie.cpp, TrieNode.h, and TrieNode.cpp) to load and validate words.

BoggleDriver.cpp deploys the Boggle class (Boggle.h and Boggle.cpp) in order to abstract the game into a more readable, digestible parts. This file prompts the user for input and then returns with the computer's response. BoggleDriver.cpp requires the "ospd.txt" (Official Scrabble Players Dictionary) as the source to import all recognizable words. It also requires a board which should be named "boggle-in.txt." The board file should have four characters on each line for four lines.
