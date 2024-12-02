

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Reindeer_Vec.hpp"
#include <limits.h>

bool is_increasing(std::vector<int> const &data)
{
    for (size_t i = 1; i < data.size(); ++i)
    {
        int difference = data[i] - data[i - 1];
        if (data[i] <= data[i - 1] || difference < 1 || difference > 3)
        {
            return false;
        }
    }
    return true;
}

bool is_decreasing(std::vector<int> const &data)
{
    for (size_t i = 1; i < data.size(); ++i)
    {
        int difference = data[i - 1] - data[i];
        if (data[i] >= data[i - 1] || difference < 1 || difference > 3)
        {
            return false;
        }
    }
    return true;
}

bool is_safe_with_removal(std::vector<int> const &data)
{
    if (is_increasing(data) || is_decreasing(data))
    {
        return true;
    }

    for (size_t i = 0; i < data.size(); ++i)
    {
        std::vector<int> modified_data = data;
        modified_data.erase(modified_data.begin() + i);
        if (is_increasing(modified_data) || is_decreasing(modified_data))
        {
            return true;
        }
    }

    return false;
}

int Reindeer_Vec::find_safe_data()
{
    int safe_count = 0;
    for (const auto &report : data)
    {
        if (is_safe_with_removal(report))
        {
            safe_count++;
        }
    }
    return safe_count;
}

void Reindeer_Vec::print_vector()
{
    for (const auto &outer : data)
    {
        for (auto i : outer)
            std::cout << i << " ";
        std::cout << "\n";
    }
}

Reindeer_Vec::Reindeer_Vec(std::string file_name)
{
    std::ifstream input(file_name);
    if (!input.is_open())
        throw std::runtime_error("Could not open file");

    std::string line;
    int value;
    std::vector<int> internal_data;

    while (std::getline(input, line))
    {
        std::stringstream ss(line);

        while (ss >> value)
        {
            internal_data.push_back(value);
        }
        data.push_back(internal_data);
        internal_data.clear();
    }
}

Reindeer_Vec::~Reindeer_Vec()
{
}