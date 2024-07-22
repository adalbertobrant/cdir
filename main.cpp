#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "utils.h" // Include the utils.h file

using namespace std;

int main() {
  vector<pair<unsigned int, unsigned int>> ranges;
  vector<pair<unsigned int, unsigned int>> out_ranges;
  int iterations = 0;
  string line;

  // Input
  while (getline(cin, line)) {
    if (line.find('#') != string::npos) {
      line = line.substr(0, line.find('#'));
    }
    if (line.empty()) continue;
    try {
      ranges.push_back(cidr_to_range(line));
    } catch (const invalid_argument& ex) {
      cerr << "ERROR: " << ex.what() << endl;
      return 1;
    }
  }

  // Merge
  while (true) {
    iterations++;
    sort(ranges.begin(), ranges.end());
    for (auto& a : ranges) {
      for (const auto& b : ranges) {
        auto result = compare_ranges(a, b);
        if (result) {
          a = *result;
        }
      }
      if (find(out_ranges.begin(), out_ranges.end(), a) == out_ranges.end()) {
        out_ranges.push_back(a);
      }
    }
    if (ranges == out_ranges) break;
    ranges = out_ranges;
    out_ranges.clear();
  }

  // Output
  sort(out_ranges.begin(), out_ranges.end());
  for (const auto& r : out_ranges) {
    try {
      for (const auto& c : range_to_cidrs(r)) {
        cout << c << endl;
      }
    } catch (const invalid_argument& ex) {
      cerr << "ERROR: " << ex.what() << endl;
      return 1;
    }
  }

  return 0;
}

