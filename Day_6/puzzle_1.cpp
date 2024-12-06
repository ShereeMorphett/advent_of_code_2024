#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream input("day_6_data.txt");

    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::vector<std::string> game_map;

    std::string line;

    while (std::getline(input, line))
    {
        game_map.push_back(line);
    }
    std::cout << "Line count is is: " << game_map.size() << "\n";

    // find the gaurd;
    // path finding algo
    // calculate each move during path algo

    // int answer = calculate_step_number(game_map, gaurd_row, gaurd_col);
    // std::cout << "Completed answer is: " << answer << "\n";

    return 0;
}
