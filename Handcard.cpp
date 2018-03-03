#include <iostream>
#include <cstdlib>
#include <string>
#include "Pair.h"
#include "Single.h"
#include "Handcard.h"

using namespace std;

int Handcard::passnum=3;

void Handcard::swap(Card& a,Card& b)
{
    Card tmp;
    tmp=a;
    a=b;
    b=tmp;
}

int Handcard::min(int start)
{
    int m=55,s=hand.size(),counter=0;
    for(int i=start;i<s;i++)
    {
        if(hand.at(i).value<m)
        {
        m=hand.at(i).value;
        counter=i;
        }
    }
    return counter;
}

void Handcard::sort()
{
    for(int i=0;i<hand.size();i++)
    {
        swap(hand.at(i),hand.at(min(i)));
    }
}

void Handcard::popout()
{
    for(int i=0;i<hand.size();i++)
    {
        if((hand.at(i).getface()==0)&&(hand.at(i).getsuit()==0))
        {
			hand.erase(hand.begin()+i);
			i--;
        }
    }
}

void Handcard::printall()
{
    for(int i=0;i<hand.size();i++)
    {
        cout<<hand.at(i).toString()<<endl;
    }
}

void Handcard::userputPair()
{
    myPair.clear();
	for(int i=0;i<(hand.size()-1);i++)
    {
		if(hand.at(i).getface()==hand.at(i+1).getface())
        {
            hand.at(i).chosen=1;
            hand.at(i+1).chosen=1;
			Pair tmp(hand.at(i),hand.at(i+1));
			myPair.push_back(tmp);
		}
	}
	sortingPair();
}

void Handcard::putPair()
{
    myPair.clear();
    for(int i=0; i<(hand.size()-1); i++)
    {
        if((hand.at(i).getface()==hand.at(i+1).getface())&&(hand.at(i).chosen==0)&&(hand.at(i+1).chosen==0))
        {
            hand.at(i).chosen=1;
            hand.at(i+1).chosen=1;
            Pair tmp(hand.at(i),hand.at(i+1));
            myPair.push_back(tmp);
        }
    }
    sortingPair();
}

void Handcard::putThree()
{
    myThree.clear();
    for(int i=0; i<(hand.size()-2); i++)
    {
        if(hand.size()<5)break;
        if((hand.at(i).getface()==hand.at(i+1).getface())&&(hand.at(i+1).getface()==hand.at(i+2).getface()))
        {
            //cout<<"ß‰®Ï∏¨ƒ™§F!!!";
            hand.at(i).chosen=1;
            hand.at(i+1).chosen=1;
            hand.at(i+2).chosen=1;
            Three tmp(hand.at(i),hand.at(i+1),hand.at(i+2));
            myThree.push_back(tmp);
        }
    }
    sortingThree();
}

void Handcard::userputThree()
{
    //    cout<<"userputthree";
    myThree.clear();
    for(int i=0; i<(hand.size()-2); i++)
    {
        if(hand.size()<5)break;
        if((hand.at(i).getface()==hand.at(i+1).getface())&&(hand.at(i+1).getface()==hand.at(i+2).getface()))
        {
            Three tmp(hand.at(i),hand.at(i+1),hand.at(i+2));
            myThree.push_back(tmp);
            Pair tmp2(hand.at(i),hand.at(i+2));
            myPair.push_back(tmp2);
        }
    }
    sortingThree();
    sortingPair();
}

void Handcard::putSingle()
{
    mySingle.clear();
    for(int i=0;i<hand.size();i++)
    {
		if((hand.at(i).chosen==0)||(hand.at(i).getface()==13))
        {
            //cout<<"putSingle"<<hand.at(i).toString()<<endl;
            Single tmp(hand.at(i));
            mySingle.push_back(tmp);
		}
    }
    sortingSingle();
}

void Handcard::classify()
{
    popout();
    sort();
    for(int i=0; i<hand.size(); i++)
    {
        hand.at(i).chosen=0;
    }
    putFour();
    putStraight();
    putThree();
    putPair();
    putSingle();

    if(myPair.size()==0)
    {
        mySingle.clear();
        myPair.clear();
        myThree.clear();
        myFour.clear();
        myStraight.clear();
        popout();
        sort();
        for(int i=0; i<hand.size(); i++)
        {
            hand.at(i).chosen=0;
        }
        putFour();
        putStraight();
        putPair();
        putSingle();
    }
}

void Handcard::userclassify()
{
    popout();
    sort();
    for(int i=0; i<hand.size(); i++)
    {
        hand.at(i).chosen=0;
    }
    putSingle();
    userputPair();
    userputThree();
    putFour();
    putStraight();
}

void Handcard::judgeclassify()
{
    popout();
    sort();
    for(int i=0; i<hand.size(); i++)
    {
        hand.at(i).chosen=0;
    }
    putStraight();
    putFour();
    putThree();
    putPair();
    putSingle();
}

int Handcard::minPair(int start)
{
    int m=55,s=myPair.size(),counter=0;
    for(int i=start;i<s;i++)
    {
        if(myPair.at(i).maxCard->value<m)
        {
            m=myPair.at(i).maxCard->value;
			counter=i;
        }
    }
    return counter;
}

void Handcard::sortingPair()
{
    for(int i=0;i<myPair.size();i++)
    {
        myPair.at(i).swap(myPair.at(i),myPair.at(minPair(i)));
    }
}

int Handcard::minThree(int start)
{
    int m=55,s=myThree.size(),counter=0;
    for(int i=start; i<s; i++)
    {
        if(myThree.at(i).maxCard->value<m)
        {
            m=myThree.at(i).maxCard->value;
            counter=i;
        }
    }
    return counter;
}
void Handcard::sortingThree()
{
    for(int i=0; i<myThree.size(); i++)
    {
        myThree.at(i).swap(myThree.at(i),myThree.at(minThree(i)));
    }
}

int Handcard::minSingle(int start)
{
    int m=55,s=mySingle.size(),counter=0;
    for(int i=start;i<s;i++)
    {
        if(mySingle.at(i).maxCard->value<m)
        {
			m=mySingle.at(i).maxCard->value;
			counter=i;
        }
    }
    return counter;
}

void Handcard::sortingSingle()
{
    for(int i=0;i<mySingle.size();i++)
    {
        //if(mySingle.at(i).CompareSingle(mySingle.at(i),mySingle.at(minSingle(i))))
        //cout<<mySingle.at(i).toString()<<"<->"<<mySingle.at(minSingle(i)).toString()<<endl;
        int locmin=minSingle(i);
        mySingle.at(i).swap(mySingle.at(i),mySingle.at(locmin));
    }
}

int Handcard::minFour(int start)
{
    int m=55,s=myFour.size(),counter=0;
    for(int i=start; i<s; i++)
    {
        if(myFour.at(i).maxCard->value<m)
        {
            m=myFour.at(i).maxCard->value;
            counter=i;
        }
    }
    return counter;
}
void Handcard::sortingFour()
{
    for(int i=0; i<myFour.size(); i++)
    {
        myFour.at(i).swap(myFour.at(i),myFour.at(minFour(i)));
    }
}
void Handcard::putFour()
{
    myFour.clear();
    for(int i=0; i<(hand.size()-3); i++)
    {
        if(hand.size()<4)break;
        if((hand.at(i).getface()==hand.at(i+1).getface())&&(hand.at(i+1).getface()==hand.at(i+2).getface())&&(hand.at(i+2).getface()==hand.at(i+3).getface())
           &&(hand.at(i).getsuit()!=hand.at(i+1).getsuit())&&(hand.at(i+1).getsuit()!=hand.at(i+2).getsuit())&&(hand.at(i+2).getsuit()!=hand.at(i+3).getsuit())
           )
        {
            hand.at(i).chosen=1;
            hand.at(i+1).chosen=1;
            hand.at(i+2).chosen=1;
            hand.at(i+3).chosen=1;
            Four tmp(hand.at(i),hand.at(i+1),hand.at(i+2),hand.at(i+3));
            myFour.push_back(tmp);
        }
    }
    sortingFour();
}
int Handcard::minStraight(int start)
{
    int m=55,s=myStraight.size(),counter=0;
    for(int i=start; i<s; i++)
    {
        if(myStraight.at(i).maxCard->value<m)
        {
            m=myStraight.at(i).maxCard->value;
            counter=i;
        }
    }

    return counter;
}
void Handcard::sortingStraight()
{
    for(int i=0; i<myStraight.size(); i++)
    {
        myStraight.at(i).swap(myStraight.at(i),myStraight.at(minStraight(i)));
    }
}
void Handcard::putStraight()
{
    myStraight.clear();
    myFlushStraight.clear();
    for(int i=0; i<(hand.size()-4); i++)
    {
        if(hand.size()<5)break;
        int a=i;
        int b=nextface(a);
        int c=nextface(b);
        int d=nextface(c);
        int e=nextface(d);
        if(
           (((hand.at(a).getface())==(hand.at(b).getface()-1)
            &&(hand.at(b).getface()-1)==(hand.at(c).getface()-2)
            &&(hand.at(c).getface()-2)==(hand.at(d).getface()-3)
            &&(hand.at(d).getface()-3)==(hand.at(e).getface()-4)
            )
           &&
           ((hand.at(a).getface()!=9)&&(hand.at(b).getface()!=10)&&(hand.at(c).getface()!=11)&&(hand.at(d).getface()!=12)&&(hand.at(e).getface()!=13)))
           ||
           ((hand.at(a).getface()==1)&&(hand.at(b).getface()==2)&&(hand.at(c).getface()==3)&&(hand.at(d).getface()==12)&&(hand.at(e).getface()==13))
           ||
           ((hand.at(a).getface()==1)&&(hand.at(b).getface()==2)&&(hand.at(c).getface()==3)&&(hand.at(d).getface()==4)&&(hand.at(e).getface()==13))
           )
        {
            hand.at(a).chosen=1;
            hand.at(b).chosen=1;
            hand.at(c).chosen=1;
            hand.at(d).chosen=1;
            hand.at(e).chosen=1;
            Straight tmp(hand.at(a),hand.at(b),hand.at(c),hand.at(d),hand.at(e));
            if(((hand.at(a).getsuit())==(hand.at(b).getsuit())
                &&(hand.at(b).getsuit())==(hand.at(c).getsuit())
                &&(hand.at(c).getsuit())==(hand.at(d).getsuit())
                &&(hand.at(d).getsuit())==(hand.at(e).getsuit())
                )==0)
                myStraight.push_back(tmp);
            if((hand.at(a).getsuit())==(hand.at(b).getsuit())
               &&(hand.at(b).getsuit())==(hand.at(c).getsuit())
               &&(hand.at(c).getsuit())==(hand.at(d).getsuit())
               &&(hand.at(d).getsuit())==(hand.at(e).getsuit())
               )
                myFlushStraight.push_back(tmp);
        }
    }
    sortingStraight();
    sortingFlushStraight();
}
int Handcard::minFlushStraight(int start)
{
    int m=55,s=myFlushStraight.size(),counter=0;
    for(int i=start; i<s; i++)
    {
        if(myFlushStraight.at(i).maxCard->value<m)
        {
            m=myFlushStraight.at(i).maxCard->value;
            counter=i;
        }
    }

    return counter;
}
void Handcard::sortingFlushStraight()
{
    for(int i=0; i<myFlushStraight.size(); i++)
    {
        myFlushStraight.at(i).swap(myFlushStraight.at(i),myFlushStraight.at(minFlushStraight(i)));
    }
}
Play Handcard::playcardAI(Play in, int inn, vector<Card> &gvector)
{
    classify();
    gvector.clear();
    switch(in.kindcode)
    {
        case 1://if the card last player play Single
        {
            if(passnum>=3)
            {
                //if already pass three times
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            int counter=-1;
            for(int i=0; i<mySingle.size(); i++)
            {
                if((mySingle.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            if(counter>-1) //if there are proper cards to play
            {
                passnum=0;
                cout<<"playcard:"<<mySingle.at(counter).toString()<<endl<<endl;
                gvector.push_back(*(mySingle.at(counter).maxCard));
                Play out(mySingle.at(counter));
                //delete hand's card
                mySingle.at(counter).maxCard->setface(0);
                mySingle.at(counter).maxCard->setsuit(0);
                //delete itself
                mySingle.erase(mySingle.begin()+counter);
                return out;
            }
            else if(counter==-1) //if no proper card to play
            {
                if(myFour.size()>0)
                {
                    Play alto(4,0);
                    return playcardAI(alto,inn, gvector);
                }
                if(myFlushStraight.size()>0)
                {
                    Play alto(6,0);
                    return playcardAI(alto,inn, gvector);
                }
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;
            }
        }
        case 2://if the card last player play Pair
        {
            if(passnum>=3)
            {
                //if already pass three times
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            int counter=-1;
            for(int i=0; i<myPair.size(); i++)
            {
                if((myPair.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            if(counter>-1) //if there are proper cards to play
            {
                passnum=0;
                if(((myPair.size()-1)>counter)&&(myThree.size()>0))         //new:if there are three to play, reserve a small pair to match it.
                    counter++;
                cout<<"playcard:"<<myPair.at(counter).toString()<<endl<<endl;
                gvector.push_back(*(myPair.at(counter).maxCard));
                gvector.push_back(*(myPair.at(counter).minCard));
                Play out(myPair.at(counter));
                //delete hand's card
                myPair.at(counter).p1->setface(0);
                myPair.at(counter).p1->setsuit(0);
                myPair.at(counter).p2->setface(0);
                myPair.at(counter).p2->setsuit(0);
                //delete itself
                myPair.erase(myPair.begin()+counter);
                return out;
            }
            else if(counter==-1) //if no proper card to play
            {
                if(myFour.size()>0)
                {
                    Play alto(4,0);
                    return playcardAI(alto,inn, gvector);
                }
                if(myFlushStraight.size()>0)
                {
                    Play alto(6,0);
                    return playcardAI(alto,inn, gvector);
                }
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;

            }
        }
        case 3://if the card last player play Three
        {
            if(passnum>=3)
            {
                //if already pass three times
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            //find min but proper three
            int counter=-1;
            for(int i=0; i<myThree.size(); i++)
            {
                if((myThree.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            //find min but proper pair
            int pcounter=-1;
            for(int i=0; i<myPair.size(); i++)
            {
                pcounter=i;
                break;
            }
            //to sum up
            if(counter>-1&&pcounter>-1) //if there are proper cards to play
            {
                passnum=0;
                cout<<"playcard:"<<myThree.at(counter).toString()<<myPair.at(pcounter).toString()<<endl<<endl;
                Play out(myThree.at(counter),myPair.at(pcounter));
                gvector.push_back(*(myThree.at(counter).t[0]));
                gvector.push_back(*(myThree.at(counter).t[1]));
                gvector.push_back(*(myThree.at(counter).t[2]));
                gvector.push_back(*(myPair.at(pcounter).maxCard));
                gvector.push_back(*(myPair.at(pcounter).minCard));
                //delete hand's card
                for(int i=0; i<3; i++)
                {
                    myThree.at(counter).t[i]->setface(0);
                    myThree.at(counter).t[i]->setsuit(0);
                }
                //delete itself
                myThree.erase(myThree.begin()+counter);
                //delete hand's card
                myPair.at(counter).p1->setface(0);
                myPair.at(counter).p1->setsuit(0);
                myPair.at(counter).p2->setface(0);
                myPair.at(counter).p2->setsuit(0);
                //delete itself
                myPair.erase(myPair.begin()+counter);
                return out;
            }
            else if(counter==-1||pcounter==-1) //if no proper card to play
            {
                if(myFour.size()>0)
                {
                    Play alto(4,0);
                    return playcardAI(alto,inn, gvector);
                }
                if(myFlushStraight.size()>0)
                {
                    Play alto(6,0);
                    return playcardAI(alto,inn, gvector);
                }
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;

            }
        }
        case 4:
        {
            if(passnum>=3)
            {
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            int counter=-1;
            for(int i=0; i<myFour.size(); i++)
            {
                if((myFour.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            //find min but proper single
            int scounter=-1;
            for(int i=0; i<mySingle.size(); i++)
            {
                scounter=i;
                break;
            }
            if (counter>-1&&scounter>-1)
            {
                passnum=0;
                cout<<"playcard:"<<myFour.at(counter).toString()<<mySingle.at(scounter).toString()<<endl<<endl;
                gvector.push_back(*(myFour.at(counter).f[0]));
                gvector.push_back(*(myFour.at(counter).f[1]));
                gvector.push_back(*(myFour.at(counter).f[2]));
                gvector.push_back(*(myFour.at(counter).f[3]));
                gvector.push_back(*(mySingle.at(scounter).maxCard));
                Play out(myFour.at(counter),mySingle.at(scounter));
                //delete hand's card
                for(int i=0; i<4; i++)
                {
                    myFour.at(counter).f[i]->setface(0);
                    myFour.at(counter).f[i]->setsuit(0);
                }
                //delete itself
                myFour.erase(myFour.begin()+counter);
                //delete hand's card
                mySingle.at(counter).maxCard->setface(0);
                mySingle.at(counter).maxCard->setsuit(0);
                //delete itself
                mySingle.erase(mySingle.begin()+counter);
                return out;
            }
            else if(counter==-1)
            {
                if(myFlushStraight.size()>0)
                {
                    Play alto(6,0);
                    return playcardAI(alto,inn, gvector);
                }
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;
            }
        }
        case 5:
        {
            if(passnum>=3)
            {
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            int counter=-1;
            for(int i=0; i<myStraight.size(); i++)
            {
                if((myStraight.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            if (counter>-1)
            {
                passnum=0;
                cout<<"playcard:"<<myStraight.at(counter).toString()<<endl<<endl;
                gvector.push_back(*(myStraight.at(counter).s[0]));
                gvector.push_back(*(myStraight.at(counter).s[1]));
                gvector.push_back(*(myStraight.at(counter).s[2]));
                gvector.push_back(*(myStraight.at(counter).s[3]));
                gvector.push_back(*(myStraight.at(counter).s[4]));
                Play out(myStraight.at(counter));
                //delete hand's card
                for(int i=0; i<5; i++)
                {
                    myStraight.at(counter).s[i]->setface(0);
                    myStraight.at(counter).s[i]->setsuit(0);
                }
                //delete itself
                myStraight.erase(myStraight.begin()+counter);
                return out;
            }
            else if(counter==-1)
            {
                if(myFour.size()>0)
                {
                    Play alto(4,0);
                    return playcardAI(alto,inn, gvector);
                }
                if(myFlushStraight.size()>0)
                {
                    Play alto(6,0);
                    return playcardAI(alto,inn, gvector);
                }
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;
            }
        }
        case 6:
        {
            if(passnum>=3)
            {
                passnum=0;
                cout<<"freely ";
                return freecardAI(inn, gvector);
            }
            int counter=-1;
            for(int i=0; i<myFlushStraight.size(); i++)
            {
                if((myFlushStraight.at(i).maxCard->value)>(in.maxCard.value))
                {
                    counter=i;
                    break;
                }
            }
            if (counter>-1)
            {
                passnum=0;
                cout<<"playcard:"<<myFlushStraight.at(counter).toString()<<endl<<endl;
                gvector.push_back(*(myFlushStraight.at(counter).s[0]));
                gvector.push_back(*(myFlushStraight.at(counter).s[1]));
                gvector.push_back(*(myFlushStraight.at(counter).s[2]));
                gvector.push_back(*(myFlushStraight.at(counter).s[3]));
                gvector.push_back(*(myFlushStraight.at(counter).s[4]));
                Play out(myFlushStraight.at(counter),6);
                //delete hand's card
                for(int i=0; i<5; i++)
                {
                    myFlushStraight.at(counter).s[i]->setface(0);
                    myFlushStraight.at(counter).s[i]->setsuit(0);
                }
                //delete itself
                myFlushStraight.erase(myFlushStraight.begin()+counter);
                return out;
            }
            else if(counter==-1)
            {
                passnum++;
                cout<<"PASS!"<<endl<<endl;
                return in;
            }
        }
    }
    Play a;
    return a;
}

Play Handcard::freecardAI(int inn,vector<Card> &gvector)
{
    classify();
    int kindarry[7];
    //find single
    if(!mySingle.size())
    {
        kindarry[1]=55;
    }
    else
        kindarry[1]=mySingle.at(0).minCard->value;
    //find pair
    if(!myPair.size())
    {
        kindarry[2]=55;
    }
    else
        kindarry[2]=myPair.at(0).minCard->value;
    //find three
    if(!myThree.size())
    {
        kindarry[3]=55;
    }
    else
        kindarry[3]=myThree.at(0).minCard->value;
    //find four
    if(!myFour.size())
    {
        kindarry[4]=55;
    }
    else
        kindarry[4]=myFour.at(0).minCard->value;
    //find straight
    if(!myStraight.size())
    {
        kindarry[5]=55;
    }
    else
        kindarry[5]=myStraight.at(0).minCard->value;
    //find flushstraight
    if(!myFlushStraight.size())
    {
        kindarry[6]=55;
    }
    else
        kindarry[6]=myFlushStraight.at(0).minCard->value;

    int in=0,min=56;
    for(int i=1; i<7; i++)
    {
        if(kindarry[i]<=min)
        {
            min=kindarry[i];
            in=i;
        }
    }
    //add super AI
    if(inn>0)
        if(in==1||in==2)
        {
            if(myStraight.size()>0)
                in=5;
            else if(myThree.size()>0)
                in=3;
        }
    //if there are straight or three in hand, play them first.
    if(inn==0)
        if(in==2)
        {
            if(myThree.size()>0)
                in=3;
        }
    //if it want to play pair at first inn, and there are three in hand, play them together.
    Play input(in,0);
    return playcardAI(input, inn, gvector);
}

bool Handcard::judgecard(Play in,int inn,vector<int> clicked)
{
    if(clicked.size()==0) //if no proper card to play
    {
        return 1;
    }
    for(int i=0; i<clicked.size(); i++)
    {
        if((clicked.at(i)>=hand.size())||(clicked.at(i)<0))
        {
            cout<<"\nout of range\n";
            return 0;
        }
    }
    Handcard preplay ;
    for(int i=0; i<clicked.size(); i++)
    {
        preplay.hand.push_back(hand.at(clicked.at(i)));
    }
    preplay.judgeclassify();
    //check wrong card shape
    int k=preplay.kindswitch();
    if(k==0)
        return 0;
    if((k==4)&&(in.kindcode!=4)&&(in.kindcode!=6))//Four can play after any other card shape
        return 1;
    if((k==6)&&(in.kindcode!=6))//FlushStraight can play after any other card shape
        return 1;

    if(passnum>=3)
    {
        in.maxCard.setface(0);
        in.maxCard.setsuit(0);
        in.maxCard.value=0;
        in.kindcode=0;
        cout<<"freely ";
    }
    if(k==in.kindcode||passnum>=3)
    {
        switch(k)
        {
            case 1:
            {
                if(preplay.mySingle.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
            case 2:
            {
                if(preplay.myPair.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
            case 3:
            {
                if(preplay.myThree.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
            case 4:
            {
                if(preplay.myFour.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
            case 5:
            {
                if(preplay.myStraight.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
            case 6:
            {
                if(preplay.myFlushStraight.at(0).maxCard->value>in.maxCard.value)
                {
                    return 1;
                }
                else
                {
                    cout<<"\nthe card is not big enough!\n";
                    return 0;
                }
            }
        }
    }
    return 0;
}

Play Handcard::userplaycard(Play a,vector <int> clicked, vector<Card> &gvector)
{
    gvector.clear();
    if(clicked.size()==0) //if user play empty card
    {
        passnum++;
        cout<<"user PASS!"<<endl<<endl;
        return a;
    }
    passnum=0;
    Handcard preplay;

    for(int i=0; i<clicked.size(); i++)
    {
        preplay.hand.push_back(hand.at(clicked.at(i)));
    }
    preplay.judgeclassify();

    switch(preplay.kindswitch())
    {
        case 1://if the card last player play is Single
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.mySingle.at(0).toString()<<endl<<"->single"<<endl;
            gvector.push_back(*(preplay.mySingle.at(0).maxCard));
            Play out(preplay.mySingle.at(0));
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.erase(hand.begin()+clicked.at(0));
            }
            //delete itself
            preplay.mySingle.erase(preplay.mySingle.begin());
            return out;
        }

        case 2://if the card last player play is Pair
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.myPair.at(0).toString()<<endl<<"->pair"<<endl;
            gvector.push_back(*(preplay.myPair.at(0).maxCard));
            gvector.push_back(*(preplay.myPair.at(0).minCard));
            Play out(preplay.myPair.at(0));
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.erase(hand.begin()+clicked.at(0));
            }
            //delete itself
            preplay.myPair.clear();
            return out;
        }
        case 3://if the card last player play is Three
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.myThree.at(0).toString()<<preplay.myPair.at(0).toString()<<endl<<"->three"<<endl;
            gvector.push_back(*(preplay.myThree.at(0).t[0]));
            gvector.push_back(*(preplay.myThree.at(0).t[1]));
            gvector.push_back(*(preplay.myThree.at(0).t[2]));
            gvector.push_back(*(preplay.myPair.at(0).maxCard));
            gvector.push_back(*(preplay.myPair.at(0).minCard));
            Play out(preplay.myThree.at(0),preplay.myPair.at(0));
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.at(clicked.at(i)).setface(0);
                hand.at(clicked.at(i)).setsuit(0);
            }
            //delete itself
            preplay.myThree.clear();
            preplay.myPair.clear();
            return out;
        }
        case 4://if the card last player play is Four
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.myFour.at(0).toString()<<preplay.mySingle.at(0).toString()<<endl<<"->four"<<endl;
            gvector.push_back(*(preplay.myFour.at(0).f[0]));
            gvector.push_back(*(preplay.myFour.at(0).f[1]));
            gvector.push_back(*(preplay.myFour.at(0).f[2]));
            gvector.push_back(*(preplay.myFour.at(0).f[3]));
            gvector.push_back(*(preplay.mySingle.at(0).maxCard));
            Play out(preplay.myFour.at(0),preplay.mySingle.at(0));
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.at(clicked.at(i)).setface(0);
                hand.at(clicked.at(i)).setsuit(0);
            }
            //delete itself
            preplay.myFour.clear();
            preplay.mySingle.clear();
            return out;
        }
        case 5://if the card last player play is Straight
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.myStraight.at(0).toString()<<endl<<"->straight"<<endl;
            gvector.push_back(*(preplay.myStraight.at(0).s[0]));
            gvector.push_back(*(preplay.myStraight.at(0).s[1]));
            gvector.push_back(*(preplay.myStraight.at(0).s[2]));
            gvector.push_back(*(preplay.myStraight.at(0).s[3]));
            gvector.push_back(*(preplay.myStraight.at(0).s[4]));
            Play out(preplay.myStraight.at(0));
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.at(clicked.at(i)).setface(0);
                hand.at(clicked.at(i)).setsuit(0);
            }
            //delete itself
            preplay.myStraight.clear();
            return out;
        }
        case 6://if the card last player play is FlushStraight
        {
            passnum=0;
            cout<<"user playcard:"<<preplay.myFlushStraight.at(0).toString()<<endl<<"->flushstraight"<<endl;
            gvector.push_back(*(preplay.myFlushStraight.at(0).s[0]));
            gvector.push_back(*(preplay.myFlushStraight.at(0).s[1]));
            gvector.push_back(*(preplay.myFlushStraight.at(0).s[2]));
            gvector.push_back(*(preplay.myFlushStraight.at(0).s[3]));
            gvector.push_back(*(preplay.myFlushStraight.at(0).s[4]));
            Play out(preplay.myFlushStraight.at(0),6);
            //delete hand's card
            for(int i=0; i<clicked.size(); i++)
            {
                hand.at(clicked.at(i)).setface(0);
                hand.at(clicked.at(i)).setsuit(0);
            }
            //delete itself
            preplay.myFlushStraight.clear();
            return out;
        }
    }
    return a;
}

bool Handcard::club3()
{
    if(hand.size()==13)
    {
        if(hand.at(0).value==1)
            return 1;
    }
    return 0;
}

int Handcard::kindswitch()
{
    if((mySingle.size()==1)&&(myPair.size()==0)&&(myThree.size()==0)&&(myFour.size()==0)&&(myStraight.size()==0)&&(myFlushStraight.size()==0))
    {
        return 1;
    }
    if((mySingle.size()==0)&&(myPair.size()==1)&&(myThree.size()==0)&&(myFour.size()==0)&&(myStraight.size()==0)&&(myFlushStraight.size()==0))
    {
        return 2;
    }
    if((mySingle.size()==0)&&(myPair.size()==1)&&(myThree.size()==1)&&(myFour.size()==0)&&(myStraight.size()==0)&&(myFlushStraight.size()==0))
    {
        return 3;
    }
    if((mySingle.size()==1)&&(myPair.size()==0)&&(myThree.size()==0)&&(myFour.size()==1)&&(myStraight.size()==0)&&(myFlushStraight.size()==0))
    {
        return 4;
    }
    if((mySingle.size()==0)&&(myPair.size()==0)&&(myThree.size()==0)&&(myFour.size()==0)&&(myStraight.size()==1)&&(myFlushStraight.size()==0))
    {
        return 5;
    }
    if((mySingle.size()==0)&&(myPair.size()==0)&&(myThree.size()==0)&&(myFour.size()==0)&&(myStraight.size()==0)&&(myFlushStraight.size()==1))
    {
        return 6;
    }
    else
        return 0;

}

int Handcard::nextface(int a)
{
    for(int i=a+1; i<hand.size(); i++)
    {
        if(hand.at(a).getface()!=hand.at(i).getface())
            return i;
    }
    for(int i=0; i<hand.size(); i++)
    {
        if(hand.at(a).getface()!=hand.at(i).getface())
            return i;
    }
    return 0;
}
