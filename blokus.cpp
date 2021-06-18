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


// NOTES from PD
//  - I did one significantly different thing compared to the lecture material
//  - Prof C saved the input tiles as vector of strings, but ... 
//  - I decided to just save the indices of the shape. (I change that part if you guys don't like how I did this)

//  - Print out of "show_tiles()" isn't quite right at the moment



// Currently working functions/methods/attributes
// (1) Tile::show()
// (2) Tile::vector<vector<int>> shape
// (3) Tile::dimension

// (4) Blokus::nexttile_id
// (5) Blokus::inventory
// (6) Blokus::create_piece()
// (7) Blokus::find_tile()
// (8) Blokus::show_tiles()

// Updated Features - June 17 - PD
// -- Updated "find_tile" - changed printing features
// -- 


typedef int TileID;


class Tile {
  // common interface. required.

 public:
  int dimension;
  vector<vector<int>> shape;
  void show() const;  // print out tile in tilebox format - made
  void rotate();
  void flipud();
  void fliplr();
};


///////////////////////////
//   Tile class methods  //
///////////////////////////

void Tile::show() const { // print out tile based on it's saved indices
    
  // creating a vector of strings for printing
  string tstr(dimension, '.');
  vector<string> output(dimension,tstr);
  
  // modifying the string
  for (vector<int> coordinate : shape)
    (output.at(coordinate.at(0))).at(coordinate.at(1)) = '*';

  // outputing the tile
  for (string line : output)
    cout << line << "\n";
}

void Tile::rotate() {
 // need to modify "this" to rotate the block
}


void Tile::flipud() {
  // need to modify "this" to flip the block vertically
}


void Tile::fliplr() {
  // need to modify "this" to flip the shape horizontally
}

struct Move {
  char tile_id;
  int move_num;
  TileID tile;
  vector<vector<int>> tile_loc;
  Move(TileID t, int move, char t_id, vector<vector<int>> board_loc) {
    tile = t;
    move_num = move;
    tile_id = t_id;
    tile_loc = board_loc;
  }
};


class Blokus {
  // common interface. required.

 public:
  int nexttile_id;
  int board_dim;
  string tile_id = "*#@ox";
  TileID move_num;
  
  map<TileID,Tile> inventory;
  vector<Move> Moves;

  Blokus() {
    nexttile_id = 100;
    move_num = 0;
  }

  Tile* find_tile(TileID);    // made
  void create_piece();        // made - needs error checking feature
  void reset();           
  void show_tiles() const;     // made
  void show_board() const;
  void play_tile(TileID, int, int);
  void set_size(int);
};

// Structures for Blokus methods

void Blokus::reset() {

}

void Blokus::show_tiles() const { // goes through map and prints all of inventory
  for (auto [key, value] : inventory) {
    cout << "Tile ID: " << key << "\n";
    value.show();
  }
}

void Blokus::show_board() const {



}

void Blokus::play_tile(TileID ID, int r, int c) {
  // grab tile from inventory
  // determine the board positions it will occupy
  // place the piece on the board
  // store the "move" in structure within blokus

  Tile* t_ptr = find_tile(ID);
  if (t_ptr == nullptr) 
    cout << "Exited play command.\n";
  else {
    vector<vector<int>> tile_placement = (t_ptr->shape);
    // moves the tile to correct position on board
    for (auto new_coord : tile_placement) {
      new_coord.at(0) += r;
      new_coord.at(1) += c;
      for (Move existing_tile : Moves) {
        for (auto exist_coord : existing_tile.tile_loc)
          if (exist_coord.at(0) == new_coord.at(0) and exist_coord.at(1) == new_coord.at(1)) {
            cout << "Cannot place tile on location already occupied by another tile.\n\n";
            break;
          }
      }
    }
    Move m{ID, move_num, tile_id.at(move_num % 5), tile_placement};
    Moves.push_back(m);
  }
  move_num++;
}

void Blokus::set_size(int dim) {
  // This functoin re-sizes the square board
}


void Blokus::create_piece() {
  Tile t;
  string temp_str;
  
  cin >> t.dimension;
  for (int row = 0; row < t.dimension; row++) {
    cin >> temp_str;
    for (int col = 0; col < t.dimension; col++) {
      if (temp_str.at(col) == '*') (t.shape).push_back({row, col});
    }
  } // end of storing tile indices

  // ADD ERROR CHECKING TO ENSURE THE PIECE HASN'T ALREADY BEEN CREATED.

  inventory.insert({nexttile_id, t});
  nexttile_id++;
}


Tile* Blokus::find_tile(TileID findkey) {
  for (auto [key, value] : inventory) {
    if (key == findkey) {
      cout << "Tile: " << key << "\n";
      return &inventory.at(key);
    }
  }
  cout << "\nTile not found.\n";
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
