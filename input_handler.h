//
// Created by emred on 29.10.22.
//
#include <iostream>

#ifndef HANGMAN_INPUT_HANDLER_H
#define HANGMAN_INPUT_HANDLER_H

bool is_valid(std::string &raw_guess);
bool is_early_guess(std::string &raw_guess);
char format_char(std::string &raw_guess);

#endif //HANGMAN_INPUT_HANDLER_H
