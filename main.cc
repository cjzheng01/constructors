#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "controller.h"
#include "file.h"
#include "player.h"
#include "shuffle.h"
using namespace std;

void makeChangeGame() {
  for (int i = 0; i <= 40; i++) {
    grid.at(i) = copy_g.at(i);
  }
  // change dice_num + change block
  for (int i = 0; i <= 18; i++) {
    block.at(i) = total.at(2 * i);
    dice_num.at(i) = total.at(2 *i + 1);
  }

  // change grid + copy block
  for (int i = 0; i <= 18; i++) {
    string replace = "BRICK ";
    if (block.at(i) == 1) replace = "ENERGY";
    else if (block.at(i) == 2) replace = "GLASS ";
    else if (block.at(i) == 3) replace = " HEAT ";
    else if (block.at(i) == 4) replace = " WIFI ";
    else if (block.at(i) == 5) replace = " PARK ";
    int x = name_x.at(i);
    int y = name_y.at(i);
    grid.at(x).replace(y-3, 6, replace);
  }
  for (int i = 0; i <= 18; i++) {
    string replace = " 2";
    if (dice_num.at(i) == 3) replace = " 3";
    else if (dice_num.at(i) == 4)  replace = " 4";
    else if (dice_num.at(i) == 5)  replace = " 5";
    else if (dice_num.at(i) == 6)  replace = " 6";
    else if (dice_num.at(i) == 7)  replace = "  ";
    else if (dice_num.at(i) == 8)  replace = " 8";
    else if (dice_num.at(i) == 9)  replace = " 9";
    else if (dice_num.at(i) == 10) replace = "10";
    else if (dice_num.at(i) == 11) replace = "11";
    else if (dice_num.at(i) == 12) replace = "12";
    int x = l_num_x.at(i);
    int y = l_num_y.at(i);
    grid.at(x).replace(y-1, 2, replace);
  }
  for (int i = 0; i <= 40; i++) {
    copy_g.at(i) = grid.at(i);
  }
  

  // place building
  for (int i = 0; i <= 53; i++) {
    int res = order[0]->getRes(i);
    int pos = 0;
    string s = "BB";
    if (res != 0) {
      pos = i;
      if (res == 2) s = "BH";
      else if (res == 3) s = "BT";
      int x = building_x.at(pos);
      int y = building_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }
  for (int i = 0; i <= 53; i++) {
    int res = order[1]->getRes(i);
    int pos = 0;
    string s = "RB";
    if (res != 0) {
      pos = i;
      if (res == 2) s = "RH";
      else if (res == 3) s = "RT";
      int x = building_x.at(pos);
      int y = building_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }
  for (int i = 0; i <= 53; i++) {
    int res = order[2]->getRes(i);
    int pos = 0;
    string s = "OB";
    if (res != 0) {
      pos = i;
      if (res == 2) s = "OH";
      else if (res == 3) s = "OT";
      int x = building_x.at(pos);
      int y = building_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }
  for (int i = 0; i <= 53; i++) {
    int res = order[3]->getRes(i);
    int pos = 0;
    string s = "YB";
    if (res != 0) {
      pos = i;
      if (res == 2) s = "YH";
      else if (res == 3) s = "YT";
      int x = building_x.at(pos);
      int y = building_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }
  // change road
  int num = 0;
  
  num = order[0]->getNumRoad();
  if (num != 0) {
    string s = "BR";
    for (int i = 0; i < num; i++) {
      int pos = order[0]->getRoad(i);
      int x = road_x.at(pos);
      int y = road_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }

  num = order[1]->getNumRoad();
  if (num != 0) {
    string s = "RR";
    for (int i = 0; i < num; i++) {
      int pos = order[1]->getRoad(i);
      int x = road_x.at(pos);
      int y = road_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }

  num = order[2]->getNumRoad();
  if (num != 0) {
    string s = "OR";
    for (int i = 0; i < num; i++) {
      int pos = order[2]->getRoad(i);
      int x = road_x.at(pos);
      int y = road_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }

  num = order[3]->getNumRoad();
  if (num != 0) {
    string s = "YR";
    for (int i = 0; i < num; i++) {
      int pos = order[3]->getRoad(i);
      int x = road_x.at(pos);
      int y = road_y.at(pos);
      grid.at(x).replace(y-1, 2, s);
    }
  }

  if (geese == -1) return;
  int xx = l_num_x.at(geese);
  int yy = l_num_y.at(geese);
  grid.at(xx+1).replace(yy-3, 5, "GEESE");
}


int main(int argc, char *argv[]){
      bool will_seed_dice = false;
      bool will_random_board = false;
      bool will_load_game = false;
      bool will_load_board = false;
      string file;
      int seed = -1;
    if (argc != 1){
      bool verified = false;
      for(int i = 1; i < argc; i++){
        if (verified){
          verified = false;
          continue;
        }
        string argv_str = argv[i];
        if (argv_str == "-random-board"){
            will_random_board = true;
          } else if (argv_str == "-seed"){
              if (i == argc - 1){
              cerr << "ERROR: -seed missing seed argument" << endl;
              exit(1);
          } else {
              will_seed_dice = true;
              verified = true;
              try {
                // string seed_str = argv[i + 1];
                seed = stoi(string(argv[i + 1]));
              }
              catch(invalid_argument& e){
		            cerr << e.what() << endl;
			          exit(1);
              }
              catch(out_of_range& e){
		            cerr << e.what() << endl;
			          exit(1);
              }
            }
        } else if (argv_str == "-board"){
            if (i == argc - 1){
              cerr << "ERROR: -board missing seed argument" << endl;
              exit(1);
            } else {
              will_load_board = true;
              verified = true;
              file = string(argv[i + 1]);
            }
        } else if (argv_str  == "-load"){
          if (i == argc - 1){
            cerr << "ERROR: -load missing seed argument" << endl;
            exit(1);
          } else {
              will_load_game = true;
              verified = true;
              file = string(argv[i + 1]);
          }
        } else {
            cerr << "ERROR: unrecognized argument " << argv_str  << endl;
            exit(1);
        }
      }
    }
    if (will_load_game && will_load_board){
      cerr << "ERROR: already specified -board, can't also specify -load" << endl;
      exit(1);
    }
    if (will_load_game || will_load_board){
        will_random_board = false;
    }
    if (will_load_game){
      to_vector_load(file);
      makeChangeGame();
    }
    if (will_load_board){
      if (cannot_open(file)){
        cerr << "ERROR: Unable to open file " << file << " for board layout." << endl;
        exit(1);
      } else {
        total = board_vector(file);
        makeChangeGame();
      }
    }
    if (will_seed_dice){
      SEED = seed;
    }
    if (will_random_board){
      total = random_board(seed);
      makeChangeGame();
    }

  Controller();
}
