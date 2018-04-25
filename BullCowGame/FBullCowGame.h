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

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); // constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO make a more rich return value
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