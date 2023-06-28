cmake_minimum_required(VERSION 3.23)
project(Hangman)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hangman main.cpp input_handler.cpp input_handler.h parameters.h)
