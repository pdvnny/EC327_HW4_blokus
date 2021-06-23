// Copyright 2021 Parker Dunn pgdunn@bu.edu
// (Alternate: pdunn91@gmail.com and parker_dunn@outlook.com)

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
  vector<string> rows;
  void show() const;
  void rotate();
  void flipud();
  void fliplr();
};


void tile_shift(Tile* t) {
  vector<vector<int>> indices = (t->shape);
  int max = 0;

  int shift_col = t->dimension - 1;
  for (int i = 0; i < (t->shape).size(); i++)
    if ((indices.at(i)).at(1) < shift_col) shift_col = (indices.at(i)).at(1);

  int shift_row = t->dimension - 1;
  for (int i = 0; i < (t->shape).size(); i++)
    if ((indices.at(i)).at(0) < shift_row) shift_row = (indices.at(i)).at(0);

  for (int j = 0; j < (t->shape).size(); j++) {
    ((t->shape).at(j)).at(0) -= shift_row;
    ((t->shape).at(j)).at(1) -= shift_col;
    if (((t->shape).at(j)).at(0) > max) max = ((t->shape).at(j)).at(0);
    if (((t->shape).at(j)).at(1) > max) max = ((t->shape).at(j)).at(1);
  }

  t->dimension = (max + 1);
}

bool tile_compare(Tile* inv, Tile* t) {
  vector<vector<int>> inv_shape = inv->shape;
  vector<vector<int>> t_shape = t->shape;

  if (inv_shape.size() != t_shape.size())
    return false;

  // compare two sets of tile indices
  int count = 0;
  for (vector<int> index1 : inv_shape)
    for (vector<int> index2 : t_shape)
      if (index1.at(0) == index2.at(0) and index1.at(1) == index2.at(1))
        count++;

  if (count == t_shape.size()) return true;
  return false;
}

bool same_tile_check(Tile inv, Tile t2) {
  bool identical = false;

  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();

  t2.fliplr();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  t2.fliplr();

  t2.flipud();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.rotate();
  t2.flipud();

  t2.fliplr();
  t2.flipud();
  if (tile_compare(&inv, &t2)) identical = true;
  t2.fliplr();
  t2.flipud();

  return identical;
}

///////////////////////////
//   Tile class methods  //
///////////////////////////

void Tile::show() const {
  if (this == nullptr) {
    cout << "Exited show tile.\n";
  } else {
    // creating a vector of strings for printing
    string tstr(dimension, '.');
    vector<string> output(dimension, tstr);

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
      // element in the "top" row
      if ((*itr).at(0) == lvl and
          ((*itr).at(1) <= olvl) and
          ((*itr).at(1) >= lvl)) {
        int ind = (*itr).at(1);
        new_shape.push_back({(lvl + (olvl - ind)), lvl});

        // element in the "last row"
      } else if ((*itr).at(0) == olvl and
                 (*itr).at(1) <= olvl and
                 (*itr).at(1) >= lvl) {
        int ind = (*itr).at(1);
        new_shape.push_back({(olvl - (ind - lvl)), olvl});

        // element in the "last column"
      } else if ((*itr).at(1) == olvl and
                 (*itr).at(0) <= olvl and
                 (*itr).at(0) >= lvl) {
        int ind = (*itr).at(0);
        new_shape.push_back({lvl, ind});

        // element in "first" column"
      } else if ((*itr).at(1) == lvl and
                 (*itr).at(0) <= olvl and
                 (*itr).at(0) >= lvl) {
        int ind = (*itr).at(0);
        new_shape.push_back({olvl, ind});
      }
    }
    lvl++;
    olvl--;
  }
  (this->shape) = new_shape;
  tile_shift(this);
}

void Tile::flipud() {
  int e = dimension - 1;
  for (int i = 0; i < shape.size(); i++)
    ((this->shape).at(i)).at(0) = e - ((this->shape).at(i)).at(0);
  tile_shift(this);
}

void Tile::fliplr() {
  int e = dimension - 1;
  for (int i = 0; i < shape.size(); i++)
    ((this->shape).at(i)).at(1) = e - ((this->shape).at(i)).at(1);
  tile_shift(this);
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

///////////////////////////////////////
//  Blokus class and blokus methods  //
///////////////////////////////////////

class Blokus {
  // common interface. required.
 public:
  TileID nexttile_id;
  int move_num;
  int board_dim;

  map<TileID, Tile> inventory;
  vector<Move> Moves;

  Blokus() {
    nexttile_id = 100;
    move_num = 0;
    board_dim = 0;
  }

  Tile* find_tile(TileID);
  void create_piece();
  void reset();
  void show_tiles() const;
  void show_board() const;
  void play_tile(TileID, int, int);
  void set_size(int);
};

// Structures for Blokus methods

void Blokus::reset() {
  board_dim = 0;
  Moves.clear();
  inventory.clear();
  move_num = 0;
}

// goes through map and prints all of inventory
void Blokus::show_tiles() const {
  cout << "tile inventory\n";
  for (auto [key, value] : inventory) {
    cout << key << "\n";
    value.show();
  }
}


void Blokus::create_piece() {
  Tile t;
  string temp_str;
  bool include = true, valid_char = false, valid_shape = true;
  string size;

  cin >> size;
  t.dimension = stoi(size);
  // add indices to "shape"
  for (int row = 0; row < t.dimension; row++) {
    cin >> temp_str;
    // CHECK FOR VALID CHARACTERS
    for (char c : temp_str) {
      if (c != '.' and c != '*') include = false;  // only * and .
      if (c == '*') valid_char = true;           // at least one *
    }
    // CHECK FOR VALID ROW LENGTH!
    if (temp_str.size() != t.dimension) include = false;

    // save cin (i.e. temp_str)
    (t.rows).push_back(temp_str);
    for (int col = 0; col < t.dimension; col++) {
      if (temp_str.at(col) == '*')
        (t.shape).push_back({row, col});
    }
  }  // end of storing tile indices

  if (!(t.shape).empty()) {
    vector<vector<int>> shape_copy = (t.shape);
    vector<int> test_coord = shape_copy.at(shape_copy.size() - 1);
    shape_copy.pop_back();
    while (!shape_copy.empty()) {
      for (auto itr = (t.shape).begin(); itr != (t.shape).end(); itr++) {
        if (test_coord.at(0) - 1 == (*itr).at(0) and
            test_coord.at(1) == (*itr).at(1)) {
          test_coord.clear();
          break;
        } else if (test_coord.at(0) + 1 == (*itr).at(0) and
                   test_coord.at(1) == (*itr).at(1)) {
          test_coord.clear();
          break;
        } else if (test_coord.at(0) == (*itr).at(0) and
                   test_coord.at(1) - 1 == (*itr).at(1)) {
          test_coord.clear();
          break;
        } else if (test_coord.at(0) == (*itr).at(0) and
                   test_coord.at(1) + 1 == (*itr).at(1)) {
          test_coord.clear();
          break;
        }
      }
      if (!test_coord.empty()) valid_shape = false;
      test_coord = shape_copy.at(shape_copy.size() - 1);
      shape_copy.pop_back();
    }
  }

  // needed a print out when shape or char is invalid
  if (!valid_shape or !include or !valid_char) cout << "invalid tile\n";

  // Compare indices to old tiles
  tile_shift(&t);
  for (auto [key, value] : inventory) {
    if (same_tile_check(value, t)) {
      cout << "discarded copy of tile " << key << "\n";
      include = false;
    }
  }

  // now tile can be added to inventory
  if (include and valid_char and valid_shape) {
    inventory.insert({nexttile_id, t});
    cout << "created tile " << nexttile_id << "\n";
    nexttile_id++;
  }
}


Tile* Blokus::find_tile(TileID findkey) {
  for (auto [key, value] : inventory) {
    if (key == findkey) {
      //  cout << key << "\n";
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
      (board.at(r)).at(c) = '*';
    }
  }
  for (string row : board)
    cout << row << "\n";
}


void Blokus::play_tile(TileID ID, int r, int c) {
  bool error = false;
  Tile* t_ptr;

  int count = 0;
  for (auto [key, value] : inventory) {
    if (key == ID) {
      t_ptr = &inventory.at(key);
      break;
    } else if (count == inventory.size()) {
      t_ptr = nullptr;
    }
    count++;
  }

  if (t_ptr == nullptr) {
    cout << "tile not in inventory.\n";

  } else {
    vector<vector<int>> tile_placement = (t_ptr->shape);

    // moves the tile to correct position on board
    int counter = 0;
    for (auto coord : tile_placement) {
      vector<int> new_coord = {coord.at(0) + r, coord.at(1) + c};
      tile_placement.at(counter) = new_coord;
      if (new_coord.at(0) >= board_dim or new_coord.at(1) >= board_dim)
        error = true;
      counter++;
    }

    for (auto coord : tile_placement) {
      for (auto prev_move : Moves)
        for (auto prev_placement : (prev_move.tile_loc))
          if (coord == prev_placement)
            error = true;
    }

    if (error) {
      cout << ID << " not played.\n";
    } else {
      Move m{ID, move_num, '*', tile_placement};
      Moves.push_back(m);
      cout << "played " << ID << "\n";
      move_num++;
    }   // end of "secondary else"
  }   // end of "main else"
}   // end of method - entirely controlled by one if-else


void Blokus::set_size(int dim) {
  board_dim = dim;

  vector<Move>::iterator itr1 = Moves.begin();
  vector<Move> temp_moves = Moves;
  vector<Move>::iterator itr2 = temp_moves.begin();

  while (itr1 != Moves.end()) {
    auto move_indices = itr2->tile_loc;
    for (auto index : move_indices) {
      if (index.at(0) >= dim or index.at(1) >= dim) {
        temp_moves.erase(itr2);
        break;
      }
    }
    itr1++;
    itr2++;
  }

  Moves = temp_moves;
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