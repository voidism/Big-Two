#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.h"
#include "Deckofcards.h"
using namespace std;

Deckofcards::Deckofcards()
{
    for(int i=1;i<5;i++)
    {
		for(int j=1;j<14;j++)
        {
			Card tmp(i,j);
            deck.push_back(tmp);
            currentCard++;
		}
    }
}

void Deckofcards::shuffle()
{
    for(int i=0;i<52;i++)
    {
        int r=rand()%52;
        Card tmp;
        tmp=deck.at(i);
        deck.at(i)=deck.at(r);
        deck.at(r)=tmp;
    }
}

void Deckofcards::printall()
{
    for(int i=0;i<52;i++)
    {
        cout<<deck.at(i).toString()<<endl;
	}
}

Card Deckofcards::dealCard()
{
    if(moreCards())
    {
        return deck.at(--currentCard);
    }
    else
    {
		cout<<"no more cards\n";
		return 0;
    }
}

bool Deckofcards::moreCards()
{
    return (currentCard!=0);
}

