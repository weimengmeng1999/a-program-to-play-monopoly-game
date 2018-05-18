#ifndef _PLAYER
#define _PLAYER
#include<iostream>//include information about the standard library of iostream
#include<string>//include information about the standard library of string
#include<iomanip>//inlcude information abou the standard library of iomanip
#include<time.h>//include information about the standard libray of time.h
#include <stdio.h>//include informaiton about the standard library of stdio.h
#include"square.h"//include informaiton about the square.h
using namespace std;//using standard name

class player:public square{//declare a class player as a subclass of square

private:
	int money;//delcare an int as money
	string username;//declare a string as username
	string role;//declare a string as role
	int nuown;//declare an int as nuown
public:
	player(int numoney, string name, string prole, int porder, int pnuown, board bboard);
	void refreshboard(board bboard);//update the board
	void move();//move forward
	int testowner();//test whether the square is occupied
	int buy();//buy the square
	void pinvest();//invesr the square
	int paypass();//fine 
	bool die();//bankruptcy
	int AI(player &x, player &y);
	void show(player &x, player &y);
	int getmoney();
	int getposition();
	int getnuown();
	board getboard();
	int play(player &x,player &y);
	
};


#endif