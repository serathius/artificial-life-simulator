#include "food.h"

void Food::decay() {
	amount_ -= decay_rate_;
	rotten_ = true;
}

Food::Food(Coordinates xy, int am, int dcr) : position_(xy),
		amount_(am),
		decay_rate_(dcr)
