#ifndef INCLUDE_MODEL_FOOD_H_
#define INCLUDE_MODEL_FOOD_H_

#include "primitives.h"

class Food
{
	Coordinates position_;
	int amount_;
	int decay_rate_;
	bool rotten_; //affect organism's health?
	void decay();
	Food (Coordinates,int,int);
};

class Vegetable : public Food
{

};

class Meat : public Food
{

};



#endif /* INCLUDE_MODEL_FOOD_H_ */
