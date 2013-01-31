#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// BlockWorld class that handles all commands
class BlockWorld {
public:
  explicit BlockWorld(size_t size) 
    : m_stacks(size)
  {
    cout << "Block world has size " << size << endl;
  }

  void parse(const string& cmd, int a, const string& desc, int b) {
    if(a == b) return;
    if(cmd == "move") {
      if     (desc == "over") move_over(a, b);
      else if(desc == "onto") move_onto(a, b);
    }
    else if(cmd == "pile") {
      if     (desc == "over") pile_over(a, b);
      else if(desc == "onto") pile_onto(a, b);
    }
  }

  void move_over(int a, int b) {
    cout << "move " << a << " over " << b << endl;
  }
 
  void move_onto(int a, int b) {
    cout << "move " << a << " onto " << b << endl;
  }
 
  void pile_over(int a, int b) {
    cout << "pile " << a << " over " << b << endl;
  }
 
  void pile_onto(int a, int b) {
    cout << "pile " << a << " onto " << b << endl;
  }

private:
  vector<vector<int> > m_stacks;
};

// Helper functions
int    read_int() { int x=0; cin >> x; return x; }
string read_str() { string x; cin >> x; return x; }

// Run the program by reading from stdin and passing data to the BlockWorld
int main(int argc, char** argv) {
  int a, b;
  string cmd, desc;
  BlockWorld world(read_int());

  while((cmd = read_str()) != "quit") {
    a    = read_int();
    desc = read_str();
    b    = read_int();
    world.parse(cmd, a, desc, b);
  }

  return 0;
}




/*
// A more C-style main function
int main(int argc, char** argv) {
  size_t size;
  int a, b;
  char cmd[5] = {0};
  char desc[5] = {0};

  cin >> size;
  BlockWorld world(size);

  while(scanf("%s %d %s %d\n", cmd, &a, desc, &b) > 0) {
    if(string(cmd) == "quit") break;
    world.parse(cmd, a, desc, b);
  }

  return 0;
}
*/
