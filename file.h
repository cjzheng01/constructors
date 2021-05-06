#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include <vector>
#include "shuffle.h"
#include "controller.h"
#include "player.h"


bool cannot_open(std::string f);

std::vector<int> board_vector(std::string f);

void to_vector_load(string f);

#endif
