#include "test_EachMaster.h"

#define THE_MASTER	CprThreeOfAKindMaster
//g++ -std=c++11 CprThreeOfAKindMaster.cpp CprEachMaster.h CprCollection.cpp CprCollection.h CprHand.cpp CprHand.h CprCard.cpp CprCard.h test_ThreeOfAKind.cpp test_EachMaster.h 
int main() {
	CprEachMasterTest<THE_MASTER> mtest;
	mtest.run();	
}

/*
### 0.in ###
0
8s 8d 3h 4s 2d
6h 6d 5h 7d 3c
7d 7s 4c

### 0.out ###
1 1 1
1
0

### 1.in ###
1
3c 4c 5c 6c 7c 4d 7d 9d 10h Kh Ah 2d 3d

### 1.out ###
1
7c 7d Ah Kh 10h
*/
