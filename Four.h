#ifndef Four_h
#define Four_h

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
using namespace std;

class Four
{
	public:
	Card *f[4]={NULL,NULL,NULL,NULL};
	Card *maxCard=NULL;
	Card *minCard=NULL;
	Four(Card& ,Card& ,Card& ,Card &);
	Four();
	int CompareFour(Four ,Four );
    string toString();
    void swap(Four &,Four &);
    static const int kindcode=4;
};
#endif

