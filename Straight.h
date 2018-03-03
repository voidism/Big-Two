#ifndef Straight_h
#define Straight_h

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
using namespace std;

class Straight
{
	public:
	Card* s[5]={NULL,NULL,NULL,NULL,NULL};
	Card *maxCard=NULL;
	Card *minCard=NULL;
	Straight(Card& ,Card& ,Card& ,Card& ,Card& );
	Straight();
	int CompareStraight(Straight ,Straight );
    string toString();
    void swap(Straight &,Straight &);
    static const int kindcode=5;
};
#endif

