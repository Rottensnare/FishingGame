#pragma once
#include <string>

class FishBase
{

public:

	virtual float getWeight();
	virtual float getLength();
	std::string getBreed();
	
	FishBase();

protected:

	//FUNCTIONS
	float RandomizeWeight(float min, float max);
	
	//VARIABLES
	float weight;
	float length;

	float minWeight;
	float maxWeigth;

	float minLength;
	float maxLength;

	std::string breed;

};

