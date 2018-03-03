#ifndef Pair_h
#define Pair_h

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
using namespace std;

class Pair
{
	public:
	Card *p1=NULL;
	Card *p2=NULL;
	Card *maxCard=NULL;
	Card *minCard=NULL;
	Pair(Card& ,Card& );//contructor's function: let p1,p2 point to the parameter's reference, find the
                        //max card, assign to maxCard.
	Pair();//constructor with no parameter
	int ComparePair(Pair ,Pair);//compare 2 pair.maxCard.value, if former is bigger, return 1 , if latter
                                //is bigger, return 0. And if the same, return (error message) -1
    string toString();
    void swap(Pair&,Pair&);
    static const int kindcode=2;
};
#endif
