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
#include "CprHanmoOuJrJrAi.h"
#include <ctime>
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
    clock_t start,stop;
    start=clock();
    _players[0]->strategy();
    stop=clock();
    cout<<"\n";
    for(int i=0;i<3;i++){
 		cout<<i+1<<" ";
    	_players[0]->_collection._hands[i].print();
    }
    cout<<"\nCalculation Time: "<<double(stop -start)/CLOCKS_PER_SEC*1000<<" miliseconds\n"<<endl;
}
void CprGame::Tsetting(){
	string ss[4]={"Greedy(0)","Greedy(1)","Greedy(2)","Greedy(3)"};
	CprPlayer* ai = new CprHanmoOuJrAi();
    ai->setId("HanmoOuJr");
    _players.push_back(ai);
    CprPlayer* ai1 = new CprHanmoOuJrJrAi();
    ai1->setId("HanmoOuJrJr");
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
	string ss[4]={"Greedy(0)","Greedy(1)","Greedy(2)","Greedy(3)"};
	string sss[4]={"Stupid(0)","Stupid(1)","Stupid(2)","Stupid(3)"};
	string hs[4]={"HanmoOuJr(0)","HanmoOuJr(1)","HanmoOuJr(2)","HanmoOuJr(3)"};
	for(int i=0;i<=3;i++){
		cout << "Player"<<i<<": Human playing or AI playing? (H/A) \n> ";
        getchar();
		char line[64];
		cin.getline(line, 64);
		char ch = line[0];
		if (ch == 'H' || ch == 'h') {
			cout << "Please type in your id:"<<endl;
			cin>>line;
			//getchar();
			CprPlayer* human = new CprHumanPlayer();
			human->setId(line);
			_players.push_back(human);
		} else {
			cout<<"Which AI?"<<endl;
			cin>>line;
			//getchar();
			char ch = line[0];
			if(ch == 'G'|| ch=='g'){
				CprPlayer* ai = new CprGreedyAi();
				ai->setId(ss[i]);
				_players.push_back(ai);
			}
			else if(ch == 'S'|| ch=='s'){
				CprPlayer* ai = new CprStupidAi();
				ai->setId(sss[i]);
				_players.push_back(ai);
			}
			else {
                CprPlayer* ai = new CprHanmoOuJrAi();
				ai->setId(hs[i]);
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
	cout<<"Type in number of Stages"<<endl;
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
