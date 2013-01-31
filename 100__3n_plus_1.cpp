#include <iostream>
#include <map>

using namespace std;

map<int,int> lengths;

// Look up the memoized cycle length, or 0 if not found
int lookup(int n) {
  map<int,int>::const_iterator iter = lengths.find(n);
  return (iter == lengths.end() ? 0 : iter->second);
}

// Compute the cycle length, with memoization
int compute_cycle_length(int n) {
  int l = lookup(n);
  if(l) return l;
  
  const int orign = n;
  int len = 1;
  while(n > 1) {
    n = (n % 2 ? (3*n) + 1 : n / 2);
    l = lookup(n);
    if(l) {
      len += l;
      break;
    }
    else {
      ++len;
    }
  }
  lengths[orign] = len;
  return len;
}

int main(int argc, char** argv) {
  int i,j;

  while(cin >> i && cin >> j) {
    int first = std::min(i,j);
    int last = std::max(i,j);
    int maxlen = 0;

    for(int cur=first; cur<=last; ++cur) {
      const int len = compute_cycle_length(cur);
      if(len > maxlen) maxlen = len;
    }

    cout << i << " " << j << " " << maxlen << endl;
  }

  return 0;
}
