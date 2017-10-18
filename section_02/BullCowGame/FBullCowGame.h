#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame {
public:
	FBullCowGame(); // Construcor


	int32 GetMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;

	bool isGameWon() const;
	EWordStatus checkGuessValidity(FString Guess) const;

	void Reset(); //TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString Guess);
	int32 getHiddenWord() const;
	void setHiddenWord(int32) const;
	
private:
	int32 MyCurrentTry ;
	int32 MyMaxTries ;
	FString MyHiddenWord;
	bool bGameIsWon;
	int32 UserInputWordLength;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	
};