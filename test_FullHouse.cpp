#include "test_EachMaster.h"

#define THE_MASTER	CprFullHouseMaster
//g++ -std=c++11 CprFullHouseMaster.cpp CprEachMaster.h CprCollection.cpp CprCollection.h CprHand.cpp CprHand.h CprCard.cpp CprCard.h test_FULLHouse.cpp
int main() {
	CprEachMasterTest<THE_MASTER> mtest;
	mtest.run();	
}

/*
### 0.in ###
0
8s 8d 4h 4s 8d
6h 6d 7h 7d 6c
7d 7s 7h

### 0.out ###
1 1 0
1


### 1.in ###
1
3c 4c 5c 6c 7c 4d 7d 9d 7h Kh Ah 2d 3d

### 1.out ###
1
7c 7d 7h 4c 4d
*/
