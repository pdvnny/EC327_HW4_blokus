// Copyright 2021 Parker Dunn pgdunn@bu.edu (Alternate: pdunn91@gmail.com)
// Copyright 2021
// Copyright 2021 

#include <iostream>
#include <map>
#include <string>
#include <vector>


// allowed includes
// tuple, utility, vector, map, set, unordered_map,
// unordered_set, algorithm

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;


typedef int TileID;


class Tile {
  // common interface. required.

 public:
  int dimension;
  vector<vector<int>> shape;
  void show() const;  // print out tile in tilebox format
  void rotate();
  void flipud();
  void fliplr();
};


///////////////////////////
//   Tile class methods  //
///////////////////////////

void Tile::show() const {
 // need to modify "this" to flip the block vertically
}

void Tile::rotate() {
 // need to modify "this" to flip the block vertically
}


void Tile::flipud() {
  // need to modify "this" to flip the block vertically
}


void Tile::fliplr() {
  // need to modify "this" to flip the shape horizontally
}


class Move : private Tile { 
// creating this variation of Tile to hold move information
// These objects can be different from Tiles by holding additional info,
  // but they should basically serve the same purpose as Tiles

// Need to be careful that some of the functions stop being available publicly
// ex. rotate, flipud, fliplr

// Some necessary features for this class to work right...
// (1) must be constructed with reference to oa Tile to provide the placed tile's info.


public:

  int move_num;
  vector<int> position;           // will hold location of the piece
  vector<vector<int>> placement;  // will hold the indices occupied on the board

  Move(int move, int row, int col, Tile TileID) {
    // constructor of a move
  }

};


class Blokus {
  // common interface. required.

 public:
  int nexttile_id,
      move_num;
  map<int,Tile> inventory;
  map<int,Move> moves;

  Blokus() {
    nexttile_id = 100;
    move_num = 0;
  }

  Tile* find_tile(TileID);
  void create_piece();
  void reset();
  void show_tiles() const;
  void show_board() const;
  void play_tile(TileID, int, int);
  void set_size(int);
};

// Structures for Blokus methods - allows compiling
void Blokus::reset() {

}

void Blokus::show_tiles() const {

}

void Blokus::show_board() const {

}

void Blokus::play_tile(TileID ID, int r, int c) {

}

void Blokus::set_size(int dim) {
  // Does this function resize the square board??
}


void Blokus::create_piece() {
  Tile t;
  
  t.dimension = 3;                          // will need to come from cin
  vector<string> input{"***","**.","*.."};  // will need to come from cin
  
  for (int row = 0; row < input.size(); row++) {
    string str_row = input.at(row);
    for (int col = 0; col < str_row.size(); col++) {
      if (str_row.at(col) == '*') (t.shape).push_back({row,col});

    }
  } // end of storing tile indices

  // ADD ERROR CHECKING TO ENSURE THE PIECE HASN'T ALREADY BEEN CREATED.

  inventory.insert({nexttile_id, t});
  nexttile_id++;
}


Tile* Blokus::find_tile(TileID findkey) {
  for (auto [key, value] : inventory) {
    cout << "Tile: " << key << "\n";    // I think this was just something Prof. did in class. Probably need to remove.
    if (key == findkey) {
      cout << "- Found tile.\n";
      return &inventory.at(key);
    }
  }
  cout << "Tile not found.\n";
  return nullptr;
}





// MAIN. Do not change the below.


int main() {
  string command;
  Blokus b;

  while (true) {
    cin >> command;
    if (command == "quit")  {
      break;
    } else if (command == "//") {
      getline(cin, command);
    } else if (command == "board") {
      b.show_board();
    } else if (command == "create") {
      b.create_piece();
    } else if (command == "reset") {
      b.reset();
    } else if (command == "show") {
      string arg;
      cin >> arg;
      if (arg == "tiles") {
        b.show_tiles();
      } else {
        auto g = b.find_tile(std::stoi(arg));
        g->show();
      }
    } else if (command == "resize") {
      int newsize;
      cin >> newsize;
      b.set_size(newsize);
      b.show_board();
    } else if (command == "play") {
      TileID id;
      int row, col;
      cin >> id >> row >> col;
      b.play_tile(id, row, col);
    } else if (command == "rotate") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->rotate();
      cout << "rotated " << id << "\n";
      g->show();
    } else if (command == "fliplr") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->fliplr();
      cout << "fliplr " << id << "\n";
      g->show();
    } else if (command == "flipud") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->flipud();
      cout << "flipud " << id << "\n";
      g->show();
    } else {
      cout << "command not understood.\n";
    }
  }
  cout << "Goodbye\n";
  return 0;
}
