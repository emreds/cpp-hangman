#include <iostream>

bool is_valid(std::string &raw_guess) {
    return ((raw_guess.length() == 1) & (raw_guess[0] >= 'a' && raw_guess[0] <= 'z'));
}

bool is_early_guess(std::string &raw_guess) {
    if ((raw_guess.length() == 1) & (raw_guess[0] == '1')){
        return true;
    }
    return false;
}

char format_char(std::string &raw_guess) {
    char guess = char(tolower(raw_guess[0]));
    return guess;
}
