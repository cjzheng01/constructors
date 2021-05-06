#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "file.h"
#include "controller.h"
using namespace std;

bool cannot_open(string f){
    ifstream infile;
    infile.open(f);
    return infile.fail();
}

vector<string> to_vector(string f){
    ifstream infile;
    infile.open(f);
    string str;
    getline(infile, str);
    std::stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> v_str(begin, end);
    return v_str;
}

void makeChangeGame_1() {
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

void to_vector_load(string f){
    LOADED =true;
    ifstream infile;
    infile.open(f);
    //TURN
    string str;
    getline(infile, str);
    loaded_round = stoi(str);

    //PLAYER BLUE
    getline(infile, str);
    std::stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> v_str(begin, end);

    order[0]->setPoint(0);
    order[1]->setPoint(0);
    order[2]->setPoint(0);
    order[3]->setPoint(0);


    order[0]->setResource("BRICK", stoi(v_str[0]));
    order[0]->setResource("ENERGY", stoi(v_str[1]));
    order[0]->setResource("GLASS", stoi(v_str[2]));
    order[0]->setResource("HEAT", stoi(v_str[3]));
    order[0]->setResource("WIFI", stoi(v_str[4]));
    int house_index = -1;
    for (unsigned int i = 5; i < v_str.size(); i++) {
        if(v_str[i] == "h"){
            house_index = i;
            break;
        }
    }
        
    for(int i = 6; i < house_index; i++) {
        
        order[0]->addRoad(stoi(v_str[i]));
    } 

    for(unsigned int i = 1; i <= (v_str.size()-house_index-1)/2; i++) {
        if (v_str[house_index+2*i] == "B") {
            order[0]->setRes(stoi(v_str[house_index+2*i - 1]), 1);
            order[0]->addPoints(1);
        } else if (v_str[house_index+2*i] == "H") {
            order[0]->setRes(stoi(v_str[house_index+2*i - 1]), 2);
            order[0]->addPoints(2);
        } else if (v_str[house_index+2*i] == "T") {
            order[0]->setRes(stoi(v_str[house_index+2*i - 1]), 3);
            order[0]->addPoints(3);
        } else {
            order[0]->setRes(stoi(v_str[house_index+2*i - 1]), 0);
        }
    }


    //PLAYER RED
    getline(infile, str);
    std::stringstream ss1(str);
    istream_iterator<string> begin1(ss1);
    istream_iterator<string> end1;
    vector<string> v_str_1(begin1, end1);

    order[1]->setResource("BRICK", stoi(v_str_1[0]));
    order[1]->setResource("ENERGY", stoi(v_str_1[1]));
    order[1]->setResource("GLASS", stoi(v_str_1[2]));
    order[1]->setResource("HEAT", stoi(v_str_1[3]));
    order[1]->setResource("WIFI", stoi(v_str_1[4]));
    house_index = -1;
    for (unsigned int i = 5; i < v_str_1.size(); i++) {
        if(v_str_1[i] == "h"){
            house_index = i;
            break;
        }
    }
        
    for(int i = 6; i < house_index; i++) {
        
        order[1]->addRoad(stoi(v_str_1[i]));
    } 
    for(unsigned int i = 1; i <= (v_str_1.size()-house_index-1)/2; i++) {
        
        if (v_str_1[house_index+2*i] == "B") {
            order[1]->setRes(stoi(v_str_1[house_index+2*i - 1]), 1);
            order[1]->addPoints(1);
        } else if (v_str_1[house_index+2*i] == "H") {
            order[1]->setRes(stoi(v_str_1[house_index+2*i - 1]), 2);
            order[1]->addPoints(2);
        } else if (v_str_1[house_index+2*i] == "T") {
            order[1]->setRes(stoi(v_str_1[house_index+2*i - 1]), 3);
            order[1]->addPoints(3);
        } else {
            order[1]->setRes(stoi(v_str_1[house_index+2*i - 1]), 0);
        }
    }


    //PLAYER ORANGE
    getline(infile, str);
    std::stringstream ss2(str);
    istream_iterator<string> begin2(ss2);
    istream_iterator<string> end2;
    vector<string> v_str_2(begin2, end2);

    order[2]->setResource("BRICK", stoi(v_str_2[0]));
    order[2]->setResource("ENERGY", stoi(v_str_2[1]));
    order[2]->setResource("GLASS", stoi(v_str_2[2]));
    order[2]->setResource("HEAT", stoi(v_str_2[3]));
    order[2]->setResource("WIFI", stoi(v_str_2[4]));
    house_index = -1;
    for (unsigned int i = 5; i < v_str_2.size(); i++) {
        if(v_str_2[i] == "h"){
            house_index = i;
            break;
        }
    }
        
    for(int i = 6; i < house_index; i++) {
        
        order[2]->addRoad(stoi(v_str_2[i]));
    } 
    for(unsigned int i = 1; i <= (v_str_2.size()-house_index-1)/2; i++) {
        
        if (v_str_2[house_index+2*i] == "B") {
            order[2]->setRes(stoi(v_str_2[house_index+2*i - 1]), 1);
            order[2]->addPoints(1);
        } else if (v_str_2[house_index+2*i] == "H") {
            order[2]->setRes(stoi(v_str_2[house_index+2*i - 1]), 2);
            order[2]->addPoints(2);
        } else if (v_str_2[house_index+2*i] == "T") {
            order[2]->setRes(stoi(v_str_2[house_index+2*i - 1]), 3);
            order[2]->addPoints(3);
        } else {
            order[2]->setRes(stoi(v_str_2[house_index+2*i - 1]), 0);
        }
    }


    //PLAYER YELLOW
    getline(infile, str);
    std::stringstream ss3(str);
    istream_iterator<string> begin3(ss3);
    istream_iterator<string> end3;
    vector<string> v_str_3(begin3, end3);

    order[3]->setResource("BRICK", stoi(v_str_3[0]));
    order[3]->setResource("ENERGY", stoi(v_str_3[1]));
    order[3]->setResource("GLASS", stoi(v_str_3[2]));
    order[3]->setResource("HEAT", stoi(v_str_3[3]));
    order[3]->setResource("WIFI", stoi(v_str_3[4]));
    house_index = -1;
    for (unsigned int i = 5; i < v_str_3.size(); i++) {
        if(v_str_3[i] == "h"){
            house_index = i;
            break;
        }
    }
        
    for(int i = 6; i < house_index; i++) {
        
        order[3]->addRoad(stoi(v_str_3[i]));
    } 
    for(unsigned int i = 1; i <= (v_str_3.size()-house_index-1)/2; i++) {
        
        if (v_str_3[house_index+2*i] == "B") {
            order[3]->setRes(stoi(v_str_3[house_index+2*i - 1]), 1);
            order[3]->addPoints(1);
        } else if (v_str_3[house_index+2*i] == "H") {
            order[3]->setRes(stoi(v_str_3[house_index+2*i - 1]), 2);
            order[3]->addPoints(2);
        } else if (v_str_3[house_index+2*i] == "T") {
            order[3]->setRes(stoi(v_str_3[house_index+2*i - 1]), 3);
            order[3]->addPoints(3);
        } else {
            order[3]->setRes(stoi(v_str_3[house_index+2*i - 1]), 0);
        }
    }
    getline(infile, str);
    std::stringstream ss_board(str);
    istream_iterator<string> begin_board(ss_board);
    istream_iterator<string> end_board;
    vector<string> v_str_board(begin_board, end_board);
    int v_str_board_len = v_str_board.size();
    vector<int> v_str_board_int;
    for(int i = 0; i < v_str_board_len; i++){
        v_str_board_int.push_back(stoi(v_str_board[i]));
    }
    total = v_str_board_int;
    makeChangeGame_1();
    //GEESE
    getline(infile, str);
    if (str == "") geese = -1;
    else geese = stoi(str);
}


vector<int> board_vector(string f){
    vector<string>  v_str = to_vector(f);
    int len = v_str.size();
    if (len != 38){
        cerr << "Something went wrong when loading." << endl;
        exit(1);
    }
    vector<int> v_int;
    int x;
    for(int i = 1; i < len; i++){
        try {
            x = stoi(v_str[i - 1]);
        }
        catch(invalid_argument& e){
		    cerr << e.what() << endl;
			exit(1);
        }
        catch(out_of_range& e){
		    cerr << e.what() << endl;
			exit(1);
        }
        if ((i % 2 == 1 && (x < 0 || x > 5)) || (i % 2 == 0 && (x < 2 || x > 12))){
            cerr << "Something went wrong when loading." << endl;
            exit(1);
        } 
        v_int.push_back(x);
    }
    return v_int;
}





