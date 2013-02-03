#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Array of all permutations of the three bottle colors
const char* ORDERS[6] = { "BGC", "BCG", "GCB", "GBC", "CBG", "CGB" };
const size_t NUM_ORDERS = 6;

// A bin class. Reads from stdin and initializes its counters
class Bin {
public:
  Bin() : brown(0), green(0), clear(0) { }
  void read(istream& in) {
    cin >> brown >> green >> clear;
  }
  size_t get(char color) const {
    switch(color) {
      case 'B': return brown;
      case 'G': return green;
      case 'C': return clear;
      default:  assert(false); return 0;
    }
  }
  size_t brown, green, clear;
};

// Given a set of bins and a desired ordering (ie. what color bottles belong in
// each bin), count the moves necessary to achieve that ordering.
size_t count_moves(const Bin bins[3], const char* order) {
  size_t moves = 0;
  for(size_t i=0; i<3; ++i) {
    const char c = order[i];
    const Bin& b2 = bins[(i+1)%3];
    const Bin& b3 = bins[(i+2)%3];
    moves += b2.get(c) + b2.get(c);
  }
  return moves;
}

// Read lines from stdin and compute most efficient sort ordering
int main() {
  Bin bins[3];
  size_t min_moves = 0;
  const char* min_order = ORDERS[0];

  while(1) {
    bins[0].read(cin);
    bins[1].read(cin);
    bins[2].read(cin);
    if(!cin) break;
  
    for(size_t i=0; i<NUM_ORDERS; ++i) {
      const char* order = ORDERS[i];
      const size_t moves = count_moves(bins, order);
      if(i == 0 || moves < min_moves) {
        min_moves = moves;
        min_order = order;
      }
    }
    cout << min_order << " " << min_moves << endl;
  }
  return EXIT_SUCCESS;
}
