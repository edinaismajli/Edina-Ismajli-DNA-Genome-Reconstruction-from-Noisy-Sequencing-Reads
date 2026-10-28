#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

std::size_t linearSearch(const std::vector<std::string>& reads,
                         const std::string& target) {
    for (std::size_t i = 0; i < reads.size(); ++i) {
        if (reads[i] == target) {
            return i;
        }
    }

    return reads.size();
}

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
