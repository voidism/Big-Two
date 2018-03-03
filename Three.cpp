#include <vector>
#include "Card.h"
#include "Three.h"
using namespace std;

Three::Three(Card &a,Card &b,Card &c){
	if((a.getface()==b.getface())&&(b.getface()==c.getface())){
		t[0]=&a;
		t[1]=&b;
		t[2]=&c;
	}
	else
		cout<<"this three"<<a.toString()<<","<<b.toString()<<","<<c.toString()<<"is not a three!\n";

    int m=55;
    for(int i=0;i<3;i++){
        if(t[i]->value<m){
        m=t[i]->value;
        minCard=t[i];
        }
    }
    int n=0;
    for(int i=0;i<3;i++){
        if(t[i]->value>n){
        n=t[i]->value;
        maxCard=t[i];
        }
    }
}
Three::Three(){
	Card a,b,c;
	t[0]=&a;
	t[0]=&b;
	t[0]=&c;
}

string Three::toString(){
    return t[0]->toString()+" & "+t[1]->toString()+" & "+t[2]->toString()+" & ";
    }

int Three::CompareThree(Three A,Three B){
	if((A.maxCard->value)>(B.maxCard->value))
		return 1;
	else if((A.maxCard->value)<(B.maxCard->value))
		return 0;
	else
		return -1;
}

void Three::swap(Three& a,Three& b){
		Three tmp;
		tmp=a;
		a=b;
		b=tmp;
	}
