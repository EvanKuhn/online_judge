#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Box class: a vector of dimensions, plus related functions
class Box {
public:
  Box() : num(0) { }

  // Read dimensions from stdin and sort descending
  void read(size_t ndims) { 
    dims.resize(ndims);
    for(size_t i=0; i<ndims; ++i) {
      cin >> dims[i];
    }
    sort(dims.rbegin(), dims.rend());
  }

  // Does this box fit in the other?
  bool fits_in(const Box& other) const {
    for(size_t i=0; i<dims.size(); ++i) {
      if(other.dims[i] <= dims[i]) return false;
    }
    return true;
  }

  // For sorting multiple boxes
  bool operator<(const Box& other) const {
    return dims[0] < other.dims[0];
  }

  vector<size_t> dims;
  size_t num;
};

// Helper function find the longest sequence of boxes that fit in one another.
//
// Params:
// - An array to write the longest sequence to
// - The array of boxes
// - The index of the first box in the subset of boxes we're searching
// - An optional bounding box (from a previous call)
//
// Uses dynamic programming. The logic is:
// - If we're searching an empty set, return an empty sequence.
// - If searching a single box, return that box only if it fits in the bound.
// - Else, find the next box that fits in the bound. From there, calculate:
//   1) The longest sequence including that next box
//   2) The longest sequence excluding that next box
//   Return the larger of #1 and #2
void longest(vector<size_t>& seq, 
             const vector<Box>& boxes, 
             size_t index, 
             const Box* bound)
{
  seq.clear();
  const size_t nboxes = boxes.size();

  // Index out of bounds: leave sequence empty
  if(index+1 > nboxes) {
    // Do nothing
  }
  // Index of last box: check if it fits in the bounding box
  else if(index+1 == nboxes) {
    if(!bound || boxes[index].fits_in(*bound)) {
      seq.push_back(boxes[index].num);
    }
    return;
  }
  // Otherwise we need to do some dynamic programming
  else {
    // The longest sequence equals the max of:
    // 
    // 1 + longest sequence of boxes 2..N that fit into box 1
    //   -or-
    // longest sequence of boxes 2..N 
    vector<size_t> seq_a;
    vector<size_t> seq_b;
  
    // Find the index of the next box that fits in the bounding box.
    // Get the longest sequence starting with that box.
    size_t f=index;
    while(f<nboxes && bound && !boxes[f].fits_in(*bound)) {
      ++f;
    }
    if(f < nboxes) {
      longest(seq_a, boxes, f+1, &boxes[f]);
      seq_a.push_back(boxes[f].num);
    }

    // Get the longest sequence without that box
    longest(seq_b, boxes, f+1, bound);

    // Return the longer one
    seq.swap(seq_a.size() > seq_b.size() ? seq_a : seq_b);
  }
}

// Find the longest sequence 
void find_longest_sequence(const vector<Box>& boxes, vector<size_t>& seq) {
  longest(seq, boxes, 0, NULL);
}

int main(int argc, char** argv) {
  while(1) {
    // Read num boxes and dimensions
    size_t nboxes, ndims;
    cin >> nboxes >> ndims;
    if(!cin) break;

    // Read boxes
    vector<Box> boxes(nboxes);
    for(size_t i=0; i<nboxes; ++i) {
      boxes[i].read(ndims);
      boxes[i].num = i;
    }
    sort(boxes.rbegin(), boxes.rend());

    // Find longest sequence and print it
    vector<size_t> seq;
    find_longest_sequence(boxes, seq);
    cout << seq.size() << endl;
    for(size_t i=0; i<seq.size(); ++i) {
      cout << (seq[i] + 1) << " ";
    }
    cout << endl;
  }
  return 0;
}
