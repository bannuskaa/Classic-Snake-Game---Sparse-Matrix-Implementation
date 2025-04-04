#ifndef RITKATOMB_H_INCLUDED
#define	RITKATOMB_H_INCLUDED

using namespace std;

class ritkatomb
{
private:
	int n;	//matrix sorainak szama
	int m;	//matrix oszlopainak szama
	int size;	//ritka tomb elemeinek szama
	int* x;		//sor tomb
	int* y;		//oszlop tomb
	int* ertek;		//ertek tomb

public:

	~ritkatomb();
	ritkatomb();
	ritkatomb(int, int);
	int getn()const;
	int getm()const;
	int lenght()const;
	int getertek(int, int)const;
	void modosit(int, int,int);
	void elemtorlese(int,int);
	ritkatomb(const ritkatomb&);
	void print();
};

#endif