//Md. Asif Hossain 1532845
//Md. Hasibur rahman 1424635
//ATIF AHNAF CHOWDHURY 1518335
//SHEIKH RIFATH RIAZ BIKU 1521147
//SAYED MUHSIN UDDIN 1413693

//CSC 1100 section 2 
// Some added feature. Modified project

#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<fstream>
using namespace std;

const int wallwide = 20;
const int wallheight = 20;
const int sar = wallwide * wallheight;
int snkar[sar];
int hxpoint;
int hypoint;
int control;
int length = 2;
bool start;

char boardlogic(int);
void snmv(int, int);
void level(); //New added
void fop();  //file operation. New added


char boardlogic(int num)
{
	if (num > 0)
		return 'X';

	switch (num) {
	case -1: return 'O';
	case -2: return '$';
	}
}
//make game board
void gmboard()
{
	for (int x = 0; x < wallwide; ++x) {
		for (int y = 0; y < wallheight; ++y) {
			cout << boardlogic(snkar[x + y * wallwide]);
		}
		
		cout << endl;
	}
}
//food generate function
void getfood() {
	int x = 0;
	int y = 0;
	do {

		x = rand() % (wallwide - 2) + 1;
		y = rand() % (wallheight - 2) + 1;
	} while (snkar[x + y * wallwide] != 0);
	snkar[x + y * wallwide] = -2;
}
// Changes snake direction from input
void controller(char key) {
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

void refresh() {
	system("cls");
}
//snake move logic
void snakeMove() {
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
	for (int i = 0; i < sar; i++) {
		if (snkar[i] > 0) snkar[i]--;
	}
}
void snmv(int x, int y)
{
	int newx = hxpoint + x;
	int newy = hypoint + y;
	if (snkar[newx + newy * wallwide] == -2) {
		length++;
		getfood();
	}
	else if (snkar[newx + newy * wallwide] != 0) {
		start = false;
	}
	hxpoint = newx;
	hypoint = newy;
	snkar[hxpoint + hypoint * wallwide] = length + 1;
}

void maingame()
{
	hxpoint = wallwide / 2;
	hypoint = wallheight / 2;
	snkar[hxpoint + hypoint * wallwide] = 1;
	//walls
	for (int x = 0; x < wallwide; ++x) {
		snkar[x] = -1;
		snkar[x + (wallheight - 1) * wallwide] = -1;
	}
	//walls
	for (int y = 0; y < wallheight; y++) {
		snkar[0 + y * wallwide] = -1;
		snkar[(wallwide - 1) + y * wallwide] = -1;
	}
	getfood();
}

void gamerun()
{
	maingame();
	start = true;
	while (start) {
		// If a key is pressed
		if (kbhit()) {
			// Change to direction determined by key pressed
			controller(getch());
		}
		snakeMove();
		refresh();
		gmboard();
		level();
	}

	cout << "\t\t!!!Game over!" << endl << "\t\tYour score is: " << length;
	cin.ignore();
}

//New adding file operation... this will print the result in txt
void fop()
{
	ofstream file;
	file.open("Score details.txt");
	file << "Your score is : " << length << endl;
	file.close();
}
// New added level.. Not included in main report
void level()
{
	if (length >= 2 && length<6)
	{
		_sleep(500);
		cout << "\n\nYou are at Level 1\n\n";
	}
	else if (length >= 6 && length<11)
	{
		_sleep(400);
		cout << "\n\nYou are at Level 2\n\n";
	}
	else if (length >= 11 && length<16)
	{
		_sleep(300);
		cout << "\n\nYou are at Level 3\n\n";
	}
	else if (length >= 16 && length<21)
	{
		_sleep(200);
		cout << "\n\nYou are at Level 4\n\n";
	}
	else
	{
		_sleep(100);
		cout << "\n\nYou are at Level 5\n\n";
	}

}


int main()
{ 
	system("COLOR 20"); //background color and text color
	gamerun();
	fop();
	return 0;
}
