#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <cstdlib>

std::map<std::string, std::vector<std::string>> readWordsFile(const std::string& file_name) {
    std::map<std::string, std::vector<std::string>> wordsMap;
    std::ifstream file(file_name);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                std::string category = line.substr(0, pos);
                std::string words = line.substr(pos + 1);

                std::istringstream wordStream(words);
                std::string word;
                std::vector<std::string> categoryWords;

                while (wordStream >> word) {
                    categoryWords.push_back(word);
                }

                wordsMap[category] = categoryWords;
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
    return wordsMap;
}


void displayHangman(const std::string& file_name) {
    std::ifstream file(file_name);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Ошибка чтения файла: " << file_name << std::endl;
    }
}

char getGuess() {
    std::cout << "Введите букву: ";
    std::string input;
    std::getline(std::cin, input);

    while (input.length() != 1 || !std::isalpha(input[0])) {
        std::cout << "Пожалуйста, введите одну букву: ";
        std::getline(std::cin, input);
    }

    return std::tolower(input[0]);
}


bool checkGuess(const std::string& word, char guess) {
    for (char letter : word) {
        if (std::tolower(letter) == std::tolower(guess)) {
            return true; // Буква угадана
        }
    }
    return false; // Буква не угадана
}   

void displayWord(const std::string& word, const std::vector<char>& guessedLetters) {
    for (char letter : word) {
        if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
            std::cout << letter << " ";
        }
        else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

std::string selectCategory(const std::map<std::string, std::vector<std::string>>& categories) {
    std::cout << "Выберите категорию:" << std::endl;
    int index = 1;

    for (const auto& category : categories) {
        std::cout << index << ". " << category.first << std::endl;
        index++;
    }

    int choice;
    std::string input;
    std::getline(std::cin, input);

    try {
        choice = std::stoi(input);

        if (choice >= 1 && choice <= categories.size()) {
            index = 1;
            for (const auto& category : categories) {
                if (index == choice) {
                    return category.first;
                }
                index++;
            }
        }
        else {
            std::cout << "Некорректный выбор категории. Попробуйте снова." << std::endl;
            return "";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Некорректный выбор категории. Попробуйте снова." << std::endl;
        return ""; 
    }

    return ""; 
}

void playHangman(const std::string& file_name) {
    std::map<std::string, std::vector<std::string>> result = readWordsFile(file_name);
    std::string category;
    while (category.empty()) {
        category = selectCategory(result);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distr(0, result[category].size() - 1);
    size_t randomWordIndex = distr(gen);
    std::string randomWord = result[category][randomWordIndex];

    std::vector<char> guessedLetters;
    int maxAttempts = 7;
    int attempts = 1;
    system("cls");
    std::cout << "Категория: " << category << std::endl;
    displayHangman(std::to_string(attempts) + ".txt");
    displayWord(randomWord, guessedLetters);
    while (true) {

        char guessedLetter = getGuess();
        bool isGuessed = checkGuess(randomWord, guessedLetter);
        if (isGuessed) {
            guessedLetters.push_back(guessedLetter);
            std::cout << "Буква '" << guessedLetter << "' есть в слове!" << std::endl;
            std::cout << "Категория: " << category << std::endl;
            displayHangman(std::to_string(attempts) + ".txt");
        }
        else {
            std::cout << "Буквы '" << guessedLetter << "' нет в слове." << std::endl;
            attempts++;
            std::cout << "Категория: " << category << std::endl;
            displayHangman(std::to_string(attempts) + ".txt");
        }

        displayWord(randomWord, guessedLetters);

        bool allGuessed = true;
        for (char letter : randomWord) {
            if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) == guessedLetters.end()) {
                allGuessed = false;
                break;
            }
        }

        if (allGuessed) {
            std::cout << "Поздравляем! Вы угадали слово: " << randomWord << std::endl;
            break;
        }

        if (attempts >= maxAttempts) {
            displayHangman(std::to_string(attempts) + ".txt");
            displayWord(randomWord, guessedLetters);
            std::cout << "Вы проиграли! Загаданное слово было: " << randomWord << std::endl;
            break;
        }
        
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string file_name = "words.txt";
    playHangman(file_name);
    return 0;
}