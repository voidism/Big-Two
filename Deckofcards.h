#ifndef Deckofcards_h
#define Deckofcards_h
#include <iostream>
#include <vector>
#include <string>
#include "Card.h"
using namespace std;

class Deckofcards
{
	public:
        int currentCard=0;
        vector <Card> deck;
        Deckofcards();
        void shuffle();
        void printall();
        Card dealCard();
        bool moreCards();
};
#endif
