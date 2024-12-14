#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <algorithm>

// Function to run the simulation
int run_simulation(std::vector<std::pair<int, int>> position, std::vector<std::pair<int, int>> velocity)
{
    const int width = 101;
    const int height = 103;
    const int time = 100;

    for (int t = 0; t < time; ++t)
    {
        for (size_t i = 0; i < position.size(); ++i)
        {

            position[i].first = (position[i].first + velocity[i].first + width) % width;
            position[i].second = (position[i].second + velocity[i].second + height) % height;
        }
    }

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    int midX = width / 2;
    int midY = height / 2;

    for (const auto &pos : position)
    {
        int x = pos.first;
        int y = pos.second;

        if (x == midX || y == midY)
            continue;

        if (x < midX && y < midY)
            ++q1;
        else if (x > midX && y < midY)
            ++q2;
        else if (x < midX && y > midY)
            ++q3;
        else if (x > midX && y > midY)
            ++q4;
    }

    return q1 * q2 * q3 * q4;
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

    int answer = run_simulation(position, velocity);
    std::cout << "The answer is: " << answer << "\n";

    return 0;
}
