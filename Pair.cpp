#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Pair.h"
using namespace std;

Pair::Pair(Card &a,Card &b)
{
	if(a.getface()==b.getface())
    {
        p1=&a;
        p2=&b;
	}
	else
    {
        cout<<"this pair"<<a.toString()<<","<<b.toString()<<"is not a pair!\n";
    }
	maxCard=((p1->getsuit())>(p2->getsuit()))?p1:p2;
	minCard=((p1->getsuit())>(p2->getsuit()))?p2:p1;
}
//contructor of the class: Pair
//Find the max card and assign it to maxCard
//The constructor when no inputs received
Pair::Pair(){
	Card a;
	Card b;
	p1=&a;
	p2=&b;
}
int Pair::ComparePair(Pair A,Pair B){

	if((A.maxCard->value)>(B.maxCard->value))
	return 1;
	else if((A.maxCard->value)<(B.maxCard->value))
	return 0;
	else
	return -1;
}
//compare two "pair.maxCard.value"
//If the former is bigger , return 1 , if latter is bigger , then return 0.
//And if the values are the same , return (error message) -1.
string Pair::toString()
{
    return p1->toString()+" & "+p2->toString();
}

void Pair::swap(Pair& a,Pair& b)
{
    Pair tmp;
    tmp=a;
    a=b;
    b=tmp;
}
