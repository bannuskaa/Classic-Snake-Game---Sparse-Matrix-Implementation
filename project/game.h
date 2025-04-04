#ifndef GAME_H_INCLUDED
#define	GAME_H_INCLUDED

struct pont
{
	int x = 0;
	int y = 0;
};
struct snake
{
	pont fej;
	pont food;
	pont tail;
	ritkatomb test;

	snake(int n, int m) : test(n, m) {} // konstruktor
};

void Updatescore(int, int);
void GameModes(int&);
void Alapmenu(int&);
void ScoreBoard();
void init();
void setColor(short);
void jatek(const int,int,int,int,bool);
void printboard(snake&, const int);
void move(int, snake&);
bool check(snake&);
bool checknowalls(snake&);

#endif