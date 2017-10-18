// BullCowGame.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintgameSummary();

FBullCowGame BCGame;

int main()
{
	do
	{
		system("CLS");
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());




	std::cout << "\n\t";
	return(0);
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries)
	{
		FText guess = GetValidGuess();
		
		//Submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		// Print Bulls and Cows
		std::cout << "\tBulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n" << std::endl;
	}
	// print summary 
	PrintgameSummary();
}


void PrintIntro() 
{
	int32 userInput;
	std::cout << "\n\tWelcome to Bulls and Cows, a fun word game!\n" << std::endl;
	std::cout << "\t          }    {               ____" << std::endl;
	std::cout << "\t          (O  O)              (O  O)" << std::endl;
	std::cout << "\t   /-------\\  /                \\  /-------\\" << std::endl;
	std::cout << "\t  / | BULL | O                  O |  COW  |\\" << std::endl;
	std::cout << "\t *  |-,----|                      |-------| *" << std::endl;
	std::cout << "\t    ^      ^                      ^       ^" << std::endl;
	//std::cout << " How many letters will you like to guess? (3-7) : ";
	//std::cin >> userInput;
	//BCGame.setHiddenWord(userInput);
	std::cout << "\tCan you guess the " << BCGame.getHiddenWordLength();
	std::cout << " letter isogram I'm Thinking of?\n" << std::endl;
}

// loop for the number of turns asking for guesses
FText GetValidGuess() 
{
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 currentTry = BCGame.getCurrentTry();
		std::cout << "\tTry " << BCGame.getCurrentTry() << " of " << BCGame.GetMaxTries() << " Enter Guess > ";
		std::getline(std::cin, Guess);

		Status = BCGame.checkGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "\tPlease enter a " << BCGame.getHiddenWordLength() << " letter word.\n" << std::endl;
			break;
		case EWordStatus::Not_LowerCase:
			std::cout << "\tPlease enter all lowercase letters\n" << std::endl;
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "\tPlease enter a word without repeating letters\n" << std::endl;
			break;

		default:
			break;
		}
		//std::cout << std::endl;
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\tDo you want to play again with the same hidden word(Y/N)?: ";
	FText response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintgameSummary()
{
	if (BCGame.isGameWon())
	{
	std::cout << "\tWELL DONE - YOU WIN!" << std::endl;
	}
	else
	{
		std::cout << "\tBetter luck next time!" << std::endl;
	}
}



/*
	Impossible is just a big word thrown around my small men who find it easier to live in the world the've been 
	given than to explore the power they have to channge it.
*/
