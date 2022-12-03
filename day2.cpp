#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#define DEBUG_LOCAL 1

#define ROCK_OPP 'A'
#define PAPER_OPP 'B'
#define SCISSORS_OPP 'C'

#define ROCK_ME 'X'
#define PAPER_ME 'Y'
#define SCISSORS_ME 'Z'

#define SHOULD_LOSE 'X'
#define SHOULD_DRAW 'Y'
#define SHOULD_WIN 'Z'

#define WIN_POINTS 6
#define LOST_POINTS 0
#define DRAW_POINTS 3

#define ROCK_POINTS 1
#define PAPER_POINTS 2
#define SCISSORS_POINTS 3

int calc_score(const std::vector<std::pair<char, char>>& inputs) {

    int score = 0, mul = 0;
    for (const auto pair: inputs) {
        switch (pair.second) {
        case ROCK_ME:
            mul = ROCK_POINTS;
            score +=  mul + (pair.first == ROCK_OPP ? DRAW_POINTS : pair.first == SCISSORS_OPP ? WIN_POINTS :  LOST_POINTS);
            break;
        case PAPER_ME:
            mul = PAPER_POINTS;
            score +=  mul + (pair.first == PAPER_OPP ? DRAW_POINTS : pair.first == ROCK_OPP ? WIN_POINTS :  LOST_POINTS);
            break;
        case SCISSORS_ME:
            mul = SCISSORS_POINTS;
            score +=  mul + (pair.first == SCISSORS_OPP ? DRAW_POINTS : pair.first == PAPER_OPP ? WIN_POINTS :  LOST_POINTS);
            break;
        }
    }
    return score;
}

int calc_score_w_predict(const std::vector<std::pair<char, char>>& inputs) {
    int score = 0;
    for (const auto pair: inputs) {
        switch (pair.first) {
        case ROCK_OPP:
            score += 
                pair.second == SHOULD_DRAW ? DRAW_POINTS + ROCK_POINTS : 
                pair.second == SHOULD_WIN ? WIN_POINTS + PAPER_POINTS:  LOST_POINTS + SCISSORS_POINTS;
            break;
        case PAPER_OPP:
            score += 
                pair.second == SHOULD_DRAW ? DRAW_POINTS + PAPER_POINTS : 
                pair.second == SHOULD_WIN ? WIN_POINTS + SCISSORS_POINTS:  LOST_POINTS + ROCK_POINTS;
            break;
        case SCISSORS_OPP:
            score += 
                pair.second == SHOULD_DRAW ? DRAW_POINTS + SCISSORS_POINTS : 
                pair.second == SHOULD_WIN ? WIN_POINTS + ROCK_POINTS:  LOST_POINTS + PAPER_POINTS;
            break;
        }
    }
    return score;
}

int main () {
    std::vector<std::pair<char, char>> inputs;
    int result;
    if (DEBUG_LOCAL) {
        inputs = {
            {'A', 'Y'},
            {'B', 'X'},
            {'C', 'Z'},
        };

        result = calc_score(inputs);
        assert(result == 15);
        result = calc_score_w_predict(inputs);
        assert(result == 12);
        inputs.clear();

    }

    std::ifstream file ("day2.txt");

    if(!file.is_open()) {
        std::cout<<"cannot read file\n";
    }

    for(char a, b; file >> a >> b; ) {
        inputs.push_back({a, b});
    }

    result = calc_score(inputs);

    std::cout<<result<<"\n";

    result = calc_score_w_predict(inputs);
    std::cout<<result<<"\n";



}