#include "Card.h"
#include <iostream>
#include <string.h>
using namespace std;

Card::Card(int a,int b)
{
    suit=a;
    face=b;
    value=4*(face-1)+suit;
    chosen=0;
}

void Card::setface(int a)
{
	face=a;
}

void Card::setsuit(int a)
{
	suit=a;
}

int Card::getface()
{
	return face;
}

int Card::getsuit()
{
	return suit;
}

string Card::facestring[]={"none","3","4","5","6","7","8","9","10","J","Q","K","A","2"};
string Card::suitstring[]={"none","Clubs","Diamonds","Hearts","Spades"};
string Card::toString()
{
    string tmp=facestring[face]+" of "+suitstring[suit];
    //strcat(tmp," of ");
    //strcat(tmp,suitstring[suit]);
    return tmp;
}

