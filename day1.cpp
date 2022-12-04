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
    int max_sum = 0, acc = 0;
    for (int i = 0; i< inputs.size(); ++i) {
        if (!strcmp(inputs[i], "")) {
            max_sum =  std::max(max_sum, acc);
            acc = 0;
        } else {
            acc+=atoi(inputs[i]);
        }
    }
   
    return max_sum;
}

int find_top_tree_calories(const std::vector<const char*>& inputs) {
    int max_sum1 = 0, max_sum2= 0, max_sum3 = 0, acc = 0, tmp;

    for (const char* input: inputs) {
        if (!strcmp(input, "")) {
            if (acc > max_sum1) {
                tmp = max_sum2;
                max_sum2 = max_sum1;
                max_sum3 = tmp; 
                max_sum1 = acc;
            } else if (acc < max_sum1 && acc > max_sum2) {
                max_sum3 = max_sum2;
                max_sum2 = acc;
            } else if (acc < max_sum2 && acc > max_sum3) {
                max_sum3 = acc;
            }
            acc = 0;
        } else {
            acc+=atoi(input);
        }
    }

    if (acc > max_sum1) {
        tmp = max_sum2;
        max_sum2 = max_sum1;
        max_sum3 = tmp; 
        max_sum1 = acc;
    } else if (acc < max_sum1 && acc > max_sum2) {
        max_sum3 = max_sum2;
        max_sum2 = acc;
    } else if (acc < max_sum2 && acc > max_sum3) {
        max_sum3 = acc;
    }

    return max_sum1 + max_sum2 +  max_sum3;

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