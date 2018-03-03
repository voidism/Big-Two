#ifndef Card_h
#define Card_h
#include <iostream>
#include <string>
using namespace std;

class Card
{
	friend class player;
    
	private:
		int suit;
		int face;
    
	public:
		int value;
		bool chosen;
		Card(int =0,int =0);
		void setface(int);
		void setsuit(int);
		int getface();
		int getsuit();
		static string test;
		static string facestring[14];
		static string suitstring[5];
		string toString();
};
#endif
