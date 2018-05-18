#include<Windows.h>
#include<fstream>
#include<iomanip>
#include"player.h"
using namespace std;

struct user{//define a struct user
	char name[10];//declare a char as name[10]
	int Hposition;//declare an int as Hposition
	int Cposition;//declare an int as Cposition
	int Hnbown;//declare an int as Hnbown
	int Cnbown;//declare an int as Cnbown
	int Hmoney;//declare an int as Hmoney
	int Cmoney;//declare an int as Cmoney
	board bod;//declare an array of board as bod
};

const char * file = "theguser.dat";
void logup(user *x);
int login(user *x);
void rewrite(user x);

int main(){
	ofstream fout;//declare fout of ofstream
	fout.open(file, ios_base::out | ios_base::app | ios_base::binary);//open the file to write information
	if (!fout.is_open()){//do the loop if the file is not opened, ask user to play the game again
		cout << "There was some error, please restart the game\n";
		Sleep(1000);
		exit(1);
	}
	fout.close();//cloase the file

	user human;//declare an array of user as human
	board inibod;//declare an array of initial board as inibod
	int success;//declare an int as success
	human.Hposition = 0;//declare the value of Hposition as 0
	human.Cposition = 0;//declare the value of Cposition as 0
	human.bod.setprice();//initialize the setprice() function
	human.bod.initialown();//initialize the initialown() function 
	human.Hmoney = 10000;//declare the Hmoney to be 10000
	human.Cmoney = 10000;//declare the Cmoney to be 10000
	human.Hnbown = 0;//declare the Hnbown to be 0
	human.Cnbown = 0;//declare the Cnbown to be 0
	int choose;//declare an int as choose
	for (;;){//do this loop continuously
		system("cls");
		cout << "welcome to the Monopoly Game! \n\nplease choose your operation\n1. create an account\n2. log in if you have an account";//ask user to create or login the account
		cin >> choose;//read player's inputted choose
		switch (choose){
		case 1://if choose is 1, than do the logup function
			logup(&human);
			break;
		case 2://if choose is 2, than assign success to be login
			success = login(&human);
			break;
		default://otherwise tell the player this is invaild input and ask player to input again
			cout << "invalid input! please input again:";
			Sleep(1000);
			system("cls");
			break;
		}
		if ((choose == 1) || (choose == 2 && success == 1)){ break; }
	}
	Sleep(1000);
	string uname;//define a string as unmae
	char *p = human.name;//switch the string to char
	uname = p;
	player HP(human.Hmoney, uname, "human", human.Hposition, human.Hnbown, human.bod);//declare component of player play
	player CP(human.Cmoney, "AI", "computer", human.Cposition, human.Cnbown, human.bod);//declare component of computer play
	human.bod.showboard(human.Hposition, human.Cposition);//declare component of board
	HP.show(HP, CP);//declare component of show function
	for (;;){//do the loop continuously
		HP.refreshboard(CP.getboard());//print the board 
		if (HP.play(HP, CP) == 1){//do the loop if the return value of play function is 1 which means the player choose to continue the game but not quit it
			if (HP.die() == 0){//continue the game if the human player is alive
				CP.refreshboard(HP.getboard());//update the board
				if (CP.AI(HP, CP) == 1){ //if the computer player is still alive, then continue the game, otherwise print AI dead
					Sleep(2000);
					continue; }
				else {
					cout << "AI is dead! you win!";
					break;
				}
			}
			else {//otherwise print player dead
				cout << "sorry, you have dead, you lose! your account will de cleared!";
				break;
			}
		}
		else{//otherwise assign the value of player to the variables in the file for resuming the play
			human.Cmoney = CP.getmoney();//assign the value of getmoney() to Cmoney
			human.Cnbown = CP.getnuown();//assign the value of getnuown() to Cnbown
			human.Cposition = CP.getposition();//assign the value of getposition to Cposition
			human.Hmoney = HP.getmoney();//assign the value of getmoney() to Hmoney
			human.Hnbown = HP.getnuown();//assign the value of getnuown() to Hnbown
			human.Hposition = HP.getposition();//assign the value of getposition() to Hposition
			human.bod = CP.getboard();//assign the value of getboard(£©to bos
			rewrite(human);//do the rewrite function
			return 0;
		}
	}
	human.Cmoney = 0;//clear all the values of the user and rewrite it into the file
	human.Cnbown = 0;//when the user login again, a new game will start.
	human.Cposition = 0;
	human.Hmoney = 10000;
	human.Hnbown = 10000;
	human.Hposition = 0;
	human.bod = inibod;
	rewrite(human);
	return 0;
}




void logup(user *x){
	for (;;){
		user a;//declare a variable of struct user as a
		cout << "please enter your username to log up (NOTE:less than 10 letters):\n";//ask user to enter the username
		cin >> x->name;//read in the input name
		user us;//declare an array of user as us

		ifstream fin;//declare fin of ifstream
		fin.open(file, ios_base::in|ios_base::binary);//open the file for write information in
		if (fin.is_open()){

			while (fin.read((char *)&us, sizeof us) && strcmp(us.name, x->name))//if player name can't be matched, continue the loop, otherwise ask the user to input another name
			{
				continue;
			}
			if (!(strcmp(us.name, x->name))){//if there is an exsisted username in the file, go back to the input step
				printf("this username exists already, please choose another one!\n");
				Sleep(1000);
				continue;
			}
		}
		else {//if fail to open, then tell the player to restart the game
			cout << "There was some error, please restart the game\n";
			Sleep(1000);
			exit(1);//exit this program
		}
		fin.close();//close the file

		ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);// open the file
		if (!fout.is_open()){//if the file can't be opened, then ask player to play again
			cout << "There was some error, please restart the game\n";
			Sleep(1000);
			exit(1);
		}
		a = *x;//assign x to a
		fout.write((char *) &a, sizeof a);//write the information of player into the file
		cout << "creat successfully!\n";
		fout.close();//close the file
		return;
	}
}


int login(user *x){
	cout << "please enter your username to log in (NOTE:less than 10 letters):\n";//ask user to login
	cin >> x->name;//read in the username
	user us;//declare an array of user as us
	ifstream fin;//declare fin of ifstream
	fin.open(file, ios_base::in | ios_base::binary);//open the file to look for data
	if (fin.is_open()){

		while (fin.read((char *)&us, sizeof us) && strcmp(us.name, x->name))//while there is no match, continue the loop
		{
			continue;
		}
		if (!(strcmp(us.name, x->name))){//if there is a match, assign the value to this new play and tell the player login successfully
			x->Cmoney = us.Cmoney;//assign the value money of us to X
			x->Cposition = us.Cposition;//assign the value of Cposition of us to x 
			x->Hmoney = us.Hmoney;//assign the value of Hmoney of us to x
			x->Hposition = us.Hposition;//assign the value of Hposition of us to x
			x->Hnbown = us.Hnbown;//assign the value of Hnbown of us to x
			x->Cnbown = us.Cnbown;//assign the value of Cnbown of us to x
			x->bod = us.bod;//assign the value of bod of us to x
			cout << "log in suceessfully!";
			Sleep(1000);
			fin.close();
			return 1;
		}
		else {
			cout << "the username does not exist! please log up first! ";//otherwise tell the player this name doesn't exist and need to create first
			Sleep(1000);
			fin.close();
			return 0;
		}
	}
	else {
		cout << "There was some error, please restart the game\n";//otherwise tell the player this is a wrong input and restart it
		Sleep(1000);
		exit(1);
	}
}

void rewrite(user x){
	user us;//declare an array of user as us
	streampos sp;//declare sp of streampos
	ifstream fin;//declare fin of ifstream
	fin.open(file, ios_base::in | ios_base::binary);//open the file
	if (fin.is_open()){//if the file is opened, do the loop

		while (fin.read((char *)&us, sizeof us) && strcmp(us.name,x.name))//find whether there is same name, if not found, continue the loop
		{
			continue;
		}
		if (!(strcmp(us.name, x.name))){//if found, assign the value of fin.tellg() to sp
			sp = fin.tellg();
		}
	}
	else {//otherwise print on the screen error and restart the game
		cout << "There was some error, please restart the game\n";
		Sleep(1000);
		exit(1);
	}
	fin.close();//close the file

	ofstream fout(file, ios_base::out | ios_base::binary);//open the file ,if can't be opened, tell the user error and restard
	if (!fout.is_open()){
		cout << "There was some error, please restart the game\n";
		Sleep(1000);
		exit(1);
	}
	fout.seekp(sp);//look for the same variable in the file
	fout.write((char *)&x, sizeof x);//write data into the file
	cout << "creat successfully!\n";//tell the user create successfully
	fout.close();//close the file
}