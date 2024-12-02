
#include "Reindeer_Vec.hpp"
#include <iostream>

// --- Part Two ---

// The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate
// a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

// Now, the same rules apply as before, except if removing a single level from an unsafe report
// would make it safe, the report instead counts as safe.

// More of the above example's reports are now safe:

//     7 6 4 2 1: Safe without removing any level.
//     1 2 7 8 9: Unsafe regardless of which level is removed.
//     9 7 6 2 1: Unsafe regardless of which level is removed.
//     1 3 2 4 5: Safe by removing the second level, 3.
//     8 6 4 4 1: Safe by removing the third level, 4.
//     1 3 6 7 9: Safe without removing any level.

// Thanks to the Problem Dampener, 4 reports are actually safe!

// Update your analysis by handling situations where the Problem Dampener can remove a single level from unsafe reports.
// How many reports are now safe?

int main()
{
    std::string file_input = "day_2_data.csv";
    Reindeer_Vec input(file_input);

    std::cout << input.find_safe_data() << std::endl;

    return 0;
}