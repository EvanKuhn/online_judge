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
bool search(double curval, 
            vector<size_t>& path, 
            vector<bool>&   used, 
            vector<size_t>& solution)
{
  //cout << "Curval=" << curval << "  Path[" << path.size() << "]:";
  //for(size_t i=0; i<path.size(); ++i) {
  //  cout << ' ' << path[i];
  //}
  //cout << endl;

  
  // Check for arbitrage by making one more conversion before converting back to
  // the first currency
  if(!path.empty()) {
    for(size_t ccy=0; ccy<dims; ++ccy) {
      // Skip if equal to first or last currency
      if(used[ccy]) continue;

      //cout << "rate " << path.back() << " to " << ccy << " = " << rates[path.back()][ccy] << endl;
      //cout << "rate " << ccy << " to " << path.front() << " = " << rates[ccy][path.front()] << endl;

      // Check for arbitrage
      double val = curval * rates[path.back()][ccy] * rates[ccy][path.front()];
      if(val > 1.01) {
        //cout << "Found possible solution with currency " << ccy << " value " << val << endl;
        solution = path;
        solution.push_back(ccy);
        return true;
      }
    }
  }

  // Check if we reached max depth
  if(path.size() >= dims-1) return false;

  // Temporarily and optimal solutions
  vector<size_t> temp, optimal;

  // We didn't find an arbitrage opportunity, so search deeper
  for(size_t ccy=0; ccy<dims; ++ccy) {
    // Skip if equal to first or last currency
    if(used[ccy]) continue;

    // Add to conversion path
    path.push_back(ccy);
    used[ccy] = true;

    // Recurse and save optimal solution
    double newval = curval * rates[path.back()][ccy];
    if(search(newval, path, used, temp)) {
      if(optimal.empty() || temp.size() < optimal.size()) {
        optimal = temp;
      }
    }

    // Remove currency before iterating
    path.pop_back();
    used[ccy] = false;
  }
  
  // If we found a solution, return it!
  if(!optimal.empty()) {
    optimal.swap(solution);
    return true;
  }
  return false;
}

// Find and print arbitrage opportunities
void find_arbitrage() {
  vector<size_t> path;
  vector<bool>   used(MAXDIM, false);
  vector<size_t> solution;

  // Search for a solution
  const bool success = search(1.0, path, used, solution);

  // Print results
  if(success) {
    for(size_t i=0; i<solution.size(); ++i) {
      cout << (solution[i] + 1) << ' ';
    }
    cout << (solution.front() + 1) << endl;
  }
  else {
    cout << "no arbitrage sequence exists" << endl;
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

