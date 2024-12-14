#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <limits>

std::pair<int, int> get_bounding_box(const std::vector<std::pair<int, int>>& positions)
{
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (const auto& pos : positions)
    {
        minX = std::min(minX, pos.first);
        maxX = std::max(maxX, pos.first);
        minY = std::min(minY, pos.second);
        maxY = std::max(maxY, pos.second);
    }

    return {maxX - minX + 1, maxY - minY + 1};
}

int find_easter_egg(std::vector<std::pair<int, int>> position, std::vector<std::pair<int, int>> velocity)
{
    const int maxTime = 100000;
    int bestTime = 0;
    int smallestArea = std::numeric_limits<int>::max();

    for (int t = 0; t < maxTime; ++t)
    {
        auto [width, height] = get_bounding_box(position);
        int area = width * height;

        if (area < smallestArea)
        {
            smallestArea = area;
            bestTime = t;
        }

        if (t > 0 && area > smallestArea)
            break;


        for (size_t i = 0; i < position.size(); ++i)
        {
            position[i].first += velocity[i].first;
            position[i].second += velocity[i].second;
        }
    }

    return bestTime;
}


void display_positions(const std::vector<std::pair<int, int>>& positions)
{
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (const auto& pos : positions)
    {
        minX = std::min(minX, pos.first);
        maxX = std::max(maxX, pos.first);
        minY = std::min(minY, pos.second);
        maxY = std::max(maxY, pos.second);
    }

    std::vector<std::string> grid(maxY - minY + 1, std::string(maxX - minX + 1, '.'));

    for (const auto& pos : positions)
    {
        grid[pos.second - minY][pos.first - minX] = '#';
    }

    for (const auto& row : grid)
    {
        std::cout << row << '\n';
    }
}

int main()
{
    std::ifstream input("day_14_data.txt");

    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::vector<std::pair<int, int>> position;
    std::vector<std::pair<int, int>> velocity;
    std::string line;

    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string pPart, vPart;

        if (std::getline(ss, pPart, ' ') && std::getline(ss, vPart, ' '))
        {
            int px, py, vx, vy;

            if (pPart.size() > 2 && pPart.substr(0, 2) == "p=")
            {
                std::stringstream ps(pPart.substr(2));
                char comma;
                ps >> px >> comma >> py;
            }

            if (vPart.size() > 2 && vPart.substr(0, 2) == "v=")
            {
                std::stringstream vs(vPart.substr(2));
                char comma;
                vs >> vx >> comma >> vy;
            }
            position.emplace_back(px, py);
            velocity.emplace_back(vx, vy);
        }
    }

    if (position.size() != velocity.size())
    {
        std::cerr << "Warning: position and velocity sets are of different sizes!" << std::endl;
    }

    int time = find_easter_egg(position, velocity);

    for (int t = 0; t < time; ++t)
    {
        for (size_t i = 0; i < position.size(); ++i)
        {
            position[i].first += velocity[i].first;
            position[i].second += velocity[i].second;
        }
    }

    std::cout << "The fewest number of seconds is: " << time << "\n";
    std::cout << "The positions at this time step are:\n";
    display_positions(position);

    return 0;
}
