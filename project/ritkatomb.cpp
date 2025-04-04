#include <iostream>
#include "ritkatomb.h"

using namespace std;

ritkatomb::ritkatomb() //alapertelmezett konstruktor
{
	n = 0;
	m = 0;
	size = 0;
	x = new int[0] {};
	y = new int[0] {};
	ertek = new int[0] {};
}
ritkatomb::ritkatomb(int _n, int _m)	//konstruktor
{
	n = _n;
	m = _m;
	size = 0;
	x = new int[0] {};
	y = new int[0] {};
	ertek = new int[0] {};
}
ritkatomb::~ritkatomb()		//desturktor
{
	delete[]x;
	delete[]y;
	delete[]ertek;
}
int ritkatomb::getn() const		//matrix sorainak szamanak elerese
{
	return n;
}
int ritkatomb::getm() const		//matrix oszlopainak szamanak elerese
{
	return m;
}
int ritkatomb::lenght() const	//ritkatomb hosszanak elerese
{
	return size;
}
int ritkatomb::getertek(int a,int b) const	//matrix a,b koordinataju elemenek ertekenek elerese
 {
	for (int i = 0; i < size; i++)
	{
		if (x[i] == a && y[i] == b)
		{
			return ertek[i];
		}
	 }
	return 0;
 }
void ritkatomb::elemtorlese(int a, int b)		//kiveszi az a,b koordonataju elemet
{
	int* tempx, * tempy, * tempertek;
	tempx = new int[size - 1];
	tempy = new int[size - 1];
	tempertek = new int[size - 1];
	for (int i = 0; i < size-1; i++)
	{
		if (x[i] == a && y[i] == b)
		{
			
			tempx[i] = x[size - 1];
			tempy[i] = y[size - 1];
			tempertek[i] = ertek[size - 1];
			
		}
		else {
			tempx[i] = x[i];
			tempy[i] = y[i];
			tempertek[i] = ertek[i];
		}
	}
	delete[]x;
	delete[]y;
	delete[]ertek;
	x = tempx;
	y = tempy;
	ertek = tempertek;
	size--;
	return;
}
void ritkatomb::modosit(int a,int b, int ujertek)		//ertekvaltoztatasa;
{
	for (int i = 0; i < size; i++)
	{
		if (x[i] == a && y[i] == b)
		{
			if (ujertek != 0)
			{
				ertek[i] = ujertek;
			}
			else
			{
				elemtorlese(a, b);
			}
			return;
		}
	}
	int* tempx, * tempy, * tempertek;
	tempx = new int[size + 1];
	tempy = new int[size + 1];
	tempertek = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		tempx[i] = x[i];
		tempy[i] = y[i];
		tempertek[i] = ertek[i];
	}
	delete[]x;
	delete[]y;
	delete[]ertek;
	x = tempx;
	y = tempy;
	ertek = tempertek;
	x[size] = a;
	y[size] = b;
	ertek[size] = ujertek;
	size++;
}

ritkatomb::ritkatomb(const ritkatomb& a)	//masolo fuggveny
{
	n = a.getn();
	m = a.getm();
	for (int i = 0; i < a.lenght(); i++)
	{
		modosit(a.x[i], a.y[i], a.ertek[i]);
	}
}

void ritkatomb::print()	//kiiratja a tomb alapjan a matrixot 0sokall az ures pozicikoba
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << getertek(i, j) << " ";
				
		}
		cout << "\n";
	}
	fflush(stdout);
}