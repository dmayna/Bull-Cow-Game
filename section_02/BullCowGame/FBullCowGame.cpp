#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;

	TMap<int32, FString> SetHiddenWord{ {1,"a"},{2,"ab"},{2,"abc"},{0,"po"}, {3,"fry"},{4,"head"},{5,"drive"},{6,"pirate"},{7,"jupiter"} };

	const FString HIDDEN_WORD = "boxing";
	//MyHiddenWord = SetHiddenWord[getHiddenWord()]; // set back to HIDDEN_WORD to fix single hidden word
	MyHiddenWord = HIDDEN_WORD;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,9}, {6,12}, {7,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::getCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::getHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

EWordStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EWordStatus::Not_LowerCase;
	}
	else if (Guess.length() != getHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
}


// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	// loop through all letters in the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// loop through all letters agaisnt the guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{ 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		// compare letters agaisnt the hidden word
			//increment bulls if they're in the same place
			// incriment cows if not
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;   // setup our map
	for (auto Letter : Word)  // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;  // add letter to the map
		}
	}

	//loop through every letter in word
		// if the letter is in the map
			// we do NOT have an isogram
		// otherwise
			// add the to the map as seem
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) // for every letter in the word
	{
		 // if not a lowercase letter
		if(!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

int32 FBullCowGame::getHiddenWord() const
{
	return UserInputWordLength;
}

void FBullCowGame::setHiddenWord(int32 UserLength) const
{
	UserLength = UserInputWordLength;
}

