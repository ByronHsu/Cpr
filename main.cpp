/****************************************************************************
  FileName   [ main.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ main of Chinese Poker Game ]
****************************************************************************/
/*
g++ -std=c++11 CprAiPlayer.cpp            CprFlushMaster.cpp         CprHandMaster.cpp          CprStage.cpp CprAiPlayer.h   CprFourOfAKindMaster.cpp   CprHandMaster.h            CprStage.h CprCard.cpp                CprFullHouseMaster.cpp     CprHandType.h              CprStraightFlushMaster.cpp CprCard.h                  CprGame.cpp                CprHighCardMaster.cpp      CprStraightMaster.cpp CprCollection.cpp          CprGame.h                  CprHumanPlayer.cpp         CprStupidAi.cpp CprCollection.h            CprGreedyAi.cpp            CprHumanPlayer.h           CprStupidAi.h CprDealer.h                CprGreedyAi.h              CprOnePairMaster.cpp       CprThreeOfAKindMaster.cpp CprDef.h                   CprHand.cpp                CprPlayer.cpp              CprTwoPairMaster.cpp CprEachMaster.h            CprHand.h                  CprPlayer.h                main.cpp
*/
#include "CprDef.h"
#include "CprGame.h"
using namespace std;

int main() {
	// FIXME: put your group id here
	const int GroupID = 0;
	cout << "This is group " << GroupID << "'s program." << endl;

	int seed = (unsigned)time(0);
	cout << "Using seed " << seed << ".." << endl;
 	srand(seed);
 	int GameMode;
 	cout << "Choose Game Mode:" <<endl;
 	cout << "1 : Custom"<<endl;
	cout << "2 : Test"<<endl;
	cout << "3 : Ai Assistant"<<endl;
    //1 custom 2 test 3
    cin>>GameMode;
	CprGame game;
    if(GameMode==1){
        game.setting();
        game.start();
    }
    if(GameMode==2){
        game.Tsetting();
        game.Tstart();
    }
    /*
    if(GameMode==2){
        game.Asetting();
    }*/

}
