#include <iostream>
#include <vector>
#include <map>
class Game;
class CPU {
	Game& game_;
	std::map<char, int> possible_guesses_;
	std::vector<std::string> possible_words_;
	std::string unspaced_hidden_word_;
	void PrintPossibleGuesses();
	void Update();
public:
	CPU(Game& g);
	bool IsMatch(std::string s);
	void prints();
	std::string MakeGuess();
};
