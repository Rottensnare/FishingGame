#include "Vendace.h"

Vendace::Vendace()
{
	minWeight = 0.1f;
	maxWeigth = 0.5f;
	breed = "Vendace";
	weight = RandomizeWeight(minWeight, maxWeigth);
}
