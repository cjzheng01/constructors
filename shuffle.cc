/*
 * Example of using the <algorithm> std::shuffle and seeding a random number generator with either
 * the command-line argument provided seed integer, or the current system time if there is no
 * argument provided. Based off of the example at: 
 *
 *    http://www.cplusplus.com/reference/algorithm/shuffle/
 *
 *  Last updated: 2020-10-06
 *  Copyright 2020 UW. All rights reserved.
 *
 */
 // 
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include "shuffle.h"
using namespace std;
void print( std::vector<int> const & v ) {
	for ( int i : v ) std::cout << i << ' ';
	std::cout << std::endl;
}


int get_seed(int s){
	int seed;
	if (s == -1){
		seed = std::chrono::system_clock::now().time_since_epoch().count();
	} else {
		seed = s;
	}
	return seed;
}


std::vector<int> random_board(int s){
	std::vector<int> resource = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5};
	std::vector<int> dice = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
	int seed = get_seed(s);
	std::default_random_engine rng{seed};
	std::shuffle( resource.begin(), resource.end(), rng );
	std::shuffle( dice.begin(), dice.end(), rng );
	std::vector<int> v;
	int i = 0;
	int j = 0;

	while(i < 19 && j < 18){
		if (resource[i] == 5){
			v.push_back(5);
			v.push_back(7);
			i++;
		} else {
			v.push_back(resource[i]);
			v.push_back(dice[j]);
			i++;
			j++;
		}
	}
	
	return v;
} 

int random_dice(int s){
	int seed = get_seed(s);
	mt19937 generate(seed + CURR_TURN);
    uniform_int_distribution<int> distribution(2, 12);
    int dice = distribution(generate);
	return dice;
}

int random_resource(int s){
	int seed = get_seed(s);
	mt19937 generate(seed + CURR_TURN);
	uniform_int_distribution<int> distribution(0, 4);
	int rand = distribution(generate);
	return rand;
}
