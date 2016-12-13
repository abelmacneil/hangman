#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "game.hpp"
#include "cpu.hpp"
using namespace std;
void CPU::PrintPossibleGuesses() {

    map<char,int>::iterator iter;
    for(iter = possible_guesses_.begin();
        iter != possible_guesses_.end();
        iter++){
        cout << iter->first << ":" << iter->second << endl;
    }

}
CPU::CPU(Game &g):game_(g) {
    vector<string>::iterator iter;
    vector<string> tmp_words = g.words();		

    unspaced_hidden_word_ = g.hidden_word();
    unspaced_hidden_word_.erase(remove_if(unspaced_hidden_word_ .begin(),			unspaced_hidden_word_.end(), ::isspace),unspaced_hidden_word_.end());

    for(iter = tmp_words.begin();
        iter != tmp_words.end();
        iter++) {
        if(iter->length() == g.word_length()){
            possible_words_.push_back(*iter);
            for(int i = 0; i < iter->length(); i++){
                if(possible_guesses_.find(iter->at(i)) ==
                   possible_guesses_.end()){
                    possible_guesses_[iter->at(i)] = 1;
                } else {
                    possible_guesses_[iter->at(i)]+= 1;
                }
            }
        }
    }
    //PrintPossibleGuesses();
}
string CharToString(char c){
    stringstream ss;
    ss << c;
    return ss.str();

}
void CPU::Update (){
    vector<string>::iterator iter;
    vector<string> tmp_words(possible_words_);
    possible_words_.clear();
    vector<string> used_guesses(game_.good_guesses());
    for(int i = 0; i < game_.bad_guesses().size(); i++)
        used_guesses.push_back(game_.bad_guesses().at(i));

    unspaced_hidden_word_ = game_.hidden_word();
    unspaced_hidden_word_.erase(remove_if(unspaced_hidden_word_ .begin(),			unspaced_hidden_word_.end(), ::isspace),unspaced_hidden_word_.end());

    possible_guesses_.clear();
    for(iter = tmp_words.begin();
        iter != tmp_words.end();
        iter++) {
        if(IsMatch(*iter)){
            possible_words_.push_back(*iter);
            for(int i = 0; i < iter->length(); i++){
                if(find(used_guesses.begin(), used_guesses.end(),
                        CharToString(iter->at(i))) == used_guesses.end()){
                    if(possible_guesses_.find(iter->at(i)) == 
                       possible_guesses_.end()){
                        possible_guesses_[iter->at(i)] = 1;
                    } else {
                        possible_guesses_[iter->at(i)]+= 1;
                    }
                }
            }
        }
    }
    cout << possible_words_.size() << endl;
    //PrintPossibleGuesses();
}

bool CPU::IsMatch(string word){

    for(int i = 0; i < word.length(); i++) {
        if(unspaced_hidden_word_[i] != '_' && 
           unspaced_hidden_word_[i] != word[i]) {
            return false;
        }
    }
    vector<string>& bad_guesses = game_.bad_guesses();
    vector<string>::iterator iter;
    for(iter = bad_guesses.begin(); 
        iter != bad_guesses.end();
        iter++) {
        for(int j = 0; j < word.length(); j++) {
            if(iter->size() == 1 && iter->at(0) == word[j]) {
                return false;
            }
        }
    }
    return true;
}
string CPU::MakeGuess(){
    Update();
    if(possible_words_.size() == 1) {
        return possible_words_[0];
    }
    map<char,int>::iterator iter;
    char guess_char = ' ';
    int max_freq = -1;
    for(iter = possible_guesses_.begin();
        iter != possible_guesses_.end();
        iter++){
        if (iter->second > max_freq){
            guess_char = iter->first;
            max_freq = iter->second;
        }
    }
    string guess (1, guess_char);
    return guess;
}

void CPU::prints() {

    cout << game_.hidden_word()<<endl;
}
