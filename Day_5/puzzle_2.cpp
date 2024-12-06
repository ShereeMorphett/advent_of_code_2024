#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

// https://en.wikipedia.org/wiki/Topological_sorting

std::vector<int> reorder_update(const std::vector<std::pair<int, int>> &rules, const std::vector<int> &update)
{

    std::unordered_map<int, std::unordered_set<int>> graph;
    for (const auto &[first, second] : rules)
    {
        if (std::find(update.begin(), update.end(), first) != update.end() &&
            std::find(update.begin(), update.end(), second) != update.end())
        {
            graph[first].insert(second);
        }
    }

    std::unordered_map<int, int> in_degree;
    for (const auto &[node, edges] : graph)
    {
        if (in_degree.find(node) == in_degree.end())
            in_degree[node] = 0;

        for (const auto &neighbor : edges)
        {
            in_degree[neighbor]++;
        }
    }

    std::vector<int> sorted_pages;
    std::unordered_set<int> visited;
    for (const auto &page : update)
    {
        if (visited.find(page) == visited.end() && in_degree[page] == 0)
        {
            std::vector<int> stack = {page};
            while (!stack.empty())
            {
                int current = stack.back();
                stack.pop_back();

                if (visited.find(current) == visited.end())
                {
                    sorted_pages.push_back(current);
                    visited.insert(current);

                    for (const auto &neighbor : graph[current])
                    {
                        in_degree[neighbor]--;
                        if (in_degree[neighbor] == 0)
                        {
                            stack.push_back(neighbor);
                        }
                    }
                }
            }
        }
    }

    return sorted_pages;
}

std::vector<int> process_invalid_updates(const std::vector<std::pair<int, int>> &pairs, const std::vector<std::vector<int>> &page_vec)
{
    std::vector<int> reordered_middles;

    for (const auto &update : page_vec)
    {
        bool is_valid = true;

        for (const auto &[first, second] : pairs)
        {
            auto it_first = std::find(update.begin(), update.end(), first);
            auto it_sec = std::find(update.begin(), update.end(), second);

            if (it_first != update.end() && it_sec != update.end())
            {
                if (it_first > it_sec)
                {
                    is_valid = false;
                    break;
                }
            }
        }

        if (!is_valid)
        {
            auto reordered = reorder_update(pairs, update);
            reordered_middles.push_back(reordered[reordered.size() / 2]);
        }
    }

    return reordered_middles;
}

int calculate_answer(std::vector<int> &validated_data)
{
    int answer = 0;
    for (const auto &number : validated_data)
    {
        answer += number;
    }

    return answer;
}

int main()
{
    std::ifstream input("day_5_data.txt");

    if (!input.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::vector<std::pair<int, int>> pairs;

    while (std::getline(input, line))
    {
        if (line.empty())
            break;
        std::istringstream iss(line);
        std::string part1, part2;
        if (std::getline(iss, part1, '|') && std::getline(iss, part2, '|'))
        {
            part1.erase(std::remove(part1.begin(), part1.end(), ' '), part1.end());
            part2.erase(std::remove(part2.begin(), part2.end(), ' '), part2.end());
            int p1 = std::stoi(part1);
            int p2 = std::stoi(part2);
            pairs.emplace_back(p1, p2);
        }
    }

    std::cout << "Total pairs parsed: " << pairs.size() << "\n";

    std::vector<std::vector<int>> page_vec;
    std::vector<int> line_inputs;

    while (std::getline(input, line))
    {
        if (line.empty())
            break;
        std::istringstream iss(line);
        std::string part1;
        while (std::getline(iss, part1, ','))
        {
            int p1 = std::stoi(part1);
            line_inputs.push_back(p1);
        }
        page_vec.push_back(line_inputs);
        line_inputs.clear();
    }

    std::cout << "Total vectors parsed: " << page_vec.size() << "\n";

    auto reordered_middles = process_invalid_updates(pairs, page_vec);
    int answer = calculate_answer(reordered_middles);
    std::cout << "Completed answer is: " << answer << "\n";

    return 0;
}
