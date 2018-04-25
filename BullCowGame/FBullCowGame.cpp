#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map //to make code more Unreal engine friendly


FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// this adjusts the max number of tries, based on the lenght of the word
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	/*
	Considering plopping in an array of different words here in the future,
	and making it pick one at random.
	Or maybe let the user pick a word length and make the game
	pick a random word of words with suiting lenghts
	*/
	const FString HIDDEN_WORD = "planet";  //this MUST be an isogram. MUST MUST MUST

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


/*
This shit right here checks returns the guess status stuff
*/
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIrogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}



// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assumin same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// if the match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they're in the same place
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else 
				{
					BullCowCount.Cows++; // must be a cow, increment cows
				}
				
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) // if the number of bulls is the same as length of word, game is won
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIrogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms (since they can't be isograms)
	if (Word.length() <= 1) 
	{
		return true;
	}

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case (makes em lowercase)
		if (LetterSeen[Letter])
		{
			return false; //we do not have an isogram at this stage
		}
		else
		{
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}

	}
	return true; // for example in cases where /0 is entered (lolwat)
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
