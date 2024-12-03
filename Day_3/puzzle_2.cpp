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
    std::regex command_regex(R"(do\(\)|don't\(\)|mul\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\))");

    bool is_enabled = true;
    int total_sum = 0;

    while (std::getline(input, line))
    {
        std::sregex_iterator begin(line.begin(), line.end(), command_regex);
        std::sregex_iterator end;

        for (auto it = begin; it != end; ++it)
        {
            std::string match = (*it).str();

            if (match == "do()")
            {
                is_enabled = true;
                std::cout << "do() found. Mul instructions enabled." << std::endl;
            }
            else if (match == "don't()")
            {
                is_enabled = false;
                std::cout << "don't() found. Mul instructions disabled." << std::endl;
            }
            else
            {
                if (is_enabled)
                {
                    int a = std::stoi((*it)[1].str());
                    int b = std::stoi((*it)[2].str());
                    total_sum += a * b;

                    std::cout << "Processing mul(" << a << ", " << b << "). Result: " << a * b << std::endl;
                }
                else
                {
                    std::cout << "Skipping mul() as instructions are disabled." << std::endl;
                }
            }
        }
    }

    std::cout << "Total sum of all enabled mul instructions: " << total_sum << std::endl;

    return 0;
}
