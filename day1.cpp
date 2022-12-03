#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cassert>

#define DEBUG_LOCAL 1
#define BUFFER_SIZE 32

std::ostream& print_vector(const std::vector<const char*>& input, std::ostream& out) {
    for (const auto i: input) {
        out<<i<<std::endl;
    }
    return out;
} 

int find_max_calories(const std::vector<const char*>& inputs) {
    std::unordered_map<int, int> scores = {
        {0, 0}
    };
   
    for (int i = 0, j = 0; i< inputs.size(); ++i) {
        if (!strcmp(inputs[i], "")) {
            j++;
            scores[j] = 0;
        } else {
            scores[j] += atoi(inputs[i]);
        }
    }
    int max = 0;
    for (const auto score: scores) {
        max = std::max(max, score.second);
    }

    return max;
}

int find_top_tree_calories(const std::vector<const char*>& inputs) {
    std::unordered_map<int, int> scores = {
        {0, 0}
    };
   
    for (int i = 0, j = 0; i< inputs.size(); ++i) {
        if (!strcmp(inputs[i], "")) {
            j++;
            scores[j] = 0;
        } else {
            scores[j] += atoi(inputs[i]);
        }
    }

    int max = 0, max_key = 0, sum = 0;
    for (int i = 0; i < 3; ++i) {
        for (const auto score: scores) {
            if (max <= score.second) {
                max = score.second;
                max_key = score.first;
            }
        }
        scores.erase(max_key);
        sum += max;
        max = 0;
    }

    return sum;

}

int main () {
    std::vector<const char*> inputs;
    int result;
    if (DEBUG_LOCAL) {
        inputs = {
            "1000",
            "2000",
            "3000",
            "",
            "4000",
            "",
            "5000",
            "6000",
            "",
            "7000",
            "8000",
            "9000",
            "",
            "10000"
        };

        result = find_max_calories(inputs);
        assert(result == 24000);
        result = find_top_tree_calories(inputs);
        assert(result == 45000);

        inputs.clear();

    }

    std::ifstream file ("day1.txt");

    if(!file.is_open()) {
        std::cout<<"cannot read file\n";
    }

    for( std::string line; std::getline(file, line ); ) {
        inputs.push_back(strdup(line.c_str()));
    }

    result = find_max_calories(inputs);

    std::cout<<result<<std::endl;

    result = find_top_tree_calories(inputs);
    std::cout<<result<<std::endl;


}