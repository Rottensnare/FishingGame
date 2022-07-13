#include "Salmon.h"
#include "FishBase.h"



Salmon::Salmon() {
	minWeight = 1.3f;
	maxWeigth = 2.7f;
	breed = "Pink Salmon";
	weight = RandomizeWeight(minWeight, maxWeigth);
}