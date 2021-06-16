// Copyright 2021 Parker Dunn pgdunn@bu.edu (Alternate: pdunn91@gmail.com)
// Copyright 2021
// Copyright 2021 

#include <iostream>
#include <string>
#include <vector>

// allowed includes
// tuple, utility, vector, map, set, unordered_map,
// unordered_set, algorithm

using std::cin;
using std::cout;
using std::string;
using std::vector;




typedef int TileID;

class Tile {
  // common interface. required.

  // info that this class should save:
  // (1) size
  // (2) shape - via vector of strings (?) OR vector of indices (?)
  // 
  
 public:
  void show() const;  // print out tile in tilebox format
  void rotate();
  void flipud();
  void fliplr();
};

///////////////////////////
//   Tile class methods  //
///////////////////////////

void Tile::show() const {

  // this function needs to display the Tile

}

void Tile::rotate() {

  this // need to modify the object in this case


}


void Tile::flipud() {

  this // need to modify this to flip the block vertically

}


void Tile::fliplr() {

  this /// need to modify this to flip the shape horizontally

}




class Blokus {
  // common interface. required.
  
  vector<Tile> tiles; // a vector to hold all of the created tiles

 public:
  Tile* find_tile(TileID);
  void create_piece() {
    // read in the size
    // read in strings
    // make a Tile
    // store it in a collection of Tiles
  }

  void reset();
  void show_tiles() const;
  void show_board() const;
  void play_tile(TileID, int, int);
  void set_size(int);
};














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
