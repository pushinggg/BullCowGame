/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
void GetGameDifficulty();

FBullCowGame BCGame; //instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do {

		PrintIntro();
		GetGameDifficulty();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // Exit application
}

void PrintIntro()
{
	// introduce the game
	std::cout << "\n                                       /;   ;\\ " << std::endl;
	std::cout << "                                   __  \\\\___//" << std::endl;
	std::cout << "                                  /{_\\_/   `'\\____" << std::endl;
	std::cout << "                                  \\___   (o)  (o  }" << std::endl;
	std::cout << "       _____________________________/          :--'   BULL?" << std::endl;
	std::cout << "   ,-,'`@@@@@@@@       @@@@@@         \\_    `__\\       OR" << std::endl;
	std::cout << "  ;:(  @@@@@@@@@        @@@             \\___(o'o)        IT" << std::endl;
	std::cout << "  :: )  @@@@          @@@@@@        ,'@@(  `===='        COW?" << std::endl;
	std::cout << "  :: : @@@@@:          @@@@         `@@@:" << std::endl;
	std::cout << "  :: \\  @@@@@:       @@@@@@@)    (  '@@@'"<< std::endl;
	std::cout << "  ;; /\\      /`,    @@@@@@@@@\\   :@@@@@) " << std::endl;
	std::cout << "  ::/  )    {_----------------:  :~`,~~;" << std::endl;
	std::cout << " ;;'`; :   )                  :  / `; ;" << std::endl;
	std::cout << ";;;; : :   ;                  :  ;  ; :" << std::endl;
	std::cout << "`'`' / :  :                   :  :  : :" << std::endl;
	std::cout << "    )_ \\__;                   :_ ;  \\_\\ " << std::endl;
	std::cout << "    :__\\  \\                   \\  \\  :  \\ " << std::endl;
	std::cout << "        `^'                    `^'  `-^-'" << std::endl;
	std::cout << "\n\nWelcome to Bulls and Cows, a fantastic word game.\n";
	std::cout << "Can you guess the isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game
	//is NOT won and there are tries are still remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		//submits valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	//TODO Add a game summary
	return;
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations! You've Won!\n";
	}
	else 
	{
		std::cout << "Darn! Better luck next time.\n";
	}
}
FText GetValidGuess()
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//loop continually until the user gives a valid guess
		//get a guess from user

		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) 
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram. (psst. No repeating letters) \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use a lowercase letters \n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void GetGameDifficulty()
{
	int32 WORD_LENGTH = 3;
	constexpr int32 MAX_LENGTH = 7;
	do
	{
		std::cout << "How long should the word be (enter 3 through 7) ";
		std::cin >> WORD_LENGTH;
		if (WORD_LENGTH < 3 || WORD_LENGTH > MAX_LENGTH)
		{
			std::cout << "you entered an incorrect length. Let's try again\n";
		}
	} while (WORD_LENGTH < 3 || WORD_LENGTH > MAX_LENGTH);
	BCGame.HiddenWordBank(WORD_LENGTH);
	std::cout << std::endl;
	return;
}
