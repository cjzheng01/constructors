#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <vector>
#include <string>
#include "player.h"

class Player;

// load
extern int geese;
extern int loaded_round;
extern bool LOADED;
// dice
extern int LOAD_DICE;
// player
extern Player blue;
extern Player red;
extern Player orange;
extern Player yellow;
extern std::vector<Player *> player_list;
extern std::vector<Player *> first_2_run;
extern std::vector<Player *> order;



// board
extern std::vector<std::string> grid; 
extern std::vector<std::string> copy_g; 
extern std::vector<int> block;
extern std::vector<int> dice_num;
extern std::vector<int> block;
extern std::vector<int> name_x;
extern std::vector<int> name_y;
extern std::vector<int> l_num_x;
extern std::vector<int> l_num_y;
extern std::vector<int> building_x;
extern std::vector<int> building_y;
extern std::vector<int> road_x;
extern std::vector<int> road_y;
extern std::vector<int> total;

// random
extern int SEED;
extern int CURR_TURN;

// controller
class Controller {
    public:
    Controller();
    void print_all_buildings_position(std::vector<int> x, std::vector<int> y);
    void buildBuilding(int pos, char type, std::string who);
    void setGeese();
    void steal(Player *cur, std::vector<int> & list);
};

#endif
