
#include "board.h"// include information about board.h

//define the functions to declare the class of board
board::board(){
	setprice();//set the setprice() function
	initialown();//set the initialown() function
}

void board::showboard(int x,int y){
	system("cls");//clear the system
	int b[80];//declare a variable to represent the square
	string a[80];//declare a string to represent the player or computer position
	int i, j;//define two ints i and j
	for (i = 1; i < 80; i++){//b[i] equals to i+1 during the process of i increase from 1 to 80
		b[i] = i+1 ;
		if (i < 9){ a[i] = std::to_string(b[i])+" "; }//if i is smaller than 9, then convert b[i] to string and add a spcae
		else a[i]=std::to_string(b[i]);//if i is larger than 9, then convert b[i] to string

		if (bgowner[i] == 1){//if bgowner[i] is equal to 1, if x is the same as i, this is human; if y is equal to i, it is computer; otherwise this is empty
			if (x == i){a[i] = "$H";}
			else if (y == i){ a[i] = "$C"; }
			else a[i] = "$ ";
		}

		else if (bgowner[i] == 2){//if bgowner[i] is equal to 2, if x is the same as i, this is human; if y is equal to i, it is computer; otherwise this is empty
			if (x == i){ a[i] = "#H"; }
			else if (y == i){ a[i] = "#C"; }
			else a[i] = "# ";
		}
		else {//if i is another value, then if x is the same as i, this is human; if y is the same as i, this is computer
			if (x == i){ a[i] = "H "; }
			else if (y == i){a[i] = "C "; }
			}
		}
	a[0] = "**";
	
	//print the board on the screen
	for (i = 0; i < 21; i++){
		if (i == 0){ cout << "┏"; }
		else if (i == 1){ cout << "━ " << a[i - 1] << "━┯"; }
		else if (i == 20){ cout << "━ " << a[19] << "━┓"; }
		else if (i < 10){ cout << "━ " << a[i - 1] << "━┯"; }
		else cout << "━ " << a[i - 1] << "━┯";
	}
	cout << "\n";
	for (i = 0; i < 21; i++){
		if (i == 0){ cout << "┣"; }
		else if (i == 20){ cout << "━ " << a[20] << "━┫"; }
		else if (i == 1){ cout << "━ " << a[79] << "━╋"; }
		else if (i == 19){ cout << "━━━━━╋"; }
		else cout << "━━━━━┻";
	}
	cout << "\n";

	for (j = 0; j < 19; j++){
		for (i = 0; i < 21; i++){
			if (i == 0 || i == 19){ cout << "┣━ "; }
			else if (i == 1){ cout << a[78 - j] << "━┫"; }
			else if (i == 20){ cout << a[21 + j] << "━┫"; }
			else if (i>12 && i<18){ cout << "       "; }
			else cout << "      ";
		}
		cout << "\n";
	}

	for (i = 0; i < 21; i++){
		if (i == 0){
			cout << "┣━ ";
		}
		else if (i == 1){
			cout << a[59] << "━┫";
		}
		else if (i == 19){
			cout << "━ " << a[41] << "━┫";
		}
		else if (i == 20){
			cout << "━ " << a[40] << "━┫";
		}
		else cout << "━ " << a[60 - i] << "━┓";
	}
	cout << "\n";

	for (i = 0; i < 21; i++){
		if (i == 0){ cout << "┗"; }
		else cout << "━━━━━┻";
	}
	cout << "\n";


}


void board::setprice(){
	int i;//declare an int as i
	allprice[0] = 200;//declare the valur
	for (i = 1; i < 80; i++){//do the loop when i increases from 1 to 80, get the value of each square in a range from 10 to 500
		srand((unsigned)time(NULL));
		allprice[i] = 10 + rand() % 491;
	}
}

void board::initialown(){
	int i;//define an int as i
	for (i = 0; i < 80; i++){//do the loop when i increases from 1 to 80, set the bgowner[i] as 0
		bgowner[i] = 0;
	}
}

void board::cown(int x, int y){
	bgowner[x] = y;//set bgowner[x] as y
}

void board::cprice(int x, int y){
	allprice[x] = y;//set allprice[x] as y
}

int board::getowner(int x){
	return bgowner[x];//return the value of bgowner[x]
}
int board::getprice(int x){
	return allprice[x];//return the value of allprice[x]
}