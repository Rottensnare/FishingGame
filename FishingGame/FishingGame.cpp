

#include <iostream>
#include <chrono>	 //Used for waiting
#include <thread>	 //Used for waiting
#include <random>	 //Randomized fish weight and fish breed.
#include <string>
#include <list>		 //NOT USED ANYMORE. Was used to store pointers to different fish
#include "Salmon.h"	 //Fish classes are derived from FishBase
#include "Pike.h"
#include "Perch.h"
#include "Vendace.h"
#include "Trout.h"
#include <assert.h>	 //NOT USED ANYMORE. Was used for checking whether or not class was derived from FishBase
#include <Windows.h> //Used for text color
#include <fstream>	 //For reading from and writing to files
#include <ctime>	 //For getting time&date

#define FishSleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x)); //Macro to make sleep functions take less space

/*

Code by Roope Pennanen

*/

template<typename T> //Template for outputting text. Main reason is to use a more humanreadable function for output and to allow the use of multiple types.
void Say(T value) {
	std::cout << value << std::endl;
}

template<typename T, typename F> //Same as the previous but with 2 variables
void Say2(T value, F value2) {
	std::cout << value << value2 << std::endl;
}

template<typename T, typename F, typename Y> //Same as the previous but with 3 variables
void Say3(T value, F value2, Y value3) {
	std::cout << value << value2 << value3 << std::endl;
}

template<class T> //NOT USED WENT FOR A SIMPLER SOLUTION
void CreateFish1(std::list<FishBase*>& fishList, std::list<FishBase*>::iterator& it) {
	static_assert(std::is_base_of<FishBase, T>::value); //Had to switch to C++17
	T fish;
	auto pFish = &fish;
	fishList.insert(it, pFish);
}

template<class T> //Template to create every type of fish, add them to the fish array and increase the iterator.
void CreateFish2(FishBase (&arr)[20], int& fishIterator) {
	T fish;
	arr[fishIterator] = fish;
	fishIterator++;
}

enum Breeds {salmon, pike, perch, vendace, trout}; //Enum created for readability

//Starting dialogue
void OutputDialogueStart(int x) {

	switch (x) {
	case(0):
		Say("Choose your bait by entering the corresponding number.");
		Say("1. Worms \n2. Bread \n3. Small lure \n4. Big lure \n");
		return;
	case(1):
		Say("Worms selected.");
		return;
	case(2):
		Say("Bread selected.");
		return;
	case(3):
		Say("Small lure selected.");
		return;
	case(4):
		Say("Big lure selected.");
		return;
	default:
		Say("Unexpected selection.");
		return;
	}

}

//Gets the selected bait for later use
bool GetBaitNumber(int& baitNumber) {
	std::cin >> baitNumber;
	std::cout << "\x1B[2J\x1B[H"; //Clears console
	if (baitNumber < 1 || baitNumber > 4) {
		Say("Exiting program due to inability to enter correct numbers.");
		return false;
	}
	return true;
}

//Reads the total weigth of the last fishing trip from file.
void ReadFromFile() { 
	std::string line;
	std::ifstream fishFile("Fish.txt");
	if (fishFile.is_open()) {
		getline(fishFile, line);
		std::string subString = line.substr(0, line.find(','));
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
		Say2("Last fishing trip, ", subString);
		SetConsoleTextAttribute(hConsole, 7);
	}
}

//Writes total weight of fish, and Time&Date to a text file.
void WriteToFile(float totalWeight) { 
	std::ofstream fishFile("Fish.txt");

	auto start = std::chrono::system_clock::now();	//Code copied from https://stackoverflow.com/questions/62226043/how-to-get-the-current-time-in-c-in-a-safe-way because apparently ctime and localtime are unsafe.
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	char tmBuff[30];
	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);

	if (fishFile.is_open()) {
		fishFile << "Total Weight: " << totalWeight << " kg, Time & Date: "<< tmBuff << std::endl;
		fishFile.close();
	}
}

//End dialogue. Prints out caught fish and their weight. Calculates total weight. Windows.h is used to change text color.
void OutputDialogueEnd(FishBase(&arr)[20], int& fishIterator) {

	float totalWeight = 0.0f;

	Say("Fish caught: \n");
	for (int i = 0; i < fishIterator; i++) {
		Say3(arr[i].getWeight(), " kg, Breed: ", arr[i].getBreed());
	}
	for (int i = 0; i < fishIterator; i++) {
		totalWeight += arr[i].getWeight();
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	Say3("Total weight of fish caught: ", totalWeight, " kg.");
	SetConsoleTextAttribute(hConsole, 7);
	WriteToFile(totalWeight);
}

//NOT USED, OPTED FOR A SIMPLER SOLUTION WITHOUT POINTERS
void CreateFish(int fishNumber, std::list<FishBase*> &fish, std::list<FishBase*>::iterator &it) { //Not used, opted for a simpler solution
	switch (fishNumber) {
	case(0): {
		Salmon salmon;
		auto pSalmon = &salmon;
		fish.insert(it,pSalmon);
		return;
	}
	case(1): {
		Pike pike;
		auto pPike = &pike;
		fish.insert(it, pPike);
		return;
	}
	case(2): {
		Perch perch;
		auto pPerch = &perch;
		fish.insert(it, pPerch);
		return;
	}
	case(3): {
		Vendace vendace;
		auto pVendace = &vendace;
		fish.insert(it, pVendace);
		return;
	}
	case(4): {
		Trout trout;
		auto pTrout = &trout;
		fish.insert(it, pTrout);
		return;
	}	
	default:
		Say("No Fish was caugth.");
		return;
	}
} //Not used, opted for a simpler solution.

//Checks which fish has been caught, calls CreateFish2 and passes the fish iterator and the fish array. Prints the breed of the caught fish to the console.	//NOTE TO SELF: Amount of code could easily be reduced for example with a template.
bool CatchFish(int breed, FishBase(&arr)[20], int& fishIterator) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "\x1B[2J\x1B[H";
	switch (breed) {
	case(salmon):
		CreateFish2<Salmon>(arr, fishIterator);
		FishSleep(500)
		Say2("Hooked a ", arr[fishIterator-1].getBreed());
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	case(pike):
		CreateFish2<Pike>(arr, fishIterator);
		FishSleep(500)
		Say2("Hooked a ", arr[fishIterator-1].getBreed());
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	case(perch):
		CreateFish2<Perch>(arr, fishIterator);
		FishSleep(500)
		Say2("Hooked a ", arr[fishIterator-1].getBreed());
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	case(vendace):
		CreateFish2<Vendace>(arr, fishIterator);
		FishSleep(500)
		Say2("Hooked a ", arr[fishIterator-1].getBreed());
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	case(trout):
		CreateFish2<Trout>(arr, fishIterator);
		FishSleep(500)
		Say2("Hooked a ", arr[fishIterator-1].getBreed());
		SetConsoleTextAttribute(hConsole, 7);
		return true;
	default:
		FishSleep(500)
		Say("Hooked nothing.");
		SetConsoleTextAttribute(hConsole, 7);
		return false;
	}
	SetConsoleTextAttribute(hConsole, 7);
	return true;
}

//Prints ... when fishing. Calls  CatchFish after.	NOTE TO SELF: amount of code could easily be reduced by another loop.
void WaitForFish(int breed, FishBase(&arr)[20], int& fishIterator) { //Waits a few seconds before fish is caught. Based on the breed of the fish getting caught.
																	//Calls CatchFish function after. Passes the breed enum, and the array of fish and the iterator by reference.
	bool caught = false;

	switch (breed) {
	case(salmon):
		for (int i = 0; i < 4; i++) {
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			printf("\33[2K\r");
		}

		caught = CatchFish(salmon, arr, fishIterator);
		return;

	case(pike):
		for (int i = 0; i < 5; i++) {
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			printf("\33[2K\r");
		}

		caught = CatchFish(pike, arr, fishIterator);
		return;
		
	case(perch):
		for (int i = 0; i < 3; i++) {
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			printf("\33[2K\r");
		}

		caught = CatchFish(perch, arr, fishIterator);
		return;

	case(vendace):
		for (int i = 0; i < 2; i++) {
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			printf("\33[2K\r");
		}

		caught = CatchFish(vendace, arr, fishIterator);
		return;	

	case(trout):
		for (int i = 0; i < 4; i++) {
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			std::cout << ".";
			FishSleep(500)
			printf("\33[2K\r");	
		}

		caught = CatchFish(trout, arr, fishIterator);
		return;

	default:
		return;
	}
	
}

//Chooses randomly which fish was caught based on selected bait.
Breeds GenerateFish(int bait) { 
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<int> uid(0, 10);
	int rnd = uid(rand);
	switch (bait) {
	case(1):
		if (rnd < 3) {
			return pike;
		}
		else {
			return perch;
		}
	case(2):
		if (rnd < 3) {
			return perch;
		}
		else {
			return vendace;
		}
	case(3):
		
		if (rnd < 2) {
			return salmon;
		}
		else if(rnd > 2 && rnd < 5){
			return trout;
		}
		else {
			return pike;
		}
	case(4):
		if (rnd < 4) {
			return trout;
		}
		else {
			return salmon;
		}
	default:
		return vendace;
	}
}

int main()
{
	ReadFromFile();
	FishSleep(1000)
	
	int baitNumber;
	int fishIterator = 0;
	FishBase fishesArr[20];
	bool castAgain = true;
	char answer = 'n';
	
	OutputDialogueStart(0);

	if (!GetBaitNumber(baitNumber)) {
		return 0;
	}
	
	OutputDialogueStart(baitNumber);
	FishSleep(2000)
	std::cout << "\x1B[2J\x1B[H";
	
	while (castAgain) {													//Game loop
		Say("Waiting for a fish to take a bite.");
		WaitForFish(GenerateFish(baitNumber), fishesArr, fishIterator);
		Say("Cast again? y/n");
		std::cin >> answer;
		std::cout << "\x1B[2J\x1B[H";
		if (answer == 'n') {
			Say("Switch bait? y/n");
			std::cin >> answer;
			std::cout << "\x1B[2J\x1B[H";

			if (answer == 'n') {
				castAgain = false;
			}
			else {
				std::cout << "\x1B[2J\x1B[H";
				OutputDialogueStart(0);
				if (!GetBaitNumber(baitNumber)) {
					return 0;
				}
			}
		}
		if (fishIterator >= 19) {
			castAgain = false;
		}
	}

	OutputDialogueEnd(fishesArr, fishIterator);
	
}




