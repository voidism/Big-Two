#ifndef Handcard_h
#define Handcard_h
#include <iostream>
#include <string>
#include <vector>
#include "Pair.h"
#include "Single.h"
#include "Play.h"
#include "Three.h"
using namespace std;

class Handcard
{
public:
    vector <Card> hand;
    int min(int);
    void swap(Card&,Card&);
    void sort();
    void printall();
    void popout();
    
    vector <Pair> myPair;
    vector <Single> mySingle;
    vector <Three> myThree;
    vector <Four> myFour;
    vector <Straight> myStraight;
    vector <Straight> myFlushStraight;
    
    static int passnum;
    int nextface(int);//after sorting,start from the card of the parameter int number,seeking the next different face card,return its subscript(to judge straight)
    void userputPair();//if chosen, it still can be judge as pair
    void putPair();//seek all pair,put into a vector
    
    void userputThree();//three can be judge as pair
    void putThree();//seek all Three of kind, put into a vector
    
    void putFour();//seek all Four of kind, put into a vector
    void putStraight(); //seek all Straight, putvvector
    void putSingle();//seek all Single, put into a vector
    
    void classify();//execute all the function above
    void userclassify();//pair can be judge as single
    void judgeclassify();// every card can not be classify repeatedly
    
    int minPair(int);
    int minSingle(int);
    int minThree(int);
    int minFour(int);
    int minStraight(int);
    int minFlushStraight(int);
    void sortingPair();
    void sortingSingle();
    void sortingThree();
    void sortingFour();
    void sortingStraight();
    void sortingFlushStraight();
    
    Play playcardAI(Play,int, vector<Card> &);//new
    Play freecardAI(int , vector<Card> &);//new
    bool judgecard(Play,int ,vector<int>);
    Play userplaycard(Play,vector<int>, vector<Card> &);
    bool club3();
    int kindswitch();
};

#endif
