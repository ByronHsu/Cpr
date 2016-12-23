#include "test_HandMaster.h"
using namespace std;

int main() {
	CprHandMasterTest mtest;
	mtest.run();	
}

/*
### 0.in ###
0
2h 2d 2s 3h 3s
3d 4h 5s 6d 7d
9d As Ah

### 0.out ###
FullHouse
Straight
OnePair
1
1

### 1.in ###
1
3c 4c 5c 6s 7c 4d 7d 9d 7h Kh Ah 2d 3d

### 1.out ###
7c 7d 7h 4c 4d
*/
