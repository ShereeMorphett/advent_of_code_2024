#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

int main()
{
    std::ifstream input("day_3_data.csv");
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::regex mul_regex(R"(mul\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\))");
    int total_sum = 0;

    while (std::getline(input, line))
    {
        std::sregex_iterator begin(line.begin(), line.end(), mul_regex);
        std::sregex_iterator end;

        // Iterate through all matches in the line
        for (auto it = begin; it != end; ++it)
        {
            int a = std::stoi((*it)[1].str());
            int b = std::stoi((*it)[2].str());
            total_sum += a * b;
        }
    }

    std::cout << "Total sum of all valid mul instructions: " << total_sum << std::endl;

    return 0;
}
