#include "game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

Game::Game(string word){
    ifstream dict_file ("dict.txt");
    string tmp;
    while (!dict_file.eof()) {
        getline(dict_file,tmp);
        words_.push_back(tmp);
    }
    srand(time(NULL));
    word_to_guess_ = words_[rand() % words_.size()];
    //cout << word_to_guess_ << endl;
    stringstream s;	
    for (int i = 0; i < word_to_guess_.length(); i++) {
        s << "_ ";	
    }
    hidden_word_ = s.str();
}
string Game::hidden_word(){
    return hidden_word_;
}
string Game::MakeGuess(string guess){
    stringstream s;
    //if they guess the word
    if(guess.length() > 1) {
        if(guess == word_to_guess_){
            hidden_word_ = word_to_guess_;
            for(int i = 0; i < hidden_word_.length(); i++)
                s << hidden_word_[i] << " ";
            hidden_word_ = s.str();
        }else {
            bad_guesses_.push_back(guess);

        }
        return hidden_word_;
    }
    string dup = hidden_word_;
    hidden_word_.erase(
        remove_if(hidden_word_.begin(), hidden_word_.end(), ::isspace),
                       hidden_word_.end());
    for(int i = 0; i < word_to_guess_.length(); i++){
        if (guess[0] == word_to_guess_[i]){
            s << guess[0] << " ";
        } else {
            s << hidden_word_[i] << " ";
        }
    }
    if (dup == s.str()) {
        bad_guesses_.push_back(guess);
    }else {
        good_guesses_.push_back(guess);
    }
    hidden_word_ = s.str();
    return hidden_word_;
}
bool Game::HasWon() {
    string dup = hidden_word_;
    dup.erase(remove_if(dup.begin(),dup.end(), ::isspace),dup.end());
    return dup == word_to_guess_;
}
bool Game::HasLost(){
    return bad_guesses_.size() >= 7;
}

vector<string>& Game::bad_guesses(){
    return bad_guesses_;
}
vector<string>& Game::good_guesses(){
    return good_guesses_;
}

vector<string>& Game::words() {
    return words_;
}
int Game::word_length(){
    return word_to_guess_.length();
}
