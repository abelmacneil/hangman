#include "game.hpp"
#include "cpu.hpp"
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
string VectorToString(vector<string>& v)
{
    stringstream s;
    s << "[";
    for (int i = 0; i < v.size(); i++){
        s << v[i];
        if (i != v.size() - 1)
            s << ",";
    }
    s << "]";
    return s.str();

}
int main(int argc, char **argv)
{
    bool hascpu = false;
    if (argc == 2) {
        if (string(argv[1]) == "cpu") {
            hascpu = true;
        } 
    }
    Game g ("");
    CPU cpu (g);
    string guess;
    //if (hascpu)
        cout << g.hidden_word();
    while (!(g.HasWon() || g.HasLost())) {
            cout << " ";
        if (hascpu) {
            guess = cpu.MakeGuess();
        } else {
            cin >> guess;
            //cout << "\n";
        }

        cout << g.MakeGuess(guess);
        cout << VectorToString(g.bad_guesses());
    }
    cout << endl;
    if(g.HasLost()) {
        cout << "You lost!" << endl;
    } else {
        cout << "You won!" << endl;
    }
}
