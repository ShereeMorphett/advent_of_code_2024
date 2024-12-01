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
    int similarity_score = 0;
    int value = 0;

    while (leftIt != left.end() && rightIt != right.end())
    {

        int value = *leftIt;
        std::cout << *leftIt << "\t" << *rightIt << "\t" << "count: " << right.count(value) << std::endl;
        similarity_score += (*leftIt * right.count(value));
        ++leftIt;
        ++rightIt;
    }

    std::cout << "similarity_score: " << similarity_score << std::endl;

    return 0;
}
