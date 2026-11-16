#include "Algorithms.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<std::string> reads = {
        "ATCGG",
        "CGGTA",
        "GTACC"
    };
    const std::string target = "CGGTA";

    const std::size_t position = linearSearch(reads, target);

    if (position < reads.size()) {
        std::cout << "Read " << target << " found at index "
                  << position << ".\n";
    } else {
        std::cout << "Read " << target << " was not found.\n";
    }

    return 0;
}
