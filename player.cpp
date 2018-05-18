#include"player.h"

player::player(int numoney, string name, string prole, int porder, int pnuown, board bboard){//initialize the player function
	money = numoney;//the initial value of money is numoney
	username = name;//the initial value of username is name
	role = prole;//the initial value of role is prole
	order = porder;//the initial value of order is porder
	nuown = pnuown;//the initial value of nuown is pnuown
	pboard = bboard;//the initial value of pboard is bborad
}

void player::refreshboard( board bboard){
	pboard = bboard;//set the value of pboard as bbaord
}

void player::move(){
	//get the random number from 1 to 6
	srand((unsigned)time(NULL));
	order =order+ 1 + rand() % 6;
	if (order > 79){//if the order is larger than 79, then order minus 80
		order -= 80;
		if (order == 0){//if order is 0, than add 200
			money += 200;
		}
	}
}

int player::testowner(){
	if (role == "human"){//if role is human, then set the square to be one, 
		if (pboard.getowner(order) == 1){ return 1; }
		else if (pboard.getowner(order) == 2){ return 2; }
		else return 0;
	}
	if (role == "computer"){//if the role is computer, then set the square to be 2, otherwise return 0
		if (pboard.getowner(order) == 2){ return 1; }
		if( pboard.getowner(order) == 1){ return 2; }
		else return 0;
	}
}

int player::buy(){
	if (pboard.getowner(order) == 0){//if the squre is 0, than the money of player decrease and add this square to player
		money -= pboard.getprice(order);
		nuown++;
		if (role == "human"){//if the role is player, print player's board
			pboard.cown(order, 1);
		}
		if (role == "computer"){//if the role is computer, print computer's board
			pboard.cown(order, 2);
		}
		return 1;
	}
	else return 0;
}

void player::pinvest(){
	money -= pboard.getprice(order)*0.5;//if invest, the money minus half of the price of the square
	invest();
}

int player::paypass(){
	if (testowner() == 2){//if the square is owned by the computer, then player need to pay the money to pass
		money -= pboard.getprice(order)*chargeper();
		return 1;
	}
	else return 0;
}

bool player::die(){//if player's money is smaller than 0, then game over
	if (money <= 0){
		return true;
	}
	else return false;
}

int player::AI(player &x, player &y){
	move();//computer do the move function
	pboard.showboard(x.order, order);//print the board
	show(x, y);
	_sleep(3000);
	int choose;
	srand((unsigned)time(NULL));
	choose = rand() % 2;
	int a = pboard.getprice(order), a1 = pboard.getprice(order + 1), a2 = pboard.getprice(order + 2);
	if (choose == 1){
		if (money > (1.5*a + a1 + a2)){//do the loop if computer's money is larger than 1.5*a+a1+a2
			if (testowner() == 0){//if the square is empty, than computer buy it
				if (buy() == 1){
					pboard.showboard(x.order, order);//print the updated board
					show(x, y);
					cout << "\nthe AI has bought this squre";
					_sleep(3000);
				}
				pinvest();//do the invest function for computer
				invest();
				pboard.showboard(x.order, order);//print the updated board
				show(x, y);
				cout << "\nthe AI has invested this squre";
				_sleep(3000);
			}
		}
	}
	else { 
	cout << "\nthe computer player did not choose to buy the property!"; 
	_sleep(3000);
	}
	if (paypass() == 1){
		pboard.showboard(x.order, order);//print the updated board
		show(x, y);
		cout << "AI has been fined!";
		_sleep(3000);
	}//do the fine function for computer
		
		if (die() == true){ //if computer's money is smaller than 0, then game over
			return 0;
		}
		return 1;
	}




int player::getmoney(){
	return money;//return the value of money
}
int player:: getposition(){
	return order;//return the value of order
}
int player::getnuown(){
	return nuown;//reture the value of nuown
}
board player::getboard(){
	return pboard;//return the value of pboard
}



void player::show(player &x, player &y){//print the money and square owned by computer and player on the screen
	cout << "\n#############################################################################" << endl;
	cout << "# " <<x.username<<setw(15) << " money: " << setw(4) << x.money << setw(10) << "own:" << setw(3) << x.nuown
		<< "  # " <<y.username<< setw(10) << "money: " << setw(4) << y.money << setw(10) << "own:" << setw(3) << y.nuown << " #" << endl;
	cout << "#############################################################################" << endl;
}

int player::play(player &x,player &y){
	char quit;//declare a char quit
	char buys;//declare a char buys
	cout << "\nplease input 'y' to roll the dice, or other keys to quit\n";//ask user to roll the dice or quit the game
	cin >> quit;
	if (quit == 'y'){//if the input is y, then do the following functions
		move();//do the move function for player
		pboard.showboard(order, y.order);//print the updated board on the screen
		show(x, y);//do the show function
		//ask user to buy the square or not
		cout << "The value of this square is: "<<pboard.getprice(order)<<"\nDo you want to buy this square? input 'y' to buy, or other keys if you don't buy\n";
		cin >> buys;
		if (buys == 'y'){// if buy, do the following functions
			if (buy() == 1 && money >pboard.getprice(order)){
				pboard.showboard(order, y.order);//update the board
				show(x, y);//print the board on the screen
				cout << "congratualations! you have bought this squre!\n";
				cout << "Do you want to invest it? input 'y' to invest, or other keys if you don't invest\n";//ask user whether to invest the square
				cin >> buys;
				if (buys == 'y'&&money > 0.5*pboard.getprice(order)){//if player choose to buy and has enough money, then do the invest function
					pinvest();
					invest();
					cout << "invest succeessfully! the charge percent has add 5%\n";
					_sleep(3000);
				}
				else { 
					cout << "invest failed!\n"; 
					_sleep(3000);
				}
			}
			else { 
			cout << "buy failed! This sqaure has been occupied or you don't have enough money\n";
			_sleep(3000);
			}//if the square is occupied, then print occupied on the screen

		}
		return 1;
	}
	else return 0;
}

