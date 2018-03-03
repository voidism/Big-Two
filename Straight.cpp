#include <vector>
#include "Card.h"
#include "Straight.h"
using namespace std;

Straight::Straight(Card &a,Card &b,Card &c,Card &d,Card &e)
{
	if(
    (((a.getface())==(b.getface()-1)
    &&(b.getface()-1)==(c.getface()-2)
    &&(c.getface()-2)==(d.getface()-3)
    &&(d.getface()-3)==(e.getface()-4))
    &&
    ((a.getface()!=9)&&(b.getface()!=10)&&(c.getface()!=11)&&(d.getface()!=12)&&(e.getface()!=13)))
    ||
    ((a.getface()==1)&&(b.getface()==2)&&(c.getface()==3)&&(d.getface()==12)&&(e.getface()==13))
    ||
    ((a.getface()==1)&&(b.getface()==2)&&(c.getface()==3)&&(d.getface()==4)&&(e.getface()==13))
    )
    {
	s[0]=&a;
	s[1]=&b;
	s[2]=&c;
	s[3]=&d;
	s[4]=&e;
	}
	else
	cout<<"this straight"<<a.toString()<<","<<b.toString()<<","<<c.toString()<<","<<d.toString()<<","<<e.toString()<<"is not a straight!\n";
	maxCard=s[4];
	minCard=s[0];
}

Straight::Straight()
{
	Card a,b,c,d,e;
	s[0]=&a;
	s[1]=&b;
	s[2]=&c;
	s[3]=&d;
	s[4]=&e;
}

string Straight::toString()
{
    return s[0]->toString()+" & "+s[1]->toString()+" & "+s[2]->toString()+" & "+s[3]->toString()+" & "+s[4]->toString();
}

int Straight::CompareStraight(Straight A,Straight B)
{
	if((A.maxCard->value)>(B.maxCard->value))
	return 1;
	else if((A.maxCard->value)<(B.maxCard->value))
	return 0;
	else
	return -1;
}

void Straight::swap(Straight& a,Straight& b)
{
    Straight tmp;
    tmp=a;
    a=b;
    b=tmp;
}
