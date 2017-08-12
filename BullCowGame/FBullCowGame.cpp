#include "FBullCowGame.h"
#include <map>
#define TMap std::map 
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bVictoryStatus; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 8}, {4, 10}, {5,15}, {6,18}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::HiddenWordBank(int32 WORD_LENGTH)
{
	TMap<int32, FString> WordLengthToHiddenWord{ { 3,"cam" },{ 4,"nude" },{ 5,"swear" },{ 6,"petrol" },{ 7,"matched" } };
	MyHiddenWord = WordLengthToHiddenWord[WORD_LENGTH];
	return;
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bVictoryStatus = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess))//if guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) //if guess isnt all lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length; 	//if guess length is wrong
	}
	else
	{
		return EGuessStatus::OK;	//otherwise return OK
	}
}
//receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//loop through guess and compare letters against hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) 
				{ 	//if they're in the same place
					BullCowCount.Bulls++; //increment bulls 
				}
				else 
				{
					BullCowCount.Cows++; //must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bVictoryStatus = true;
	}
	else {
		bVictoryStatus = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)		//for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) //if letter is in the map
		{
			return false; //we dont have isogram
		}
		else
		{
			LetterSeen[Letter] = true;//add letter to the map as seen
		}

	}
	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1) { return true; }
	for (auto Letter : Word)
	{
		if (!islower(Letter)) //if letter is lowercase
		{ 
			return false; 
		}
	}
	return true;
}
