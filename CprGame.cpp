/****************************************************************************
  FileName   [ CprGame.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprGame member functions ]
****************************************************************************/

#include "CprGame.h"
#include "CprStage.h"
#include "CprStupidAi.h"
#include "CprGreedyAi.h"
#include "CprHumanPlayer.h"
#include <cstdio>
#include "CprHanmoOuJrAi.h"
CprGame::CprGame() {
	cout << endl;
	cout << "****************************" << endl;
	cout << "* Welcome to Chinese Poker *" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

CprGame::~CprGame() {
	for (unsigned i = 0; i < _players.size(); ++i) {
		CprPlayer *p = _players.at(i);
		delete p;
	}
}
void CprGame::Assistant(){
	_players.clear();
	CprPlayer* ai = new CprHanmoOuJrAi();
    ai->setId("HanmoOuJr");
    _players.push_back(ai);

    cout<<"Type in your cardlist:"<<endl;
    for(int i=0;i<13;i++){
    	CprCard c;
    	cin>>c;
    	_players[0]->_collection._cards.push_back(c);
    	_players[0]->_collection._availCards.push_back(c);
		sort((_players[0]->_collection)._cards.begin(), (_players[0]->_collection)._cards.end());
		sort((_players[0]->_collection)._availCards.begin(), (_players[0]->_collection)._availCards.end());
		(_players[0]->_collection).computeACR();
    }
    _players[0]->strategy();
    for(int i=0;i<3;i++){
 		cout<<i+1<<":";
    	_players[0]->_collection._hands[i].print();
    }	
}
void CprGame::Tsetting(){
	string ss[4]={"AI0","AI1","AI2","AI3"};
	CprPlayer* ai = new CprGreedyAi();
    ai->setId("HanmoOuJr");
    _players.push_back(ai);
    CprPlayer* ai1 = new CprGreedyAi();
    ai1->setId(ss[1]);
    _players.push_back(ai1);
    CprPlayer* ai2 = new CprGreedyAi();
    ai2->setId(ss[2]);
    _players.push_back(ai2);
    CprPlayer* ai3 = new CprGreedyAi();
    ai3->setId(ss[3]);
    _players.push_back(ai3);
}
void CprGame::setting() {
	// FIXME: modify AI by your greedy/regular/custom AI
	//const int playerNum = 4;
	string ss[4]={"AI0","AI1","AI2","AI3"};
	for(int i=0;i<=3;i++){
		cout << "Player"<<i<<": Human playing or AI playing? (H/A) \n> ";
        getchar();
		char line[64];
		cin.getline(line, 64);
		char ch = line[0];
		if (ch == 'H' || ch == 'h') {
			cout << "Please type in your id:"<<endl;
			cin.getline(line, 64);
			CprPlayer* human = new CprHumanPlayer();
			human->setId(line);
			_players.push_back(human);
		} else {
			cout<<"Which AI?"<<endl;
			cin.getline(line, 64);
			char ch = line[0];
			if(ch == 'G'|| ch=='g'){
				CprPlayer* ai = new CprGreedyAi();
				ai->setId(ss[i]);
				_players.push_back(ai);
			}
			else if(ch == 'S'|| ch=='s'){
				CprPlayer* ai = new CprStupidAi();
				ai->setId(ss[i]);
				_players.push_back(ai);
			}
			else {
                CprPlayer* ai = new CprHanmoOuJrAi();
				ai->setId("OuJr");
				_players.push_back(ai);
			}
		}
	}


}

void CprGame::start() {
	const int StageNum = 4;
	for (int i = 1; i <= StageNum; ++i) {
		srand(clock());
		CprStage stage(0,_players, i);
		stage.start();
	}
	end();
}
void CprGame::Tstart() {
	int StageNum;
	cout<<"Type in number of games"<<endl;
	cin>>StageNum;
	for (int i = 1; i <= StageNum; ++i) {
		srand(clock());
		CprStage stage(1,_players, i);
		stage.start();
		if(i%100==0)cout<<"Completed "<<i<<" Stages."<<endl;
		if(i==StageNum){
            cout<<endl;
            for(int player=0;player<=3;player++){
                cout<<stage._players[player]->_id<<":scores="<<stage._players[player]->_score<<endl;
            }
            cout<<endl;
            end();
		}
	}

}
void CprGame::end() {
	cout << "Game End." << endl;
	cout << "Press any button to exit.." << endl;
	system("pause");
}
