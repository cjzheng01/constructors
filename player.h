#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <vector>
#include "shuffle.h"
using namespace std;

class Player {
    string name;
    int points;
    int numBasement;
    int numHouse;
    int numTower;
    int numRoad;
    int brick;
    int energy;
    int glass;
    int heat;
    int wifi;
    char dice_type = 'l';
    vector<int> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> roads;

    public:
        Player(string name, int points, int numBasement, int numHouse, int numTower, int numRoad,
               int brick, int energy, int glass, int heat, int wifi);
        bool win();
        bool addBuilding(string target);
        void addPoints(int adder);
        void addResource(string target, int adder);
        void print_status();
        string get_name();
        void setDice(char c);
        bool isLoad();
        int numResource();
        void mayLoseResourceToGeese();
        int getResource(string type);
        bool canImprove(char what);
        void improveRes(int x);
        void printRes();
        int getRes(int pos);
        int getNumRoad();
        int getRoad(int pos);
        void addRoad(int pos);
        void addBasement();
        void setResource(string target, int num);
        void setRes(int pos, int num);
        void setPoint(int num);
        void clearRoad();
        void setNumRoad();
};

void randomLoseResource(Player *from, Player *to);


#endif
