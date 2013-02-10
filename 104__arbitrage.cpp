#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define MAXDIM 20

// Conversion rates table and dimensions
double rates[MAXDIM][MAXDIM];
size_t dims = 0;

// Initialize conversion rates table from stdin
void init_rates_table() {
  for(size_t i=0; i<dims; ++i) {
    for(size_t j=0; j<dims; ++j) {
      if(i == j) rates[i][j] = 1.0;
      else cin >> rates[i][j];
    }
  }
}

// The meat!
void solve(vector<size_t>& convs, double curval) {
  const size_t first_ccy = convs.front();
  const size_t curr_ccy = convs.back();

  // Choose next currency
  for(size_t next_ccy=0; next_ccy<dims; ++next_ccy) {
    if(next_ccy == first_ccy) continue;
    if(next_ccy == curr_ccy) continue;
    convs.push_back(next_ccy);
    
    // Check if converting to the next currency and back to the first will
    // result in a gain of > 1%
    double val = curval * rates[curr_ccy][next_ccy] * rates[next_ccy][first_ccy];
    if(val > 1.01) {
      return;
    }

  }
}

// Find and print arbitrage opportunities
void find_arbitrage() {
  // Array of conversions
  vector<size_t> min_convs;
  
  // Actually look for arbitrage
  for(size_t ccy=0; ccy<dims; ++ccy) {
    vector<size_t> convs(1, ccy);
    convs.reserve(MAXDIM);
    solve(convs, ccy);
    if(convs
  }
  
  // Print results
  if(convs.empty()) {
    cout << "no arbitrage sequence exists" << endl;
  }
  else {
    for(size_t i=0; i<convs.size(); ++i) {
      cout << (convs[i] + 1) << ' ';
    }
    cout << convs.front() << endl;
  }
}

// Read, solve, print, loop
int main(int argc, char** argv) {
  while(1) {
    cin >> dims;
    if(!cin) break;
    init_rates_table();
    find_arbitrage();
  }
  return 0;
}
