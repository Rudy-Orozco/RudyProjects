/* Donna French 1000074079 */

#ifndef _GAMELIB_H_
#define _GAMELIB_H_

#include <stdio.h>
#include <ctype.h>

#define MAX_INPUT 81
#define STRIKES 3

void StartGame(char ChosenPhrase[]);
int GuessALetter(char Phrase[], char DashedPhrase[], char UpperPhrase[]);
void DashIt(char *Phrase, char DashPhrase[]);
void CheckPhrase(char *Phrase);

#endif
