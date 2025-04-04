#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "ritkatomb.h"
#include "game.h"


using namespace std;
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

void Updatescore(int mode, int score) //Scoreboardot frissiti
{
	ifstream f("scores.txt");
	int board[6];
	for (int i = 1; i <= 5; i++)
	{
		f >> board[i];
	}
	if (board[mode] < score)
	{
		cout << endl;
		cout << "Congratulations!! New high score!!" << endl;
		board[mode] = score;
	}
	f.close();
	ofstream g("scores.txt");
	for (int i = 1; i <= 5; i++)
	{
		g << board[i] << endl;
	}
	f.close();
}
void GameModes(int& k)//Game mode menu
{
	system("cls");
	setColor(13);
	cout << "GAME MODES:" << endl;
	cout << endl;
	cout << "1.Easy Mode" << endl;
	cout << "2.Medium Mode" << endl;
	cout << "3.Hard Mode" << endl;
	cout << "4.Extreme Mode" << endl;
	cout << "5.No Wall Mode" << endl;
	cout << "6.Custom Mode" << endl;
	setColor(5);
	cout << endl;
	cout << "(EXIT game modes by pressing ENTER)" << endl;
	setColor(7);
	while (!_kbhit()) {}
	k = _getch();
	switch (k)
	{
	case '1':
	{
		jatek(300, 20, 20,1,true);
		break;
	}
	case '2':
	{
		jatek(200, 20, 20,2,true);
		break;
	}
	case '3':
	{
		jatek(100, 20, 20, 3,true);
		break;
	}
	case '4':
	{
		jatek(50, 20, 20, 4,true);
		break;
	}
	case '5':
	{
		jatek(100, 20, 20, 5,false);
		break;
	}
	case '6':
	{
		int wall, speed, size;
		system("cls");
		cout << "Costum Mode: " << endl;
		cout << "1.No Walls or 2.With Walls" << endl;
		while (!_kbhit())
		{
		}
		wall = _getch()-'0';
		system("cls");
		cout << "Costum Mode: " << endl;
		cout << "Speed 1-5?" << endl;
		while (!_kbhit())
		{
		}
		speed = _getch() - '0';
		system("cls");
		cout << "Costum Mode: " << endl;
		cout << "Size 1-3?" << endl;
		while (!_kbhit())
		{
		}
		size = _getch() - '0';
		speed = (6 - speed) * 50;
		size = size * 10;
		system("cls");
		cout << "press ENTER to START" << endl;
		int k = 0;
		while (k != ENTER)
		{
			k = _getch();
		}

		wall--;
		jatek(speed, size, size,6,wall);

		break;
	}
	}


}
void ScoreBoard() //kiirja a kulonbozo jatekmodokban eleret legmagasabb pontszamot
{
	system("cls");
	ifstream f("scores.txt");
	int score;
	setColor(13);
	cout << "HIGHEST SCORES: " << endl;
	cout << endl;
	f >> score;
	cout << "Easy Mode: " << score << endl;
	f >> score;
	cout << "Medium Mode: " << score << endl;
	f >> score;
	cout << "Hard Mode: " << score << endl;
	f >> score;
	cout << "Extreme Mode: " << score << endl;
	f >> score;
	cout << "No Walls Mode: " << score << endl;
	cout << endl;
	setColor(5);
	cout << "(EXIT scoreboard by pressing any key)" << endl;
	setColor(7);
	f.close();
	while (!_kbhit()) {}
	_getch();
}
void Alapmenu(int& k)// kiirja a menut, elerheto belole a jatekmodok es a legmagasabb pontszamok listaja
{
	system("cls");
	cout << "   SNAKE" << endl;
	cout << endl;
	cout << "1. Game Modes" << endl;
	cout << "2. Highest Scores" << endl;
	cout << endl;
	cout << "(EXIT by pressing ENTER)" << endl;

	while (!_kbhit())
	{
	}
	k = _getch();
	switch (k)
	{
	case '1':
	{
		int t;
		do {
			GameModes(t);
		} while (t != ENTER);
		break;
	}
	case '2':
	{
		ScoreBoard();
		break;
	}
	}
}
void init()// kulonboyo rendszerbeallitasok a helyes mukodes erdekeben
{
	setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
	ios_base::sync_with_stdio(false);
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false; // Hide the cursor
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	srand(time(NULL));
}
void setColor(short colour)// kiirt karakterek szinet valtoztatja
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colour);
}
void newfood(snake &kigyo)//uj almat general ha tud
{
	bool found = false;
	pont newfood;
	if (kigyo.test.lenght() < kigyo.test.getn() * kigyo.test.getm()) {
		while (!found)
		{
			newfood.x = rand() % kigyo.test.getn();
			newfood.y = rand() % kigyo.test.getm();
			found = true;
			if (kigyo.test.getertek(newfood.x, newfood.y) != 0)
			{
				found = false;
			}
		}
	}
	kigyo.food = newfood;
}
void printboard(snake &kigyo, const int wall)//a jatekra szemelyreszabott kiiratas
{
	cout << "\033[0;0H";
	int n = kigyo.test.getn();
	int m = kigyo.test.getm();
	for (int i = 0; i <=m; i++)
	{
		cout  << (char)wall<< (char)wall;
	}
	cout << (char)wall;
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << (char)wall << (char)wall;
		for (int j = 0; j < m; j++)
		{
				
					if (kigyo.test.getertek(i,j)!=0)
					{
						if (j != 0)cout << " ";
						if (kigyo.fej.x==i && kigyo.fej.y==j)
						{
							cout << "@";
						}
						else
						{
							cout << ".";
						}
					}
					else
					{
						if (i == kigyo.food.x && j == kigyo.food.y)
						{
							if (j != 0)
							{
								cout << " ";
							}
							cout << "*";
						}
						else
						{
							if (j != 0)
							{
								cout << " ";
							}
							cout << " ";
						}
					}
		}
		cout<< (char)wall << (char)wall;
		cout << "\n";
	}
	for (int i = 0; i <= m ; i++)
	{
		cout << (char)wall << (char)wall;
	}
	cout << (char)wall;
	
	fflush(stdout);
}
void move(int dir, snake& kigyo, bool& el,bool walls)// modositja a ritka tombot a kigyo mozgasanak megfeleloen egyben azt is ellenorizve hogy almat talalte
{
	el = false;
	switch (dir)
	{
	case RIGHT:
	{
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 1);
		kigyo.fej.y++;
		if (walls)
		{
			if (check(kigyo))
			{
				el = true;
			}
		}
		else
		{
			if (checknowalls(kigyo))
			{
				el = true;
			}
		}
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 1);

		if (kigyo.food.x == kigyo.fej.x && kigyo.food.y == kigyo.fej.y)
		{
			newfood(kigyo);
		}
		else
		{
			int irany = kigyo.test.getertek(kigyo.tail.x, kigyo.tail.y);
			kigyo.test.modosit(kigyo.tail.x, kigyo.tail.y, 0);
			switch (irany)
			{
			case 1:
			{
				if (!walls && kigyo.tail.y == kigyo.test.getm() - 1)
				{
					kigyo.tail.y = 0;
				}
				else
				{
					kigyo.tail.y++;
				}
				break;
			}
			case 2:
			{
				if (!walls && kigyo.tail.x == kigyo.test.getn() - 1)
				{
					kigyo.tail.x = 0;
				}
				else
				{
					kigyo.tail.x++;
				}
				break;
			}
			case 3:
			{
				if (!walls && kigyo.tail.y == 0)
				{
					kigyo.tail.y = kigyo.test.getm() - 1;
				}
				else {
					kigyo.tail.y--;
				}
				break;
			}
			case 4:
			{
				if (!walls && kigyo.tail.x == 0)
				{
					kigyo.tail.x = kigyo.test.getn() - 1;
				}
				else
				{
					kigyo.tail.x--;
				}
				break;
			}
			}
		}
		break;
	}
	case DOWN:
	{
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 2);
		kigyo.fej.x++;
		if (walls)
		{
			if (check(kigyo))
			{
				el = true;
			}
		}
		else
		{
			if (checknowalls(kigyo))
			{
				el = true;
			}
		}
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 2);

		if (kigyo.food.x == kigyo.fej.x && kigyo.food.y == kigyo.fej.y)
		{
			newfood(kigyo);
		}
		else {
			int irany = kigyo.test.getertek(kigyo.tail.x, kigyo.tail.y);
			kigyo.test.modosit(kigyo.tail.x, kigyo.tail.y, 0);
			switch (irany)
			{
			case 1:
			{
				if (!walls && kigyo.tail.y == kigyo.test.getm() - 1)
				{
					kigyo.tail.y = 0;
				}
				else
				{
					kigyo.tail.y++;
				}
				break;
			}
			case 2:
			{
				if (!walls && kigyo.tail.x == kigyo.test.getn() - 1)
				{
					kigyo.tail.x = 0;
				}
				else
				{
					kigyo.tail.x++;
				}
				break;
			}
			case 3:
			{
				if (!walls && kigyo.tail.y == 0)
				{
					kigyo.tail.y = kigyo.test.getm() - 1;
				}
				else {
					kigyo.tail.y--;
				}
				break;
			}
			case 4:
			{
				if (!walls && kigyo.tail.x == 0)
				{
					kigyo.tail.x = kigyo.test.getn() - 1;
				}
				else
				{
					kigyo.tail.x--;
				}
				break;
			}
			}
		}
		break;
	}
	case LEFT:
	{
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 3);
		kigyo.fej.y--;
		if (walls)
		{
			if (check(kigyo))
			{
				el = true;
			}
		}
		else
		{
			if (checknowalls(kigyo))
			{
				el = true;
			}
		}
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 3);

		if (kigyo.food.x == kigyo.fej.x && kigyo.food.y == kigyo.fej.y)
		{
			newfood(kigyo);
		}
		else {
			int irany = kigyo.test.getertek(kigyo.tail.x, kigyo.tail.y);
			kigyo.test.modosit(kigyo.tail.x, kigyo.tail.y, 0);
			switch (irany)
			{
			case 1:
			{
				if (!walls && kigyo.tail.y == kigyo.test.getm() - 1)
				{
					kigyo.tail.y = 0;
				}
				else
				{
					kigyo.tail.y++;
				}
				break;
			}
			case 2:
			{
				if (!walls && kigyo.tail.x == kigyo.test.getn() - 1)
				{
					kigyo.tail.x = 0;
				}
				else
				{
					kigyo.tail.x++;
				}
				break;
			}
			case 3:
			{
				if (!walls && kigyo.tail.y == 0)
				{
					kigyo.tail.y = kigyo.test.getm() - 1;
				}
				else {
					kigyo.tail.y--;
				}
				break;
			}
			case 4:
			{
				if (!walls && kigyo.tail.x == 0 )
				{
					kigyo.tail.x = kigyo.test.getn()-1;
				}
				else
				{
					kigyo.tail.x--;
				}
				break;
			}
			}
		}
		break;
	}
	case UP:
	{
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 4);
		kigyo.fej.x--;
		if (walls)
		{
			if (check(kigyo))
			{
				el = true;
			}
		}
		else
		{
			if (checknowalls(kigyo))
			{
				el = true;
			}
		}
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 4);

		if (kigyo.food.x == kigyo.fej.x && kigyo.food.y == kigyo.fej.y)
		{
			newfood(kigyo);
		}
		else
		{
			int irany = kigyo.test.getertek(kigyo.tail.x, kigyo.tail.y);
			kigyo.test.modosit(kigyo.tail.x, kigyo.tail.y, 0);
			switch (irany)
			{
			case 1:
			{
				if (!walls && kigyo.tail.y == kigyo.test.getm() - 1)
				{
					kigyo.tail.y = 0;
				}
				else
				{
					kigyo.tail.y++;
				}
				break;
			}
			case 2:
			{
				if (!walls && kigyo.tail.x == kigyo.test.getn() - 1)
				{
					kigyo.tail.x = 0;
				}
				else
				{
					kigyo.tail.x++;
				}
				break;
			}
			case 3:
			{
				if (!walls && kigyo.tail.y == 0)
				{
					kigyo.tail.y = kigyo.test.getm() - 1;
				}
				else {
					kigyo.tail.y--;
				}
				break;
			}
			case 4:
			{
				if (!walls && kigyo.tail.x == 0)
				{
					kigyo.tail.x = kigyo.test.getn() - 1;
				}
				else
				{
					kigyo.tail.x--;
				}
				break;
			}
			}
		}
		break;
	}
	}
}
bool checknowalls(snake &kigyo)// fal nelkuli modba leellenerozi hogy volte utkozes es ha falnak megy modositja hogy a szemkozti falbol jojjon ki
{
	int x1 = kigyo.fej.x, y1 = kigyo.fej.y;
	if (kigyo.test.getertek(x1, y1) != 0)
	{
		return false;
	}
	if (x1 >= kigyo.test.getn())
	{
		kigyo.test.modosit(x1,y1, 0);
		kigyo.fej.x = 0;
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y,2);

	} 
	if (x1 < 0)
	{
		kigyo.test.modosit(x1, y1, 0);
		kigyo.fej.x = kigyo.test.getn()-1;
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 4);

	}
	if (y1 >= kigyo.test.getm())
	{
		kigyo.test.modosit(x1, y1, 0);
		kigyo.fej.y=0;
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 1);

	} 
	if (y1 < 0)
	{
		kigyo.test.modosit(x1, y1, 0);
		kigyo.fej.y = kigyo.test.getm()-1;
		kigyo.test.modosit(kigyo.fej.x, kigyo.fej.y, 3);

	}
	return true;
}
bool check(snake& kigyo)//ellenorzi hogy volte utkozes es az "el" logikai valtozon keresztul jelzi a jatek fuggvenynek ezt
{
	int x1 = kigyo.fej.x, y1 = kigyo.fej.y;
	if (kigyo.test.getertek(x1, y1) != 0)
	{
		return false;
	}
	if (x1 >= kigyo.test.getn() || x1 < 0 || y1 >= kigyo.test.getm() || y1 < 0)
	{
		return false;
	}
	return true;
}
void jatek(const int speed,int n,int m,int mode,bool walls)//fo jatek fuggveny ami meghivja a tobbi fuggvenyt
{
	snake kigyo(n,m);
	kigyo.test.modosit(0, 0, 1);
	kigyo.test.modosit(0, 1, 1);
	newfood(kigyo);
	kigyo.fej.x = 0;
	kigyo.fej.y = 1;
	kigyo.tail.x = 0;
	kigyo.tail.y = 0;
	int dir = RIGHT;
	bool el = true;
	while (el) 
	{
		if(kigyo.test.lenght()>=kigyo.test.getn()*kigyo.test.getm())
		{
			system("cls");
			cout << "Congratulations!! You have won the game!!" << endl;
			break;
		}
		move(dir, kigyo,el,walls);
		if (el) {
			char ch;
			bool hit=false;
			while (!hit && _kbhit()) {
				ch = _getch();
				switch (ch)
				{
				case UP:
				{
					if (!hit && dir != DOWN)
					{
						dir = UP;
						hit = true;
					}
					break;
				}
				case DOWN:
				{
					if (!hit && dir != UP)
					{
						dir = DOWN;
						hit = true;
					}
					break;
				}
				case LEFT:
				{
					if (!hit && dir != RIGHT) {
						dir = LEFT;
						hit = true;
					}
					break;
				}
				case RIGHT:
				{
					if (!hit && dir != LEFT)
					{
						dir = RIGHT;
						hit = true;
					}
					break;
				}
				}
			}
			if (walls)
			{
				printboard(kigyo, 219);
			}
			else
			{
				printboard(kigyo, 176);
			}
			this_thread::sleep_for(std::chrono::milliseconds(speed));
		
			
			}
		}
		
	if ( kigyo.test.lenght() <= kigyo.test.getn() * kigyo.test.getm())
	{
		system("cls");
	}
	cout << "GAME OVER"<<endl;
	cout << endl;
	cout << "SCORE= ";
	setColor(3);
	cout << kigyo.test.lenght() - 2 << endl;
	
	if (mode != 6)
	{
		Updatescore(mode, kigyo.test.lenght() - 2);
	}
	setColor(7);
	int k = 1;
	cout << endl;
	cout << "(exit by pressing enter)" << endl;
	while (k != ENTER)
	{
		k = _getch();
	}

}

