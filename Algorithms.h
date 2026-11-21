#pragma once

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

// Kthen indeksin e read-it nëse gjendet; përndryshe kthen reads.size().
size_t linearSearch(const vector<string>& reads,
    const string& target);