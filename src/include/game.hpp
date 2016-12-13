#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <vector>


class Game {
	std::string word_to_guess_;
	std::string hidden_word_;
	std::vector<std::string> good_guesses_;
	std::vector<std::string> bad_guesses_;
	std::vector<std::string> words_;
public:
	Game(std::string word);
	//Game(){};
	std::string hidden_word();
	std::string MakeGuess(std::string guess);
	bool HasWon();
	bool HasLost();
	std::vector<std::string>& bad_guesses();
	std::vector<std::string>& good_guesses();
	std::vector<std::string>& words();
	int word_length();
};
#endif
