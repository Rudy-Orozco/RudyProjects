/* Coding Assignment 5 */

#include <stdio.h>
#include <string.h>
#include "GameLib.h"

int main(void)
{
	char Phrase[MAX_INPUT] = {};
	char DashedPhrase[MAX_INPUT] = {};
	char UpperPhrase[MAX_INPUT] = {};
	int Strikes = 0;
	int i;
	
	/* Call StartGame and pass in Phrase */
	StartGame(Phrase);

	/* Call DashIt and pass in Phrase and DashedPhrase */
	DashIt(Phrase, DashedPhrase);

	/* uppercase Phrase */
	for(int i = 0; i < strlen(Phrase); i++)
	{
		UpperPhrase[i] = toupper(Phrase[i]);
	}
	
	printf("\nHere's the phrase you need to guess\n");

	do
	{
		//printf("%s\n", DashedPhrase);
		if(GuessALetter(Phrase, DashedPhrase, UpperPhrase) == 0)
		{
			Strikes++;
			printf("\nStrike %d", Strikes);
		}
	}
	while(strchr(DashedPhrase, '-') && (Strikes < STRIKES));
	/* while (call strchr() with DashedPhrase with -) AND strike counter is less than strikes define */

	if (Strikes < STRIKES)
	{
		printf("\n\nYou figured it out!!\n\nThe phrase was \n\n%s", Phrase);
		printf("\n\nYOU WIN!!!!\n");
	}
	else
	{
		printf("\n\n");
		printf("%d STRIKES - YOU'RE OUT!!\n\n", STRIKES);
		printf("Game over\n\n");
	}
	return 0;
}
