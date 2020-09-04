#include<iostream>
#include<conio.h>
using namespace std;
const int wallwide = 20;
const int wallheight = 20;
const int sar = wallwide * wallheight;
int snkar[sar];//snake array
int hxpoint;
int hypoint;
int control;
void snmv(int, int);
int length = 2;
// game running boolean statement
bool start;
//drawing wall and snake
char boardlogic(int num)
{
	if (num > 0)
		return 'X';
	switch (num) {
		//wall
	case -1: return 'O';
		//food
	case -2: return '$';
	}
}
//make game board
void gmboard()
{
	for (int x = 0; x < wallwide; ++x) {
		for (int y = 0; y < wallheight; ++y) {
			// Prints the value at current x,y location
			cout << boardlogic(snkar[x + y * wallwide]);
		}
		cout << endl;
	}
}
void getfood() //food making function
{
	int x = 0;
	int y = 0;
	do {
		x = rand() % (wallwide - 2) + 1;
		y = rand() % (wallheight - 2) + 1;
	} while (snkar[x + y * wallwide] != 0);
	snkar[x + y * wallwide] = -2;
}
void controller(char key) //keyboard input a,s,d,w
{
	switch (key) {
	case 'w':
		if (control != 2) 
			control = 0;
		break;
	case 'd':
		if (control != 3) 
			control = 1;
		break;
	case 's':
		if (control != 4)
			control = 2;
		break;
	case 'a':
		if (control != 5) 
			control = 3;
		break;
	}
}
void refresh() //refresh the console area after every loop 
{
	system("cls");
}
void snakeMove() 
{
	// snake direction
	switch (control) {
	case 0: snmv(-1, 0);
		break;
	case 1: snmv(0, 1);
		break;
	case 2: snmv(1, 0);
		break;
	case 3: snmv(0, -1);
		break;
	}
	// reduce snake size when it turns to new location.
	for (int i = 0; i < sar; i++) {
		if (snkar[i] > 0) snkar[i]--;
	}
}
void snmv(int x, int y) 
{
	// New head position after eationg target
	int newx = hxpoint + x;
	int newy = hypoint + y;
	if (snkar[newx + newy * wallwide] == -2) {
		// increase length of snake
		length++;
		// After eating the target new food
		getfood();
	}
	// Check location is free
	else if (snkar[newx + newy * wallwide] != 0) {
		start = false;
	}
// Move head to new location
	hxpoint = newx;
	hypoint = newy;
	snkar[hxpoint + hypoint * wallwide] = length + 1;
}
void maingame()
{
	// Initial snake head position
	hxpoint = wallwide / 2;
	hypoint = wallheight / 2;
	snkar[hxpoint + hypoint * wallwide] = 1;
	// up and down wall
	for (int x = 0; x < wallwide; ++x) {
		snkar[x] = -1;
		snkar[x + (wallheight - 1) * wallwide] = -1;
	}
	// left and right wall
	for (int y = 0; y < wallheight; y++) {
		snkar[0 + y * wallwide] = -1;
		snkar[(wallwide - 1) + y * wallwide] = -1;
	}
	getfood();
}
int main()
{
	
	maingame();
	start = true;
	while (start) {
		// key is pressed
		if (kbhit()) {
			// Change direction by keyboard
			controller(getch());
		}
		snakeMove();
		refresh();
		gmboard();
		_sleep(200);
	}
	// Game over and score
	cout << "\n\n\t\t!!!Game over!" << endl << "\t\tYour score is: " << length;
	cin.ignore();
	return 0;
}