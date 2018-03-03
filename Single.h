#ifndef Single_h
#define Single_h

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
using namespace std;

class Single
{
	public:
        Card *maxCard=NULL;
        Card *minCard=NULL;
        Single(Card& );
        int CompareSingle(Single ,Single);
        string toString();
        void swap(Single&,Single&);
        static const int kindcode=1;
};
#endif
