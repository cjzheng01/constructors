#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include "controller.h"
#include "player.h"
#include "strategy.h"
using namespace std;

// ----------------------------- Global Variables ----------------------------
int geese = -1;
// initialize the players
Player blue{"Blue",     2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
Player red{"Red",       2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
Player orange{"Orange", 2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
Player yellow{"Yellow", 2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
vector<Player *> player_list = {&blue, &red, &orange, &yellow};
Player *cur = &blue;  // start with blue
vector<Player *> first_2_run = {&blue, &red, &orange, &yellow, &yellow, &orange, &red, &blue};
vector<Player *> order = {&blue, &red, &orange, &yellow};
vector<string> grid {"                                         | 0|-- 0--| 1|                                         ",
                     "                                        /              \\                                        ",
                     "                                       1                2                                       ",
                     "                                      /         0        \\                                      ",
                     "                        | 2|-- 3--| 3|       BRICK        | 4|-- 4--| 5|                        ",
                     "                       /              \\         3        /              \\                       ",
                     "                      5                6                7                8                      ",
                     "                     /         1        \\              /         2        \\                     ",
                     "       | 6|-- 9--| 7|       ENERGY       | 8|--10--| 9|        HEAT        |10|--11--|11|       ",
                     "      /              \\        10        /              \\         5        /              \\      ",
                     "     12               13               14               15               16               17    ",
                     "    /         3        \\              /         4        \\              /         5        \\    ",
                     "|12|       ENERGY       |13|--18--|14|        PARK        |15|--19--|16|        HEAT        |17|",
                     "    \\         4        /              \\                  /              \\        10        /    ",
                     "     20               21               22               23               24               25    ",
                     "      \\              /         6        \\              /         7        \\              /      ",
                     "       |18|--26--|19|       GLASS        |20|--27--|21|       BRICK        |22|--28--|23|       ",
                     "      /              \\        11        /              \\         3        /              \\      ",
                     "     29               30               31               32               33               34    ",
                     "    /         8        \\              /         9        \\              /        10        \\    ",
                     "|24|        HEAT        |25|--35--|26|       BRICK        |27|--36--|28|       BRICK        |29|",
                     "    \\         8        /              \\         2        /              \\         6        /    ",
                     "     37               38               39               40               41               42    ",
                     "      \\              /        11        \\              /        12        \\              /      ",
                     "       |30|--43--|31|       ENERGY       |32|--44--|33|        WIFI        |34|--45--|35|       ",
                     "      /              \\         8        /              \\        12        /              \\       ",
                     "     46               47               48               49               50               51    ",
                     "    /        13        \\              /        14        \\              /        15        \\    ",
                     "|36|       ENERGY       |37|--52--|38|        WIFI        |39|--53--|40|       GLASS        |41|",
                     "    \\         5        /              \\        11        /              \\         4        /    ",
                     "     54               55               56               57               58               59    ",
                     "      \\              /        16        \\              /        17        \\              /      ",
                     "       |42|--60--|43|        WIFI        |44|--61--|45|       GLASS        |46|--62--|47|       ",
                     "                     \\         6        /              \\         9        /                     ",
                     "                      63               64               65               66                     ",
                     "                       \\              /        18        \\              /                       ",
                     "                        |48|--67--|49|       GLASS        |50|--68--|51|                        ",
                     "                                      \\         9        /                                      ",
                     "                                       69               70                                      ",
                     "                                        \\              /                                        ",
                     "                                         |52|--71--|53|                                         "};
vector<string> copy_g {"                                         | 0|-- 0--| 1|                                         ",
                     "                                        /              \\                                        ",
                     "                                       1                2                                       ",
                     "                                      /         0        \\                                      ",
                     "                        | 2|-- 3--| 3|       BRICK        | 4|-- 4--| 5|                        ",
                     "                       /              \\         3        /              \\                       ",
                     "                      5                6                7                8                      ",
                     "                     /         1        \\              /         2        \\                     ",
                     "       | 6|-- 9--| 7|       ENERGY       | 8|--10--| 9|        HEAT        |10|--11--|11|       ",
                     "      /              \\        10        /              \\         5        /              \\      ",
                     "     12               13               14               15               16               17    ",
                     "    /         3        \\              /         4        \\              /         5        \\    ",
                     "|12|       ENERGY       |13|--18--|14|        PARK        |15|--19--|16|        HEAT        |17|",
                     "    \\         4        /              \\                  /              \\        10        /    ",
                     "     20               21               22               23               24               25    ",
                     "      \\              /         6        \\              /         7        \\              /      ",
                     "       |18|--26--|19|       GLASS        |20|--27--|21|       BRICK        |22|--28--|23|       ",
                     "      /              \\        11        /              \\         3        /              \\      ",
                     "     29               30               31               32               33               34    ",
                     "    /         8        \\              /         9        \\              /        10        \\    ",
                     "|24|        HEAT        |25|--35--|26|       BRICK        |27|--36--|28|       BRICK        |29|",
                     "    \\         8        /              \\         2        /              \\         6        /    ",
                     "     37               38               39               40               41               42    ",
                     "      \\              /        11        \\              /        12        \\              /      ",
                     "       |30|--43--|31|       ENERGY       |32|--44--|33|        WIFI        |34|--45--|35|       ",
                     "      /              \\         8        /              \\        12        /              \\       ",
                     "     46               47               48               49               50               51    ",
                     "    /        13        \\              /        14        \\              /        15        \\    ",
                     "|36|       ENERGY       |37|--52--|38|        WIFI        |39|--53--|40|       GLASS        |41|",
                     "    \\         5        /              \\        11        /              \\         4        /    ",
                     "     54               55               56               57               58               59    ",
                     "      \\              /        16        \\              /        17        \\              /      ",
                     "       |42|--60--|43|        WIFI        |44|--61--|45|       GLASS        |46|--62--|47|       ",
                     "                     \\         6        /              \\         9        /                     ",
                     "                      63               64               65               66                     ",
                     "                       \\              /        18        \\              /                       ",
                     "                        |48|--67--|49|       GLASS        |50|--68--|51|                        ",
                     "                                      \\         9        /                                      ",
                     "                                       69               70                                      ",
                     "                                        \\              /                                        ",
                     "                                         |52|--71--|53|                                         "};
vector<string>::iterator it;
vector<int> building_x {0 , 0, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 12, 12, 12, 12, 12, 12, 16, 16, 16, 16,
                        16, 16, 20, 20, 20, 20, 20, 20, 24, 24, 24, 24, 24, 24, 28, 28, 28, 28, 28, 28,
                        32, 32, 32, 32, 32, 32, 36, 36, 36, 36, 40, 40};
vector<int> building_y {43, 53, 26, 36, 60, 70, 9, 19, 43, 53, 77, 87, 2, 26, 36, 60, 70, 94, 9, 19,
                        43, 53, 77, 87, 2, 26, 36, 60, 70, 94, 9, 19, 43, 53, 77, 87, 2, 26, 36, 60, 70,
                        94, 9, 19, 43, 53, 77, 87, 26, 36, 60, 70, 43, 53};

vector<int> road_x {0, 2, 2, 4, 4, 6, 6, 6, 6, 8, 8, 8, 10, 10, 10, 10, 10, 10, 12, 12, 14, 14,
                    14, 14, 14, 14, 16, 16, 16, 18, 18, 18, 18, 18, 18, 20, 20, 22, 22, 22, 22,
                    22, 22, 24, 24, 24, 26, 26, 26, 26, 26, 26, 28, 28, 30, 30, 30, 30, 30, 30,
                    32, 32, 32, 34, 34, 34, 34, 36, 36, 38, 38, 40};
vector<int> road_y {48, 40, 57, 31, 65, 23, 40, 57, 74, 14, 48, 82,  6, 23, 40, 57, 74, 91, 31,
                    65,  6, 23, 40, 57, 74, 91, 14, 48, 82,  6, 23, 40, 57, 74, 91, 31, 65,  6,
                    23, 40, 57, 74, 91, 14, 48, 82,  6, 23, 40, 57, 74, 91, 31, 65,  6, 23, 40,
                    57, 74, 91, 14, 48, 82, 23, 40, 57, 74, 31, 65, 40, 57, 48};

vector<int> l_num_x{5, 9, 9, 13, 13, 13, 17, 17, 21, 21, 21, 25, 25, 29, 29, 29, 33, 33, 37};
vector<int> l_num_y{48, 31, 65, 14, 48, 82, 31, 65, 14, 48, 82, 31, 65, 14, 48, 82, 31, 65, 48};
//
vector<int> dice_num{3, 10, 5, 4, 0, 10, 11, 3, 8, 2, 6, 8, 12, 5, 11, 4, 6, 9, 9};

// 
vector<int> name_x{4, 8, 8, 12, 12, 12, 16, 16, 20, 20, 20, 24, 24, 28, 28, 28, 32, 32, 36};
vector<int> name_y{48, 31, 65, 14, 48, 82, 31, 65, 14, 48, 82, 31, 65, 14, 48, 82, 31, 65, 48};

// block name [BRICK = 0] [ENERGY = 1] [GALSS = 2] [HEAT = 3] [WIFI = 4] [Park = 5]
vector<int> block{0, 1, 3, 1, 5, 3, 2, 0, 3, 0, 0, 1, 4, 1, 4, 2, 4, 2, 2};

vector<int> blue_gain{0, 0, 0, 0, 0};
vector<int> red_gain {0, 0, 0, 0, 0};
vector<int> orange_gain{0, 0, 0, 0, 0};
vector<int> yellow_gain{0, 0, 0, 0, 0};

vector<int> total{0, 3, 1, 10, 3, 5, 1, 4, 5, 7, 3, 10, 2, 11, 0, 3, 3, 8, 0, 2,
                  0, 6, 1, 8, 4, 12, 1, 5, 4, 11, 2, 4, 4, 6, 2, 9, 2, 9};

int loaded_round = 0;
int ROUND = 0;
int CURR_TURN;
int SEED = -1; // seed
bool LOADED =false;

// dice
int LOAD_DICE;
Load LD;
Fair FD;
// ----------------------------- HELPER FUNCTIONS ----------------------------

// is_number(s) returns true if s is a number.
bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_colour(char c) {
  return (c == 'B' || c == 'R' || c == 'O' || c == 'Y');
}

void print_board() {
  for (auto i = grid.begin(); i != grid.end(); i++) {
    cout << *i << endl;
  }
}


void Controller::print_all_buildings_position(vector<int> x, vector<int> y) {
  cout << "Basements already exist as locations: ";
  int len = x.size();
  for (int i =0; i < len; i++) {
    int xx = x.at(i);
    int yy = y.at(i);
    string s = grid.at(xx);
    char c = s.at(yy);
    if (c=='B' || c =='H' || c=='T') {
      string copy_s = copy_g.at(xx);
      if (copy_s.at(yy-1)!=' ') cout << copy_s.at(yy-1);
      cout << copy_s.at(yy) << " ";
    }
  }
  cout << endl;
}

char getChar(int x, int y) {
  if (x < 0 || x > 40 || y < 0 || y > 95) { // put of bound
  return '?'; // ?  means out of bound
  }
  string s = grid.at(x);
  return s.at(y);
}

bool buildingChar(char c) {
  return c == 'B' || c == 'T' || c == 'H';
}

bool canPutBasement(int pos) {
  // check if it is empty
  int x = building_x.at(pos);
  int y = building_y.at(pos);
  // check if it is empty
  if (getChar(x, y) == 'B' || getChar(x, y) == 'H' || getChar(x, y) == 'T') return false;
  // check surrondings
  // two cases
  if (y == 2 || y == 19 || y == 36 || y == 53 || y == 70 || y == 87) {
    // left, top-right, bottom-right checker
    if (buildingChar(getChar(x, y-10)) || buildingChar(getChar(x-4, y+7)) || buildingChar(getChar(x+4, y+7))) {
      return false;
    }
    return true;
  } else if (y == 9 || y == 26 || y == 43 || y == 60 || y == 77 || y == 94) {
    // right, top-left, bottom-left checker
    if (buildingChar(getChar(x, y+10)) || buildingChar(getChar(x-4,y-7)) || buildingChar(getChar(x+4, y-7))) {
      return false;
    }
    return true;
  }
  return false;
}

void Controller::buildBuilding(int pos, char type, string who) {
  // color
  string first = "B";
  if (who == "Red") first = "R";
  else if (who == "Orange") first = "O";
  else if (who == "Yellow") first = "Y";
  // building
  string second = "";
  second.push_back(type);
  first+=second;
  int x = building_x.at(pos);
  int y = building_y.at(pos);
  // replace gird
  grid.at(x).replace(y-1, 2, first);
}


void addResource(string type, vector<Player *> list) {
  int len = list.size();
  if (type == "ENERGY") {
    for (int i = 0; i < len; i++) {
      string name = list.at(i)->get_name();
      if (name == "Blue") blue_gain.at(1)++;
      else if (name == "Red") red_gain.at(1)++;
      else if (name == "Orange") orange_gain.at(1)++;
      else yellow_gain.at(1)++;
    }
  } else if (type == "WIFI") {
    for (int i = 0; i < len; i++) {
      string name = list.at(i)->get_name();
      if (name == "Blue") blue_gain.at(4)++;
      else if (name == "Red") red_gain.at(4)++;
      else if (name == "Orange") orange_gain.at(4)++;
      else yellow_gain.at(4)++;
    }
  } else if (type == "BRICK") {
    for (int i = 0; i < len; i++) {
      string name = list.at(i)->get_name();
      if (name == "Blue") blue_gain.at(0)++;
      else if (name == "Red") red_gain.at(0)++;
      else if (name == "Orange") orange_gain.at(0)++;
      else yellow_gain.at(0)++;
    }
  } else if (type == "GLASS") {
    for (int i = 0; i < len; i++) {
      string name = list.at(i)->get_name();
      if (name == "Blue") blue_gain.at(2)++;
      else if (name == "Red") red_gain.at(2)++;
      else if (name == "Orange") orange_gain.at(2)++;
      else yellow_gain.at(2)++;
    }
  } else {
    for (int i = 0; i < len; i++) {
      string name = list.at(i)->get_name();
      if (name == "Blue") blue_gain.at(3)++;
      else if (name == "Red") red_gain.at(3)++;
      else if (name == "Orange") orange_gain.at(3)++;
      else yellow_gain.at(3)++;
    }
  }
}

void getResource(int dice, Player *blue, Player *red, Player *orange, Player *yellow) {
  if (dice == 7) return;
  if (dice < 2 || dice > 12) return;
  // dice_num -> block_num -> block_coor -> resource_name ->building_corr->update
  int dice_num_len = dice_num.size();
  for (int i = 0; i < dice_num_len; i++) { // 
    if (dice_num.at(i) == dice) { // 
      vector<Player *> list;
      // 
      int x = name_x.at(i);
      int y = name_y.at(i);
      // check GEESE
      if (getChar(x+2, y) != ' ') { // meet Geese
        continue;
      }
      char c1 = getChar(x-4, y-6);
      char c2 = getChar(x-4, y+4);
      char c3 = getChar(x, y-13);
      char c4 = getChar(x, y+11);
      char c5 = getChar(x+4, y-6);
      char c6 = getChar(x+4, y+4);
      // add to list
      if (c1 == 'B') list.emplace_back(blue);
      else if (c1 == 'R') list.emplace_back(red);
      else if (c1 == 'O') list.emplace_back(orange);
      else if (c1 == 'Y') list.emplace_back(yellow);
      if (c2 == 'B') list.emplace_back(blue);
      else if (c2 == 'R') list.emplace_back(red);
      else if (c2 == 'O') list.emplace_back(orange);
      else if (c2 == 'Y') list.emplace_back(yellow);
      if (c3 == 'B') list.emplace_back(blue);
      else if (c3 == 'R') list.emplace_back(red);
      else if (c3 == 'O') list.emplace_back(orange);
      else if (c3 == 'Y') list.emplace_back(yellow);
      if (c4 == 'B') list.emplace_back(blue);
      else if (c4 == 'R') list.emplace_back(red);
      else if (c4 == 'O') list.emplace_back(orange);
      else if (c4 == 'Y') list.emplace_back(yellow);
      if (c5 == 'B') list.emplace_back(blue);
      else if (c5 == 'R') list.emplace_back(red);
      else if (c5 == 'O') list.emplace_back(orange);
      else if (c5 == 'Y') list.emplace_back(yellow);
      if (c6 == 'B') list.emplace_back(blue);
      else if (c6 == 'R') list.emplace_back(red);
      else if (c6 == 'O') list.emplace_back(orange);
      else if (c6 == 'Y') list.emplace_back(yellow);
      if (getChar(x, y) == 'R') addResource("ENERGY", list);
      else if (getChar(x, y) == 'S') addResource("GLASS", list);
      else if (getChar(x, y) == 'C') addResource("BRICK", list);
      else if (getChar(x, y) == 'A') addResource("HEAT", list);
      else addResource("WIFI", list);
    }
  }
}

bool justGotResource(string who) {
  if (who == "Blue") {
    for (int i = 0; i < 5; i++) {
      if (blue_gain.at(i)!=0) {
        return true;
      }
    }
  } else if (who == "Red") {
    for (int i = 0; i < 5; i++) {
      if (red_gain.at(i)!=0) {
        return true;
      }
    }
  } else if (who == "Orange") {
    for (int i = 0; i < 5; i++) {
      if (orange_gain.at(i)!=0) {
        return true;
      }
    }
  } else {
    for (int i = 0; i< 5; i++) {
      if (yellow_gain.at(i)!=0) {
        return true;
      }
    }
  }
  return false;
}

void print_gain(Player *who) {
  if (who->get_name() == "Blue") {
    for (int i = 0; i < 5; i++) {
      if (blue_gain.at(i)!=0) {
        cout << blue_gain.at(i) << " ";
        if (i == 0) cout << "BRICK" << endl, who->addResource("BRICK", blue_gain.at(i));
        else if (i == 1) cout << "ENERGY" << endl, who->addResource("ENERGY", blue_gain.at(i));
        else if (i == 2) cout << "GLASS" << endl, who->addResource("GLASS", blue_gain.at(i));
        else if (i == 3) cout << "HEAT" << endl, who->addResource("HEAT", blue_gain.at(i));
        else cout << "WIFI" << endl, who->addResource("WIFI", blue_gain.at(i));
      }
    }
  } else if (who->get_name() == "Red") {
    for (int i = 0; i < 5; i++) {
      if (red_gain.at(i)!=0) {
        cout << red_gain.at(i) << " ";
        if (i == 0) cout << "BRICK" << endl, who->addResource("BRICK", red_gain.at(i));
        else if (i == 1) cout << "ENERGY" << endl, who->addResource("ENERGY", red_gain.at(i));
        else if (i == 2) cout << "GLASS" << endl, who->addResource("GLASS", red_gain.at(i));
        else if (i == 3) cout << "HEAT" << endl, who->addResource("HEAT", red_gain.at(i));
        else cout << "WIFI" << endl, who->addResource("WIFI", red_gain.at(i));
      }
    }
  } else if (who->get_name() == "Orange") {
    for (int i = 0; i < 5; i++) {
      if (orange_gain.at(i)!=0) {
        cout << orange_gain.at(i) << " ";
        if (i == 0) cout << "BRICK" << endl, who->addResource("BRICK", orange_gain.at(i));
        else if (i == 1) cout << "ENERGY" << endl, who->addResource("ENERGY", orange_gain.at(i));
        else if (i == 2) cout << "GLASS" << endl, who->addResource("GLASS", orange_gain.at(i));
        else if (i == 3) cout << "HEAT" << endl, who->addResource("HEAT", orange_gain.at(i));
        else cout << "WIFI" << endl, who->addResource("WIFI", orange_gain.at(i));
      }
    }
  } else {
    for (int i = 0; i < 5; i++) {
      if (yellow_gain.at(i)!=0) {
        cout << yellow_gain.at(i) << " ";
        if (i == 0) cout << "BRICK" << endl, who->addResource("BRICK", yellow_gain.at(i));
        else if (i == 1) cout << "ENERGY" << endl, who->addResource("ENERGY", yellow_gain.at(i));
        else if (i == 2) cout << "GLASS" << endl, who->addResource("GLASS", yellow_gain.at(i));
        else if (i == 3) cout << "HEAT" << endl, who->addResource("HEST", yellow_gain.at(i));
        else cout << "WIFI" << endl, who->addResource("WIFI", yellow_gain.at(i));
      }
    }
  }
}

void reset_gain() {
  for (int i = 0; i < 5; i++) {
    blue_gain.at(i) = 0;
    red_gain.at(i) = 0;
    orange_gain.at(i) = 0;
    yellow_gain.at(i) = 0;
  }
}

void Controller::setGeese() {
  if (geese == -1) { cout << "geese = -1 , error, setGeese" << endl; return; }
  int x = name_x.at(geese);
  int y = name_y.at(geese);
  x += 2;
  y -= 3;
  grid.at(x).replace(y, 5, "GEESE");
}

void Controller::steal(Player *cur, vector<int> & list) {
  // check surronding
  if (geese == -1) { cout << "geese = -1 , error steal" << endl; return; }
  int x = name_x.at(geese);
  int y = name_y.at(geese);
  char c1 = getChar(x-4, y-6);
  char c2 = getChar(x-4, y+4);
  char c3 = getChar(x, y-13);
  char c4 = getChar(x, y+11);
  char c5 = getChar(x+4, y-6);
  char c6 = getChar(x+4, y+4);
  if (c1 == 'B' || c2 == 'B'|| c3== 'B' ||c4 == 'B' || c5 == 'B' ||c6 == 'B') list.at(0) = 1;
  if (c1 == 'R' || c2 == 'R'|| c3== 'R' ||c4 == 'R' || c5 == 'R' ||c6 == 'R') list.at(1) = 1;
  if (c1 == 'O' || c2 == 'O'|| c3== 'O' ||c4 == 'O' || c5 == 'O' ||c6 == 'O') list.at(2) = 1;
  if (c1 == 'Y' || c2 == 'Y'|| c3== 'Y' ||c4 == 'Y' || c5 == 'Y' ||c6 == 'Y') list.at(3) = 1;
  if (cur->get_name() == "Blue") list.at(0) = 0;
  else if (cur->get_name() == "Red") list.at(1) = 0;
  else if (cur->get_name() == "Orange") list.at(2) = 0;
  else list.at(3) = 0;
}

// has side effect
bool canStealFrom(vector<Player*> list, string in, Player *cur) {
  if (in == "BLUE" || in == "blue" || in == "Blue") in = "Blue";
  else if (in == "RED" || in == "red" || in == "Red") in = "Red";
  else if (in == "ORANGE" || in == "orange" || in == "Orange") in = "Orange";
  else if (in == "YELLOW" || in == "yellow" || in == "Yellow") in = "Yellow";
  else {cout << "Invalid colour." << endl; return false;}
  int len = list.size();
  bool check = false;
  Player *target = nullptr;
  for (int i = 0; i < len; i++) {
    if (list.at(i)->get_name() == in) {
      target = list.at(i);
      check = true;
      break;
    }
  }
  if (!check) {cout << "They can't be stolen from." << endl; return false;}
  randomLoseResource(target, cur);
  return true;
}

string toColour(string str) {
  if (str == "Blue" || str == "blue" || str == "BLUE") return "Blue";
  else if (str == "Red" || str == "red" || str == "RED") return "Red";
  else if (str == "Orange" || str == "orange" || str == "ORANGE") return "Orange";
  else if (str == "Yellow" || str == "yellow" || str == "YELLOW") return "Yellow";
  else return "?";
}

string toResource(string str) {
  if (str == "ENERGY" || str == "energy" ) return "ENERGY";
  else if (str == "BRICK" || str == "brick" ) return "BRICK";
  else if (str == "HEAT" || str == "heat") return "HEAT";
  else if (str == "WIFI" || str == "wifi" ) return "WIFI";
  else if (str == "GLASS" || str == "glass") return "GLASS";
  else return "?";
}

bool checkBuildRoad(int pos, string na) {
  char name = 'B';
  if (na == "Red") name = 'R';
  else if (na == "Orange") name = 'O';
  else if (na == "Yellow") name = 'Y';
  // check valid
  if (pos < 0 || pos > 71) return false;
  // check this pos
  int x = road_x.at(pos);
  int y = road_y.at(pos);
  char c = getChar(x, y);
  if (c == 'R') return false;
  bool building = false;
  bool road = false;
  // check building
  if (getChar(x, y-6) == name || getChar(x, y+4) == name || getChar(x-2, y+2) == name ||
      getChar(x+2, y-5) == name || getChar(x-2, y-5) == name || getChar(x+2, y+2) == name) {
    building = true;
  }
  // check road
  if(getChar(x-2, y-9) == name || getChar(x-2, y+8) == name || getChar(x+2, y-9) == name ||
     getChar(x+2, y+8) == name || getChar(x-4, y-1) == name || getChar(x-2, y-10) == name || 
     getChar(x+2, y+7) == name || getChar(x+4, y-1) == name || getChar(x+2, y-5) == name) {
    road = true;
  }
  return building || road;
}

bool checkBasement(int pos, string na) {
  char name = 'B';
  if (na == "Red") name = 'R';
  else if (na == "Orange") name = 'O';
  else if (na == "Yellow") name = 'Y';
  // check valid
  if (pos < 0 || pos > 53) return false;
  // check this pos
  int x = building_x.at(pos);
  int y = building_y.at(pos);
  char c = getChar(x, y-1);
  y--;
  if (is_colour(c)) return false;
  // check building
  if (is_colour(getChar(x-4, y-7)) || is_colour(getChar(x, y+10)) ||
      is_colour(getChar(x+4, y-7)) || is_colour(getChar(x-4, y+7)) || 
      is_colour(getChar(x, y-10)) || is_colour(getChar(x+4, y+7))) {
    return false;
  }
  // check road
  if(getChar(x, y-5) == name || getChar(x-2, y+4) == name || getChar(x+2, y+4) == name ||
     getChar(x, y+5) == name || getChar(x-2, y-3) == name || getChar(x+2, y-3) == name) {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------
Controller::Controller(){
if (LOADED == false){
  // print it at the beginninng of the game
  for (auto i = grid.begin(); i != grid.end(); i++) {
    cout << *i << endl;
  }

  //  reset the plyer's info
  order[0]->setResource("brick", 0);
  order[0]->setResource("energy", 0);
  order[0]->setResource("wifi", 0);
  order[0]->setResource("glass", 0);
  order[0]->setResource("heat", 0);
  order[0]->setPoint(2);
  order[1]->setResource("brick", 0);
  order[1]->setResource("energy", 0);
  order[1]->setResource("wifi", 0);
  order[1]->setResource("glass", 0);
  order[1]->setResource("heat", 0);
  order[1]->setPoint(2);
  order[2]->setResource("brick", 0);
  order[2]->setResource("energy", 0);
  order[2]->setResource("wifi", 0);
  order[2]->setResource("glass", 0);
  order[2]->setResource("heat", 0);
  order[2]->setPoint(2);
  order[3]->setResource("brick", 0);
  order[3]->setResource("energy", 0);
  order[3]->setResource("wifi", 0);
  order[3]->setResource("glass", 0);
  order[3]->setResource("heat", 0);
  order[3]->setPoint(2);
  // roads
  order[0]->clearRoad();
  order[1]->clearRoad();
  order[2]->clearRoad();
  order[3]->clearRoad();
  order[0]->setNumRoad();
  order[1]->setNumRoad();
  order[2]->setNumRoad();
  order[3]->setNumRoad();
  // res
  for(int i = 0; i<= 53; i++) {
    order[0]->setRes(i, 0);
    order[1]->setRes(i, 0);
    order[2]->setRes(i, 0);
    order[3]->setRes(i, 0);
  }


  // define local some variable
  
  int first_2_run_len = first_2_run.size();

  
  
  for (int i = 0; i < first_2_run_len; i++) {
    //
    cur = first_2_run.at(i);
    cout << "Builder " << cur->get_name() << " where do you want to build a basement? [end] to end game, [print] to print the board."
         << endl;
    cout << "> ";
    // reads the position
    string in;
    while (getline(cin, in)) {
      if (in == "end") {
        cout << "Bye :-)" << endl;
        return;
      }
      bool check = true; // 
      if (in == "print") {
        print_board();
        cout << "Builder " << cur->get_name() << " where do you want to build a basement? [end] to end game, [print] to print the board."
         << endl;
        cout << "> ";
        check = false;
      }else if (!is_number(in) && in != "print") { //
        check = false;
        cout << "ERROR: Builder " << cur->get_name() 
             << " where do you want to build a basement? isn't a valid integer." << endl;
        cout << "> ";
      } else {  
        int x = stoi(in);
        
        if (x < 0 || x > 53) {
          cout << "You cannot build here." << endl;
          print_all_buildings_position(building_x, building_y);
          cout << "Builder " << cur->get_name() << " where do you want to build a basement? [end] to end game, [print] to print the board."
         << endl;
          cout << "> ";
          check = false;
        } else { 
          if (canPutBasement(x)) { 
            buildBuilding(x, 'B', cur->get_name());
            // change player's info
            cur->improveRes(x);
          } else {  
            cout << "You cannot build here." << endl;
            print_all_buildings_position(building_x, building_y);
            cout << "Builder " << cur->get_name() << " where do you want to build a basement? [end] to end game, [print] to print the board."
         << endl;
            cout << "> ";
            check = false;
          }
        }
      } 
      
      if (check) break;
    }

  }
}

//-------------------two runs ends------------------------

  
  int occ = 0;

  while (true) {
    
    if (loaded_round != 0 && LOADED == true){
      ROUND = loaded_round / 4;
      occ = loaded_round % 4;
      LOADED = false;
      --loaded_round;
    }
    
    print_board();
    if (occ == 4) {
      occ = 0;
      ++ROUND;
    }
    CURR_TURN = ROUND * 4 + occ;
    cur = order.at(occ);
    cout << "Builder " << cur->get_name() << "'s turn." << endl;
    cout << "> ";
    // wait for command
    string in;

    bool end_command_one = false;
    // first round
    while ((!end_command_one) && getline(cin, in)) {

      if (in == "help") { //------------------------------------ help
        cout << "Valid commands:" << endl;
        cout << "~ load : changes current builder's dice type to 'loaded'" << endl;
        cout << "~ fair : changes current builder's dice type to 'fair'" << endl;
        cout << "~ roll : rolls the dice and distributes resources." << endl;
        cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << endl;
        cout << "~ help : prints out the list of commands." << endl;
        cout << "~ end: end the game now." << endl;
        cout << "> ";
        continue;
      } 
      else if (in == "load") { // ----------------------------------- load
        cur->setDice('l');
        cout << "Builder " << cur->get_name() << " now has loaded Dice." << endl;
        cout << "> ";
        continue;
      } 
      else if (in == "fair") {  //  ------------------------------------fair
        cur->setDice('f');
        cout << "Builder " << cur->get_name() << " now has fair Dice." << endl;
        cout << "> ";
      } 
      else if (in == "roll") { // -----------------------------------------------------------------------------roll
        if (cur->isLoad()) { // ---------------------------------------------------------is load dice
          cout << "Input a roll between 2 and 12:" << endl;
          cout << "> ";
          string dice_num_str;
          while (getline(cin, dice_num_str)) {  // check for number
            if(is_number(dice_num_str)) {
              int x = stoi(dice_num_str);
              if (x < 2 || x > 12) { // invalid number
                cout << "Invalid roll " << x << "." << endl;
                cout << "> ";
                continue;
              } else {  // valid number
                cout << "The number you rolled is " << x << "." << endl;
                getResource(x, &blue, &red, &orange, &yellow);
                // add resource to player
                bool check = false;
                if (justGotResource("Blue") || justGotResource("Red") ||
                    justGotResource("Orange") || justGotResource("Yellow")) {
                    check = true;
                }
                if (check) { // somewho got resource
                  if (justGotResource("Blue")) {
                    cout << "Builder Blue gained:" << endl;
                    print_gain(&blue);
                  }
                  if (justGotResource("Red")) {
                    cout << "Builder Red gained:" << endl;
                    print_gain(&red);
                  }
                  if (justGotResource("Orange")) {
                    cout << "Builder Orange gained:" << endl;
                    print_gain(&orange);
                  }
                  if (justGotResource("Yellow")) {
                    cout << "Builder Yellow gained:" << endl;
                    print_gain(&yellow);
                  }
                  // clear all gain to empty
                  reset_gain();
                } else {
                  if (x == 7) { //------------------------------------------------------GEESE
                    // >=10 resource player lose resource
                    blue.mayLoseResourceToGeese();
                    red.mayLoseResourceToGeese();
                    orange.mayLoseResourceToGeese();
                    yellow.mayLoseResourceToGeese();
                    cout << "Choose where to place the GEESE." << endl;
                    cout << "> ";
                    string whereGeese;
                    while (getline(cin, whereGeese)) {
                      if (!is_number(whereGeese)) {
                        cout << "ERROR: Choose where to place the GEESE. isn't a valid integer." << endl;
                        cout << "> ";
                      } else {
                        int where = stoi(whereGeese);
                        if (where == geese || where < 0 || where > 18) { //重复了or 出格了
                          cout << "Geese can't move here." << endl;
                          cout << "> ";
                        } else { // 可以放这
                          if (geese != -1) { // has geese somewhere, clear the position
                            int x = name_x.at(geese);
                            int y = name_y.at(geese);
                            x += 2;
                            y -= 3;
                            grid.at(x).replace(y, 5, "     ");
                          }
                          geese = where;
                          setGeese();
                          vector<int> list;
                          for (int i = 0; i < 4; i++) {
                            list.emplace_back(0);
                          }
                          steal(cur, list);
                          bool canSteal = false;
                          for (int i = 0; i < 4; i++) {
                            if (list.at(i) != 0) canSteal = true;
                          }
                          if (canSteal) {
                            canSteal = false;
                            for (int i = 0; i < 4; i++) {
                              if (list.at(i) != 0 && player_list.at(i)->numResource() > 0) {
                                canSteal = true;
                              }
                            }
                          }
                          if (!canSteal) {
                            cout << "Builder " << cur->get_name() << " has no builders to steal from." << endl;
                            cout << "> ";
                          } else { // has target to steal
                            vector<Player *> steal_list;
                            for (int i = 0; i < 4; i++) {
                              if (list.at(i) != 0 && player_list.at(i)->numResource() > 0) {
                                steal_list.emplace_back(player_list.at(i));
                              }
                            }
                            cout << "Builder " << cur->get_name() << " can choose to steal from ";
                            cout << "> ";
                            int len  = steal_list.size();
                            for (int i = 0; i < len; i++) {
                              cout << steal_list.at(i)->get_name();
                              if (i == len - 1) {
                                cout << "." << endl;
                              } else {
                                cout << ", ";
                              }
                            }
                            // print message ends
                            cout << "Choose a builder to steal from." << endl;
                            cout << "> ";
                            string stealfrom;
                            while (getline(cin, stealfrom)) {
                              if (canStealFrom(steal_list, stealfrom, cur)) {
                                break;
                              } else { // cannot steal from
                                cout << "Choose a builder to steal from." << endl;
                                cout << "> ";
                              }
                            }
                          }
                          break;
                        }
                      }
                    }
                  } else {
                    cout << "No builders gained resources." << endl;
                  }
                  end_command_one = true;
                  break;
                }
                end_command_one = true; // end the first round
                break;
              }
            } else { // input is not even a number
              cout << "ERROR:  isn't a valid integer." << endl;
              cout << "> ";
              continue;
            }
          }
        } else { // ---------------------------------------------------------------------fair dice rolling
          /*int x;
          int y;
          x = (rand()%6) + 1;
          y = (rand()%6) + 1;
          x += y;
          */
          int x = FD.roll_fair();
              if (x < 2 || x > 12) { // invalid number
                cout << "Invalid roll " << x << "." << endl;
                cout << "> ";
                continue;
              } else {  // valid number
                cout << "The number you rolled is " << x << "." << endl;
                getResource(x, &blue, &red, &orange, &yellow);
                // add resource to player
                bool check = false;
                if (justGotResource("Blue") || justGotResource("Red") ||
                    justGotResource("Orange") || justGotResource("Yellow")) {
                    check = true;
                }
                if (check) { // somewho got resource
                  if (justGotResource("Blue")) {
                    cout << "Builder Blue gained:" << endl;
                    print_gain(&blue);
                  }
                  if (justGotResource("Red")) {
                    cout << "Builder Red gained:" << endl;
                    print_gain(&red);
                  }
                  if (justGotResource("Orange")) {
                    cout << "Builder Orange gained:" << endl;
                    print_gain(&orange);
                  }
                  if (justGotResource("Yellow")) {
                    cout << "Builder Yellow gained:" << endl;
                    print_gain(&yellow);
                  }
                  // clear all gain to empty
                  reset_gain();
                } else {
                  if (x == 7) { //------------------------------------------------------GEESE
                    // >=10 resource player lose resource
                    blue.mayLoseResourceToGeese();
                    red.mayLoseResourceToGeese();
                    orange.mayLoseResourceToGeese();
                    yellow.mayLoseResourceToGeese();
                    cout << "Choose where to place the GEESE." << endl;
                    cout << "> ";
                    string whereGeese;
                    while (getline(cin, whereGeese)) {
                      if (!is_number(whereGeese)) {
                        cout << "ERROR: Choose where to place the GEESE. isn't a valid integer." << endl;
                        cout << "> ";
                      } else {
                        int where = stoi(whereGeese);
                        if (where == geese || where < 0 || where > 18) { //重复了or 出格了
                          cout << "Geese can't move here." << endl;
                          cout << "> ";
                        } else { // 可以放这
                          if (geese != -1) { // has geese somewhere, clear the position
                            int x = name_x.at(geese);
                            int y = name_y.at(geese);
                            x += 2;
                            y -= 3;
                            grid.at(x).replace(y, 5, "     ");
                          }
                          geese = where;
                          setGeese();
                          vector<int> list;
                          for (int i = 0; i < 4; i++) {
                            list.emplace_back(0);
                          }
                          steal(cur, list);
                          bool canSteal = false;
                          for (int i = 0; i < 4; i++) {
                            if (list.at(i) != 0) canSteal = true;
                          }
                          if (canSteal) {
                            canSteal = false;
                            for (int i = 0; i < 4; i++) {
                              if (list.at(i) != 0 && player_list.at(i)->numResource() > 0) {
                                canSteal = true;
                              }
                            }
                          }
                          if (!canSteal) {
                            cout << "Builder " << cur->get_name() << " has no builders to steal from." << endl;
                            cout << "> ";
                          } else { // has target to steal
                            vector<Player *> steal_list;
                            for (int i = 0; i < 4; i++) {
                              if (list.at(i) != 0 && player_list.at(i)->numResource() > 0) {
                                steal_list.emplace_back(player_list.at(i));
                              }
                            }
                            cout << "Builder " << cur->get_name() << " can choose to steal from ";
                            cout << "> ";
                            int len  = steal_list.size();
                            for (int i = 0; i < len; i++) {
                              cout << steal_list.at(i)->get_name();
                              if (i == len - 1) {
                                cout << "." << endl;
                              } else {
                                cout << ", ";
                              }
                            }
                            // print message ends
                            cout << "Choose a builder to steal from." << endl;
                            cout << "> ";
                            string stealfrom;
                            while (getline(cin, stealfrom)) {
                              if (canStealFrom(steal_list, stealfrom, cur)) {
                                break;
                              } else { // cannot steal from
                                cout << "Choose a builder to steal from." << endl;
                                cout << "> ";
                              }
                            }
                          }
                          break;
                        }
                      }
                    }
                  } else {
                    cout << "No builders gained resources." << endl;
                  }
                  end_command_one = true;
                  break;
                }
                end_command_one = true; // end the first round
                break;
              }
        } //--------------------------------------------------------------------------------------roll ends
      } 
      else if (in == "status") { // ----------------------------------- status
        order.at(0)->print_status();
        order.at(1)->print_status();
        order.at(2)->print_status();
        order.at(3)->print_status();
        cout << "> ";
      } 
      else if (in == "end") {  // ------------------------------------------------ end the game
      // here
        string filename = "backup.sv";
        ofstream file(filename);

        // curTurn
        file << CURR_TURN << endl;

        //Player 0 
        //-----RESOURCE--------//
        file << blue.getResource("BRICK") << " " << blue.getResource("ENERGY") 
             << " " << blue.getResource("GLASS") << " " << blue.getResource("HEAT") 
             << " " << blue.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (blue.getNumRoad() != 0) {
            for (int i = 0; i < blue.getNumRoad(); i++) {
                file << blue.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (blue.getRes(i) != 0) {
                file << i << " ";
                if (blue.getRes(i) == 1) file << "B ";
                else if (blue.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 1 
        //-----RESOURCE--------//
        file << red.getResource("BRICK") << " " << red.getResource("ENERGY") << " " 
             << red.getResource("GLASS") << " " << red.getResource("HEAT") << " " 
             << red.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (red.getNumRoad() != 0) {
            for (int i = 0; i < red.getNumRoad(); i++) {
                file << red.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (red.getRes(i) != 0) {
                file << i << " ";
                if (red.getRes(i) == 1) file << "B ";
                else if (red.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 2
        //-----RESOURCE--------//
        file << orange.getResource("BRICK") << " " << orange.getResource("ENERGY") 
             << " " << orange.getResource("GLASS") << " " << orange.getResource("HEAT") 
             << " " << orange.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (orange.getNumRoad() != 0) {
            for (int i = 0; i < orange.getNumRoad(); i++) {
                file << orange.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (orange.getRes(i) != 0) {
                file << i << " ";
                if (orange.getRes(i) == 1) file << "B ";
                else if (orange.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;
        
        //Player 3 
        //-----RESOURCE--------//
        file << yellow.getResource("BRICK") << " " << yellow.getResource("ENERGY") 
             << " " << yellow.getResource("GLASS") << " " << yellow.getResource("HEAT") 
             << " " << yellow.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r "; 
        if (yellow.getNumRoad() != 0) {
            for (int i = 0; i < yellow.getNumRoad(); i++) {
                file << yellow.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (yellow.getRes(i) != 0) {
                file << i << " ";
                if (yellow.getRes(i) == 1) file << "B ";
                else if (yellow.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //board
        for (int i = 0; i <= 18; i++) {
          file << block[i] << " ";
          if (block[i] == 5) {
            file << 7 << " ";
          } else {
            file << dice_num[i] << " ";
          }
        }
        file << endl;

        //geese
        if (geese != -1) {
          file << geese << endl;
        }

        file.close();
        cout << "Bye :-)" << endl;
        return;
      } 
      else { //--------------------------------------------------------Invalid input
        cout << "Invalid command." << endl;
        cout << "Please enter 'help' for a list of valid commands." << endl;
        cout << "> ";
      }
    }
  
    cout << "Enter a command: " << endl;
    cout << "> ";

    // second round
    while (getline(cin, in)) {
      if (in == "board") { //---------------------------------------------------------------------board
        print_board();
        cout << "Enter a command: " << endl;
        cout << "> ";
      } 
      else if (in == "status") { //-------------------------------------------------------------status
        order.at(0)->print_status();
        order.at(1)->print_status();
        order.at(2)->print_status();
        order.at(3)->print_status();
        cout << "Enter a command: " << endl;
        cout << "> ";
      } 
      else if (in == "residences") { //---------------------------------------------------------residences
        cur->printRes();
        cout << "Enter a command: " << endl;
        cout << "> ";
      } 
      else if (in == "build-road") { //----------------------------------------------------------build-road
        string in;
        int pos = 0;
        cout << "> ";
        while (getline(cin, in)) {
          if (!is_number(in)) {
            cout << "ERROR:  isn't a valid integer." << endl;
            cout << "> ";
          } else {
            pos = stoi(in); 
            break;
          }
        }
        // check resource
        bool canBuildRoad = true;
        if (cur->getResource("HEAT") == 0 || cur->getResource("WIFI") == 0) {
          canBuildRoad = false;
          cout << "You do not have enough resources." << endl;
          cout << "The cost of a Road is one HEAT and one WIFI resource." << endl;
        }
        if (canBuildRoad) {
          canBuildRoad = checkBuildRoad(pos, cur->get_name());
        }
        if (canBuildRoad) {
          // change board
          string replace = "BR";
          if (cur->get_name() == "Red") replace = "RR";
          else if (cur->get_name() == "Orange") replace = "OR";
          else if (cur->get_name() == "Yellow") replace = "YR";
          int x = road_x.at(pos);
          int y = road_y.at(pos);
          grid.at(x).replace(y-1, 2, replace);
          // change player's status
          cur->addRoad(pos);
          cur->addResource("HEAT", -1);
          cur->addResource("WIFI", -1);
          cout << "> Builder " << cur->get_name() << " successfully built a Road at " << pos << "." << endl;
        } else { // cannot build road
          cout << "> You cannot build here." << endl;
        }
        cout << "Enter a command:" << endl;
        cout << "> ";
      } 
      else if (in == "build-res") { //------------------------------------------------------------build-res
        string in;
        int pos = 0;
        cout << "> ";
        while (getline(cin, in)) {
          if (!is_number(in)) {
            cout << "ERROR:  isn't a valid integer." << endl;
            cout << "> ";
          } else {
            pos = stoi(in);
            break;
          }
        }
        bool canBuildBasement = true;
        if (cur->getResource("BRICK") == 0 || cur->getResource("ENERGY") == 0 || 
            cur->getResource("WIFI") == 0 || cur->getResource("GLASS") == 0) {
          canBuildBasement = false;
          cout << "You do not have enough resources." << endl;
          cout << "The cost of a Basement is one BRICK, one ENERGY, one GLASS, and one WIFI resource." << endl;
        }
        if (canBuildBasement) {
          if (!checkBasement(pos, cur->get_name())) { // cannot build
            cout << "> You cannot build here." << endl;
          } else { // can build here
            // change board
            string replace = "BB";
            if (cur->get_name() == "Red") replace = "RB";
            else if (cur->get_name() == "Orange") replace = "OB";
            else if (cur->get_name() == "Yellow") replace = "YB";
            int x = building_x.at(pos);
            int y = building_y.at(pos);
            grid.at(x).replace(y-1, 2, replace);
            // change player's status
            cur->improveRes(pos);
            cur->addBasement();
            cur->addPoints(1);
            cur->addResource("BRICK", -1);
            cur->addResource("ENERGY", -1);
            cur->addResource("GLASS", -1);
            cur->addResource("WIFI", -1);
            cout << "> Builder " << cur->get_name() << " successfully built a Basement at " 
                 << pos << "." << endl;
            // check win
            if (cur->win()) {
              cout << "Would you like to play again?" << endl;
              cout << "> ";
              string ans;
              while (getline(cin, ans)) {
                if (ans == "yes" || ans == "y" || ans == "YES" || ans == "Y") {
                  for (int i = 0; i <= 40; i++) {
                    grid.at(i) = copy_g.at(i);
                  }
                  LOADED = false;
                  Controller();
                  return;
                } else if (ans == "no" || ans == "n" || ans == "NO" || ans == "N"){
                  cout << "Bye :-)" << endl;
                  return;
                } else {
                  cout << "Invalid answer." << endl;
                  cout << "Would you like to play again?" << endl;
                  cout << "> ";
                }
              }
            }
          }
        }
        cout << "Enter a command:" << endl;
        cout << "> ";
      } 
      else if (in == "improve") { //--------------------------------------------------------------improve
        cout << "> ";
        while (getline(cin, in)) { // for the number of improve
          if (!is_number(in)) {
            cout << "ERROR:  isn't a valid integer." << endl;
            cout << "> ";
          }  else {
            int x = stoi(in);
            if (x < 0 || x > 53) {
              cout << "Invalid residence." <<endl;
              cout << "> ";
              break;
            } else { // x is the valid number
              char colour = 'B';
              if (cur->get_name() == "Red") colour = 'R';
              else if (cur->get_name() == "Orange") colour = 'O';
              else if (cur->get_name() == "Yellow") colour = 'Y';
              // check if the position is a building
              char before = getChar(building_x.at(x), building_y.at(x)-1);
              char after = getChar(building_x.at(x), building_y.at(x));
              if (before == colour && (after == 'B' || after == 'H')) { // basement or house
                if (cur->canImprove(after)) {
                  //bool hi = blue.canImprove(after);
                  if (after == 'B') grid.at(building_x.at(x)).replace(building_y.at(x), 1, "H");
                  else grid.at(building_x.at(x)).replace(building_y.at(x), 1, "T");
                  if (after == 'B') {
                    cout << "Builder " << cur->get_name() << " successfully built a House at " << x << endl;
                    cur->improveRes(x);
                    // check win
                    if (cur->win()) {
                      cout << "Would you like to play again?" << endl;
                      cout << "> ";
                      string ans;
                      while (getline(cin, ans)) {
                        if (ans == "yes" || ans == "y" || ans == "YES" || ans == "Y") {
                          for (int i = 0; i <= 40; i++) {
                            grid.at(i) = copy_g.at(i);
                          }
                          LOADED = false;
                          Controller();
                          return;
                        }else if (ans == "no" || ans == "n" || ans == "NO" || ans == "N"){
                          cout << "Bye :-)" << endl;
                          return;
                        } else {
                          cout << "Invalid answer." << endl;
                          cout << "Would you like to play again?" << endl;
                          cout << "> ";
                        }
                      }
                    }
                  }
                  else {
                    cout << "Builder " << cur->get_name() << " successfully built a Tower at " << x << "." << endl;
                    cur->improveRes(x);
                    if (cur->win()) {
                      cout << "Would you like to play again?" << endl;
                      cout << "> ";
                      string ans;
                      while (getline(cin, ans)) {
                        if (ans == "yes" || ans == "y" || ans == "YES" || ans == "Y") {
                          for (int i = 0; i <= 40; i++) {
                            grid.at(i) = copy_g.at(i);
                          }
                          LOADED = false;
                          Controller();
                          return;
                        }else if (ans == "no" || ans == "n" || ans == "NO" || ans == "N"){
                          cout << "Bye :-)" << endl;
                          return;
                        } else {
                          cout << "Invalid answer." << endl;
                          cout << "Would you like to play again?" << endl;
                          cout << "> ";
                        }
                      }
                    }
                  }
                  cout << "Enter a command: " << endl;
                  cout << "> ";
                  break;
                } else {
                  cout << "> You do not have enough resources." << endl;
                  cout << endl;
                  cout << "The cost to improve a Basement to a House is two GLASS and three HEAT resource." << endl;
                  cout << "The cost to improve a House to a Tower is three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT." << endl;
                  cout << "Enter a command: " << endl;
                  cout << "> ";
                  break;
                }
              }  // basement or house end
              else if (before == colour && after == 'T') {
                cout << "You can't improve that building." << endl;
                cout << "Enter a command: " << endl;
                cout << "> ";
                break;
              }
              else {
                cout << "Invalid residence." << endl;
                cout << "Enter a command: " << endl;
                cout << "> ";
                break;
              }
            }
          }
        } // for number ends
      } 
      else if (in == "trade") { //-----------------------------------------------------------------trade
        string colour;
        string give;
        string get;
        cout << "> ";
        while (getline(cin, colour)) {
          colour = toColour(colour);
          if (colour != "?") break;
          else {
            cout << "Invalid colour." << endl;
            cout << "> ";
          }
        }
        cout << "> ";
        while (getline(cin, give)) {
          give = toResource(give);
          if (give != "?") break;
          else {
            cout << "Invalid item." << endl;
            cout << "> ";
          }
        }
        cout << "> ";
        while (getline(cin, get)) {
          get = toResource(get);
          if (get != "?") break;
          else {
            cout << "Invalid item." << endl;
            cout << "> ";
          }
        }
        bool canTrade = true;
        if (colour == cur->get_name()) {
          cout << "> Can't trade with yourself." << endl;
          canTrade = false;
        } else if (get == give) {
          cout << "> Why are you trading for the same resource..." << endl;
          canTrade = false;
        }
        Player *target = &blue;
        if (canTrade) {
          if (colour == "Red") target = &red;
          else if (colour == "Orange") target = &orange;
          else if (colour == "Yellow") target = &yellow;

          // check resource
          if (cur->getResource(give) == 0) {
            cout << "> You don't have enough ENERGY." << endl;
            canTrade = false;
          } else if (target->getResource(get) == 0) {
            cout << "> " << target->get_name() << " doesn't have enough " << get << "." << endl;
            canTrade = false;
          }
        }
        if (canTrade) {
          cout << "> > > " << cur->get_name() << " offers " << target->get_name() 
               << " one " << give << " for one " << get << "." << endl;
          cout << "Does "  << target->get_name() << " accept this offer?" << endl;
          cout << "> ";
          string ans;
          while (getline(cin, ans)) {
            if (ans == "y" || ans == "yes" || ans == "YES" || ans == "Y") { // agree to tarde
              cur->addResource(give, -1);
              cur->addResource(get, 1);
              target->addResource(give, 1);
              target->addResource(get, -1);
              cout << cur->get_name() << " gains one " << get << " and loses one " << give << "," << endl;
              cout << target->get_name() << " gains one " << give << " and loses one " << get << "." << endl;
              break;
            } else if (ans == "n" || ans == "no" || ans == "NO" || ans == "N") { // disagree
              cout << target->get_name() << " declined the trade." << endl;
              break;
            } else {
              cout << "Invalid command" << endl;
              cout << "Does "  << target->get_name() << " accept this offer?" << endl;
              cout << "> ";
            }
          }
        }
        cout << "Enter a command: " << endl; // this is just for testing
        cout << "> ";
      }
      else if (in == "market") { //------------------------------------------------------------------market
        string give;
        string get;
        cout << "> ";
        getline(cin, give);
        cout << "> ";
        getline(cin, get);
        give = toResource(give);
        get = toResource(get);
        if (give == "?" || get == "?") {
          cout << "Invalid item." << endl;
        } else { // valid resource
          if (give == get) {
            cout << "> Why are you buying the same resource?" << endl;
          } else { // different resource
            if (cur->getResource(give) < 4) {
              cout << "You don't have enough " << give << ". You need 4.";
            } else { // has enough resource
              cur->addResource(give, -4);
              cur->addResource(get, 1);
              cout << cur->get_name() << " gains one " << get << " and loses four " << give << "." << endl;
            }
          }
        }
        cout << "Enter a command: " << endl;
        cout << "> ";
      } 
      else if (in == "next") { //---------------------------------------------------------------------next
        break;
      } 
      else if (in == "save") { //-------------------------------------------------------------------save
        // here
        string filename;
        cout << "> ";
        getline(cin, filename);
        ofstream file(filename);

        // curTurn
        file << CURR_TURN << endl;

        //Player 0 
        //-----RESOURCE--------//
        file << blue.getResource("BRICK") << " " << blue.getResource("ENERGY") 
             << " " << blue.getResource("GLASS") << " " << blue.getResource("HEAT") 
             << " " << blue.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (blue.getNumRoad() != 0) {
            for (int i = 0; i < blue.getNumRoad(); i++) {
                file << blue.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (blue.getRes(i) != 0) {
                file << i << " ";
                if (blue.getRes(i) == 1) file << "B ";
                else if (blue.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 1 
        //-----RESOURCE--------//
        file << red.getResource("BRICK") << " " << red.getResource("ENERGY") << " " 
             << red.getResource("GLASS") << " " << red.getResource("HEAT") << " " 
             << red.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (red.getNumRoad() != 0) {
            for (int i = 0; i < red.getNumRoad(); i++) {
                file << red.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (red.getRes(i) != 0) {
                file << i << " ";
                if (red.getRes(i) == 1) file << "B ";
                else if (red.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 2
        //-----RESOURCE--------//
        file << orange.getResource("BRICK") << " " << orange.getResource("ENERGY") 
             << " " << orange.getResource("GLASS") << " " << orange.getResource("HEAT") 
             << " " << orange.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (orange.getNumRoad() != 0) {
            for (int i = 0; i < orange.getNumRoad(); i++) {
                file << orange.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (orange.getRes(i) != 0) {
                file << i << " ";
                if (orange.getRes(i) == 1) file << "B ";
                else if (orange.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;
        
        //Player 3 
        //-----RESOURCE--------//
        file << yellow.getResource("BRICK") << " " << yellow.getResource("ENERGY") 
             << " " << yellow.getResource("GLASS") << " " << yellow.getResource("HEAT") 
             << " " << yellow.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r "; 
        if (yellow.getNumRoad() != 0) {
            for (int i = 0; i < yellow.getNumRoad(); i++) {
                file << yellow.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (yellow.getRes(i) != 0) {
                file << i << " ";
                if (yellow.getRes(i) == 1) file << "B ";
                else if (yellow.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //board
        for (int i = 0; i <= 18; i++) {
          file << block[i] << " ";
          if (block[i] == 5) {
            file << 7 << " ";
          } else {
            file << dice_num[i] << " ";
          }
        }
        file << endl;

        //geese
        if (geese != -1) {
          file << geese << endl;
        }

        file.close();

        cout << "Enter a command:" << endl;
        cout << "> ";
      } 
      else if (in == "help") { //-------------------------------------------------------------------Help
        cout << "Valid commands :" << endl;
        cout << "~ board : prints the current board." << endl;
        cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << endl;
        cout << "~ residences : prints the residences the current builder has currently completed." << endl;
        cout << "~ build - road <road#> : attempts to builds the road at <road#>." << endl;
        cout << "~ build - res <housing#> : attempts to builds a basement at <housing#>." << endl;
        cout << "~ improve <housing#> : attempts to improve the residence at <housing#>." << endl;
        cout << "~ trade <colour> <give> <take> : attempts to trade with builder <colour>," <<
                " giving one resource of type <give> and receiving one resource of type <take>." << endl;
        cout << "~ market <sell> <buy> : attempts to sell resources on the market," <<
                " giving four resource of type <sell> and receiving one resource of type <buy>." << endl;
        cout << "~ next : passes control onto the next builder in the game." << endl;
        cout << "~ save <file> : saves the current game state to <file>." << endl;
        cout << "~ help : prints out the list of commands." << endl;
        cout << "~ end : end the game." << endl;
        cout << "Enter a command:" << endl;
        cout << "> ";
      } 
      else if (in == "end") { //--------------------------------------------------------------------End
        // here
        string filename = "backup.sv";
        ofstream file(filename);

        // curTurn
        file << CURR_TURN << endl;

        //Player 0 
        //-----RESOURCE--------//
        file << blue.getResource("BRICK") << " " << blue.getResource("ENERGY") 
             << " " << blue.getResource("GLASS") << " " << blue.getResource("HEAT") 
             << " " << blue.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (blue.getNumRoad() != 0) {
            for (int i = 0; i < blue.getNumRoad(); i++) {
                file << blue.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (blue.getRes(i) != 0) {
                file << i << " ";
                if (blue.getRes(i) == 1) file << "B ";
                else if (blue.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 1 
        //-----RESOURCE--------//
        file << red.getResource("BRICK") << " " << red.getResource("ENERGY") << " " 
             << red.getResource("GLASS") << " " << red.getResource("HEAT") << " " 
             << red.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (red.getNumRoad() != 0) {
            for (int i = 0; i < red.getNumRoad(); i++) {
                file << red.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (red.getRes(i) != 0) {
                file << i << " ";
                if (red.getRes(i) == 1) file << "B ";
                else if (red.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //Player 2
        //-----RESOURCE--------//
        file << orange.getResource("BRICK") << " " << orange.getResource("ENERGY") 
             << " " << orange.getResource("GLASS") << " " << orange.getResource("HEAT") 
             << " " << orange.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r ";
        if (orange.getNumRoad() != 0) {
            for (int i = 0; i < orange.getNumRoad(); i++) {
                file << orange.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (orange.getRes(i) != 0) {
                file << i << " ";
                if (orange.getRes(i) == 1) file << "B ";
                else if (orange.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;
        
        //Player 3 
        //-----RESOURCE--------//
        file << yellow.getResource("BRICK") << " " << yellow.getResource("ENERGY") 
             << " " << yellow.getResource("GLASS") << " " << yellow.getResource("HEAT") 
             << " " << yellow.getResource("WIFI") << " ";
        //-----ROAD--------//
        file << "r "; 
        if (yellow.getNumRoad() != 0) {
            for (int i = 0; i < yellow.getNumRoad(); i++) {
                file << yellow.getRoad(i) << " ";
            }
        }
        //-----HOUSE--------//
        file << "h ";
        for (int i = 0; i <= 53; i++) {
            if (yellow.getRes(i) != 0) {
                file << i << " ";
                if (yellow.getRes(i) == 1) file << "B ";
                else if (yellow.getRes(i) == 2) file << "H ";
                else file << "T ";
            }
        }
        file << endl;

        //board
        for (int i = 0; i <= 18; i++) {
          file << block[i] << " ";
          if (block[i] == 5) {
            file << 7 << " ";
          } else {
            file << dice_num[i] << " ";
          }
        }
        file << endl;

        //geese
        if (geese != -1) {
          file << geese << endl;
        }

        file.close();
        cout << "Bye :-)" << endl;
        return;
      } 
      else { //-------------------------------------------------------------------------------------Invalid command
        cout << "Invalid command." << endl;
        cout << "Please enter 'help' for a list of valid commands." << endl;
        cout << "Enter a command: " << endl;
        cout << "> ";
      }
    }
    occ++;
  }
}
