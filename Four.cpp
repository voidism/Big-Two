#include <vector>
#include <iostream>
#include "Card.h"
#include "Four.h"
using namespace std;

Four::Four(Card &a,Card &b,Card &c,Card &d)
{
	if((a.getface()==b.getface())&&(b.getface()==c.getface())&&(c.getface()==d.getface()))
    {
		f[0]=&a;
		f[1]=&b;
		f[2]=&c;
		f[3]=&d;
	}
	else
		cout<<"this four"<<a.toString()<<","<<b.toString()<<","<<c.toString()<<","<<d.toString()<<"is not a four!\n";

	int m=55;
    for(int i=0;i<3;i++)
    {
        if(f[i]->value<m)
        {
            m=f[i]->value;
            minCard=f[i];
        }
    }
    int n=0;
    for(int i=0;i<3;i++)
    {
        if(f[i]->value>n)
        {
            n=f[i]->value;
            maxCard=f[i];
        }
    }
}

Four::Four()
{
	Card a,b,c,d;
	f[0]=&a;
    f[1]=&b;
    f[2]=&c;
    f[3]=&d;
}

string Four::toString()
{
    return f[0]->toString()+" & "+f[1]->toString()+" & "+f[2]->toString()+" & "+f[3]->toString()+"___";
}

int Four::CompareFour(Four A,Four B)
{
	if((A.maxCard)>(B.maxCard))
		return 1;
	else if((A.maxCard)<(B.maxCard))
		return 0;
	else
		return -1;
}

void Four::swap(Four& a,Four& b)
{
    Four tmp;
    tmp=a;
    a=b;
    b=tmp;
}
