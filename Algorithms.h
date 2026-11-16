#pragma once

#include <cstddef>
#include <string>
#include <vector>

// Kthen indeksin e read-it nëse gjendet; përndryshe kthen reads.size().
std::size_t linearSearch(const std::vector<std::string>& reads,
                         const std::string& target);
