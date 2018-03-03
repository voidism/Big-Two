#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Card.h"
#include "Play.h"
#include "Pair.h"
#include "Single.h"
using namespace std;


Play::Play()
{
    Card i(0,0);
    kindcode=1;
    maxCard=i;
}

Play::Play(Single a)
{
    kindcode=1;
    maxCard=*(a.maxCard);
}

Play::Play(Pair a)
{
    kindcode=2;
    maxCard=*(a.maxCard);
}

Play::Play(int a,int b)
{
    kindcode=a;
    maxCard=b;
}

Play::Play(Three a,Pair b)
{
    kindcode=3;
    maxCard=*(a.maxCard);
}

Play::Play(Four a,Single b)
{
    kindcode=4;
    maxCard=*(a.maxCard);
}

Play::Play(Straight a)
{
    kindcode=5;
    maxCard=*(a.maxCard);
}

Play::Play(Straight a,int b)
{
    kindcode=6;
    maxCard=*(a.maxCard);
}
