#ifndef Three_h
#define Three_h

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
using namespace std;

class Three{
	public:
	Card* t[3]={NULL,NULL,NULL};
	Card *maxCard=NULL;
	Card *minCard=NULL;
	Three(Card& ,Card& ,Card& );
	Three();
	int CompareThree(Three ,Three );
    string toString();
    void swap(Three &,Three &);
    static const int kindcode=3;
};
#endif
