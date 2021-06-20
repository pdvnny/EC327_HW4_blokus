// Copyright 2021 Parker Dunn pgdunn@bu.edu (Alternate: pdunn91@gmail.com)


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
  void show() const;
  void rotate();
  void flipud();
  void fliplr();
};

///////////////////////////
//   Tile class methods  //
///////////////////////////

void Tile::show() const { // print out tile based on it's saved indices
  
  if (this == nullptr) {
    cout << "Exited show tile.\n";
  } else {
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
}

void Tile::rotate() {
 
  int lvl = 0, olvl = dimension - 1;
  vector<vector<int>> new_shape;

  while (lvl <= olvl) {
    for (auto itr = (this->shape).begin(); itr != (this->shape).end(); ++itr) {
      if ((*itr).at(0) == lvl and ((*itr).at(1) <= olvl) and ((*itr).at(1) >= lvl)) { // element in the "top" row
        int ind = (*itr).at(1);
        new_shape.push_back({ind, olvl});

      } else if ((*itr).at(0) == olvl and ((*itr).at(1) <= olvl) and ((*itr).at(1) >= lvl)) { // element in the "last row"
        int ind = (*itr).at(1);
        new_shape.push_back({ind, lvl});

      } else if ((*itr).at(1) == olvl and ((*itr).at(0) <= olvl) and ((*itr).at(0) >= lvl)) { // element in the "last column"
        int ind = (*itr).at(0);
        new_shape.push_back({olvl, (olvl-ind)});

      } else if ((*itr).at(1) == lvl and ((*itr).at(0) <= olvl) and ((*itr).at(0) >= lvl)) { // element in "first" column"
        int ind = (*itr).at(0);
        new_shape.push_back({lvl, (olvl-ind)});
      }
    }
    lvl++;
    olvl--;
  }
  (this->shape) = new_shape;
}


void Tile::flipud() {
  int e = dimension - 1;
  for (int i = 0; i < shape.size(); i++)
    ((this->shape).at(i)).at(0) = e - ((this->shape).at(i)).at(0);
}

void Tile::fliplr() {
  int e = dimension - 1;
  for (int i = 0; i < shape.size(); i++)
    ((this->shape).at(i)).at(1) = e - ((this->shape).at(i)).at(1);
}

/////////////////////////////
//  Structs and Functions  //
/////////////////////////////

struct Move {
  char tile_style;
  int move_num;
  TileID tile;
  vector<vector<int>> tile_loc;
  Move(TileID t, int move, char t_id, vector<vector<int>> board_loc) {
    tile = t;
    move_num = move;
    tile_style = t_id;
    tile_loc = board_loc;
  }
};

void check_board_area(int r, int c, vector<vector<int>> compare_coords, bool* error, bool* proximity) {
  // check if the new coordinate is already filled
  for (auto coord : compare_coords) {
    if (coord.at(0) == r and coord.at(1) == c) *error = true;

    // check if there is a neighboring board piece
    for (int i = -1; i < 2; i++)
      for (int j = -1; j < 2; j++)
        if ( (coord.at(0) + i) == r and (coord.at(1) + j) == c ) *proximity = true;
  }
}

void tile_shift(Tile* t) {
  vector<vector<int>> indices = t->shape;
  
  int shift_col = t->dimension;
  for (int i = 0; i < (t->dimension); i++)
    if ((indices.at(i)).at(1) < shift_col) shift_col = (indices.at(i)).at(1);

  int shift_row = t->dimension;
    for (int i = 0; i < (t->dimension); i++)
    if ((indices.at(i)).at(0) < shift_col) shift_row = (indices.at(i)).at(0);

  for (auto index : t->shape) {
    index.at(0) -= shift_row;
    index.at(1) -= shift_col;
  }
}

bool tile_compare (Tile* inv, Tile* t) {
  vector<vector<int>> inv_shape = inv->shape;
  vector<vector<int>> t_shape = t->shape;

  if (inv_shape.size() != t_shape.size())
    return false;

  // compare two sets of tile indices
  int count = 0;
  for (vector<int> index1 : inv_shape)
    for (vector<int> index2 : t_shape)
      if (index1.at(0) == index2.at(0) and index1.at(1) == index2.at(1)) count++;

  if (count == t_shape.size()) return true;

  cout << "\nComparing same size tiles ...\n";
  return false;
}

bool same_tile_check(Tile inv, Tile t) {
  bool identical = false;

  tile_shift(&inv);
  tile_shift(&t);

  identical = tile_compare(&inv, &t);
  if (identical) return true;
  
  t.rotate();
  identical = tile_compare(&inv, &t);
  if (identical) return true;
  t.rotate();
  identical = tile_compare(&inv, &t);
  if (identical) return true;
  t.rotate();
  identical = tile_compare(&inv, &t);
  if (identical) return true;
  t.rotate();

  t.fliplr();
  identical = tile_compare(&inv, &t);
  if (identical) return true;
  t.fliplr();

  t.flipud();
  identical = tile_compare(&inv, &t);
  if (identical) return true;

  return false;
}

///////////////////////////////////////
//  Blokus class and blokus methods  //
///////////////////////////////////////

class Blokus {
  // common interface. required.
 public:
  TileID nexttile_id;
  int move_num;
  int board_dim;
  string tile_style = "*#@ox";
  
  map<TileID,Tile> inventory;
  vector<Move> Moves;

  Blokus() {
    nexttile_id = 100;
    move_num = 0;
    board_dim = 0;
  }

  Tile* find_tile(TileID);    // made
  void create_piece();        // made - needs error checking feature
  void reset();               // made
  void show_tiles() const;     // made
  void show_board() const;          // made
  void play_tile(TileID, int, int); // made
  void set_size(int);               // made - needs feature to remove tiles when they are off the board
};

// Structures for Blokus methods

void Blokus::reset() {
  board_dim = 0;
  Moves.clear();
  move_num = 0;
}

void Blokus::show_tiles() const { // goes through map and prints all of inventory
  for (auto [key, value] : inventory) {
    cout << "Tile ID: " << key << "\n";
    value.show();
  }
}

void Blokus::create_piece() {
  Tile t;
  string temp_str;
  bool include = true, valid_dim = true;
  string size;
  
  cin >> size;
  for (char c : size)
    if (c < '1' or c > '9') valid_dim = false;

  if (valid_dim) {
    t.dimension = stoi(size);
    // add indices to "shape"
    for (int row = 0; row < t.dimension; row++) {
      cin >> temp_str;
      for (int col = 0; col < t.dimension; col++) {
        if (temp_str.at(col) == '*') (t.shape).push_back({row, col});
      }
      for (char c : temp_str) {
        if (c != '.' and c != '*') {
          cout << "\nInvalid character entered. Use * and . to create pieces.\n";
          include = false;
        }
      }
    } // end of storing tile indices

    // Compare indices to old tiles
    for (auto [key, value] : inventory) {
      if (same_tile_check(value, t)) {
        cout << "Tile already in inventory. Tile " << key << "\n";
        include = false;
      }
    }

    if (include) {
      
      inventory.insert({nexttile_id, t});
      nexttile_id++;
    }
  }
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


void Blokus::show_board() const {
  string empty_row(board_dim, '.');
  vector<string> board(board_dim, empty_row);
  for (Move m : Moves) {
    for (auto coord : m.tile_loc) {
      int r = coord.at(0);
      int c = coord.at(1);
      (board.at(r)).at(c) = m.tile_style;
    }
  }
  for (string row : board)
    cout << row << "\n";
}


void Blokus::play_tile(TileID ID, int r, int c) {

  bool error = false;
  bool proximity = false;
  Tile* t_ptr = find_tile(ID);

  if (t_ptr == nullptr) {
    cout << "Exited play command.\n";
  } else {
    vector<vector<int>> tile_placement = (t_ptr->shape);
    
    // moves the tile to correct position on board
    int counter = 0;
    for (auto new_coord : tile_placement) {
      new_coord.at(0) += r;
      new_coord.at(1) += c;
      tile_placement.at(counter) = {new_coord.at(0), new_coord.at(1)};
      for (Move played_tile : Moves)
        check_board_area(new_coord.at(0), new_coord.at(1), played_tile.tile_loc, &error, &proximity);
      if (new_coord.at(0) >= board_dim or new_coord.at(1) >= board_dim) error = true;
      counter++;
    }
    
    if (error) {
      cout << "Cannot place tile on another tile or off the board.\n";
    } else if (!proximity and move_num > 0) {
      cout << "Tile must neighbor another tile.\n";
    } else {
      Move m{ID, move_num, tile_style.at(move_num % 5), tile_placement};
      Moves.push_back(m);
      move_num++;
    }   // end of "secondary else"
  }   // end of "main else"
}   // end of method - entirely controlled by one if-else



void Blokus::set_size(int dim) {
  board_dim = dim;

  for (vector<Move>::iterator itr = Moves.begin(); itr != Moves.end(); itr++) {
    vector<vector<int>> board_indices = (itr->tile_loc);
    for (auto index : board_indices) 
      if (index.at(0) >= dim or index.at(1) >= dim) Moves.erase(itr);
  }
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
