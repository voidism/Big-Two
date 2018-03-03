#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Single.h"
using namespace std;

Single::Single(Card &a)
{
	maxCard=&a;
	minCard=&a;
    //kindcode=1;
}
//contructor of the class Single
int Single::CompareSingle(Single A,Single B)
{
	if((A.maxCard->value)>(B.maxCard->value))
        return 1;
	else if((A.maxCard->value)<(B.maxCard->value))
        return 0;
	else
        return -1;
}
//compare 2 single.maxCard.value, if former is bigger, return 1 , if latter is bigger, return 0.
//And if the values are the same, return (error message) -1
string Single::toString()
{
    return maxCard->toString();
}

void Single::swap(Single& a,Single& b)
{
    Single tmp=a;
    a=b;
    b=tmp;
}
