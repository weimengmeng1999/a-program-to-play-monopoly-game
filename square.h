
#ifndef _SQUARE
#define _SQUARE

#include"board.h"//include the information about the board.h

class square
{
protected:
	int order;//declare an protected int as order
	board pboard;//declare an array of board as pboard
public:
	void invest();//invest the square
	int chargeper();//charge the fine
};

#endif