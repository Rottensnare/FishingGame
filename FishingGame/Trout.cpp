#include "Trout.h"

Trout::Trout()
{
	minWeight = 0.9f;
	maxWeigth = 2.5f;
	breed = "Rainbow Trout";
	weight = RandomizeWeight(minWeight, maxWeigth);
}
