#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int count_xmas_patterns(const std::vector<std::string> &grid)
{
    int count = 0;
    size_t rows = grid.size();
    size_t cols = rows > 0 ? grid[0].size() : 0;

    for (size_t row = 1; row < rows - 1; ++row)
    {
        for (size_t col = 1; col < cols - 1; ++col)
        {
            if (grid[row][col] != 'A')
                continue;

            std::string topLeft = {grid[row - 1][col - 1], grid[row][col], grid[row + 1][col + 1]};
            std::string topRight = {grid[row - 1][col + 1], grid[row][col], grid[row + 1][col - 1]};

            if ((topLeft == "MAS" || topLeft == "SAM") && (topRight == "MAS" || topRight == "SAM"))
            {
                ++count;
            }
        }
    }

    return count;
}

int main()
{
    std::ifstream input("day_4_data.txt");
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(input, line))
    {
        grid.push_back(line);
    }

    int total_count = count_xmas_patterns(grid);

    std::cout << "Total X-MAS patterns found: " << total_count << std::endl;

    return 0;
}
