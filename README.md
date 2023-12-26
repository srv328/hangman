# Hangman Game

This Hangman game allows users to guess words from different categories. The program reads words and categories from a file and prompts users to select a category and guess the hidden word.

## Overview

The Hangman game consists of the following key components:

### File Reading
- `readWordsFile(const std::string& file_name)`: Reads words and categories from a file and stores them in a `std::map`.

### Gameplay Functions
- `selectCategory(const std::map<std::string, std::vector<std::string>>& categories)`: Allows users to choose a category from the available list.
- `getGuess()`: Takes user input for guessing a letter.
- `checkGuess(const std::string& word, char guess)`: Checks if the guessed letter is present in the word.

### Game Loop
- `playHangman(const std::string& file_name)`: Manages the game loop, including category selection, word selection, and user input. Displays game progress and results.

## Usage

### Input File Format
- The input file should have categories and corresponding words listed, separated by a colon.
- Example: 
    ```
    Animals: cat dog elephant
    Countries: italy japan brazil
    ```

### How to Run
- Compile and run the program.
- The game will prompt you to select a category and start guessing letters to uncover the hidden word.
- The player has a limited number of attempts to guess the word correctly.

## How to Contribute
- Feel free to fork this repository and contribute improvements or additional features to the game.
