#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <stdexcept>

int main()
{
    std::ifstream input("p1_input.csv");
    if (!input.is_open())
        throw std::runtime_error("Could not open file");

    std::multiset<int> left;
    std::multiset<int> right;

    std::string line;

    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string leftValue, rightValue;
        if (std::getline(ss, leftValue, ' ') && std::getline(ss, rightValue, ' '))
        {
            int leftVal = std::stoi(leftValue);
            int rightVal = std::stoi(rightValue);
            left.insert(leftVal);
            right.insert(rightVal);
        }
    }

    if (left.size() != right.size())
    {
        std::cerr << "Warning: Left and Right sets are of different sizes!" << std::endl;
    }

    auto leftIt = left.begin();
    auto rightIt = right.begin();
    int distance = 0;
    int total_distance = 0;
    std::cout << "Left\tRight\tDistance" << std::endl;

    while (leftIt != left.end() && rightIt != right.end())
    {
        if (*leftIt > *rightIt)
        {
            distance = *leftIt - *rightIt;
        }
        else
        {
            distance = *rightIt - *leftIt;
        }

        int value = *leftIt;
        std::cout << *leftIt << "\t" << *rightIt << "\t" << distance << std::endl;
        total_distance += distance;
        ++leftIt;
        ++rightIt;
    }

    std::cout << "distance: " << total_distance << std::endl;

    return 0;
}
