#include "test_EachMaster.h"

#define THE_MASTER	CprStraightMaster
//g++ -std=c++11 CprStraightMaster.cpp CprEachMaster.h CprCollection.cpp CprCollection.h CprHand.cpp CprHand.h CprCard.cpp CprCard.h test_Straight.cpp test_EachMaster.h 
int main() {
	CprEachMasterTest<THE_MASTER> mtest;
	mtest.run();	
}

/*
### 0.in ###
0
7s 6h 5s 4s 3s
Ks Qh Js 10s 9s
7d 8s 9h

### 0.out ###
1 1 0
0


### 1.in ###
1
Qc 4c 5c 6c 8c 4d 7d 9d 4h Kh Ah 2d 3d

### 1.out ###
1
5c 6c 7d 8c 9d 
*/

