
#include <vector>
#include <string>

class Reindeer_Vec
{

private:
    std::vector<std::vector<int>> data;

public:
    int find_safe_data();

    void print_vector();
    Reindeer_Vec(std::string file_name);
    ~Reindeer_Vec();
};