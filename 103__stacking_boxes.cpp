#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const size_t MAXDIM = 10;
const size_t MAXBOX = 30;

class Box {
public:
  void read(size_t ndims) { 
    for(size_t i=0; i<ndims; ++i) {
      dims.resize(ndims);
      cin >> dims[i];
    }
  }
  vector<size_t> dims;
};

void find_longest_sequence(const vector<Box>& boxes, vector<size_t>& seq) {
  //TODO
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
    }

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
