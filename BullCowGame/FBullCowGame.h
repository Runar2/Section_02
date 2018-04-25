/*
The game logic (no view code or direct user interaction)
Basically deals with underlaying things.
*/

#pragma once
#include <string>

using int32 = int;
using FString = std::string;

// all values init'd to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

/*
This is is the enums to return depending
on if the guess is a valid one or not
*/
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

/*
This is the contructor for the game apparently.
tbh I'm not even sure what that means heh :(
*/
class FBullCowGame {
public:
	FBullCowGame(); // constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);


// no worry about this yet lolol teehee XD
private:
	// see consstructor for init
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIrogram(FString) const;
	bool IsLowercase(FString) const;
};