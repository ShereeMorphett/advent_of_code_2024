#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/*

This word search allows words to be horizontal, vertical, diagonal, written backwards,
or even overlapping other words. It's a little unusual, though, as you don't merely need to find one
instance of XMAS - you need to find all of them. Here are a few ways XMAS might appear, where irrelevant
characters have been replaced with .:

..X...
.SAMX.
.A..A.
XMAS.S
.X....

The actual word search will be full of letters instead. For example:

MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX

In this word search, XMAS occurs a total of 18 times; here's the same word search again, but where letters not involved in any XMAS have been replaced with .:

....XXMAS.
.SAMXMS...
...S..A...
..A.A.MS.X
XMASAMX.MM
X.....XA.A
S.S.S.S.SS
.A.A.A.A.A
..M.M.M.MM
.X.X.XMASX

Take a look at the little Elf's word search. How many times does XMAS appear?*/
int horizontal_check(const std::vector<std::string> &input, const std::string &key)
{
    int found = 0;

    for (const auto &str : input)
    {
        for (size_t i = 0; i <= str.size() - key.size(); ++i)
        {
            if (str.substr(i, key.size()) == key)
            {
                found++;
            }
        }
    }

    return found;
}

int vertical_check(std::vector<std::string> input, std::string key)
{
    int found = 0;
    size_t rows = input.size();
    if (rows == 0)
        return 0;
    size_t cols = input[0].size();

    for (size_t col = 0; col < cols; ++col)
    {
        for (size_t row = 0; row <= rows - key.size(); ++row)
        {
            bool match = true;
            for (size_t k = 0; k < key.size(); ++k)
            {
                if (input[row + k][col] != key[k])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found++;
            }
        }
    }

    return found;
}

int diagonal_check(std::vector<std::string> input, std::string key)
{
    int found = 0;

    size_t rows = input.size();
    if (rows == 0)
        return 0;
    size_t cols = input[0].size();

    // top left - bottom right

    for (size_t row = 0; row <= rows - key.size(); ++row)
    {
        for (size_t col = 0; col <= cols - key.size(); ++col)
        {
            bool match = true;
            for (size_t k = 0; k < key.size(); ++k)
            {
                if (input[row + k][col + k] != key[k])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found++;
            }
        }
    }
    // top right - bottom left
    for (size_t row = 0; row <= rows - key.size(); ++row)
    {
        for (size_t col = key.size() - 1; col < cols; ++col)
        {
            bool match = true;
            for (size_t k = 0; k < key.size(); ++k)
            {
                if (input[row + k][col - k] != key[k])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found++;
            }
        }
    }

    return found;
}

int main()
{
    std::ifstream input("day_4_data.txt");
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    std::vector<std::string> input_vec;
    int total_sum = 0;
    while (std::getline(input, line))
    {
        input_vec.push_back(line);
    }

    total_sum += horizontal_check(input_vec, "XMAS");
    total_sum += vertical_check(input_vec, "XMAS");
    total_sum += diagonal_check(input_vec, "XMAS");

    total_sum += horizontal_check(input_vec, "SAMX");
    total_sum += vertical_check(input_vec, "SAMX");
    total_sum += diagonal_check(input_vec, "SAMX");

    std::cout << "Total sum of all valid mul instructions: " << total_sum << std::endl;

    return 0;
}
