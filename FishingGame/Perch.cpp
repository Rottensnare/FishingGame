#include "Perch.h"

Perch::Perch()
{
	minWeight = 0.3f;
	maxWeigth = 1.5f;
	breed = "European Perch";
	weight = RandomizeWeight(minWeight, maxWeigth);
}
