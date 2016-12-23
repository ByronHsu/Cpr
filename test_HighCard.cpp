#include "test_EachMaster.h"

#define THE_MASTER	CprHighCardMaster
//g++ -std=c++11 CprHighCardMaster.cpp CprEachMaster.h CprCollection.cpp CprCollection.h CprHand.cpp CprHand.h CprCard.cpp CprCard.h test_HighCard.cpp test_EachMaster.h 
int main() {
	CprEachMasterTest<THE_MASTER> mtest;
	mtest.run();	
}

/*
### 0.in ###
0
Ad Jd 10h 4s 8d
6h 4d 2h Kd Qc
7d 5s Ah

### 0.out ###
1 1 1
1
0

### 1.in ###
1
3c 4c 5c 6c 7c 4d 7d 9d 7h Kh Ah 2d 3d

### 1.out ###
1
Ah Kh 9d 7c 7d 
*/
