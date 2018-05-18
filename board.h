#ifndef _BOARD 
#define _BOARD
#include<iostream>//include the information of standard library iostream
#include<time.h>//include the information of standard library time.h
#include<string>//include the informaition of standard libray string
using namespace std;//using standard name

class board{
private:
	int allprice[80];//define a private int as allprice[80]
	int bgowner[80];//define a private int as bgowner[80]

public:
	board();//initialize the board function
	void showboard(int x, int y);//showboard function
	void setprice();//set the price of each square
	void initialown();//initialize the ownership of each square
	void cown(int x, int y);
	void cprice(int x, int y);
	int getowner(int x);//get the owner of the square
	int getprice(int x);
};
#endif