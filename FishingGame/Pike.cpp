#include "Pike.h"

Pike::Pike()
{
	minWeight = 0.7f;
	maxWeigth = 3.2f;
	breed = "Northern Pike";
	weight = RandomizeWeight(minWeight, maxWeigth);
}
