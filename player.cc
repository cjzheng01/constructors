#include "player.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

Player::Player(string name, int points, int numBasement, int numHouse, int numTower, int numRoad, 
               int brick, int energy, int glass, int heat, int wifi) {
    this->name = name;
    this->points = points;
    this->numBasement = numBasement;
    this->numHouse = numHouse;
    this->numTower = numTower;
    this->numRoad = numRoad;
    this->brick = brick;
    this->energy = energy;
    this->glass = glass;
    this->heat = heat;
    this->wifi = wifi;
}

bool Player::win() {
    return points >= 10;
}

bool Player::addBuilding(string target) {
    if (target == "basement" || target == "Basement") {
        if(brick > 0 && energy > 0 && glass > 0) {
            brick--; energy--; glass--;
            points++;
            numBasement++;
            return true;
        }
    } else if (target == "house" || target == "House") {
        if (glass >= 2 && heat >= 3 && numBasement > 0) {
            glass-=2; heat-=3;
            points++;
            numBasement--;
            numHouse++;
            return true;
        }
    } else if (target == "tower" || target == "Tower") {
        if (brick >= 3 && energy >= 2 && glass >= 2 && wifi >= 1 && heat >= 2 && numHouse > 0) {
            brick-=3; energy-=2; glass-=2; wifi-=1; heat-=2;
            points++;
            numHouse--;
            numTower++;
            return true;
        }
    }
    return false;
}

void Player::addPoints(int adder) {
    points+=adder;
}

void Player::addResource(string target, int adder) {
    if (target == "brick" || target == "BRICK") brick+=adder;
    else if (target == "energy" || target == "ENERGY") energy+=adder;
    else if (target == "heat" || target == "HEAT") heat+=adder;
    else if (target == "wifi" || target == "WIFI") wifi+=adder;
    else if (target == "glass" || target == "GLASS") glass+=adder;
}

void Player::print_status() {
    cout << "Builder ";
    if (name == "Blue") cout << "Blue    has ";
    else if (name == "Red") cout << "Red     has ";
    else if (name == "Orange") cout << "Orange  has ";
    else cout << "Yellow  has ";
    cout << points << " building points, " << brick << " BRICK, " << energy << " ENERGY, "
      << glass << " GLASS, " << heat << " HEAT, " << wifi << " WIFI." << endl;
}

string Player::get_name() {
    return name;
}

void Player::setDice(char c) {
    if (c == 'l') dice_type = 'l';
    else dice_type = 'f';
}

bool Player::isLoad() {
    return dice_type == 'l';
}

int Player::numResource() {
    return brick + energy + wifi + heat + glass;
}

void Player::mayLoseResourceToGeese() {
    if (numResource() < 10) {
        return;
    }
    int x = numResource() / 2;
    int xx = x;
    vector<int> lose;
    for (int i = 0; i < 5; i++) {
        // brick energy glass heat wifi
        lose.emplace_back(0);
    }

    while (x > 0) {
        int target = random_resource(SEED);
        if (target == 0 && brick > 0) x--, brick--, lose.at(0)++;
        else if (target == 1 && energy > 0) x--, energy--, lose.at(1)++;
        else if (target == 2 && glass > 0) x--, glass--, lose.at(2)++;
        else if (target == 3 && heat > 0) x--, heat--, lose.at(3)++;
        else if (target == 4 && wifi > 0) x--, wifi--, lose.at(4)++;
    }
    cout << "Builder " << name << " loses " << xx << " resources to the geese. They lose :" << endl;
    for (int i = 0; i < 5; i++) {
        if (lose.at(i)!=0) {
            cout << lose.at(i);
            if (i == 0) cout << " BRICK" << endl;
            else if (i == 1) cout << " ENERGY" << endl;
            else if (i == 2) cout << " GLASS" << endl;
            else if (i == 3) cout << " HEAT" << endl;
            else cout << " WIFI" << endl;
        }
    }
}

int Player::getResource(string type) {
    if (type == "BRICK") return brick;
    else if (type == "ENERGY") return energy;
    else if (type == "GLASS") return glass;
    else if (type == "HEAT") return heat;
    return wifi;
} 

// decrease resource
bool Player::canImprove(char what) {
    if (what == 'B') {
        if (glass >= 2 && heat >= 3) {
            glass-=2, heat-=3;
            points++;
            numBasement--, numHouse++;
            return true;
        }
    } else if (what == 'H') {
        if (brick >= 3 && energy >= 2 && glass >= 2 && wifi >= 1 && heat >= 2) {
            brick-=3, energy-=2, glass-=2, wifi--, heat-=2;
            points++;
            numHouse--, numTower++;
            return true;
        }
    }
    return false;
}

void Player::improveRes(int x) {
    this->res.at(x)++;
}

void Player::printRes() {
    cout << name << " has built:" << endl;
    for (int i = 0; i <= 53; i++) {
        if (res.at(i) != 0) {
            cout << i << " ";
            if (res.at(i) == 1) cout << "B" << endl;
            else if (res.at(i) == 2) cout << "H" << endl;
            else cout << "T" << endl;
        }
    }
}

int Player::getRes(int pos) {
    return res.at(pos);
}

void Player::setRes(int pos, int num) {
    res.at(pos) = num;
}

int Player::getNumRoad() {
    return numRoad;
}

int Player::getRoad(int pos) {
    return roads.at(pos);
}

void Player::addRoad(int pos) {
    numRoad++;
    roads.emplace_back(pos);
}

void Player::addBasement() {
    numBasement++;
}

void Player::setResource(string target, int num) {
    if (target == "brick" || target == "BRICK") brick = num;
    else if (target == "energy" || target == "ENERGY") energy = num;
    else if (target == "heat" || target == "HEAT") heat = num;
    else if (target == "wifi" || target == "WIFI") wifi = num;
    else if (target == "glass" || target == "GLASS") glass = num;
}

void Player::setPoint(int num) {
    points = num;
}

void Player::clearRoad() {
    roads.clear();
}

void Player::setNumRoad() {
    numRoad = 0;
}

void randomLoseResource(Player *from, Player *to) {
    if (from->numResource() == 0) {
        cout << from->get_name() << "has no resource! error! Player::randomLoseResource" << endl;
        return;
    }
    int x = random_resource(SEED);
    while (true) {
        if (x == 0 && from->getResource("BRICK") != 0) {
            from->addResource("BRICK", -1), to->addResource("BRICK", 1); 
            cout << "Builder " << to->get_name() << " steals BRICK from builder " << from->get_name() << "." << endl;
            return;
        }
        if (x == 1 && from->getResource("ENERGY") != 0) {
            from->addResource("ENERGY", -1), to->addResource("ENERGY", 1);
            cout << "Builder " << to->get_name() << " steals ENERGY from builder " << from->get_name() << "." << endl;
            return;
        }
        if (x == 2 && from->getResource("GLASS") != 0) {
            from->addResource("GLASS", -1), to->addResource("GLASS", 1); 
            cout << "Builder " << to->get_name() << " steals GLASS from builder " << from->get_name() << "." << endl;
            return;
        }
        if (x == 3 && from->getResource("HEAT") != 0) {
            from->addResource("HEAT", -1), to->addResource("HEAT", 1); 
            cout << "Builder " << to->get_name() << " steals HEAT from builder " << from->get_name() << "." << endl;
            return;
        }
        if (x == 4 && from->getResource("WIFI") != 0) {
            from->addResource("WIFI", -1), to->addResource("WIFI", 1);
            cout << "Builder " << to->get_name() << " steals WIFI from builder " << from->get_name() << "." << endl;
            return;
        }
        x = random_resource(SEED);
    }
}


