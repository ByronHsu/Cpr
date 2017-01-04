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

void CprGame::setting() {
	// FIXME: modify AI by your greedy/regular/custom AI
	const int playerNum = 4;
	/*
	if (playerNum >= 4) {
		CprPlayer* ai = new CprGreedyAi();
		ai->setId("AI3");
		_players.push_back(ai);
	}
	if (playerNum >= 3) {
		CprPlayer* ai = new CprGreedyAi();
		ai->setId("AI2");
		_players.push_back(ai);
	}
	CprPlayer* ai = new CprGreedyAi();
	ai->setId("AI1");
	_players.push_back(ai);
	*/
	string ss[4]={"AI0","AI1","AI2","AI3"};
	for(int i=0;i<=3;i++){
		cout << "Player"<<i<<": Human playing or AI playing? (H/A) \n> ";
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
			if(ch == 'S'|| ch=='s'){
				CprPlayer* ai = new CprStupidAi();
				ai->setId(ss[i]);
				_players.push_back(ai);
			}
		}
	}
}

void CprGame::start() {
	const int StageNum = 4;
	for (int i = 1; i <= StageNum; ++i) {
		srand(clock());
		CprStage stage(_players, i);
		stage.start();
	}
	end();
}

void CprGame::end() {
	cout << "Game End." << endl;
	cout << "Press any button to exit.." << endl;
	system("pause");
}