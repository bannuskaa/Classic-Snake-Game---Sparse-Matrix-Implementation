#include <iostream>
#include "ritkatomb.h""
#include "game.h"

using namespace std;

int main()
{
	init();
	int k=0;
	do {
		Alapmenu(k);
	} while (k !=13);
}