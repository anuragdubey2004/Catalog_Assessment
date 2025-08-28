#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
#include "lagrange.hpp"

using json = nlohmann::json;

long long decode_base(const std::string& value, int base) {
    long long result = 0;
    for (char ch : value) {
        int digit = (ch >= '0' && ch <= '9') ? ch - '0' :
                    (ch >= 'a' && ch <= 'z') ? ch - 'a' + 10 : 0;
        result = result * base + digit;
    }
    return result;
}

int main() {
    // Read input JSON
    std::ifstream inFile("input.json");
    json input;
    inFile >> input;

    int n = input["keys"]["n"];
    int k = input["keys"]["k"];
    std::vector<long long> x_arr, y_arr;
    for (int i = 1; i <= n; ++i) {
        std::string idx = std::to_string(i);
        int base = std::stoi((std::string)input[idx]["base"]);
        std::string val = input[idx]["value"];
        x_arr.push_back(i);
        y_arr.push_back(decode_base(val, base));
    }

    
    std::vector<long long> x(x_arr.begin(), x_arr.begin() + k);
    std::vector<long long> y(y_arr.begin(), y_arr.begin() + k);

    double secret = lagrange_interpolate(x, y, 0); 
    std::ofstream outFile("output.txt");
    outFile << "Secret (constant term): " << secret << std::endl;
    outFile.close();

    std::cout << "See output.txt for result.\n";
    return 0;
}
