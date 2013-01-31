#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// BlockWorld class that handles all commands
class BlockWorld {
public:
  explicit BlockWorld(size_t size) 
    : m_size   (size)
    , m_stacks (size)
  {
    for(size_t i=0; i<size; ++i) {
      m_stacks[i].reserve(size);
      m_stacks[i].push_back(i);
      m_locs[i] = i;
    }
  }

  // Print the block world state
  void print() {
    for(size_t i=0; i<m_size; ++i) {
      cout << i << ':';
      const vector<int>& blocks = m_stacks[i];
      for(size_t b=0; b<blocks.size(); ++b) {
        cout << ' ' << blocks[b];
      }
      cout << endl;
    }
  }

  // Parse the input command and run the proper command function
  // - Ignore command if it specifies the same block twice, or two blocks on
  //   the same stack.
  void parse(const string& cmd, int a, const string& desc, int b) {
    if(a == b) return;
    if(m_locs[a] == m_locs[b]) return;
    if(cmd == "move") {
      if     (desc == "onto") move_onto(a, b);
      else if(desc == "over") move_over(a, b);
    }
    else if(cmd == "pile") {
      if     (desc == "onto") pile_onto(a, b);
      else if(desc == "over") pile_over(a, b);
    }
  }

  void move_onto(int a, int b) {
    //cout << "move " << a << " onto " << b << endl;
    uncover(a);
    uncover(b);
    move_top(loc(a), loc(b));
  }
 
  void move_over(int a, int b) {
    //cout << "move " << a << " over " << b << endl;
    uncover(a);
    move_top(loc(a), loc(b));
  }
 
  void pile_onto(int a, int b) {
    //cout << "pile " << a << " onto " << b << endl;
    uncover(b);
    move_pile(a, loc(b));
  }

  void pile_over(int a, int b) {
    //cout << "pile " << a << " over " << b << endl;
    move_pile(a, loc(b)); 
  }
 
private:
  // Get the location (stack index) for the given block number
  size_t loc(int blocknum) {
    return m_locs[blocknum];
  }

  // Uncover a block by moving all blocks on top of it back to their initial 
  // stacks.
  void uncover(int blocknum) {
    vector<int>& s = m_stacks[loc(blocknum)];
    while(!s.empty() && s.back() != blocknum) {
      const int top = s.back();
      s.pop_back();
      m_stacks[top].push_back(top);
      m_locs[top] = top;
    }
  }

  // Given two stack locations, move the top block from stack A onto stack B
  void move_top(size_t from_loc, size_t to_loc) {
    vector<int>& from = m_stacks[from_loc];
    vector<int>& to   = m_stacks[to_loc];
    if(from.empty()) return;
    const int block = from.back();
    from.pop_back();
    to.push_back(block);
    m_locs[block] = to_loc;
  }

  // Given a block number, move that block and all blocks on top of it to the
  // target location
  void move_pile(int from_block, size_t to_loc) {
    vector<int>& from = m_stacks[loc(from_block)];
    vector<int>& to   = m_stacks[to_loc];
    // Find index of block
    size_t index = 0;
    for( ; from[index] != from_block; ++index) { }
    // Copy each block in pile to new stack
    for(size_t i=index; i<from.size(); ++i) {
      const int block = from[i];
      to.push_back(block);
      m_locs[block] = to_loc;
    }
    // Remove pile from old stack
    from.resize(index);
  }

  // Data
  size_t               m_size;
  vector<vector<int> > m_stacks;
  map<int,int>         m_locs;
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
  world.print();
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
  world.print();
  return 0;
}
*/
