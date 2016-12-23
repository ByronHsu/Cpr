#include "test_EachMaster.h"

#define THE_MASTER	CprStraightFlushMaster
//g++ -std=c++11 CprStraightFlushMaster.cpp CprEachMaster.h CprCollection.cpp CprCollection.h CprHand.cpp CprHand.h CprCard.cpp CprCard.h test_StraightFlush.cpp test_EachMaster.h 
int main() {
	CprEachMasterTest<THE_MASTER> mtest;
	mtest.run();	
}
//c d h s
/*
### 0.in ###
0
7s 6s 5s 4s 3s
Ks Qs Js 10s 9s
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

