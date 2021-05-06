#include "strategy.h"

int Strategy::checkDiceType(std::string s) {
    if (s == "LOAD" || s == "Load" || s == "load") {
        return 0;
    } else if (s == "FAIR" || s == "Fair" || s == "fair") {
        return 1;
    } else {
        return -1;
    }
}

int Load::roll_load(){
    return LOAD_DICE;
}

int Fair::roll_fair(){
    return random_dice(SEED);
}
