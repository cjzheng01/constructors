#ifndef _SHUFFLE_H_
#define _SHUFFLE_H_
#include <vector>
#include "controller.h"

void print( std::vector<int> const & v );

std::vector<int> random_board(int s);

int random_resource(int s);

int random_dice(int s);

#endif
