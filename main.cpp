#include <iostream>
#include <fstream>
#include <vector>

#include "parameters.h"
#include "input_handler.h"

int fill_corrects(int riddle_length,
                  char guess,
                  std::string &riddle,
                  std::string &word_placeholder) {

    int correct_count = 0;
    for (int i = 0; i < riddle_length; ++i) {
        if (guess == riddle[i]) {
            word_placeholder[i] = guess;
            ++correct_count;
        }
    }

    return correct_count;
}


int get_random_index(int list_size) {
    srand(time(nullptr));
    int rand_index = rand() % list_size;

    return rand_index;
}

bool get_word_list(std::vector<std::string> &word_list, std::string &list_name) {

    std::ifstream word_list_file(list_name);
    if (!word_list_file) {
        std::cerr << "Cannot open the file: " << list_name << std::endl;
        return false;
    }
    std::string word;

    while (getline(word_list_file, word)) {
        if (!word.empty()) {
            word_list.push_back(word);
        }
    }

    return true;
}

int main() {
    // Debugger runs from the debug folder.
    // While debugging change the path into `../word_list.txt`.
    std::string list_name{"../word_list.txt"};
    std::vector<std::string> word_list;
    get_word_list(word_list, list_name);
    int list_size = word_list.size();
    int rand_index = get_random_index(list_size);
    std::string riddle = word_list[rand_index];
    int riddle_length = riddle.length();
    std::cout << "You have a riddle with " << riddle_length << " letters." << std::endl;

    std::string word_placeholder = std::string(riddle_length, '_');
    std::cout << word_placeholder << std::endl;

    int guess_count = 0;
    char old_guesses[GUESS_LIMIT]{};
    std::string raw_guess;
    bool winner = false;
    std::cout << "Please enter the first character," << std::endl;
    std::cout << "When you would like to guess the whole word, please enter `1`" << std::endl;
    while (guess_count < GUESS_LIMIT) {
        std::cin.clear();
        std::cin >> raw_guess;
        if (is_early_guess(raw_guess)){
            std::string whole_guess;
            std::cout << "Please enter your guess for the word," << std::endl;
            std::cin >> whole_guess;
            if (whole_guess == riddle){
                std::cout<< "Your guess was correct congratulations!" << std::endl;
                winner = true;
                break;
            } else {
                std::cout << "Your guess was not correct :(" << std::endl;
                std::cout << "Now you are closer to lose..." <<std::endl;
                ++guess_count;
                continue;
            }
        }

        if (!is_valid(raw_guess)) {
            std::cout << "Please enter a valid character" << std::endl;
            continue;
        }

        char guess = format_char(raw_guess);
        old_guesses[guess_count] = guess;
        std::cout << "The character you have entered is: " << guess << std::endl;

        int correct_count = fill_corrects(riddle_length, guess, riddle, word_placeholder);
        ++guess_count;
        std::cout << "There are " << correct_count << ' ' << guess << "(s) in the word." << std::endl;
        std::cout << "This is how the riddle looks like after your guess:" << std::endl;
        std::cout << word_placeholder << std::endl;

        if (word_placeholder == riddle) {
            std::cout << "You Won!" << std::endl;
            winner = true;
            break;
        }
        std::cout << "Previously entered characters are:" << std::endl << old_guesses << std::endl;
        std::cout << "Please enter the next character" << std::endl;
    }
    // TODO: Add difficulty levels to the game.

    if (not winner) {
        std::cout << "You Lose :(" << std::endl;
        std::cout << "The answer was:" << riddle << std::endl;
    }

    return 0;
}


