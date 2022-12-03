#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <unordered_map>

#define DEBUG_LOCAL 1
#define GROUP_SIZE 3

int priority_sum(const std::vector<std::string>& inputs) {
    int sum = 0, mid;
    bool found = false;
    char v;
    for (const std::string& input: inputs) {
        mid = input.size() / 2;
        found = false;
        for (int i = 0; i < mid && !found; ++i) {
            for (int j = mid; j<input.size() && !found; ++j ) {
                if (input[i] == input[j]) {
                    found = true;
                    v = input[i];
                }
            }
        }
        sum+= (v >= 97 && v<= 122) ? v-96 : v-96+32+26;
    }

    return sum;
}

int badge_sum(const std::vector<std::string>& inputs) {
    int sum = 0;

    size_t i = 0;
    std::vector<std::string> group;
    while ( i < inputs.size()) {
        auto start = inputs.begin() + i;
        auto end = inputs.begin() + i +GROUP_SIZE;
      
        group = std::vector<std::string>(start, end);
        std::unordered_map<char, int[GROUP_SIZE]> m;
        for (int i = 0; i < group.size(); ++i) {
            for (int j = 0; j<group[i].size(); j++) {
                m[group[i][j]] [i] ++;
            }
        }
        for (const auto pair: m) {
            int i = 0;
            while (i < GROUP_SIZE && pair.second[i] != 0) ++i;

            if (i == GROUP_SIZE) {
                 sum+= (pair.first >= 97 && pair.first<= 122) ? pair.first-96 : pair.first-96+32+26;
            }
        }
        i+=GROUP_SIZE;
    }

    return sum;
}


int main () {
    std::vector<std::string> inputs;
    int result;
    if (DEBUG_LOCAL) {
        inputs = {
          "vJrwpWtwJgWrhcsFMMfFFhFp",
          "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
          "PmmdzqPrVvPwwTWBwg",
          "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
          "ttgJtRGJQctTZtZT",
          "CrZsJsPPZsGzwwsLwLmpwMDw"
        };

        result = priority_sum(inputs);
        assert(result == 157);
        result = badge_sum(inputs);
        assert(result == 70);
        inputs.clear();

    }

    std::ifstream file ("day3.txt");

    if(!file.is_open()) {
        std::cout<<"cannot read file\n";
    }

    for(std::string s; file >> s; ) {
        inputs.push_back(s);
    }

    result = priority_sum(inputs);
    std::cout<<result<<"\n";
    
    result = badge_sum(inputs);
    std::cout<<result<<"\n";


}