#include "FishBase.h"
#include <random>
#include <iostream> //Used for std::cerr


float FishBase::getWeight()
{
	return weight;
}

float FishBase::getLength()
{
	return length;
}

std::string FishBase::getBreed()
{
	try {
		return breed;
	}
	catch (std::bad_alloc& exception) {
		std::cerr << "bad_alloc" << exception.what();
	}
	return "";
}


float FishBase::RandomizeWeight(float min, float max)
{
	std::random_device rd;
	std::mt19937 rand1(rd());
	std::uniform_real_distribution<float> urd(min, max);
	return urd(rand1);
}

FishBase::FishBase()
{
	length = 0.0f;
	weight = 0.0f;
	minLength = 0.0f;
	minWeight = 0.0f;
	maxLength = 0.0f;
	maxWeigth = 0.0f;
	breed = "NOTHING";
}
