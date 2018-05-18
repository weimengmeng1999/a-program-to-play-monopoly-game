#include "square.h"//include the information about square.h


void square::invest(){//invest the square
	int charge =1.05* pboard.getprice(order);//define an int charge as 1.05 times the price of the board
	pboard.cprice(order, charge);
}

int square::chargeper(){
	int per=1;//define an int per as 1
	int a = pboard.getowner(order), a1 = pboard.getowner(order + 1), b1 = pboard.getowner(order - 1), a2 = pboard.getowner(order + 2), b2 = pboard.getowner(order - 2);
	if (a ==b1 || a == a1){//if a is same as b1 or a is same as a1, then per plus 0.15
		per += 0.15;
	}
	if ((a == b1 && a == a1) ||(a == b1 && a == b2)||(a == a1&& a == a2) ){//id a is same as b1 and a1 or a is same as b1 and b2 or a is same as a1 and a2, then per plus 0.2
		per += 0.2;
	}
	else per += 0.1;//under other situation, per plus 0.1
	return per;
}


